#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <ros/ros.h>
#include <string>

#ifndef QNODE_HPP_
#define QNODE_HPP_

class Drone : public QDialog
{

    Q_OBJECT

public:

    Drone(int argc, char** argv );
    ~Drone();
    void forward();
    void backward();
    void left();
    void right();
    void stop();
    void reset();
    void take_off();
    void land();
    ros::NodeHandle nh;

public:

    int init_argc;
    char** init_argv;
    ros::Publisher publisher;

};

#endif /* QNODE_HPP_ */
