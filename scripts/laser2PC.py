#!/usr/bin/env python3

import rospy
from sensor_msgs.msg import LaserScan
from sensor_msgs.msg import PointCloud2 as pc2
from laser_geometry import LaserProjection

class Laser2PC():
  def __init__(self):
    self.laserProj = LaserProjection()
    self.pcPub = rospy.Publisher("/laser2PC2", pc2, queue_size=1)
    self.pcPub_2 = rospy.Publisher("/laser2PC2_2", pc2, queue_size=1)
    self.laserSub = rospy.Subscriber("/scan", LaserScan, self.laserCallback)
    self.laserSub2 = rospy.Subscriber("/scan_2", LaserScan, self.laserCallback2)

  def laserCallback(self, data):
    cloud_out = self.laserProj.projectLaser(data)
    self.pcPub.publish(cloud_out)

  def laserCallback2(self, data):
    cloud_out = self.laserProj.projectLaser(data)
    self.pcPub_2.publish(cloud_out)

if __name__=='__main__':
  rospy.init_node("laser2PointClou2")
  l2pc = Laser2PC()
  rospy.spin()
