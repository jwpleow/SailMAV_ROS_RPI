#!/bin/bash

# source ros
source /opt/ros/melodic/setup.bash

source devel/setup.bash
dir=$(pwd)
roscore &
sleep 2
${dir}/camera_ros/build/camera_publisher & rosrun ros_icm20948_publisher ros_imu_publisher.py &


# set better default gain
sleep 10
v4l2-ctl --set-ctrl=gain=6
sleep 2
v4l2-ctl --set-ctrl=gain=5
wait
