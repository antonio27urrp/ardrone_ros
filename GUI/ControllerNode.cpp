#include "ControllerNode.h"

ControllerNode::ControllerNode(){

    std::cout << "create drone class" << std::endl;
    gr_sub = nh.subscribe("/ground_truth/state", 1000, &ControllerNode::goal_callback, this);
    vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

}


double ControllerNode::CalculateYaw(double x, double y, double z, double w) {
    double siny = +2.0 * (w * z + x * y);
    double cosy = +1.0 - 2.0 * (y * y + z * z);
    double yaw = atan2(siny, cosy);
    yaw = yaw*180/3.1415;
    if (yaw < 0) {
        yaw = 360+yaw;
    }

    return yaw;
}


void ControllerNode::MoveTo(double x, double y) {

    goal_x = x;
    goal_y = y;
    std::cout << goal_x << std::endl;
    std::cout << goal_y << std::endl;
}


void ControllerNode::Hover() {

    geometry_msgs::Twist velocity;

    velocity.linear.x = 0;
    velocity.linear.y = 0;
    velocity.linear.z = 0;
    velocity.angular.x = 0;
    velocity.angular.y = 0;
    velocity.angular.z = 0;

    vel_pub.publish(velocity);

}


void ControllerNode::Control() {

    while (std::abs(goal_x-current_x_coord) > 0.1 || std::abs(goal_y-current_y_coord) > 0.1){
        gr_sub = nh.subscribe("/ground_truth/state", 1000, &ControllerNode::goal_callback, this);

        double yaw;
        yaw = CalculateYaw(x, y, z, w);

        double length;
        length = std::sqrt((goal_x-current_x_coord)*(goal_x-current_x_coord)
                +(goal_y-current_y_coord)*(goal_y-current_y_coord));

        std::cout << length << std::endl;

        double delta_x, delta_y;
        delta_x = goal_x - current_x_coord;
        delta_y = goal_y - current_y_coord;

        double bearing;
        bearing = atan2(delta_y, delta_x)*180/3.1415;

        double course_angle;
        course_angle = bearing - yaw;

        if (std::abs(course_angle) > 180) course_angle = course_angle -
                                                    course_angle/std::abs(course_angle) * 360;

        std::cout << course_angle << std::endl;

        double base_speed;
        base_speed = 1 * tanh(length) * cos (course_angle);
        if (std::abs(base_speed) > 1) base_speed = base_speed/std::abs(base_speed);
        //if (std::abs(base_speed) < 0.4 && std::abs(length) > 1) base_speed = 1;
        //std::cout << base_speed << std::endl;

        double angular_speed;
        angular_speed = 0.2 * course_angle + sin(course_angle) * base_speed / length;

        geometry_msgs::Twist velocity;
        velocity.linear.x = std::abs(base_speed);
        velocity.angular.z = angular_speed;
        vel_pub.publish(velocity);

        ros::getGlobalCallbackQueue()->callAvailable(ros::WallDuration(0.1));
    }
}

void ControllerNode::goal_callback(const nav_msgs::Odometry &msg){

    x = msg.pose.pose.orientation.x;
    y = msg.pose.pose.orientation.y;
    z = msg.pose.pose.orientation.z;
    w = msg.pose.pose.orientation.w;

    current_x_coord = msg.pose.pose.position.x;
    current_y_coord = msg.pose.pose.position.y;

}
