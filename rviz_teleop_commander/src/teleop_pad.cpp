#include <stdio.h>

#include <QPainter>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <std_msgs/String.h>
#include <moveit_msgs/RobotState.h>

#include <QDebug>

#include "teleop_pad.h"

namespace rviz_teleop_commander
{

// 构造函数，初始化变量
TeleopPanel::TeleopPanel( QWidget* parent )
  : rviz::Panel( parent )

{
    // 创建一个输入topic命名的窗口
    QVBoxLayout* topic_layout = new QVBoxLayout;
    topic_layout->addWidget( new QLabel( "choose car:" ));

    box = new QComboBox;
    box->clear();
    QStringList str;
    str<<"CAR1"<<"CAR2"<<"CAR3"<<"CAR4";
    box->addItems(str);
    topic_layout->addWidget(box);
    // 的窗口
    topic_layout->addWidget( new QLabel( "TwoJointsArm:" ));
    start = new QPushButton(tr("START"));
    topic_layout->addWidget( new QLabel( "lowJointGoTo:" ));
    slider1 = new QSlider;
   slider1->setOrientation(Qt::Horizontal);
    topic_layout->addWidget( slider1 );

    topic_layout->addWidget( new QLabel( "highJointGoTo:" ));
    slider2 = new QSlider;
    slider2->setOrientation(Qt::Horizontal);
    topic_layout->addWidget( slider2 );

    topic_layout->addWidget( new QLabel( "ThreeJointsArm:" ));
    go = new QPushButton(tr("GO"));
    topic_layout->addWidget( go);
    back = new QPushButton(tr("BACK"));
    topic_layout->addWidget( back);

    topic_layout->addWidget( new QLabel( "backMouth:" ));
    close1 = new QPushButton(tr("CLOSE"));
    topic_layout->addWidget( close1);
    open1 = new QPushButton(tr("OPEN"));
    topic_layout->addWidget( open1);

    topic_layout->addWidget( new QLabel( "sideMouth:" ));
    close2 = new QPushButton(tr("CLOSE"));
    topic_layout->addWidget( close2);
    open2 = new QPushButton(tr("OPEN"));
    topic_layout->addWidget( open2);


    QHBoxLayout* layout = new QHBoxLayout;
    layout->addLayout( topic_layout );
    setLayout( layout );

    // 设置信号与槽的连接

    connect( start, SIGNAL( clicked() ), this, SLOT( sendMsg() ));
    connect( go, SIGNAL( clicked() ), this, SLOT( resetInput() ));
    publisher_ = nh_.advertise<std_msgs::String>( "arm_cmd_topic", 1000 );
}



// 发布消息
void TeleopPanel::sendMsg()
{
    if( ros::ok() && publisher_ )
    {
        std_msgs::String msg;

        publisher_.publish( msg );
    }
}
void TeleopPanel::resetInput()
{

}
// 重载父类的功能
void TeleopPanel::save( rviz::Config config ) const
{
    rviz::Panel::save( config );
}

// 重载父类的功能，加载配置数据
void TeleopPanel::load( const rviz::Config& config )
{
    rviz::Panel::load( config );

}

} // end namespace rviz_teleop_commander

// 声明此类是一个rviz的插件
#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(rviz_teleop_commander::TeleopPanel,rviz::Panel )
// END_TUTORIAL
