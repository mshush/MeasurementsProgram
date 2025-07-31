#include "selectionrectclass.h"

SelectionRectClass::SelectionRectClass(QCustomPlot *parent): QCPSelectionRect(parent)
{}


void SelectionRectClass::draw(QCPPainter *painter)
{
    if (mActive)
    {
        if (!XAxisLocked and !YAxisLocked)
        {
            painter->setPen(pen());
            painter->setBrush(QBrush(QColor(0,0,255,50)));
            painter->drawRect(mRect);
        }

        if (XAxisLocked)
        {
            painter->setPen(pen());
            painter->setBrush(QBrush(QColor(0,0,255,50)));
            QRect TempRect = mRect;
            TempRect.setLeft(qobject_cast<QCustomPlot*>(this->parent())->axisRect()->left());
            TempRect.setRight(qobject_cast<QCustomPlot*>(this->parent())->axisRect()->right());
            painter->drawRect(TempRect);
        }

        if (YAxisLocked)
        {
            painter->setPen(pen());
            painter->setBrush(QBrush(QColor(0,0,255,50)));
            QRect TempRect = mRect;
            TempRect.setTop(qobject_cast<QCustomPlot*>(this->parent())->axisRect()->top());
            TempRect.setBottom(qobject_cast<QCustomPlot*>(this->parent())->axisRect()->bottom());
            painter->drawRect(TempRect);
        }
    }

    //QCPSelectionRect::draw(painter);
}
