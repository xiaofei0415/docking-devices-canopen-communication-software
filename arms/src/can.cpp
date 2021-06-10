#include "arms/can.h"
#include "arms/controlcan.h"
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#define DevType 3
#define DevIdx 0
#define CANINDEX 0
#define NODE_NUM 0//TO MODIFY

bool ControlCan::init(){
    if (!VCI_OpenDevice(DevType, DevIdx, 0)) {
        printf("VCI_OpenDevice failed\n");
        return false;
    }
    int Baud = 0x1c00;//大小写有关系吗
    VCI_INIT_CONFIG config;
    config.AccCode = 0;
    config.AccMask = 0xffffffff;
    config.Filter = 1;
    config.Mode = 0;
    config.Timing0 = Baud & 0xff;
    config.Timing1 = (Baud >> 8)& 0xff;

    if (!VCI_InitCAN(DevType, DevIdx, CANINDEX, &config))
    {
        printf("VCI_InitCAN failed\n");
        return false;
    }

    if (!VCI_StartCAN(DevType, DevIdx, CANINDEX))
    {
        printf("VCI_StartCAN failed\n");
        return false;
    }
    return true;
}

void ControlCan::close(){
    VCI_CloseDevice(DevType, DevIdx);
}

int ControlCan::send(VCI_CAN_OBJ *can, int len)//函数定义出也可以写默认参数吗？
{
   return VCI_Transmit(DevType, DevIdx, CANINDEX, can, len);
}

int ControlCan::receive(VCI_CAN_OBJ *can, int len, int wait_time)
{
    return VCI_Receive(DevType, DevIdx, CANINDEX, can, len, wait_time);
}

void ControlCan::clearBuffer()
{
    VCI_ClearBuffer(DevType, DevIdx, CANINDEX);
}

int ControlCan::getBufferNum()
{
    return VCI_GetReceiveNum(DevType, DevIdx, CANINDEX);
}


bool ControlCan::startNMT()
{
    clearBuffer();
    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ;
    can_frame->ID=0x000;
    can_frame->DataLen=2;
    can_frame->Data[0]=0x01;
    can_frame->Data[1]=0x00;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    send(can_frame);
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));
    if(getBufferNum() != NODE_NUM){
        delete can_frame;
        clearBuffer(); 
        return false;
    }
    delete can_frame;
    clearBuffer(); 

    return true;   
}
