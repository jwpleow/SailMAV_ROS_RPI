#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <chrono>
#include <mutex>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

#include "Utils.h"
#include "thirdparty/SPSCQueue.h"

namespace Camera{

class CameraBase
{
    public:
    CameraBase();
    virtual ~CameraBase();

    int64_t read(cv::Mat& frame); // returns timestamp (ms from epoch) and frame

    protected:
    // opens VideoCapture
    bool openVideoCapture();
    // updates last_frame
    void update();
    // starts update() in a thread
    void startUpdateThread();

    protected:
    Utils::FPSCounter fps;
    int frame_width;
    int frame_height;

    cv::VideoCapture video_capture;
    rigtorp::SPSCQueue<std::pair<cv::Mat, int64_t>> frame_buffer; // pair of image and timestamp in ms (epoch)
    cv::Mat last_frame;
    int64_t last_frame_timestamp; // timestamp in ms
    std::thread frame_read_thread;
    std::mutex frame_read_lock;
    std::atomic<bool> grabOn;
};

} // namespace Camera