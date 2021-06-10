#include <ros/ros.h>
#include <motion_msgs/Motion.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <string>
#include <std_msgs/String.h>

#define KEYCODE_R 0x43 
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_G 103
#define KEYCODE_H 104
#define KEYCODE_B 98
#define KEYCODE_V 118
#define KEY_ENTER 10

class TeleopTurtle
{
public:
  TeleopTurtle();
  void keyLoop();

private: 
  ros::NodeHandle nh_;
  ros::Publisher twist_pub_;
  ros::Publisher car_pub_;
  
};

TeleopTurtle::TeleopTurtle()
{
  
  twist_pub_ = nh_.advertise<motion_msgs::Motion>("arm_cmd_topic", 1000);
  car_pub_ = nh_.advertise<std_msgs::String>("keys", 1000);
}

int kfd =0;
struct termios cooked, raw;

void quit(int sig)
{
  (void)sig;
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "remote_publisher");
  TeleopTurtle teleop_turtle;

  signal(SIGINT,quit);

  teleop_turtle.keyLoop();
  
  return(0);
}

void TeleopTurtle::keyLoop()
{
  char c;
  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Press any keys to see what happen.");
  //pkg_template::Try msg;
  motion_msgs::Motion msg;

  int i = 0;
  int j = 0;
  for(;;)
  {
    // get the next event from the keyboard  
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

    if(c == KEYCODE_L){
      if(msg.arm == "twoj")     
        msg.motion="left";   
      else if(msg.arm == "three")
        msg.motion = "disable";
      else if (msg.arm == "side" || msg.arm == "back")
        msg.motion = "close";   
      ROS_INFO("Now: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
    }
      else if(c == KEYCODE_R){
        if(msg.arm == "twoj")     
          msg.motion="right";   
        else if(msg.arm == "three")
          msg.motion = "enable";
        else if (msg.arm == "side" || msg.arm == "back")
          msg.motion = "open";   
        ROS_INFO("Now: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
      }      
      else if(c == KEYCODE_U){
          if(msg.arm == "twoj")     
          msg.motion="up";   
        else if(msg.arm == "three")
          msg.motion = "go";
        
        ROS_INFO("Now: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
       }
      else if(c == KEYCODE_D){
        if(msg.arm == "twoj")     
          msg.motion="down";   
        else if(msg.arm == "three")
          msg.motion = "back";
        ROS_INFO("Now: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
      }
   
    else if(c == KEYCODE_B){
      if(msg.arm == "twoj")    
        msg.motion="start";
      ROS_INFO("Now: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
    }
    else if(c == KEYCODE_V){
      if(msg.arm == "twoj")    
        msg.motion="disable";
      ROS_INFO("Now: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
     }
     else if(c == 't'){
        i++;
        if(i==5) i = 1;
        std::string car = "car";
        msg.car = car + std::to_string(i);
        ROS_INFO("Now: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
     }
     else if(c == 'y'){
        j++;
        if(j == 5) j = 1;
        if(j == 1) msg.arm = "twoj";
        else if(j==2) msg.arm = "three";
        else if(j == 3) msg.arm = "back";
        else msg.arm = "side";
        ROS_INFO("Now: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
     }
     else if(c == KEY_ENTER){
        twist_pub_.publish(msg);
        ROS_INFO("Send: %s %s %s", msg.car.c_str(), msg.arm.c_str(), msg.motion.c_str()); 
     }
    else{
        if(c != '[' && c!='\e'){
             std_msgs::String msg;
            msg.data = c;
            car_pub_.publish(msg);
        }   
    }
  }
}
