#ifndef RESULTPARAMETERSWIDGET_H
#define RESULTPARAMETERSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>



class ResultParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ResultParametersWidget(QWidget *parent = nullptr);


    QVBoxLayout * OutermostVerticalLayout;
    QGroupBox * AnglesGroupBox;
    QGridLayout * AnglesGroupBoxLayout;

    //QHBoxLayout * SetCurrentRotationAngleLayout;
    QLabel * SetCurrentRotationAngleLabel;
    QLineEdit * SetCurrentRotationAngleEdit;
    QPushButton * SetCurrentRotationAngleButton;

    //QHBoxLayout * SetCurrentTiltAngleLayout;
    QLabel * SetCurrentTiltAngleLabel;
    QLineEdit * SetCurrentTiltAngleEdit;
    QPushButton * SetCurrentTiltAngleButton;


signals:
};

#endif // RESULTPARAMETERSWIDGET_H
