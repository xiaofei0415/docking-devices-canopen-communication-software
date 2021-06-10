#ifndef CAN_H
#define CAN_H
#include "arms/controlcan.h"
class ControlCan
{
public:
    /*
    初始化can设备
    
    */   
    bool init();

    bool startNMT();

    
    void close();

    int send(VCI_CAN_OBJ *can, int len = 1);
    //block mode read one frame
    int receive(VCI_CAN_OBJ *can, int len = 1, int wait_time = 200);

    void clearBuffer();

    int getBufferNum();

private:

};

extern ControlCan can;
#endif
