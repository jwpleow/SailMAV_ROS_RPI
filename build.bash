#!/bin/bash

source /opt/ros/melodic/setup.bash

dir=$(pwd)
mkdir -p ${dir}/camera_ros/build
cd ${dir}/camera_ros/build
cmake ..
make -j

cd ${dir}
catkin_make
chmod +x src/ICM20948_ROS_Publisher_Py/src/ros_imu_publisher.py

