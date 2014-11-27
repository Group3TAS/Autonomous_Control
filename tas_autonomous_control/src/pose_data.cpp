#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include "wlan_data.h"

using std::vector;
using std::cout;
using std::endl;

//void chatterCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
//{
//   ROS_INFO("I heard: [%f]", msg->pose.pose.position.x);
//}

void nextCallback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg){
  ROS_INFO("X Coordinate: %f", msg->pose.pose.position.x);
  ROS_INFO("Y Coordinate: %f", msg->pose.pose.position.y);
  ROS_INFO("Z Coordinate: %f", msg->pose.pose.position.z);

  int x = msg->pose.covariance.size();
  vector<float> cov_vec;
  for (int i = 0; i != x ; i++)
  {
      cov_vec.push_back(msg->pose.covariance[i]);
      cout << cov_vec[i] << endl;
  }

  wlan_data_write(msg->pose.pose.position.x,msg->pose.pose.position.y,cov_vec);
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line. For programmatic
   * remappings you can use a different version of init() which takes remappings
   * directly, but for most command-line programs, passing argc and argv is the easiest
   * way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "pose_data_reader");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("amcl_pose", 1000, nextCallback);
  //ros::Subscriber sub2 = n.subscribe("move_base_simple/goal",1000,chatterCallback);

  ros::spin();

  return 0;
}
