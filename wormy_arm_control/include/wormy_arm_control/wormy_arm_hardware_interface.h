#ifndef __WORMY_ARM_HARDWARE_INTERFACE_H__
#define __WORMY_ARM_HARDWARE_INTERFACE_H__

#include <ros/ros.h>

#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <joint_limits_interface/joint_limits.h>
#include <joint_limits_interface/joint_limits_interface.h>
#include <joint_limits_interface/joint_limits_rosparam.h>

#include <map>
#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "wormy_arm_control/dynamixel_driver.h"
#include "wormy_arm_control/visibility_control.h"
#include "wormy_arm_control/yaml_parser.h"

class WormyArm : public hardware_interface::RobotHW
{
public:
  WormyArm();
  ~WormyArm();

  ros::Time getTime() const { return ros::Time::now(); }
  ros::Duration getPeriod() const { return ros::Duration(0.01); }

  void init_move();

  void read(ros::Time, ros::Duration);

  void write(ros::Time, ros::Duration);

protected:
  hardware_interface::JointStateInterface jnt_state_interface;
  hardware_interface::PositionJointInterface jnt_pos_interface;
  hardware_interface::EffortJointInterface jnt_eff_interface;
  joint_limits_interface::PositionJointSoftLimitsInterface jnt_lmt_interface;

  std::unique_ptr<ros::NodeHandle> pnh_;

  std::shared_ptr<DynamixelDriver> driver_;
  double timeout_seconds_;
  bool read_velocities_;
  bool read_loads_;
  bool read_voltages_;
  bool read_temperatures_;
  DynamixelInfo dynamixel_info_;

  std::vector<double> hw_position_commands_;
  std::vector<double> hw_position_states_;
  std::vector<double> hw_velocity_states_;
  std::vector<double> hw_effort_states_;
  std::vector<double> hw_load_states_;
  std::vector<double> hw_voltage_states_;
  std::vector<double> hw_temperature_states_;

  bool timeout_has_printed_;

  std::string param_name_yaml_ = "dynamixel_yaml";
};
#endif // __WORMY_ARM_HARDWARE_INTERFACE_H__