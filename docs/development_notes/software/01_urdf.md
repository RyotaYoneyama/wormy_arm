# URDF
Memo about how to generate the URDF file of wormy-arm.
## Steps

1. Check documents about OnShape to robot.
2. Setup OnShape to robot.
3. Modify wormy-arm on OnShape.
4. Create a config file for Onshape to robot.
5. Export a URDF file of wormy-arm.
6. Test the URDF file with VREP.
7. Test th URDF with ROS.
8. Convert the URDF file to xacro file manually.

## Check documents about onshape to robot.
- [Documents of Onshape to robot](https://onshape-to-robot.readthedocs.io/en/latest/index.html)
- [Video of onshape to robot, highly recommend](https://www.youtube.com/watch?v=C8oK4uUmbRw)
- [Examples of onshape to robot](https://github.com/rhoban/onshape-to-robot-examples)

## Setup onshape to robot.
Follow [this](https://onshape-to-robot.readthedocs.io/en/latest/installation.html).

## Modify wormy-arm on OnShape.
You need to have revolute joints in your assembly file. Moreover, the revolute joints should be named 'dof_'.


## Create a config file for Onshape to robot.
The example of the config file is as follow:
<pre>
{
    "documentId": "3f8fd3cb66199d54e5d8a8ef", ## documentId the next of https://cad.onshape.com/documents/
    "outputFormat": "urdf",
    "assemblyName": "whole_assembly",
    "jointMaxEffort": {
        "default": 1.5,
        "head_pitch": 0.5
    },
    "jointMaxVelocity": 22,

    "dynamics": {
        "base_case": "fixed"
    },
    "robotName": "wormy-arm",
    "addDummyBaseLink": true,
}

Put the config file under wormy_arm_description/urdf/raw/ for instance.
</pre>

## Export a URDF file of wormy-arm

~~~
onshape-to-robot wormy_arm_description/urdf/raw
~~~
Then, you will have robot.urdf in wormy_arm_description/urdf/raw.

## Test the URDF file with VREP.
~~~
onshape-to-robot-bullet wormy_arm_description/urdf/raw
~~~
You will see VREP windows with wormy-arm.

## Test the URDF file with ROS.
1. Run docker container.
2. Catkin build
~~~
cd catkin_ws
catkin build
source devel/setup.bash
~~~
3. Modify the URDF file.
- Joint limits
~~~
<limit effort="1.5" velocity="3.14"/>
->
<limit lower="-3.14" upper="3.14" effort="1.5" velocity="3.14"/>
~~~
- Package path
~~~
package:///
->
package://wormy_arm_description/urdf/raw/
~~~
4. Run
~~~
roslaunch urdf_tutorial display.launch model:=src/wormy_arm/wormy_arm_description/urdf/raw/robot.urdf
~~~
## Convert the URDF file to xacro file manually.
Just do it!
The fi
