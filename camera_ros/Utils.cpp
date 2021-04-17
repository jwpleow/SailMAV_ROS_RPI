#include "Utils.h"
namespace Utils{

    void combineImages(const cv::Mat &left, const cv::Mat &right, cv::Mat &combined)
    {
        cv::hconcat(left, right, combined);
    }
    
    std::string getCvMatType(int type)
    {
        // taken from https://stackoverflow.com/questions/10167534/how-to-find-out-what-type-of-a-mat-object-is-with-mattype-in-opencv
        std::stringstream oss;

        uchar depth = type & CV_MAT_DEPTH_MASK;
        int channels = 1 + (type >> CV_CN_SHIFT);

        switch ( depth ) {
            case CV_8U:  oss << "CV_8U"; break;
            case CV_8S:  oss << "CV_8S"; break;
            case CV_16U: oss << "CV_16U"; break;
            case CV_16S: oss << "CV_16S"; break;
            case CV_32S: oss << "CV_32S"; break;
            case CV_32F: oss << "CV_32F"; break;
            case CV_64F: oss << "CV_64F"; break;
            default:     oss << "Undefined"; break;
        }
        
        oss << "C";
        oss << channels;
    
        return oss.str();
    }
    
    void printCvMatProperties(const cv::Mat& mat)
    {
        double minVal, maxVal;
        cv::minMaxLoc(mat, &minVal, &maxVal);

        cv::Scalar means = cv::mean(mat);

        std::cout << "Dimensions: " << mat.dims << "\n"
                  << "Datatype: " << getCvMatType(mat.type()) << "\n"
                  << "Size: " << mat.size << "\n"
                  << "Number of Elements: " << mat.total() << "\n"
                  << "Max value: " << maxVal << "\n"
                  << "Min value: " << minVal << "\n"
                  << "Means of each channel: " << means << "\n";
    }

    std::string GetDateTime()
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t); // not thread safe!
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }
    
    int64_t getMsSinceEpoch()
    {
        return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    }

    // FPSCounter
    FPSCounter::FPSCounter()
    {
    }

    FPSCounter::~FPSCounter()
    {
    }

    void FPSCounter::init()
    {
        start_time_ = std::chrono::system_clock::now();
    }

    void FPSCounter::printAvgFps()
    {
        std::cout << std::setprecision(2) << std::fixed << "Average fps: " << avg_fps_ << std::endl;
    }

    float FPSCounter::getAvgFps()
    {
        return avg_fps_;
    }

    void FPSCounter::tick(bool print)
    {
        // if past 1 second, reset the start time and calculate the new fps
        if (int millisecond_count = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_time_).count() > 1000)
        {
            start_time_ = std::chrono::system_clock::now();
            avg_fps_ = 0.8f * avg_fps_ + 0.2f * static_cast<float>(frames1sec_) * (1000.f / static_cast<float>(1000 + millisecond_count));
            frames1sec_ = 0;
            if (print)
                std::cout << "FPS: " << avg_fps_ << "\n";
        }
        frames1sec_++;
    }

} // namespace Utils