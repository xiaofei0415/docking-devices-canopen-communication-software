#!/usr/bin/env python
import sys, select, tty, termios
import rospy
from std_msgs.msg import String
if __name__ == '__main__':
        key_pub = rospy.Publisher('keys', String, queue_size=1)
        rospy.init_node("remote_publisher")
        rate = rospy.Rate(100)
        old_attr = termios.tcgetattr(sys.stdin)
        tty.setcbreak(sys.stdin.fileno())
        print "\nReading from the keyboard and Publishing to control the car!"
	print "\nDate:2019/11/30"
	print "Author:WangShuai"
	print "Version:1.1"
	print "-------------------------------------------------------------"
	print "\nMoving around:\n"
	print " |          Master          |            Slave         |"
	print " |                          |                          |"
	print " | -----------------------  |  ----------------------- |"
	print " | -       car_Master    -  |  -       car_Slave     - |"
	print " | -                     -  |  -                     - |"
	print " | -  q       w       e  -  |  -  u       i       o  - |"
	print " | -  a       s       d  -  |  -  j       k       l  - |"
	print " | -  z       x       c  -  |  -  m       ,       .  - |" 
	print " | -----------------------  |  ----------------------- |"
	print " |                          |                          |"
	print " | -----------------------  |  ----------------------- |"
	print " | -       arm_Master    -  |  -       arm_Slave     - |"
	print " | -                     -  |  -                     - |"
	print " | -          t          -  |  -          ;          - |"
	print " | -  f       g       h  -  |  -                     - |"
	print " | -          b          -  |  -          '          - |" 
	print " | -----------------------  |  ----------------------- |\n\n"

	print "     [/]        : increase/decrease max speeds by 10%"
	print "     s/k        : stop the car_Master/car_Slave"
	print "t/b & f/h & g   : arm_Master  up/down  & left/right  &  finish"
	print "     ;/'        : arm_Slave   lock/unlock"
	print "\nPress Ctrl-C to exit..."

	#print ";/' :increase/decrease only linear speed by 10%"
	#print "n/m :increase/decrease only angular speed by 10%"
        while not rospy.is_shutdown():
                if select.select([sys.stdin], [], [], 0)[0] == [sys.stdin]:
                        key_pub.publish(sys.stdin.read(1))
                rate.sleep()
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_attr)
