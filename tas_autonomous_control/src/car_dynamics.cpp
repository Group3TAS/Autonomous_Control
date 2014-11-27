#include <iostream>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>
#include <vector>
#include "laser_processing.h"

using std::vector;


class dynamics_control
{
private:
  ros::NodeHandle nh_;
  ros::Publisher cmd_vel_pub_;
  ros::Subscriber laser_sub;
  geometry_msgs::Twist base_cmd;
public:
  dynamics_control(ros::NodeHandle &nh)
  {
    nh_ = nh;
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  };
  void laserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
  {
    vector<float>::size_type x;
    vector<float> ranges;
    ranges = scan->ranges;
    x = ranges.size();
    
    float test = process_laser_data(ranges);

    ROS_INFO("Minimum Range: [%f]", scan->range_min);
    ROS_INFO("Maximum Range: [%f]", scan->range_max);
    ROS_INFO("Size of Range Vector: [%i]",x);
    ROS_INFO("Range Vector Value 1: [%f]",ranges[0]);
    ROS_INFO("Angle_Increment: [%f]", scan->angle_increment);
    ROS_INFO("Angle_Min: [%f]", scan->angle_min);
    ROS_INFO("Angle_Max: [%f]",scan->angle_max);

    if(test == 0)
    {
        base_cmd.linear.x = 0;
        base_cmd.angular.z = 0;
    }
    else if (test == 1)
    {
        base_cmd.linear.x = 1;
        base_cmd.angular.z = -1 ;
    }
    else if (test == 2)
    {
        base_cmd.linear.x = 1;
        base_cmd.angular.z = 1;
    }

    cmd_vel_pub_.publish(base_cmd);
  };
};


int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "car_dynamics");
  ros::NodeHandle nh;
  dynamics_control car_control(nh);
  ros::Subscriber laser_sub = nh.subscribe("scan", 1000, &dynamics_control::laserCallback, &car_control);
  ros::spin();
  //ros::Subscriber sub = nh.subscribe("scan", 1000, &dynamics_control::laserCallback, &car_control);
  

  /*
  ros::Publisher cmd_vel_pub_ = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  ros::Subscriber sub = nh.subscribe("scan",50,laserCallback);
  ros::Rate loop_rate(40);

  geometry_msgs::Twist base_cmd;
  while(ros::ok())
    {
      base_cmd.linear.x = 0.25;
      base_cmd.linear.z = -0.75;
      cmd_vel_pub_.publish(base_cmd);
      ros::spinOnce();

      loop_rate.sleep();
    }
  */
}
