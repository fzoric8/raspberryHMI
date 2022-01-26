# Instructions to setup Raspberry Pi 4 for HMI 

This file contains all files neccessary to enable `Ubuntu Mate 20.04" 
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
