#include "../include/bebop/dependencies.h"
/*
enum {
    state_landed = 0u,
    state_takingoff = 1u,
    state_hovering = 2u,
    state_flying = 3u,
    state_landing = 4u,
    state_emergency = 5u,
    state_usertakeoff = 6u,
    state_motor_ramping = 7u,
    state_emergency_landing = 8u,
  };
  */
void isr(const bebop_msgs::Ardrone3PilotingStateFlyingStateChanged& x)
{   
    printf("%hhu",x.state);
}
int main(int argc, char** argv)
{
    ros::init(argc,argv,"subberFlyingState");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/bebop/states/ardrone3/PilotingState/FlyingStateChanged",1000,isr);
    ros::spin();
}