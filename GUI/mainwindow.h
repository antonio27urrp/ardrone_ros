#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include "drone.h"
#include "ControllerNode.h"

class Window : public QDialog
{
    Q_OBJECT //макрос, который дает понять, что будет обработан мок для сигналов и слотов

public:

    Window(int argc, char** argv, QWidget *parent=0);

private:

    QLabel *lbl;
    QLabel *navdata;
    QLabel *x;
    QLabel *y;

    QPushButton *button_forward;
    QPushButton *button_backward;
    QPushButton *button_hover;
    QPushButton *button_reset;
    QPushButton *button_takeoff;
    QPushButton *button_left;
    QPushButton *button_right;
    QPushButton *button_land;
    QPushButton *button_moveto;

    QLineEdit *x_field;
    QLineEdit *y_field;

private Q_SLOTS:

    void ForwardIsClicked();
    void BackwardIsClicked();
    void HoverIsClicked();
    void ResetIsClicked();
    void TakeoffIsClicked();
    void LeftIsClicked();
    void RightIsClicked();
    void LandIsClicked();
    void MovetoIsClicked();

private: 
    ControllerNode node;
    Drone drone;
};

#endif // WINDOW_H
