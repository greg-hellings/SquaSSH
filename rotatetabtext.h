#ifndef ROTATETABTEXT_H
#define ROTATETABTEXT_H

#include <QProxyStyle>

class RotateTabText : public QProxyStyle
{
public:
    RotateTabText();
    ~RotateTabText();
    void drawItemText(QPainter*, const QRect&, int, const QPalette&, bool, const QString&, QPalette::ColorRole) const;
    void drawControl(ControlElement element, const QStyleOption * option, QPainter * painter, const QWidget * widget = 0 ) const;
};

#endif // ROTATETABTEXT_H
