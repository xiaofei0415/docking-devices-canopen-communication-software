#include <ros/ros.h>
#include <ar_track_alvar_msgs/AlvarMarkers.h>
#include <std_msgs/String.h>
#include <math.h>
#include <stdlib.h>
#include <exception>
#include <motion_msgs/Motion.h>
double x =0.0;
double z = 0.0;


void camComandCallback(const ar_track_alvar_msgs::AlvarMarkersConstPtr &msg)
{
        ar_track_alvar_msgs::AlvarMarker mark;
        try
        {
            mark = msg->markers.at(0);

            if(mark.id != 0) 
                throw std::exception();   
        }
        catch (std::exception)
        {

            return;
        }                 
        
         x = mark.pose.pose.position.x;
        //double y = mark.pose.pose.position.y;
         z = mark.pose.pose.position.z;
        /*
        double x_angle = atan2(x, z) * 180 / 3.14;
        if(fabs(x_angle) > 3){
            int tem = (int)75 * (fabs(x_angle) - 3);         
            x_speed = copysign(min(1500, max(tem, 500)), x_angle);
        }else x_speed = 0;

        double y_angle = atan2(y, z) * 180 / 3.14;
        if(fabs(y_angle) > 3){
            int tem = (int)75 * (fabs(y_angle) - 3);         
            y_speed = copysign(min(1200, max(tem, 400)), y_angle);
        }else y_speed = 0;

        ROS_INFO("x_speed: %d", x_speed);
        ROS_INFO("y_speed: %d", y_speed);
        */

}

int main(int argc, char *argv[])
{
  
    ros::init(argc, argv, "visual_arm_node");

	ros::NodeHandle n;
	ros::Rate loop_rate(10);

  ros::Subscriber sub2 = n.subscribe("ar_pose_marker", 1, camComandCallback);
  ros::Publisher pub = n.advertise<motion_msgs::Motion>("arm_cmd_topic", 1);
  //n.subscribe()
  int temp = 0;
    while (ros::ok())
    {
       double x_angle = atan2(x, z) * 180 / M_PI;
       ROS_INFO("x angle: %lf", x_angle);
       int num = x_angle * 4096 / 360;
       ROS_INFO("x num: %d", num);
       if(abs(num-temp)>8){
         temp = num;
         motion_msgs::Motion msg;
         msg.car = "car1";
         msg.arm = "twoj";
         msg.motion = "low";
         msg.num = num;
         pub.publish(msg);
       }

       ros::spinOnce();
	   loop_rate.sleep();     
    }
    
    return 0;
}
