#!/bin/bash

# source ros
source /opt/ros/melodic/setup.bash

# change ip's
roscore_ip=192.168.1.58 # this should be the IP/hostname of the computer running roscore
rpi_ip=$(/bin/hostname -I) # assuming we're running this on the raspi
export ROS_MASTER_URI=http://${roscore_ip}:11311
export ROS_HOSTNAME=raspberrypi
export ROS_IP=${rpi_ip}

echo "ROS_MASTER_URI: $ROS_MASTER_URI"
echo "ROS_IP: $ROS_IP"

dir=$(pwd)
${dir}/camera_ros/build/camera_publisher & ${dir}/LSM9DS1_RPI_ROS/build/imu_ros