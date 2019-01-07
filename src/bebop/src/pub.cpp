#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <unistd.h>
#include <sstream>

int main(int argc, char** argv)
{
    std::cout << "Press l(land) or press t(takeoff)\n";
    std::string opt;
    std::cin >> opt;
    printf("You chose option: %s\n",opt.c_str());
    ros::init(argc,argv,"talker");
    ros::NodeHandle n;
    std_msgs::Empty myMsg;
    std::string properopt = ((opt=="t")?"/bebop/takeoff":"/bebop/land");
    sleep(1);
    ros::Publisher takeOff = n.advertise<std_msgs::Empty>(properopt,1);
    sleep(1);
    //std::cout << "mane\n";
    takeOff.publish(myMsg);
    ros::spinOnce();
    return 0;

}