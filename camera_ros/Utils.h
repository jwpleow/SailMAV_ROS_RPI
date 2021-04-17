#pragma once

#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>


namespace Utils{

    void combineImages(const cv::Mat &left, const cv::Mat &right, cv::Mat &combined);
    
    std::string getCvMatType(int type);

    void printCvMatProperties(const cv::Mat& mat);

    std::string GetDateTime();
    int64_t getMsSinceEpoch();

    /*
    Simple FPSCounter that uses a moving average
    To use, initialise somewhere, and call tick() every frame
    */
    class FPSCounter
    {
    public:
        FPSCounter();
        virtual ~FPSCounter();

        // call init when ready to start measuring
        void init();
        // prints avg_fps_
        void printAvgFps();
        // returns avg_fps_
        float getAvgFps();
        // tick. set print to true to print a message when fps updates
        void tick(bool print = false);

    protected:
        std::chrono::system_clock::time_point start_time_; // start time to count till 1 second

        float avg_fps_ = 10; // average fps so far, initialise with an estimate
        int frames1sec_ = 0; // frames so far in the last second
        int frames_all_ = 0; // total frames seen so far
    };

} // namespace Utils