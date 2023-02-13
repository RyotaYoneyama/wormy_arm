#include "wormy_arm_control/yaml_parser.h"


bool yaml2dynamixel_info(const std::string yaml_path, DynamixelInfo &dynamixel_info)
{
    YAML::Node node = YAML::LoadFile(yaml_path);
    if (node == NULL) return false;

    std::cout<<"yaml_path:"<<yaml_path<<std::endl;
    std::cout<<"node:"<<node<<std::endl;

    dynamixel_info.baud_rate = node["baud_rate"].as<int>();
    dynamixel_info.port_name = node["port_name"].as<std::string>();
    
    dynamixel_info.timeout_seconds = node["timeout_seconds"].as<double>();
    dynamixel_info.read_velocities = node["read_velocities"].as<bool>();
    dynamixel_info.read_loads = node["read_loads"].as<bool>();
    dynamixel_info.read_temperatures = node["read_temperatures"].as<bool>();

    YAML::Node node_joints = node["joints"];


    for (YAML::const_iterator it_file = node_joints.begin(); it_file != node_joints.end(); it_file++)
    {
        std::string name = it_file->first.as<std::string>();
        if (name.size() == 0)
        {
            continue;
        }

        YAML::Node item = node_joints[name];
        for (YAML::const_iterator it_item = item.begin(); it_item != item.end(); it_item++)
        {
            std::string item_name = it_item->first.as<std::string>();
            if (item_name == "ID")
            {
                JointInfo joint_info;
                joint_info.name = name;
                joint_info.id = it_item->second.as<int>();
                dynamixel_info.joint_infos.push_back(joint_info);
            }
        }
    }


    return true;
}