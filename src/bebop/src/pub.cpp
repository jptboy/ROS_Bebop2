#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <unistd.h>
#include <sstream>
#include "../include/bebop/dependencies.h"
// int main(int argc, char** argv)
// {
//     std::cout << "Press l(land) or press t(takeoff)\n";
//     std::string opt;
//     std::cin >> opt;
//     printf("You chose option: %s\n",opt.c_str());
//     ros::init(argc,argv,"talker");
//     ros::NodeHandle n;
//     std_msgs::Empty myMsg;
//     std::string properopt = ((opt=="t")?"/bebop/takeoff":"/bebop/land");
//     sleep(1);
//     ros::Publisher takeOff = n.advertise<std_msgs::Empty>(properopt,1);
//     sleep(1);
//     //std::cout << "mane\n";
//     takeOff.publish(myMsg);
//     ros::spinOnce();
//     return 0;

// }
static double velVal = 5.0;
static inline void prompt()
{
    std::cout 
        << "|---------------------------------------------|\n"
        << "|            Bebop 2 Keyboard Control:        |\n"
        << "| Takeoff: r | Land  f    |         |         |\n"
        << "| Forward: w | Back: s    | Left: a | Right: d|\n"
        << "|            | RotateL: j | RotR: k |         |\n"
        << "|            | Ascend : z | Desc: x |         |\n"
        << "|            | Quit:    q |         |         |\n"
        << "|---------------------------------------------|\n";
}
void flyingStateHandler()
{
    printf("foo\n");
}
int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "Please provide a velocity value!\n";
        std::cout << "Usage talker velVal\n";
        return 0;
    }
    ros::init(argc,argv,"talker");
    ros::NodeHandle n;
    try
    {
        velVal = std::stod(argv[1]);
    }
    catch(...)
    {
        std::cerr << "Please provide a valid velocity value!\n";
        std::cout << "Usage: talker velVal\n";
        return 0;
    }
    char opt;
    do
    {
        prompt();
        std::cin >> opt;
        (opt != 'q') ? printf("You selected option: %c\n", opt) : printf("Quitting\n");
        sleep(1);//sleep for 1 second to avoid race
        switch(opt)
        {
            case 'r'://takeoff
            {
                std_msgs::Empty emptyMsg;
                ros::Publisher takeOff = n.advertise<std_msgs::Empty>("/bebop/takeoff",1);
                
                sleep(1);
                takeOff.publish(emptyMsg);
                sleep(1);
                takeOff.~Publisher();//you need to destroy publisher before publishing again
                //ros::spinOnce();
                break;
            }    
            case 'f'://land
            {
                std_msgs::Empty emptyMsg;
                ros::Publisher takeOff = n.advertise<std_msgs::Empty>("/bebop/land",1);
                sleep(1);
                takeOff.publish(emptyMsg);
                sleep(1);
                takeOff.~Publisher();
                //ros::spinOnce();
                break;
            }
            //publish geometry_msgs/Twist to /bebop/cmd_vel topic while bebop is flying to move it
            case 'w'://forward
            {
                geometry_msgs::Twist twistMsg;
                twistMsg.linear.x = velVal;
                ros::Publisher takeOff = n.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);
                sleep(1);
                ros::Time begin = ros::Time::now();
                ros::Duration seconds = ros::Duration(3);
                ros::Time endTime = begin + seconds;
                while(ros::Time::now() < endTime) takeOff.publish(twistMsg);
                sleep(1);
                takeOff.~Publisher();
                break;
            }
            case 'a':
            {//left
                geometry_msgs::Twist twistMsg;
                twistMsg.linear.y = velVal;
                ros::Publisher takeOff = n.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);
                sleep(1);
                ros::Time begin = ros::Time::now();
                ros::Duration seconds = ros::Duration(3);
                ros::Time endTime = begin + seconds;
                while(ros::Time::now() < endTime) takeOff.publish(twistMsg);
                sleep(1);
                takeOff.~Publisher();
                break;
            }
            case 's'://backwards
            {
                geometry_msgs::Twist twistMsg;
                twistMsg.linear.x = -1*velVal;
                ros::Publisher takeOff = n.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);
                sleep(1);
                ros::Time begin = ros::Time::now();
                ros::Duration seconds = ros::Duration(3);
                ros::Time endTime = begin + seconds;
                while(ros::Time::now() < endTime) takeOff.publish(twistMsg);
                sleep(1);
                takeOff.~Publisher();
                break;
            }
            case 'd'://right
            {
                geometry_msgs::Twist twistMsg;
                twistMsg.linear.y = -1*velVal;
                ros::Publisher takeOff = n.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);
                sleep(1);
                ros::Time begin = ros::Time::now();
                ros::Duration seconds = ros::Duration(3);
                ros::Time endTime = begin + seconds;
                while(ros::Time::now() < endTime) takeOff.publish(twistMsg);
                sleep(1);
                takeOff.~Publisher();
                break;
            }
            case 'j'://rotate ccw
            {
                geometry_msgs::Twist twistMsg;
                twistMsg.angular.z = velVal;
                ros::Publisher takeOff = n.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);
                sleep(1);
                ros::Time begin = ros::Time::now();
                ros::Duration seconds = ros::Duration(3);
                ros::Time endTime = begin + seconds;
                while(ros::Time::now() < endTime) takeOff.publish(twistMsg);
                sleep(1);
                takeOff.~Publisher();
                break;
            }
            case 'k'://rotate cw
            {
                geometry_msgs::Twist twistMsg;
                twistMsg.angular.z = -1*velVal;
                ros::Publisher takeOff = n.advertise<geometry_msgs::Twist>("/bebop/cmd_vel",1);
                sleep(1);
                ros::Time begin = ros::Time::now();
                ros::Duration seconds = ros::Duration(3);
                ros::Time endTime = begin + seconds;
                while(ros::Time::now() < endTime) takeOff.publish(twistMsg);
                sleep(1);
                takeOff.~Publisher();
                break;
            }
            case 'q':
            {
                //check if drone is flying and if so land it
                bebop_msgs::Ardrone3PilotingStateFlyingStateChanged flyingState;
                //ros::Subscriber sub = n.subscribe("/bebop/states/ardrone3/PilotingState/FlyingStateChanged",1000,flyingStateHandler);
                break;
            }
            default:
                std::cout << "Please enter a valid option!";
        }
    }while(opt!='q');
    

    
    return 0;
}