#!/bin/bash


# kill all subshells and processes on exit
trap "kill 0" SIGINT

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
sleep 1
v4l2-ctl --set-ctrl=exposure=620
sleep 1

# actual gain to set
v4l2-ctl --set-ctrl=gain=1
sleep 1
v4l2-ctl --set-ctrl=exposure=400
wait


