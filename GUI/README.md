# ardrone_ros

### 1. Introduction

Hello everyone! This is my ARDrone 2.0 project, which connected with practice work.

There are a few parts, in this one I'll consider quadrotor movement/ move to point/ flying by points.

In this project I'll connect ROS and QtCreator. First of all we need it's rewrite CMakesFiles.txt. I'm using Qt4, so if you use Qt5, you wil need to go to Qt offical site and read, how to convert qmake to cmake.

### 2. CMakeFiles

In this part we connect ROS and Qtcreator( QtGui, QtCore, Qt Designer).

   2.1. Check cmake version:

    cmake_minimum_required(VERSION 2.8.3)
   2.2. Set project name:    

       set(PROJECT YOUR_PROJECT_NAME)
       project(${PROJECT})
   2.3. Set sources files:    

       set(SOURCES
             main.cpp
             mainwindow.cpp
             ControllerNode.cpp
          )
          
   2.4. Set moc headers files:    

       set(MOC_HEADERS
             mainwindow.cpp
             ControllerNode.hpp
          )
          
   2.5. Set UI's files( if you need it):    

       set(UIS
             mainwindow.ui
          )
   2.6. Next lines needed for building all Qt projects:

       find_package(Qt4 REQUIRED)
       include(${QT_USE_FILE})
       add_definitions(${QT_DEFINITIONS})
       include_directories(${CMAKE_BINARY_DIR})
       
   2.7. Find ROS packages. Dependencies on other catkin packages can be added in a COMPONENTS section on
this line( we added roscpp, for example):

       find_package(catkin REQUIRED COMPONENTS roscpp)
   2.8. Using Qt meta-system (precompiler):

       QT4_WRAP_UI(UI_HEADERS ${UIS})
       QT4_WRAP_CPP(MOC_SRCS ${MOC_HEADERS})
   2.9. Compile:

       add_executable(${PROJECT} ${SOURCES} ${MOC_SRCS} ${UI_HEADERS})
   2.10. Build it (link libraries):

       target_link_libraries(${PROJECT} ${QT_LIBRARIES} ${catkin_LIBRARIES})
