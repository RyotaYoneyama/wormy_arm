# wormy_arm
This is the repository for 3D-printed robot arm named "Wormy Arm".
I designed by myself for my education from mechanical design and electronics to ros-based software.

Please freely reproduce your wormy arm with 3D printers and move it using this ros-based repository under MIT license.

I am also adding some notes about the process of development of the robot because it would be useful for someone learning ROS and robotics like me.

## How to setup your Wormy Arm.
### Mechanical side
#### 3D-printed parts


Please download parts from the [link](https://cad.onshape.com/documents/3f8fd3cb66199d54e5d8a8ef/w/dd6d2618a85894306c9569e8/e/543bf18749a4cd6580b86a53?renderMode=0&uiState=63ea472403b3c042dfd15e70).

It has multiple parts but you are supposed to assemble a robot named "wormy_short", which has 6 degree of freedom.
Therefore, the parts you should print out are

| Module | Part                   | Number |
| ------ | ---------------------- | ------ |
| link_0 | base_mount_motor       | x1     |
|        | base_mount_raspberrypi | x1     |
|        | base_case              | x1     |
|        | base_cover             | x1     |
| link_1 | motor_mount_a1         | x1     |
|        | motor_mount_b          | x1     |
|        | joint_connector_a      | x1     |
| link_2 | motor_mount_a1         | x1     |
|        | motor_mount_b          | x1     |
|        | joint_connector_a      | x1     |
| link_3 | motor_mount_a1         | x1     |
|        | motor_mount_b          | x1     |
|        | joint_connector_a      | x1     |
| link_4 | motor_mount_a1         | x1     |
|        | motor_mount_b          | x1     |
|        | joint_connector_a      | x1     |
| link_5 | motor_mount_a1         | x1     |
|        | motor_mount_b          | x1     |
|        | joint_connector_a      | x1     |
|        | joint_connector_a2     | x1     |


#### Non 3D-printed parts
- Motors and the accessories.
  - [dynamixel AX-12a](https://emanual.robotis.com/docs/en/dxl/ax/ax-12a/) x 6.
  - [SMPS2Dynamixel](https://e-shop.robotis.co.jp/product.php?id=175) x 1.
  - [U2D2 RS485](https://emanual.robotis.com/docs/en/parts/interface/u2d2/) x 1.

- Bolts
  - M2-14mm x 6
  - M2-8mm x 24
  - (M3-16mm x 8)
  - M3-10mm x 30 

- Bush
I used 6 [these bushes](https://www.monotaro.com/p/0045/6477/) to support rotating axis of which outer diameter is 28 mm and inner diameter is 25 mm.

### Electronic side
### Software side

#### Clone 

<!-- sudo chmod 666 /dev/ttyUSB0
sudo vim /sys/bus/usb-serial/devices/ttyUSB0/latency_timer -->