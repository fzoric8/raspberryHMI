# Instructions to setup Raspberry Pi 4 for HMI

This file contains all files neccessary to enable `Ubuntu Mate 20.04` 
for HMI client. 

If you want to enable GPIO UART on Raspberry Pi, you have precompiled 
boot binary configuration that follows this [instructions](https://fzoric8.github.io/2022/01/21/how-to-enable-UART-on-rPi-4-Ubuntu-20.04.html). 

Arduino programs for rosserial can be found also here. 

As well as script that builds ROS and ROS workspace. 

## Add user to dialout group 

We want to add user to dialout group to be able to access serial devices: 
```
sudo adduser ${USER} dialout
```

## Install ROS noetic 

Install ROS noetic following this [instructions](http://wiki.ros.org/noetic/Installation/Ubuntu)

## Install ArduinoIde for Ros serial

If we're using raspberry which has ARM64 it's neccessary to download such Arduino IDE architecture. 

Install ROS serial on your PC: 
```
sudo apt-get install ros-${ROS_DISTRO}-rosserial-arduino
sudo apt-get install ros-${ROS_DISTRO}-rosserial
```

After that, we need to install `ros_lib` package but which contains `hmi_msgs` in order to do so
follow this instructions: 
```
cp -r /hmi_msgs <catkin_ws>/src/
cd <catkin_ws> 
catkin_make 
source ../devel/setup.bash 
cd <arduino_ide>/libraries 
rosrun rosserial_arduino make_libraries.py .
```

After that you can open `*.ino` file in your arduino IDE and upload it to your arduino. 

To run rosserial run this command with correct baud rate. 
```
rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600
```


## TODO: 


#### HP
- [ ] Create launch file
- [ ] Convert Int8List to joy msg
#### LP
- [ ] Test on GPIO Raspberry UART
- [ ] Create casing 
