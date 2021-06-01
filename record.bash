trap "kill 0" SIGINT
source /opt/ros/melodic/setup.bash
dir=$(pwd)
${dir}/run_local.bash & 
sleep 12
rosbag record -b 1024 /imu/data_temp /imu/mag /stereo/image
