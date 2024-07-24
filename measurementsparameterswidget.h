#ifndef MEASUREMENTSPARAMETERSWIDGET_H
#define MEASUREMENTSPARAMETERSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>


class MeasurementsParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MeasurementsParametersWidget(QWidget *parent = nullptr);

signals:
};

#endif // MEASUREMENTSPARAMETERSWIDGET_H
