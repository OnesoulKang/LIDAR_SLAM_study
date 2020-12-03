// src/example.cpp

#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
// PCL specific includes
#include <pcl/conversions.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/filters/voxel_grid.h>

#include <iostream>       // std::cout
#include <typeinfo>       // operator typeid

ros::Publisher pub;

typedef pcl::PointCloud<pcl::PointXYZ> point_cloud_t;

pcl::PCLPointCloud2 input_1;
pcl::PCLPointCloud2 input_2;

void 
callback1 (const sensor_msgs::PointCloud2 msg)
{
  pcl_conversions::toPCL(msg, input_1);
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;

  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("/laser2PC2", 1, callback1);
  //ros::Subscriber sub2 = nh.subscribe ("/laser2PC2_2", 1, callback2);

  while(1)
  {
    std::cout<<input_1<<"\n";
    // Create a ROS publisher for the output point cloud
    //pub = nh.advertise<sensor_msgs::PointCloud2> ("output", 1);

    // Spin
    ros::spinOnce();
  }
}
