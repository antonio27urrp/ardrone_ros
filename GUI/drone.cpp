#include "mainwindow.h"
#include <ros/ros.h>
#include "drone.h"
#include <ardrone_autonomy/Navdata.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>
#include <iostream>

const char topic[] = "/cmd_vel";
const char reset[] = "/ardrone/reset";
const float persentage_of_cmd_vel = 50;

Drone::Drone(int argc, char** argv ) :
    init_argc(argc),
    init_argv(argv)
    {
    }

Drone::~Drone() {
    if(ros::isStarted()) {
        std::cout<< "" << std::endl; // for soul xD
        ROS_INFO_STREAM("The application was closed --> closing ROS");
        ros::shutdown(); // explicitly needed since we use ros::start();
        ros::waitForShutdown();
    }
    wait();
}

void Drone::forward() {
    publisher = nh.advertise<geometry_msgs::Twist>(topic, 1000,true);
    geometry_msgs::Twist msg;
    msg.linear.x = 1*persentage_of_cmd_vel/100;
    publisher.publish(msg);
}

void Drone::backward() {
    publisher = nh.advertise<geometry_msgs::Twist>(topic, 1000, true);
    geometry_msgs::Twist msg;
    msg.linear.x = -1*persentage_of_cmd_vel/100;
    publisher.publish(msg);
}

void Drone::right() {
    publisher = nh.advertise<geometry_msgs::Twist>(topic, 1000, true);
    geometry_msgs::Twist msg;
    msg.linear.y = 1*persentage_of_cmd_vel/100;
    publisher.publish(msg);
}

void Drone::left() {
    publisher = nh.advertise<geometry_msgs::Twist>(topic, 1000, true);
    geometry_msgs::Twist msg;
    msg.linear.y = -1*persentage_of_cmd_vel/100;
    publisher.publish(msg);
}

void Drone::stop() {
    publisher = nh.advertise<geometry_msgs::Twist>(topic, 1000, true);
    geometry_msgs::Twist msg;
    msg.angular.x = 0;
    msg.angular.y = 0;
    msg.angular.z = 0;
    msg.linear.x = 0;
    msg.linear.y = 0;
    msg.linear.z = 0;
    publisher.publish(msg);
}

void Drone::reset() {
    publisher = nh.advertise<std_msgs::Empty>("/ardrone/reset", 1000, true);
    std_msgs::Empty msg;
    publisher.publish(msg);
}

void Drone::take_off() {
    publisher = nh.advertise<std_msgs::Empty>("/ardrone/takeoff", 1000, true);
    std_msgs::Empty msg;
    publisher.publish(msg);
}

void Drone::land() {
    publisher = nh.advertise<std_msgs::Empty>("/ardrone/land", 1000, true);
    std_msgs::Empty msg;
    publisher.publish(msg);
}
