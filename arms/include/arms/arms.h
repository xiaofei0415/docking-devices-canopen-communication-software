#ifndef ARMS_H
#define ARMS_H

class Mouth
{
public:
    Mouth(int id, int close, int open);
    void init();

    void open();

    void close();

private:
    int id_;
    int close_;
    int open_;
};

class TwoJointsArm
{
public:
    TwoJointsArm(int ori1, int ori2);
    void init();

    void start();

    void disable();

    void up();

    void down();

    void left();

    void right();

    void highJointGoTo(int num);

    void lowJointGoTo(int num);
 private:
    int lpos_;
    int hpos_;
    bool is_start;


};
class ThreeJointsArm
{
public:
  ThreeJointsArm();
  void init();
  void go();
  void back();
  void enable();
  void disable();

private:
  bool is_enable;
};

#endif
