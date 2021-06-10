/**
 * 该例程将订阅keys话题，消息类型String
 */
 
#include "ros/ros.h"
#include "std_msgs/String.h"

// 接收到订阅的消息后，会进入消息回调函数
void keysCallback(const std_msgs::String::ConstPtr& msg)
{
  // 将接收到的消息打印出来
  
  char* result = (char*)msg->data.c_str();  /*c_str()，它返回const char*类型，不能修改指向的内容（但是可以强制类型转换成char*类型），并且实际上返回string内部那个数组的首地址的一个指针，并且数组末尾有'\0'。*/
  switch(result[0])
  {
	case 'i':
		ROS_INFO("Slave: Forward!");
		break;
	case ',':
		ROS_INFO("Slave: Back away!");
		break;
	case 'j':
		ROS_INFO("Slave: Turn left!");
		break;
	case 'l':
		ROS_INFO("Slave: Turn right!");
		break;
	case 'k':
		ROS_INFO("Slave: Stop!");
		break;
	default:
		//ROS_INFO("error~");		
		break;
  }
  // ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
  // 初始化ROS节点
  ros::init(argc, argv, "remote_subscriber_Slave");

  // 创建节点句柄
  ros::NodeHandle n;

  // 创建一个Subscriber，订阅名为keys的topic，注册回调函数keysCallback
  ros::Subscriber sub = n.subscribe("keys", 1000, keysCallback);

  // 循环等待回调函数
  ros::spin();

  return 0;
}
