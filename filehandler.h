#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "spritelayout.h"

class FileHandler: public QObject
{
    Q_OBJECT
public:
    FileHandler(SpriteLayout& spriteLayout);
    SpriteLayout* sprite;
    QString fileName;
public slots:
    void saveExistingFile_slot();
    void saveNewFile_slot(QString);
    void openExistingFile_slot(QString, QByteArray);
signals:
    void getFileName_signal();
};

#endif // FILEHANDLER_H
