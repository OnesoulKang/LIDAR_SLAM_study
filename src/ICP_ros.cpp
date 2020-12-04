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

pcl::PointCloud<pcl::PointXYZ> input_cloud_1;
pcl::PointCloud<pcl::PointXYZ> input_cloud_2;

bool a = false;
bool b = false;

void 
callback1 (const sensor_msgs::PointCloud2 msg)
{
  pcl::PCLPointCloud2 pcl_pc;
  pcl_conversions::toPCL(msg, pcl_pc);

  pcl::fromPCLPointCloud2(pcl_pc, input_cloud_1);  

  a = true;
}

void 
callback2 (const sensor_msgs::PointCloud2 msg)
{
  pcl::PCLPointCloud2 pcl_pc;
  pcl_conversions::toPCL(msg, pcl_pc);

  pcl::fromPCLPointCloud2(pcl_pc, input_cloud_2);

  b=true;
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "save_pcd");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("/laser2PC2", 1, callback1);
  ros::Subscriber sub2 = nh.subscribe ("/laser2PC2_2", 1, callback2);

  pcl::PointCloud<pcl::PointXYZ> combined_cloud;

  while(ros::ok())
  {
    if (a and b)
    {
      combined_cloud = input_cloud_1 + input_cloud_2;
      pcl::io::savePCDFileASCII("test_pcd.pcd", combined_cloud);  
    }
    ros::spinOnce();
  }
}
