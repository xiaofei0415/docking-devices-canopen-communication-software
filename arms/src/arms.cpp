#include "arms/arms.h"
#include "arms/consts.h"
#include "arms/can.h"
Mouth::Mouth(int id, int close, int open):id_(id),close_(close),open_(open)
{
}

void Mouth::init()
{

    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
    can_frame->ID=0x300+id_;//MO=0 necessary?
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x00;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+id_;//UM=5
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x55;
    can_frame->Data[1] = 0x4d;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x05;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);

    int speed = 500;
    can_frame->ID=0x300+id_;//SP=500
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x53;
    can_frame->Data[1] = 0x50;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = speed&0xff;
    can_frame->Data[5] = (speed>>8)&0xff;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);

    delete can_frame;

}

void Mouth::open()
{
    can.clearBuffer();
    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
    //MO=1
    can_frame->ID=0x300+id_;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x01;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    //PA=Open
    can_frame->ID=0x300+id_;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x50;
    can_frame->Data[1] = 0x41;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = open_&0xff;
    can_frame->Data[5] = (open_>>8)&0xff;
    can_frame->Data[6] = (open_>>16)&0xff;
    can_frame->Data[7] = (open_>>24)&0xff;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+id_;//BG
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x42;
    can_frame->Data[1] = 0x47;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    //wait
    int i = 0;
    while(1){
      if(++i >= 10) {
        can_frame->ID=0x300+id_;//ST
        can_frame->SendType=0;
        can_frame->ExternFlag=0;
        can_frame->DataLen=4;
        can_frame->Data[0] = 0x53;
        can_frame->Data[1] = 0x54;
        can_frame->Data[2] = 0x00;
        can_frame->Data[3] = 0x00;
        can.send(can_frame);
        can.receive(can_frame);
        break;
      }
      can.receive(can_frame);//wait
      if((can_frame->ID == 0x180+id_) && can_frame->Data[0]==0x37 &&can_frame->Data[1]==0x16) break;
    }

    //wait still,MO=0
    can_frame->ID=0x300+id_;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x00;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
}

void Mouth::close()
{
  can.clearBuffer();
  VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
  //MO=1
  can_frame->ID=0x300+id_;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x01;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  //PA=Close
  can_frame->ID=0x300+id_;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = close_&0xff;
  can_frame->Data[5] = (close_>>8)&0xff;
  can_frame->Data[6] = (close_>>16)&0xff;
  can_frame->Data[7] = (close_>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+id_;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);
  //wait
  int i = 0;
      while(1){
        if(++i >=10) {
          can_frame->ID=0x300+id_;//ST
          can_frame->SendType=0;
          can_frame->ExternFlag=0;
          can_frame->DataLen=4;
          can_frame->Data[0] = 0x53;
          can_frame->Data[1] = 0x54;
          can_frame->Data[2] = 0x00;
          can_frame->Data[3] = 0x00;
          can.send(can_frame);
          can.receive(can_frame);
          break;
        }
        can.receive(can_frame);//wait
        if((can_frame->ID == 0x180+id_) && can_frame->Data[0]==0x37 &&can_frame->Data[1]==0x16) break;
      }
  //wait still,MO=0
  can_frame->ID=0x300+id_;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x00;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);
}

TwoJointsArm::TwoJointsArm(int ori1, int ori2):lpos_(ori1),hpos_(ori2)
{
  is_start = false;
}
void TwoJointsArm::init()
{
  can.clearBuffer();
  VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
  can_frame->ID=0x300+J2LID;//MO=0 necessary?
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x00;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J2LID;//UM=5
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x55;
  can_frame->Data[1] = 0x4d;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x05;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  int speed = 500;
  can_frame->ID=0x300+J2LID;//SP=500
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x53;
  can_frame->Data[1] = 0x50;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = speed&0xff;
  can_frame->Data[5] = (speed>>8)&0xff;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J2HID;//
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x00;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J2HID;//UM=5
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x55;
  can_frame->Data[1] = 0x4d;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x05;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  speed = 400;
  can_frame->ID=0x300+J2HID;//SP=400
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x53;
  can_frame->Data[1] = 0x50;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = speed&0xff;
  can_frame->Data[5] = (speed>>8)&0xff;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  delete can_frame;

}

void TwoJointsArm::start()
{
  if(!is_start){

  //low joint and hign joint move to original pos
  can.clearBuffer();
  VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
  can_frame->ID=0x300+J2LID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x01;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J2LID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = J2L_ORI&0xff;
  can_frame->Data[5] = (J2L_ORI>>8)&0xff;
  can_frame->Data[6] = (J2L_ORI>>16)&0xff;
  can_frame->Data[7] = (J2L_ORI>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J2LID;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);
  int i = 0;
  while(1){
    if(++i >=10) break;
    can.receive(can_frame);//wait
    if((can_frame->ID == 0x180+J2LID) && can_frame->Data[0]==0x37 &&can_frame->Data[1]==0x16) break;
  }
  can_frame->ID=0x300+J2HID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x01;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J2HID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = J2H_ORI&0xff;
  can_frame->Data[5] = (J2H_ORI>>8)&0xff;
  can_frame->Data[6] = (J2H_ORI>>16)&0xff;
  can_frame->Data[7] = (J2H_ORI>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J2HID;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);
  delete can_frame;
  is_start = true;
   }
}

void TwoJointsArm::disable()
{//we can send stop first
  if(is_start){
    can.clearBuffer();
    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();

    can_frame->ID=0x300+J2LID;//ST
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x53;
    can_frame->Data[1] = 0x54;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J2HID;//ST
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x53;
    can_frame->Data[1] = 0x54;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J2LID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x00;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J2HID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x00;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    delete can_frame;
    is_start=false;
  }
}

void TwoJointsArm::lowJointGoTo(int num)
{
  if(is_start){
    can.clearBuffer();
    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
    can_frame->ID=0x300+J2LID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x50;
    can_frame->Data[1] = 0x41;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = num&0xff;
    can_frame->Data[5] = (num>>8)&0xff;
    can_frame->Data[6] = (num>>16)&0xff;
    can_frame->Data[7] = (num>>24)&0xff;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J2LID;//BG
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x42;
    can_frame->Data[1] = 0x47;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    lpos_ = num;
    delete can_frame;
  }
}

void TwoJointsArm::highJointGoTo(int num)
{
  if(is_start){
    can.clearBuffer();
    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
    can_frame->ID=0x300+J2HID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x50;
    can_frame->Data[1] = 0x41;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = num&0xff;
    can_frame->Data[5] = (num>>8)&0xff;
    can_frame->Data[6] = (num>>16)&0xff;
    can_frame->Data[7] = (num>>24)&0xff;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J2HID;//BG
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x42;
    can_frame->Data[1] = 0x47;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    hpos_ = num;
    delete can_frame;
  }
}
void TwoJointsArm::up()
{
  if(is_start)
  {

    if(hpos_+J2H_STEP <J2H_MAX){
      hpos_ += J2H_STEP;
      can.clearBuffer();
      VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
      can_frame->ID=0x300+J2HID;
      can_frame->SendType=0;
      can_frame->ExternFlag=0;
      can_frame->DataLen=8;
      can_frame->Data[0] = 0x50;
      can_frame->Data[1] = 0x41;
      can_frame->Data[2] = 0x00;
      can_frame->Data[3] = 0x00;
      can_frame->Data[4] = hpos_&0xff;
      can_frame->Data[5] = (hpos_>>8)&0xff;
      can_frame->Data[6] = (hpos_>>16)&0xff;
      can_frame->Data[7] = (hpos_>>24)&0xff;
      can.send(can_frame);
      can.receive(can_frame);

      can_frame->ID=0x300+J2HID;//BG
      can_frame->SendType=0;
      can_frame->ExternFlag=0;
      can_frame->DataLen=4;
      can_frame->Data[0] = 0x42;
      can_frame->Data[1] = 0x47;
      can_frame->Data[2] = 0x00;
      can_frame->Data[3] = 0x00;
      can.send(can_frame);
      can.receive(can_frame);
      //can.receive(can_frame);
      delete can_frame;
    }
  }
}

void TwoJointsArm::down()
{
  if(is_start)
  {

  if(hpos_-J2H_STEP >J2H_MIN){
    hpos_ -= J2H_STEP;
    can.clearBuffer();
    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
    can_frame->ID=0x300+J2HID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x50;
    can_frame->Data[1] = 0x41;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = hpos_&0xff;
    can_frame->Data[5] = (hpos_>>8)&0xff;
    can_frame->Data[6] = (hpos_>>16)&0xff;
    can_frame->Data[7] = (hpos_>>24)&0xff;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J2HID;//BG
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x42;
    can_frame->Data[1] = 0x47;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    //can.receive(can_frame);
    delete can_frame;
  }
  }
}

void TwoJointsArm::left()
{
  if(is_start)
  {

    if(lpos_-J2L_STEP >J2L_MIN){
      lpos_ -= J2L_STEP;
      can.clearBuffer();
      VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
      can_frame->ID=0x300+J2LID;
      can_frame->SendType=0;
      can_frame->ExternFlag=0;
      can_frame->DataLen=8;
      can_frame->Data[0] = 0x50;
      can_frame->Data[1] = 0x41;
      can_frame->Data[2] = 0x00;
      can_frame->Data[3] = 0x00;
      can_frame->Data[4] = lpos_&0xff;
      can_frame->Data[5] = (lpos_>>8)&0xff;
      can_frame->Data[6] = (lpos_>>16)&0xff;
      can_frame->Data[7] = (lpos_>>24)&0xff;
      can.send(can_frame);
      can.receive(can_frame);

      can_frame->ID=0x300+J2LID;//BG
      can_frame->SendType=0;
      can_frame->ExternFlag=0;
      can_frame->DataLen=4;
      can_frame->Data[0] = 0x42;
      can_frame->Data[1] = 0x47;
      can_frame->Data[2] = 0x00;
      can_frame->Data[3] = 0x00;
      can.send(can_frame);
      can.receive(can_frame);
      //can.receive(can_frame);
      delete can_frame;
    }
  }
}

void TwoJointsArm::right()
{
  if(is_start)
  {

    if(lpos_+J2L_STEP <J2L_MAX){
      lpos_ += J2L_STEP;
      can.clearBuffer();
      VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
      can_frame->ID=0x300+J2LID;
      can_frame->SendType=0;
      can_frame->ExternFlag=0;
      can_frame->DataLen=8;
      can_frame->Data[0] = 0x50;
      can_frame->Data[1] = 0x41;
      can_frame->Data[2] = 0x00;
      can_frame->Data[3] = 0x00;
      can_frame->Data[4] = lpos_&0xff;
      can_frame->Data[5] = (lpos_>>8)&0xff;
      can_frame->Data[6] = (lpos_>>16)&0xff;
      can_frame->Data[7] = (lpos_>>24)&0xff;
      can.send(can_frame);
      can.receive(can_frame);

      can_frame->ID=0x300+J2LID;//BG
      can_frame->SendType=0;
      can_frame->ExternFlag=0;
      can_frame->DataLen=4;
      can_frame->Data[0] = 0x42;
      can_frame->Data[1] = 0x47;
      can_frame->Data[2] = 0x00;
      can_frame->Data[3] = 0x00;
      can.send(can_frame);
      can.receive(can_frame);
      //can.receive(can_frame);
      delete can_frame;
    }
  }
}

ThreeJointsArm::ThreeJointsArm(){
  is_enable = false;
}

void ThreeJointsArm::go(){
  if(!is_enable)
    enable();
  can.clearBuffer();
  VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
  can_frame->ID=0x300+J3BID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = J3B_OK&0xff;
  can_frame->Data[5] = (J3B_OK>>8)&0xff;
  can_frame->Data[6] = (J3B_OK>>16)&0xff;
  can_frame->Data[7] = (J3B_OK>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3BID;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3LID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = J3L_OK&0xff;
  can_frame->Data[5] = (J3L_OK>>8)&0xff;
  can_frame->Data[6] = (J3L_OK>>16)&0xff;
  can_frame->Data[7] = (J3L_OK>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3LID;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3HID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = J3B_OK&0xff;
  can_frame->Data[5] = (J3H_OK>>8)&0xff;
  can_frame->Data[6] = (J3H_OK>>16)&0xff;
  can_frame->Data[7] = (J3H_OK>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3HID;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  delete can_frame;
}

void ThreeJointsArm::back(){
  if(!is_enable)
    enable();

  can.clearBuffer();
  VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
  can_frame->ID=0x300+J3BID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = J3B_ORI&0xff;
  can_frame->Data[5] = (J3B_ORI>>8)&0xff;
  can_frame->Data[6] = (J3B_ORI>>16)&0xff;
  can_frame->Data[7] = (J3B_ORI>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3BID;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3LID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = J3L_ORI&0xff;
  can_frame->Data[5] = (J3L_ORI>>8)&0xff;
  can_frame->Data[6] = (J3L_ORI>>16)&0xff;
  can_frame->Data[7] = (J3L_ORI>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3LID;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3HID;
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x50;
  can_frame->Data[1] = 0x41;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = J3H_ORI&0xff;
  can_frame->Data[5] = (J3H_ORI>>8)&0xff;
  can_frame->Data[6] = (J3H_ORI>>16)&0xff;
  can_frame->Data[7] = (J3H_ORI>>24)&0xff;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3HID;//BG
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=4;
  can_frame->Data[0] = 0x42;
  can_frame->Data[1] = 0x47;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);
  can.receive(can_frame);

  int i = 0;
  int j = 0;
  while(1){
    if(++i >=20) break;
    can.receive(can_frame);//wait
    if((can_frame->ID == 0x180+J3LID) && can_frame->Data[0]==0x37 &&can_frame->Data[1]==0x16) j++;
    if((can_frame->ID == 0x180+J3HID) && can_frame->Data[0]==0x37 &&can_frame->Data[1]==0x16) j++;
    if(j==2) break;
  }

  delete can_frame;

  disable();

}

void ThreeJointsArm::init(){
  can.clearBuffer();
  VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
  can_frame->ID=0x300+J3BID;//MO=0
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x00;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3BID;//UM=5
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x55;
  can_frame->Data[1] = 0x4d;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x05;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  int speed = 2000;
  can_frame->ID=0x300+J3BID;//SP=500
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x53;
  can_frame->Data[1] = 0x50;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = speed&0xff;
  can_frame->Data[5] = (speed>>8)&0xff;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3LID;//MO=0
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x00;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3LID;//UM=5
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x55;
  can_frame->Data[1] = 0x4d;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x05;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

   speed = 2000;
  can_frame->ID=0x300+J3LID;//SP=500
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x53;
  can_frame->Data[1] = 0x50;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = speed&0xff;
  can_frame->Data[5] = (speed>>8)&0xff;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3HID;//MO=0
  can_frame->SendType=0;
  can_frame->ExternFlag=0;
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x4d;
  can_frame->Data[1] = 0x4f;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x00;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  can_frame->ID=0x300+J3HID;//UM=5
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x55;
  can_frame->Data[1] = 0x4d;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = 0x05;
  can_frame->Data[5] = 0x00;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

   speed = 2000;
  can_frame->ID=0x300+J3HID;//SP=500
  can_frame->DataLen=8;
  can_frame->Data[0] = 0x53;
  can_frame->Data[1] = 0x50;
  can_frame->Data[2] = 0x00;
  can_frame->Data[3] = 0x00;
  can_frame->Data[4] = speed&0xff;
  can_frame->Data[5] = (speed>>8)&0xff;
  can_frame->Data[6] = 0x00;
  can_frame->Data[7] = 0x00;
  can.send(can_frame);
  can.receive(can_frame);

  delete can_frame;
}

void ThreeJointsArm::enable(){
  if(!is_enable){

    can.clearBuffer();
    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
    can_frame->ID=0x300+J3BID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x01;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J3LID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x01;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J3HID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x01;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    delete can_frame;

    is_enable = true;
  }
}

void ThreeJointsArm::disable(){
  if(is_enable){
    can.clearBuffer();
    VCI_CAN_OBJ *can_frame = new VCI_CAN_OBJ();
    can_frame->ID=0x300+J3BID;//ST
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x53;
    can_frame->Data[1] = 0x54;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J3LID;//ST
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x53;
    can_frame->Data[1] = 0x54;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J3HID;//ST
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=4;
    can_frame->Data[0] = 0x53;
    can_frame->Data[1] = 0x54;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J3BID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x01;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J3LID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x01;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    can_frame->ID=0x300+J3HID;
    can_frame->SendType=0;
    can_frame->ExternFlag=0;
    can_frame->DataLen=8;
    can_frame->Data[0] = 0x4d;
    can_frame->Data[1] = 0x4f;
    can_frame->Data[2] = 0x00;
    can_frame->Data[3] = 0x00;
    can_frame->Data[4] = 0x01;
    can_frame->Data[5] = 0x00;
    can_frame->Data[6] = 0x00;
    can_frame->Data[7] = 0x00;
    can.send(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);
    can.receive(can_frame);

    delete can_frame;

    is_enable = false;
  }
}

