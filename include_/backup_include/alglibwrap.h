#ifndef ALGLIBWRAP_H
#define ALGLIBWRAP_H

#include <QObject>
#include "fasttransforms.h"


class AlgLibWrap : public QObject
{
    Q_OBJECT
public:
    explicit AlgLibWrap(QObject *parent = nullptr);


signals:

};

#endif // ALGLIBWRAP_H
