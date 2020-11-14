#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float64.h>
ros::NodeHandle nh;

float x;
float y;

void messageCb( const std_msgs::Float64& msg){
  x = msg.data;
}

void messageCb1( const std_msgs::Float64& msg){
  y = msg.data;
}

ros::Subscriber<std_msgs::Float64> sub("right_publish", &messageCb);
ros::Subscriber<std_msgs::Float64> sub2("left_publish", &messageCb1);

void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
pinMode(11,OUTPUT);
pinMode(10,OUTPUT);
pinMode(9,OUTPUT);
pinMode(6,OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  nh.subscribe(sub2);
}

void loop() {
    nh.spinOnce();
  delay(5);
  
  
  if (x>0)
  {
    analogWrite(9,x);
    digitalWrite(6,LOW);
  }
  if (x<0)
  { //x=-1*x;
    digitalWrite(6,HIGH);
    analogWrite(9,-x);
  }
  if(x==0.0)
  {
    digitalWrite(9,LOW);
    digitalWrite(6,LOW);
  }


  if (y>0.0)
  {
    analogWrite(11,y);
    digitalWrite(10,LOW);
  }
  if (y<0.0)
  {
    //y=-1*y;
    digitalWrite(10,HIGH);
    analogWrite(11,-y);
  }
  if(y==0.0)
  {
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
  }


}
