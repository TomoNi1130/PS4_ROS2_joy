cmake_minimum_required(VERSION 3.8)
project(joy_controller_pkg)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(test_interface REQUIRED)

execute_process(
  COMMAND ${Python3_EXECUTABLE} -m pip show em
  RESULT_VARIABLE EM_INSTALLED
)

add_executable(listener 
src/listener.cpp
)

ament_target_dependencies(listener 
rclcpp 
std_msgs
sensor_msgs
test_interface
)

add_executable(serial_talker 
src/serial_talker.cpp
)

ament_target_dependencies(serial_talker 
  rclcpp 
  std_msgs 
  test_interface
)

# Install targets
install(TARGETS
  listener
  serial_talker
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch/
  DESTINATION share/${PROJECT_NAME}/launch
)

# Add testing if enabled
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
