source /opt/ros/melodic/setup.bash
dir=$(pwd)
${dir}/run_local.bash & 
sleep 10
rosbag record /imu/data_temp /imu/mag /stereo/image
