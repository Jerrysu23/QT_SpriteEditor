#include "view.h"
#include "colorpalette.h"
#include "filehandler.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SpriteLayout spriteLayout;
    ColorPalette colorPalette;
    FileHandler fileHandler(spriteLayout);
    View w(spriteLayout, colorPalette, fileHandler);
    w.show();
    return a.exec();
}
