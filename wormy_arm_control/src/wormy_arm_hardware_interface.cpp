#include <ros/ros.h>
#include <ros/package.h>
#include <angles/angles.h>
#include <iostream> // for debug
#include <math.h>

#include "wormy_arm_control/wormy_arm_hardware_interface.h"

WormyArm::WormyArm()
{
  pnh_ = std::make_unique<ros::NodeHandle>("~");
  std::string yaml_file;
  pnh_->getParam(param_name_yaml_, yaml_file);

  if (yaml2dynamixel_info(yaml_file, dynamixel_info_) == false)
    ROS_ERROR("YAML parse error.");

  std::vector<uint8_t> dxl_id_list;
  for (auto joint_info : dynamixel_info_.joint_infos)
  {
    dxl_id_list.push_back(joint_info.id);
  }

  int num_joint = dynamixel_info_.joint_infos.size();
  hw_position_commands_.resize(num_joint, 0);
  hw_position_states_.resize(num_joint, 0);
  hw_velocity_states_.resize(num_joint, 0);
  hw_effort_states_.resize(num_joint, 0);
  hw_load_states_.resize(num_joint, 0);
  hw_voltage_states_.resize(num_joint, 0);
  hw_temperature_states_.resize(num_joint, 0);

  // Open a crane_plus_driver
  std::cout << "dynamixel_info_.port_name:" << dynamixel_info_.port_name << std::endl;
  driver_ = std::make_shared<DynamixelDriver>(dynamixel_info_.port_name, dynamixel_info_.baud_rate, dxl_id_list);
  if (!driver_->open_port())
  {
    ROS_ERROR("Dyanamixel port open error:", driver_->get_last_error_log());
    return;
  }
  if (!driver_->torque_enable(true))
  {
    std::cout << "Dynamixel torque enable error:" << driver_->get_last_error_log() << std::endl;
    return;
  }

  // connect and register the joint state interface
  for (int i = 0; i < num_joint; i++)
  {
    hardware_interface::JointStateHandle state_handle(dynamixel_info_.joint_infos[i].name, &hw_position_states_[i], &hw_velocity_states_[i], &hw_effort_states_[i]);
    jnt_state_interface.registerHandle(state_handle);
  }
  registerInterface(&jnt_state_interface);

  for (int i = 0; i < num_joint; i++)
  {
    hardware_interface::JointHandle pos_handle(jnt_state_interface.getHandle(dynamixel_info_.joint_infos[i].name), &hw_position_commands_[i]);
    jnt_pos_interface.registerHandle(pos_handle);

    joint_limits_interface::SoftJointLimits soft_limits;
      joint_limits_interface::JointLimits limits;

    if( joint_limits_interface::getJointLimits( dynamixel_info_.joint_infos[i].name, *pnh_, limits ) ){
        soft_limits.k_position = 1.0;
        soft_limits.k_velocity = 1.0;
        soft_limits.max_position = limits.max_position;
        soft_limits.min_position = limits.min_position;
        joint_limits_interface::PositionJointSoftLimitsHandle
                        reg_limits_handle( pos_handle, limits, soft_limits );
        jnt_lmt_interface.registerHandle( reg_limits_handle );
    }
  }
  registerInterface(&jnt_pos_interface);




  timeout_has_printed_ = false;
  init_move();
}

WormyArm::~WormyArm()
{
  driver_->torque_enable(false);
  driver_->close_port();
}

void WormyArm::init_move()
{
  std::vector<double> joint_positions;
  if (!driver_->read_present_joint_positions(joint_positions))
  {
    ROS_ERROR("Joint read error:", driver_->get_last_error_log());
    return;
  }
  else
  {
    for (uint i = 0; i < hw_position_states_.size(); ++i)
    {
      hw_position_states_[i] = joint_positions[i];
      hw_position_commands_[i] = joint_positions[i];
    }
  }
}

void WormyArm::read(ros::Time time, ros::Duration period)
{

  std::vector<double> joint_positions;
  if (!driver_->read_present_joint_positions(joint_positions))
  {
    ROS_ERROR("Joint read error:", driver_->get_last_error_log());
    return;
  }
  else
  {
    for (uint i = 0; i < hw_position_states_.size(); ++i)
    {
      hw_position_states_[i] = joint_positions[i];
    }
  }

  // Reading joint speeds, loads, voltages or temperatures
  // causes a decrease of the communication rate.
  if (read_velocities_)
  {
    std::vector<double> joint_speeds;
    if (driver_->read_present_joint_speeds(joint_speeds))
    {
      for (uint i = 0; i < hw_velocity_states_.size(); ++i)
      {
        hw_velocity_states_[i] = joint_speeds[i];
      }
    }
  }

  if (read_loads_)
  {
    std::vector<double> joint_loads;
    if (driver_->read_present_joint_loads(joint_loads))
    {
      for (uint i = 0; i < hw_load_states_.size(); ++i)
      {
        hw_load_states_[i] = joint_loads[i];
      }
    }
  }

  if (read_voltages_)
  {
    std::vector<double> joint_voltages;
    if (driver_->read_present_joint_voltages(joint_voltages))
    {
      for (uint i = 0; i < hw_voltage_states_.size(); ++i)
      {
        hw_voltage_states_[i] = joint_voltages[i];
      }
    }
  }

  if (read_temperatures_)
  {
    std::vector<double> joint_temperatures;
    if (driver_->read_present_joint_temperatures(joint_temperatures))
    {
      for (uint i = 0; i < hw_temperature_states_.size(); ++i)
      {
        hw_temperature_states_[i] = joint_temperatures[i];
      }
    }
  }
}

void WormyArm::write(ros::Time time, ros::Duration period)
{
  if (!driver_->write_goal_joint_positions(hw_position_commands_))
  {
    ROS_ERROR("Command write error:", driver_->get_last_error_log());
    return;
  }
}
