#ifndef __YAML_PARSER_H__
#define __YAML_PARSER_H__

#include <iostream>
#include <yaml-cpp/yaml.h>

struct JointInfo
{
    int id;
    std::string name;
};
struct DynamixelInfo
{
    std::string port_name;
    int baud_rate;
    double timeout_seconds;
    bool read_velocities;
    bool read_loads;
    bool read_temperatures;
    std::vector<JointInfo> joint_infos;
};

bool yaml2dynamixel_info(const std::string yaml_path, DynamixelInfo &dynamixel_info);
#endif // __YAML_PARSER_H__
