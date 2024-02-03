cmake_minimum_required(VERSION 3.0)
project(transform_point_cloud)

find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  geometry_msgs
  roscpp
  roslint
  rospy
  sensor_msgs
  tf2_py
  tf2_ros
  tf2_sensor_msgs
)

roslint_cpp()
set(ROSLINT_PYTHON_OPTS "--ignore=W503" "1>&2")
roslint_python()

generate_dynamic_reconfigure_options(
  cfg/LookupTransform.cfg
)

catkin_package(
  CATKIN_DEPENDS
  dynamic_reconfigure
  geometry_msgs
  roscpp
  sensor_msgs
  tf2_ros
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}
  src/transform_point_cloud.cpp
)

add_executable(publish_odometry_to_tf
  src/publish_odometry_to_tf.cpp
)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_gencfg)
target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES})

target_link_libraries(publish_odometry_to_tf ${catkin_LIBRARIES})

install(TARGETS
  ${PROJECT_NAME}
  publish_odometry_to_tf
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(PROGRAMS
  scripts/generate_point_cloud.py
  scripts/${PROJECT_NAME}_py.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
