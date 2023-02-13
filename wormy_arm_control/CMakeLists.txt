cmake_minimum_required(VERSION 2.8.3)
project(wormy_arm_control)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  hardware_interface
  transmission_interface
  controller_manager
  dynamixel_sdk
)

# find_package(dynamixel_sdk REQUIRED)
find_package(PkgConfig)

pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp hardware_interface transmission_interface controller_manager dynamixel_sdk
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${YAMLCPP_INCLUDE_DIRS}
)

add_executable(wormy_arm_control src/wormy_arm_control.cpp src/wormy_arm_hardware_interface.cpp src/dynamixel_driver.cpp src/yaml_parser.cpp)



target_link_libraries(wormy_arm_control
  ${catkin_LIBRARIES}
  ${YAMLCPP_LIBRARIES}
)

install(TARGETS wormy_arm_control
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
