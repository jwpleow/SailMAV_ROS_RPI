# Raspberry Pi ROS nodes
Publishes the raw camera feed to `/camera`   
Publishes the IMU linear accel and gyro to `/imu/data_raw`   
Publishes the IMU magnetometer readings to `/imu/mag`

=> can then use imu_tools madgwick filter to get orientation

## Dependencies
```
ROS 1 (with image_transport, sensor_msgs and cv_bridge)
```

## Setup raspberry pi 4B with Arducam:
Follow this gist: <https://gist.github.com/jwpleow/7ad5ff0a24b67db39c93606133e62594>


## Build & Run
make sure to fix the roscore_ip and ROS_HOSTNAME variables in run.bash
```
bash build.bash
bash run.bash
```