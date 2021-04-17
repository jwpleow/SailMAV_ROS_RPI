#!/bin/bash

# source ros
source /opt/ros/melodic/setup.bash

# change ip's
roscore_ip=192.168.1.58 # this should be the IP of the computer running roscore
rpi_ip=$(/bin/hostname -I)
export ROS_MASTER_URI=http://${roscore_ip}:11311
export ROS_IP=${rpi_ip}

echo $ROS_MASTER_URI
echo $ROS_IP

dir=$(pwd)

${dir}/camera_ros/build/camera_publisher & ${dir}/lsm9ds1_rpi_grpc/build/imu_ros