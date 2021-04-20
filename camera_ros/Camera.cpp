#include "Camera.h"


namespace Camera
{

CameraBase::CameraBase()
: frame_buffer(4)
{
    if (!openVideoCapture())
    {
        throw std::runtime_error("Error: Could not open camera!\n");
    }

    grabOn.store(true);
    startUpdateThread();
}

CameraBase::~CameraBase()
{
    grabOn.store(false);
    if (frame_read_thread.joinable())
        frame_read_thread.join();
    video_capture.release();
}

bool CameraBase::openVideoCapture()
{
    std::cout << "Attempting to connect to VideoCapture...\n";
    if (video_capture.open(0, cv::CAP_GSTREAMER))
    {
        video_capture.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
        video_capture.set(cv::CAP_PROP_FRAME_HEIGHT, 400);
        // get one frame to find details
        video_capture >> last_frame;
        frame_width = last_frame.cols;
        frame_height = last_frame.rows;
        std::cout << "VideoCapture opened successfully. Mat type: " << Utils::getCvMatType(last_frame.type()) << ", Size: " << last_frame.size() << std::endl;

        return true;
    }
    else
    {
        return false;
    }
}

void CameraBase::update()
{
    fps.init();
    cv::Mat temp;
    int64_t temp_timestamp;
    while (grabOn.load() == true)
    {
        temp_timestamp = Utils::getMsSinceEpoch();
        video_capture >> temp;
        {
            std::lock_guard<std::mutex> scopeLock(frame_read_lock);
            if (!frame_buffer.try_push(std::make_pair(temp, temp_timestamp)))
            {
                frame_buffer.pop(); // TODO: hmm... this is a terrible solution
            }
        }
        fps.tick(false);
    }
}

void CameraBase::startUpdateThread()
{
    frame_read_thread = std::thread(&CameraBase::update, this);
}

int64_t CameraBase::read(cv::Mat& frame)
{
    std::pair<cv::Mat, int64_t> temp;

    int n;
    while (frame_buffer.empty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        n++;
        if ((n % 10) == 0 && n > 1) std::cout << "Frame buffer empty, waiting for image...\n";
    }

    {
        std::lock_guard<std::mutex> scopeLock(frame_read_lock); // todo: use a proper circular buffer
        temp = (*frame_buffer.front());
        frame = temp.first.clone();
        frame_buffer.pop();
    }
    return temp.second;
}

} // namespace Camera