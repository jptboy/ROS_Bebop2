#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>

static const int ERR = -1;
static const int TAKEOFF = 1;
void takeoff(ros::NodeHandle& n)
{
    std_msgs::Empty takeoffmsg;
    ros::Publisher takeoff = n.advertise<std_msgs::Empty>("/bebop/takeoff",1);
    sleep(1);
    takeoff.publish(takeoffmsg);
    sleep(1);
    takeoff.~Publisher();
}
void land(ros::NodeHandle& n)
{
    std_msgs::Empty takeoffmsg;
    ros::Publisher takeoff = n.advertise<std_msgs::Empty>("/bebop/land",1);
    sleep(1);
    takeoff.publish(takeoffmsg);
    sleep(1);
    takeoff.~Publisher();
}
int main(int argc, char** argv)
{  
    ros::init(argc,argv,"pubber");
    ros::NodeHandle n;
    if(argc != 2)
    {
        std::cerr << "Error Please Include Arg\n";
        return ERR;
    }
    auto cmd = std::stoi(argv[1]);
    switch(cmd)
    {
        case 1:
        {
            takeoff(n);
            break;
        }
        case 2:
        {
            land(n);
            break;
        }
        default:
        {
            std::cerr << "Eror, please input valid command!\n";
            break;
        }
    }
        
}