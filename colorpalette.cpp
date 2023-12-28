#include "colorpalette.h"
#include <QColor>

/**
 * @brief ColorPalette::ColorPalette
 * @param parent
 */
ColorPalette::ColorPalette(QObject *parent) : QObject(parent)
{
    color1IsSet = false;
    color2IsSet = false;
    color3IsSet = false;
    color4IsSet = false;
    color5IsSet = false;
    color6IsSet = false;
    color7IsSet = false;
    color8IsSet = false;
    color9IsSet = false;
    colorPicker = new QColorDialog();
}

/**
 * @brief ColorPalette::setColor1_slot. If color 1 has not been set yet pull up a color dialog and set color1 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor1_slot()
{
    currentlySelectedButton = 1;
    if (!color1IsSet)
    {
        color1 = colorPicker->getColor();
        emit setButtonColor1_signal("QPushButton {background-color: " + color1.name() + ";}");
        color1IsSet = true;
    }
}

/**
 * @brief ColorPalette::setColor2_slot. If color 2 has not been set yet pull up a color dialog and set color2 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor2_slot()
{
    currentlySelectedButton = 2;
    if (!color2IsSet)
    {
        color2 = colorPicker->getColor();
        emit setButtonColor2_signal("QPushButton {background-color: " + color2.name() + ";}");
        color2IsSet = true;
    }
}

/**
 * @brief ColorPalette::setColor3_slot. If color 3 has not been set yet pull up a color dialog and set color3 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor3_slot()
{
    currentlySelectedButton = 3;
    if (!color3IsSet)
    {
        color3 = colorPicker->getColor();
        emit setButtonColor3_signal("QPushButton {background-color: " + color3.name() + ";}");
        color3IsSet = true;
    }
}

/**
 * @brief ColorPalette::setColor4_slot. If color 4 has not been set yet pull up a color dialog and set color4 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor4_slot()
{
    currentlySelectedButton = 4;
    if (!color4IsSet)
    {
        color4 = colorPicker->getColor();
        emit setButtonColor4_signal("QPushButton {background-color: " + color4.name() + ";}");
        color4IsSet = true;
    }
}

/**
 * @brief ColorPalette::setColor5_slot. If color 5 has not been set yet pull up a color dialog and set color5 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor5_slot()
{
    currentlySelectedButton = 5;
    if (!color5IsSet)
    {
        color5 = colorPicker->getColor();
        emit setButtonColor5_signal("QPushButton {background-color: " + color5.name() + ";}");
        color5IsSet = true;
    }
}

/**
 * @brief ColorPalette::setColor6_slot. If color 6 has not been set yet pull up a color dialog and set color6 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor6_slot()
{
    currentlySelectedButton = 6;
    if (!color6IsSet)
    {
        color6 = colorPicker->getColor();
        emit setButtonColor6_signal("QPushButton {background-color: " + color6.name() + ";}");
        color6IsSet = true;
    }
}

/**
 * @brief ColorPalette::setColor7_slot. If color 7 has not been set yet pull up a color dialog and set color7 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor7_slot()
{
    currentlySelectedButton = 7;
    if (!color7IsSet)
    {
        color7 = colorPicker->getColor();
        emit setButtonColor7_signal("QPushButton {background-color: " + color7.name() + ";}");
        color7IsSet = true;
    }
}

/**
 * @brief ColorPalette::setColor8_slot. If color 8 has not been set yet pull up a color dialog and set color8 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor8_slot()
{
    currentlySelectedButton = 8;
    if (!color8IsSet)
    {
        color8 = colorPicker->getColor();
        emit setButtonColor8_signal("QPushButton {background-color: " + color8.name() + ";}");
        color8IsSet = true;
    }
}

/**
 * @brief ColorPalette::setColor9_slot. If color 9 has not been set yet pull up a color dialog and set color9 to the chosen color.
 * Then emit a signal to change the color of the button in the ui.
 */
void ColorPalette::setColor9_slot()
{
    currentlySelectedButton = 9;
    if (!color9IsSet)
    {
        color9 = colorPicker->getColor();
        emit setButtonColor9_signal("QPushButton {background-color: " + color9.name() + ";}");
        color9IsSet = true;
    }
}

/**
 * @brief ColorPalette::changeColor_slot. Checks which button is currently pressed. Then pulls up a color dialog to change the color associated
 * with that button and also the color of the button.
 */
void ColorPalette::changeColor_slot()
{
    switch (currentlySelectedButton)
    {
    case 1:
        color1 = colorPicker->getColor();
        emit setButtonColor1_signal("QPushButton {background-color: " + color1.name() + ";}");
        break;
    case 2:
        color2 = colorPicker->getColor();
        emit setButtonColor2_signal("QPushButton {background-color: " + color2.name() + ";}");
        break;
    case 3:
        color3 = colorPicker->getColor();
        emit setButtonColor3_signal("QPushButton {background-color: " + color3.name() + ";}");
        break;
    case 4:
        color4 = colorPicker->getColor();
        emit setButtonColor4_signal("QPushButton {background-color: " + color4.name() + ";}");
        break;
    case 5:
        color5 = colorPicker->getColor();
        emit setButtonColor5_signal("QPushButton {background-color: " + color5.name() + ";}");
        break;
    case 6:
        color6 = colorPicker->getColor();
        emit setButtonColor6_signal("QPushButton {background-color: " + color6.name() + ";}");
        break;
    case 7:
        color7 = colorPicker->getColor();
        emit setButtonColor7_signal("QPushButton {background-color: " + color7.name() + ";}");
        break;
    case 8:
        color8 = colorPicker->getColor();
        emit setButtonColor8_signal("QPushButton {background-color: " + color8.name() + ";}");
        break;
    case 9:
        color9 = colorPicker->getColor();
        emit setButtonColor9_signal("QPushButton {background-color: " + color9.name() + ";}");
        break;
    }
}

/**
 * @brief ColorPalette::getSelectedColor. Checks which button is currently selected and returns the color associated with that button.
 * @return returns the color associated with the selected button.
 */
QColor ColorPalette::getSelectedColor()
{
    switch (currentlySelectedButton)
    {
    case 1:
        return color1;
        break;
    case 2:
        return color2;
        break;
    case 3:
        return color3;
        break;
    case 4:
        return color4;
        break;
    case 5:
        return color5;
        break;
    case 6:
        return color6;
        break;
    case 7:
        return color7;
        break;
    case 8:
        return color8;
        break;
    case 9:
        return color9;
        break;
    default:
        return QColor(0, 0, 0, 255);
        break;
    }
}
