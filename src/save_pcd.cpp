// src/example.cpp

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
// PCL specific includes
#include <pcl/io/pcd_io.h>
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/voxel_grid.h>

#include <iostream>       // std::cout
#include <typeinfo>       // operator typeid

void 
callback1 (const sensor_msgs::PointCloud2 msg)
{
  pcl::PCLPointCloud2 pcl_pc;
  pcl_conversions::toPCL(msg, pcl_pc);

  pcl::PointCloud<pcl::PointXYZ> input_cloud;
  pcl::fromPCLPointCloud2(pcl_pc, input_cloud);

  pcl::io::savePCDFileASCII("test_pcd.pcd", input_cloud);  
  /*cloud.width    = msg.width;
  cloud.height   = msg.height;
  cloud.is_dense = msg.is_dense;
  cloud.points.resize(cloud.width * cloud.height);*/
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "save_pcd");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("/laser2PC2", 1, callback1);
  //ros::Subscriber sub2 = nh.subscribe ("/laser2PC2_2", 1, callback2);

  ros::spin();
}
