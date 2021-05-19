#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <atomic>
#include <memory>
#include <chrono>
#include <mutex>

#include "ros/ros.h"
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

    void read(cv::Mat& frame, ros::Time& timestamp); // returns timestamp and frame

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
    rigtorp::SPSCQueue<std::pair<cv::Mat, ros::Time>> frame_buffer; // pair of image and timestamp in ms (epoch)
    cv::Mat last_frame;
    ros::Time last_frame_timestamp;
    std::thread frame_read_thread;
    std::mutex frame_read_lock;
    std::atomic<bool> grabOn;
};

} // namespace Camera