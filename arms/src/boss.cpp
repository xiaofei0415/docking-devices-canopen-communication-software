#include "arms/boss.h"
#include <iostream>
#include "arms/can.h"
#include "ros/ros.h"
#include <string>
#include <cstdlib>
#include "arms/consts.h"
#include "motion_msgs/Motion.h"

std::string Boss::car_ = "hhh";
std::string Boss::arm_ = "hhh";
std::string Boss::motion_ = "hhh";
int Boss::num_ = 0;

Boss::Boss(std::string carid):
  //backMouth_(BACKID, BACK_CLOSE_LIMIT, BACK_OPEN_LIMIT),
  //twoJointsArm_(J2L_ORI, J2H_ORI),
  //threeJointsArm_(),
  carid_(carid),loop_rate_(10)//string&??
{  
    sub_ = nh_.subscribe("arm_cmd_topic", 1000, arm_cmd_callback);//???

    ROS_INFO("boss constructed.");
}
bool Boss::init(){
     if(!can.init()){
        std::cout<<"can device init error!"<<std::endl;
        can.close();
        return false;
    }
    if(!can.startNMT()){
        std::cout<<"NMT start error!"<<std::endl;
        can.close();
        //exit(EXIT_FAILURE);//有没有其他更好的结束程序的方式，比如exception
        return false;
    }

   //backMouth_.init();

   //twoJointsArm_.init();

   //threeJointsArm_.init();
   return true;
}
Boss::~Boss()
{
    can.close();
    ROS_INFO("boss desconstructed.");
}
void Boss::keyLoop()
{
    while(ros::ok())
    {
        //main loop
        if(car_ == carid_)
        {
          /*
            if(arm_ == "back")
            {
                if(motion_ == "open"){
                    backMouth_.open();
                    ROS_INFO("back mouth open");
                }
                else if(motion_ == "close"){
                    backMouth_.close();
                    ROS_INFO("back mouth close");
                }
            }else
          if(arm_ == "twoj")
            {
                if(motion_ == "start"){
                    twoJointsArm_.start();
                    ROS_INFO("twojoints start");
                }
                else if(motion_ == "disable"){
                    twoJointsArm_.disable();
                    ROS_INFO("twojoints disable");
                }

                else if(motion_ == "low"){
                  int num = num_ + J2L_ORI;//clock wise
                  if((num>J2L_MIN)&&(num<J2L_MAX))
                    twoJointsArm_.lowJointGoTo(num);
                  ROS_INFO("twojoints low joints goto");
                }
                else if(motion_ == "high"){
                  //num_ is final result
                  if((J2H_MIN<num_)&&(num_<J2H_MAX)){//J2H_MIN<num_<J2H_MAX can t?
                    twoJointsArm_.highJointGoTo(num_);
                  }

                  ROS_INFO("twojoints high joints goto");
                }

                else if(motion_ == "up"){
                    twoJointsArm_.up();
                    ROS_INFO("twojoints up");
                }
                else if(motion_ == "down"){
                    twoJointsArm_.down();
                    ROS_INFO("twojoints down");
                }
                else if(motion_ == "left"){
                    twoJointsArm_.left();
                    ROS_INFO("twojoints left");
                }
                else if(motion_ == "right"){
                    twoJointsArm_.right();
                    ROS_INFO("twojoints right");
                }
            }

            else if(arm_ == "three"){
              if(motion_ == "go"){
                threeJointsArm_.go();
                ROS_INFO("threej go");
              }else if(motion_ == "back"){
                threeJointsArm_.back();
                ROS_INFO("threej back");
              }else if(motion_ == "enable"){
                threeJointsArm_.enable();
                ROS_INFO("threej enable");
              }else if(motion_ == "disable"){
                threeJointsArm_.disable();
                ROS_INFO("threej disable");
              }
            }
            */
            car_ = "hhh";
        }

        ros::spinOnce();
        loop_rate_.sleep();
    }
    
}

void Boss::arm_cmd_callback(const motion_msgs::MotionConstPtr &cmd)
{
     arm_ = cmd->arm;
     car_ = cmd->car;
     motion_ = cmd->motion;
     num_ = cmd->num;//

}
