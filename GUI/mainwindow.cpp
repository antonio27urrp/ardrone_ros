#include "mainwindow.h"
#include "drone.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/String.h>
#include <QVBoxLayout>
#include <QHBoxLayout>

Window::Window(int argc, char **argv, QWidget *parent)
    : QDialog(parent)
    , drone(argc,argv)
{
    lbl = new QLabel("", this);
    x = new QLabel("x: ", this);
    y = new QLabel("y: ", this);

    button_forward = new QPushButton("forward", this);
    button_backward = new QPushButton("backward", this);
    button_hover = new QPushButton("hover", this);
    button_reset = new QPushButton("reset", this);
    button_takeoff = new QPushButton("takeoff", this);
    button_left = new QPushButton("left", this);
    button_right = new QPushButton("right", this);
    button_land = new QPushButton("land", this);
    button_moveto = new QPushButton("moveTo", this);

    x_field = new QLineEdit();
    y_field = new QLineEdit();

    QVBoxLayout *layout = new QVBoxLayout;
    QVBoxLayout *layout_2 = new QVBoxLayout;
    QVBoxLayout *layout_4 = new QVBoxLayout;
    QHBoxLayout *layout_3 = new QHBoxLayout;
    QVBoxLayout *layout_5 = new QVBoxLayout;
    QHBoxLayout *coords_field = new QHBoxLayout;
    QHBoxLayout *layout_7 = new QHBoxLayout;
    QVBoxLayout *moveto_field = new QVBoxLayout;

    layout->addWidget(button_takeoff);
    layout->addWidget(button_land);
    layout->addWidget(button_reset);

    layout -> addWidget(lbl);

    layout_2->addWidget(button_forward);

    layout_3->addWidget(button_left);
    layout_3 -> addWidget(button_hover);
    layout_3->addWidget(button_right);

    layout_4 -> addWidget(button_backward);
    layout_4 -> addWidget(lbl);

    layout_5 -> addLayout(layout);
    layout_5 -> addLayout(layout_2);
    layout_5 -> addLayout(layout_3);
    layout_5 -> addLayout(layout_4);

    coords_field -> addWidget(x);
    coords_field -> addWidget(x_field);
    coords_field -> addWidget(y);
    coords_field -> addWidget(y_field);
    moveto_field->addWidget(button_moveto);

    moveto_field -> addLayout(coords_field);

    layout_7 -> addLayout(layout_5);
    layout_7 -> addLayout(moveto_field);

    connect(button_forward, SIGNAL(clicked()), this, SLOT(ForwardIsClicked()));
    connect(button_backward, SIGNAL(clicked()), this, SLOT(BackwardIsClicked()));
    connect(button_hover, SIGNAL(clicked()), this, SLOT(HoverIsClicked()));
    connect(button_reset, SIGNAL(clicked()), this, SLOT(ResetIsClicked()));
    connect(button_takeoff, SIGNAL(clicked()), this, SLOT(TakeoffIsClicked()));
    connect(button_left, SIGNAL(clicked()), this, SLOT(LeftIsClicked()));
    connect(button_right, SIGNAL(clicked()), this, SLOT(RightIsClicked()));
    connect(button_land, SIGNAL(clicked()), this, SLOT(LandIsClicked()));
    connect(button_moveto, SIGNAL(clicked()), this, SLOT(MovetoIsClicked()));

    setLayout(layout_7);
    setWindowTitle("ARDrone 2.0 Controller");

    QIcon icon;
    icon.addFile(QString::fromUtf8("../../../\320\240\320\260\320\261\320\276\321\207\320\270\320\271 \321\201\321\202\320\276\320\273/123.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);

}

void Window::ForwardIsClicked() {

    drone.forward();

}

void Window::BackwardIsClicked() {

    drone.backward();

}

void Window::HoverIsClicked() {

    drone.stop();

}

void Window::ResetIsClicked() {

    drone.reset();

}

void Window::TakeoffIsClicked() {

    drone.take_off();

}

void Window::LeftIsClicked() {

    drone.left();

}

void Window::RightIsClicked() {

    drone.right();

}

void Window::LandIsClicked() {

    drone.land();

}

void Window::MovetoIsClicked() {

    QString str_goal_x_coord, str_goal_y_coord;
    double goal_x_coord, goal_y_coord;

    str_goal_x_coord = x_field->text();
    str_goal_y_coord = y_field -> text();

    goal_x_coord = str_goal_x_coord.toDouble();
    goal_y_coord = str_goal_y_coord.toDouble();

    std::cout << "Move to (" << goal_x_coord << ", " << goal_y_coord << ")" << std::endl;

    node.MoveTo(goal_x_coord, goal_y_coord);
    node.Control();
    node.Hover();

    std::cout << "Hover mode" << std::endl;

}
