#include <ros/ros.h>
#include <controller_manager/controller_manager.h>
#include <wormy_arm_control/wormy_arm_hardware_interface.h>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "wormy_arm_control");
  ros::NodeHandle nh;

  WormyArm wormy_arm;
  controller_manager::ControllerManager cm(&wormy_arm, nh);

  ros::AsyncSpinner spinner(1);
  spinner.start();
    ros::Duration dt = wormy_arm.getPeriod();

  while (ros::ok())
  {
    ros::Time now = wormy_arm.getTime();

    wormy_arm.read(now, dt);
    cm.update(now, dt);

    wormy_arm.write(now, dt);
    dt.sleep();
  }
  spinner.stop();

  return 0;
}
