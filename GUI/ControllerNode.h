#include <math.h>
#include <cmath>
#include <ros/ros.h>
#include </opt/ros/indigo/include/ros/ros.h>
#include <ardrone_autonomy/Navdata.h>
#include <nav_msgs/Odometry.h>
#include <iomanip>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Imu.h>
#include <ros/callback_queue.h>

class ControllerNode {

    ros::NodeHandle nh;
    ros::Subscriber gr_sub;
    ros::Subscriber nav_sub;
    ros::Publisher vel_pub;

public:

    ControllerNode();
    void Control();
    double CalculateYaw(double x, double y, double z, double w);
    void run();
    void MoveTo(double x, double y);
    void Hover();
    void goal_callback(const nav_msgs::Odometry & msg);

private:
    double x, y, z, w;
    double current_x_coord, current_y_coord;
    double goal_x, goal_y;
};
