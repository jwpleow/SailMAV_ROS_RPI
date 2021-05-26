#!/bin/bash

# kill all subshells and processes on exit
trap "kill 0" SIGINT

# source ros
source /opt/ros/melodic/setup.bash

# change ip's
roscore_ip=192.168.1.58 # this should be the IP/hostname of the computer running roscore
rpi_ip=192.168.1.70 # assuming we're running this on the raspi
export ROS_MASTER_URI=http://${roscore_ip}:11311
export ROS_HOSTNAME=raspberrypi
export ROS_IP=${rpi_ip}

echo "ROS_MASTER_URI: $ROS_MASTER_URI"
echo "ROS_IP: $ROS_IP"

source devel/setup.bash
dir=$(pwd)
${dir}/camera_ros/build/camera_publisher & rosrun ros_icm20948_publisher ros_imu_publisher.py &

# set better default gain
sleep 10
v4l2-ctl --set-ctrl=gain=4
sleep 2
v4l2-ctl --set-ctrl=gain=3
wait
