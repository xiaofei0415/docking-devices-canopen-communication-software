#include "arms/boss.h"
#include "arms/can.h"
//#include "motion_msgs/Motion.h"
ControlCan can;

 int main(int argc, char *argv[])
{
    ros::init(argc, argv, "arm_cmd_sub_node");//具体的每个车上的节点名称不一样,可以放在这里吗
    Boss boss("car1");
    //if(!boss.init()){
      //  return -1;
    //}
    ROS_INFO("enter keyloop.");

    boss.keyLoop();

    ROS_INFO("leave keyloop.");
    return 0;
}
