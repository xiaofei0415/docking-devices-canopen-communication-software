# my-arms
# 运行方式
1-	打开Ubuntu终端Terminal，运行：roscore；

2-	连接好所有硬件，在新终端中输入：rosrun arms arm_cmd_sub_node；若硬件初始化启动成功，则底层通信和控制系统成功运行

![image](https://user-images.githubusercontent.com/80371110/121506071-fa749380-ca15-11eb-9981-fcbd6b3bf8d5.png)

3-	在新终端中输入：roslaunch arm_vision ar_track_camera.launch 启动视觉引导功能；

4-	在ROS rviz菜单栏中依次选择Panels->Add New Panel，打开TeleopPannel插件，可进行手动遥控；

 ![image](https://user-images.githubusercontent.com/80371110/121506025-f21c5880-ca15-11eb-97ce-b04ea18da9b4.png)
 
 # 介绍
 
运动控制系统接口

![image](https://user-images.githubusercontent.com/80371110/121506266-255ee780-ca16-11eb-92fd-d35bfb647b5b.png)
![image](https://user-images.githubusercontent.com/80371110/121506282-2859d800-ca16-11eb-934b-6b747f5e6242.png)
![image](https://user-images.githubusercontent.com/80371110/121506291-2b54c880-ca16-11eb-8111-3007f9f78711.png)

can通信类

![image](https://user-images.githubusercontent.com/80371110/121506339-33ad0380-ca16-11eb-98a5-aefafbcb1697.png)

表示运动控制总类及与各类的组合关系的UML类图

![image](https://user-images.githubusercontent.com/80371110/121506433-46273d00-ca16-11eb-8fef-27c53bda3334.png)

视觉自动引导对准功能

![image](https://user-images.githubusercontent.com/80371110/121506486-56d7b300-ca16-11eb-9b55-ae503a2d2871.png)
![image](https://user-images.githubusercontent.com/80371110/121506500-59d2a380-ca16-11eb-9dec-8f0758785738.png)

远程遥控终端

![image](https://user-images.githubusercontent.com/80371110/121506560-6820bf80-ca16-11eb-963c-c4647a7b05d9.png)
![image](https://user-images.githubusercontent.com/80371110/121506576-6c4cdd00-ca16-11eb-9018-bdeb3bc66f33.png)
