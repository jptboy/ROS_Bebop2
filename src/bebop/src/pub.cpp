#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <unistd.h>
#include <sstream>
#include "../include/bebop/foo.h"
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
static inline void prompt()
{
    std::cout 
        << "|---------------------------------------------|\n"
        << "|            Bebop 2 Keyboard Control:        |\n"
        << "| Takeoff: r | Land  f    |         |         |\n"
        << "| Forward: w | Back: s    | Left: a | Right: d|\n"
        << "|            | RotateL: j | RotR: k |         |\n"
        << "|            | Quit:    q |         |         |\n"
        << "|---------------------------------------------|\n";
}

int main(int argc, char** argv)
{
    ros::init(argc,argv,"talker");
    ros::NodeHandle n;
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
            case 'w'://forward
                break;
            case 'a'://left
                break;
            case 's'://backwards
                break;
            case 'd'://right
                break;
            case 'j'://rotate left
                break;
            case 'k'://rotate right
                break;
            case 'q':
                break;
            default:
                std::cout << "Please enter a valid option!";
        }
    }while(opt!='q');
    

    
    return 0;
}