#include <chrono>
#include <string>

#include "ros/ros.h"
#include "sensor_msgs/Image.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/point_cloud2_iterator.h"
#include "sensor_msgs/image_encodings.h"
#include "std_msgs/Header.h"
#include "cv_bridge/cv_bridge.h"
#include "image_transport/image_transport.h"

#include "Camera.h"

// compress? https://github.com/jkammerl/compressed_image_transport/blob/master/src/compressed_publisher.cpp
void publishImage(const image_transport::Publisher& pub, const cv::Mat& image, const std::string& encoding, int64_t timestamp)
{
    sensor_msgs::ImagePtr msg;
    std_msgs::Header header;
    header.stamp.sec = timestamp / 1000;
    header.stamp.nsec = (timestamp % 1000) * 1000000;
    msg = cv_bridge::CvImage(header, encoding, image).toImageMsg();
    pub.publish(msg);
}

int main(int argc, char** argv)
{
    std::string capture_string = "v4l2src ! video/x-raw, width=1280, height=400, format=GRAY8 ! videoconvert ! video/x-raw, format=I420 ! appsink";
    Camera::CameraBase camera(capture_string);
    ros::init(argc, argv, "camera_publisher");

    const std::string cam_topic = "/stereo/image";
    ros::NodeHandle nh;

    image_transport::ImageTransport it(nh);
    image_transport::Publisher image_pub = it.advertise(cam_topic, 1);

    ros::Rate rate(30.0);

    uint32_t seq = 0;
    cv::Mat frame, frame_mono;
    int64_t timestamp;
    if (ros::ok())
        ROS_INFO("Camera publisher started on %s", cam_topic.c_str());

    while (ros::ok())
    {
        timestamp = camera.read(frame);
        cv::extractChannel(frame, frame_mono, 0);
        publishImage(image_pub, frame_mono.clone(), sensor_msgs::image_encodings::MONO8, timestamp);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
