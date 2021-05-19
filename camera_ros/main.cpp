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
void publishImage(const image_transport::Publisher& pub, const cv::Mat& image, const std::string& encoding, const ros::Time timestamp)
{
    sensor_msgs::ImagePtr msg;
    std_msgs::Header header;
    header.stamp = timestamp;
    msg = cv_bridge::CvImage(header, encoding, image).toImageMsg();
    pub.publish(msg);
}

int main(int argc, char** argv)
{
    const std::string cam_topic = "/stereo/image";

    ros::init(argc, argv, "camera_publisher");
    ros::NodeHandle nh;
    Camera::CameraBase camera;
    
    image_transport::ImageTransport it(nh);
    image_transport::Publisher image_pub = it.advertise(cam_topic, 1);

    ros::Rate rate(30.0);

    uint32_t seq = 0;
    cv::Mat frame, frame_mono;
    ros::Time timestamp;
    if (ros::ok())
        ROS_INFO("Camera publisher started on %s", cam_topic.c_str());

    while (ros::ok())
    {
        camera.read(frame, timestamp);
        cv::extractChannel(frame, frame_mono, 0);
        publishImage(image_pub, frame_mono.clone(), sensor_msgs::image_encodings::MONO8, timestamp);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
