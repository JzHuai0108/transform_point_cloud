#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>

/*
 * subscribe to an odometry topic and publish the odometry messages to tf
 */
tf2_ros::TransformBroadcaster *odom_broadcaster;
ros::Publisher *odom_pub;

void odometryCallback(const nav_msgs::Odometry &odom) {
   geometry_msgs::TransformStamped tf_stamped;
   tf_stamped.header = odom.header;
//   tf_stamped.header.stamp = current_time;
//   tf_stamped.header.frame_id = "odom";
   tf_stamped.child_frame_id = "husky2/velodyne"; // odom.child_frame_id;

   tf_stamped.transform.translation.x = odom.pose.pose.position.x;
   tf_stamped.transform.translation.y = odom.pose.pose.position.y;
   tf_stamped.transform.translation.z = odom.pose.pose.position.z;
   tf_stamped.transform.rotation = odom.pose.pose.orientation;
   odom_broadcaster->sendTransform(tf_stamped);
   odom_pub->publish(odom);
}

int main(int argc, char** argv){
  ros::init(argc, argv, "odometry_publisher");
  ros::NodeHandle n;
  tf2_ros::TransformBroadcaster _odom_broadcaster;
  odom_broadcaster = &_odom_broadcaster;

  ros::Publisher _odom_pub = n.advertise<nav_msgs::Odometry>("mirror_odom", 50);
  odom_pub = &_odom_pub;

  ros::Subscriber sub_ = n.subscribe("/husky2/lo_frontend/odometry", 100, &odometryCallback);

  ros::Rate r(30.0);
  while(n.ok()){
    ros::spinOnce();
    r.sleep();
  }
}
