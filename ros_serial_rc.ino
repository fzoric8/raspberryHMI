// Define used ROS librarires and msgs
#include <ros.h>
#include <ros/time.h>
#include <hmi_msgs/Int8List.h>
#include <std_msgs/Int8.h>


// Define used channels for input values
#define CH1 3
#define CH2 5
#define CH3 6
#define CH4 9
#define CH6 10
#define BAUD 115200


ros::NodeHandle nh; 
hmi_msgs::Int8List joy; 
ros::Publisher joy_pub("joy_raw", &joy);

// Read input channel over arduino 
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue)
{
  int ch = pulseIn(channelInput, HIGH, 30000);
  if ( ch < 100) return defaultValue; 
  return map(ch, 1090, 1950, minLimit, maxLimit);

}

void setup() {
  
  // Set PIN modes to receive signal in range (1100-1900)
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT); 
  pinMode(CH6, INPUT); 

  // Set baudRate
  nh.getHardware()->setBaud(BAUD); 
  nh.initNode();
  nh.advertise(joy_pub);   

}

int ch1Value, ch2Value, ch3Value, ch4Value, ch6Value; 

void loop() {
  // put your main code here, to run repeatedly:

  while (!nh.connected())
  {     
    nh.spinOnce();
    nh.loginfo("Started RC ROS bridge..."); 
  }

  // Read channel values
  ch1Value = readChannel(CH1, -100, 100, 0); 
  ch2Value = readChannel(CH2, -100, 100, 0); 
  ch3Value = readChannel(CH3, -100, 100, 0); 
  ch4Value = readChannel(CH4, -100, 100, 0); 
  // Mode selector channel
  ch6Value = readChannel(CH6, -1, 1, 0); 

  // Assign read values to Int8 format
  std_msgs::Int8 val1; std_msgs::Int8 val2; 
  std_msgs::Int8 val3; std_msgs::Int8 val4;
  std_msgs::Int8 val5; 
  val1.data = ch1Value; 
  val2.data = ch2Value; 
  val3.data = ch3Value; 
  val4.data = ch4Value; 
  val5.data = ch6Value; 

  joy.header.stamp = nh.now(); 
  joy.data[0] = val1;  
  joy.data[1] = val2; 
  joy.data[2] = val3; 
  joy.data[3] = val4;  
  joy.data[4] = val5;  
  joy_pub.publish(&joy); 

  // Delay (not neccessary)
  delay(25); 

}
