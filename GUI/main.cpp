#include "mainwindow.h"
#include <QApplication>
#include <stdlib.h>

int main(int argc, char **argv){

    ros::init(argc, argv, "controller_node_cpp");
    QApplication a(argc, argv);
    Window window(argc, argv);
    window.setGeometry(400, 400, 200, 100);
    window.show();

    return a.exec();

}

