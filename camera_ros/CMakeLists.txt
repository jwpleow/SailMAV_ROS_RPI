cmake_minimum_required(VERSION 3.0)
project(camera_publisher)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(OpenCV REQUIRED)

set(ROS_FOUND FALSE)
if(DEFINED ENV{ROS_DISTRO})
  set(FOUND_ROS_DISTRO $ENV{ROS_DISTRO})
  set(ROS_FOUND TRUE)
else()
  message("ROS distro variable not set. Trying to figure it out...")
  set(AVAILABLE_ROS_VERSIONS "noetic;melodic;lunar;kinetic;jade;indigo")
  set(ROS_FOUND FALSE)
  foreach(version ${AVAILABLE_ROS_VERSIONS})
    if(NOT ROS_FOUND)
      find_path(ROS_H ros.h PATHS /opt/ros/${version}/include/ros)
      if(ROS_H)
        message("Found ros version ${version}")
        set(FOUND_ROS_DISTRO ${version})
        set(ROS_FOUND TRUE)
      endif()
    endif()
  endforeach()
endif()

if(ROS_FOUND)
  include_directories(/opt/ros/$ENV{ROS_DISTRO}/include/ /opt/ros/$ENV{ROS_DISTRO}/lib/)
  add_executable(camera_publisher main.cpp Camera.cpp Utils.cpp)
  target_link_libraries(camera_publisher -I/opt/ros/$ENV{ROS_DISTRO}/include -L/opt/ros/$ENV{ROS_DISTRO}/lib
  -lroscpp -lrostime -lrosconsole -lroscpp_serialization -lcv_bridge -limage_transport)
  target_link_libraries(camera_publisher ${OpenCV_LIBS})

endif()