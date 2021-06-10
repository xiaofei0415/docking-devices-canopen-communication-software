#ifndef BOSS_H
#define BOSS_H
#include "arms/arms.h"
#include "ros/ros.h"
#include "motion_msgs/Motion.h"
#include <string>

class Boss
{
public:
    Boss(std::string carid);
    void keyLoop();
    bool init();
    static void arm_cmd_callback(const motion_msgs::MotionConstPtr &cmd);//???
    ~Boss();
private:
    //Mouth backMouth_;
    //Mouth sideMouth_();
    //TwoJointsArm twoJointsArm_;
    //ThreeJointsArm threeJointsArm_;
    ros::NodeHandle nh_;
    ros::Subscriber sub_;
    std::string carid_;
    ros::Rate loop_rate_;
    static std::string arm_,car_,motion_;
    static int num_;
};
#endif
