#ifndef COLORPALETTE_H
#define COLORPALETTE_H
#include "qcolor.h"
#include <QObject>
#include <QColorDialog>


class ColorPalette : public QObject
{
    Q_OBJECT
private:
    QColor color1;
    QColor color2;
    QColor color3;
    QColor color4;
    QColor color5;
    QColor color6;
    QColor color7;
    QColor color8;
    QColor color9;
    bool color1IsSet;
    bool color2IsSet;
    bool color3IsSet;
    bool color4IsSet;
    bool color5IsSet;
    bool color6IsSet;
    bool color7IsSet;
    bool color8IsSet;
    bool color9IsSet;
    int currentlySelectedButton = 0;
    QColorDialog *colorPicker;
public:
    explicit ColorPalette(QObject *parent = nullptr);
    QColor getSelectedColor();
public slots:
    void setColor1_slot();
    void setColor2_slot();
    void setColor3_slot();
    void setColor4_slot();
    void setColor5_slot();
    void setColor6_slot();
    void setColor7_slot();
    void setColor8_slot();
    void setColor9_slot();
    void changeColor_slot();
signals:
    void setButtonColor1_signal(QString);
    void setButtonColor2_signal(QString);
    void setButtonColor3_signal(QString);
    void setButtonColor4_signal(QString);
    void setButtonColor5_signal(QString);
    void setButtonColor6_signal(QString);
    void setButtonColor7_signal(QString);
    void setButtonColor8_signal(QString);
    void setButtonColor9_signal(QString);
};
#endif // COLORPALETTE_H
