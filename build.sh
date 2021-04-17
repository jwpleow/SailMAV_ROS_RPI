#!/bin/bash

dir=$(pwd)
mkdir -p ${dir}/camera_ros/build
cd ${dir}/camera_ros/build
cmake ..
make -j

mkdir -p ${dir}/lsm9ds1_rpi_grpc/build
cd ${dir}/lsm9ds1_rpi_grpc/build
cmake ..
make -j