#include "rotatetabtext.h"
#include <QPainter>
#include <QDebug>
#include <QWidget>

RotateTabText::RotateTabText()
{

}

RotateTabText::~RotateTabText()
{

}

void RotateTabText::drawItemText(QPainter *painter, const QRect &rect, int flags, const QPalette &pal, bool enabled, const QString &text, QPalette::ColorRole textRole) const
{
    painter->save();
    painter->translate(65, 20);
    painter->rotate(90);
//    int x = rect.x(), y = rect.y();
//    rect.setX(y);
//    rect.setY(x);
    QCommonStyle::drawItemText(painter, rect, flags, pal, enabled, text, textRole);
    painter->restore();
}

void RotateTabText::drawControl(ControlElement element, const QStyleOption * option, QPainter * painter, const QWidget * widget ) const
{
    QCommonStyle::drawControl(element, option, painter, widget);
}
