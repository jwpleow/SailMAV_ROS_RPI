#!/bin/bash

dir=$(pwd)
mkdir -p ${dir}/camera_ros/build
cd ${dir}/camera_ros/build
cmake ..
make -j

mkdir -p ${dir}/LSM9DS1_RPI_ROS/build
cd ${dir}/LSM9DS1_RPI_ROS/build
cmake ..
make -j