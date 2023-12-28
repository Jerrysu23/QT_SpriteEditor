#include "filehandler.h"
#include "frame.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

/**
 * @brief FileHandler::FileHandler
 * @param spriteLayout
 */
FileHandler::FileHandler(SpriteLayout& spriteLayout)
{
    sprite = &spriteLayout;
}

/**
 * @brief FileHandler::saveExistingFile_slot
 */
void FileHandler::saveExistingFile_slot()
{
    if (fileName.isNull())
    {
        emit getFileName_signal();
        return;
    }
}

/**
 * @brief FileHandler::saveNewFile_slot
 * @param enteredFileName
 */
void FileHandler::saveNewFile_slot(QString enteredFileName)
{
    fileName = enteredFileName;
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QTextStream out(&file);

        QJsonObject jObject;
        jObject.insert("height", sprite->getFrameSize());
        jObject.insert("width", sprite->getFrameSize());
        jObject.insert("numberOfFrames", sprite->getNumberOfFrames());

        QJsonArray frames;

        //vector<vector<tuple<int,int,int,int>>> data = sprite->getFrameData(0);
        for (int i = 0; i < sprite->getNumberOfFrames(); i++)
        {
            vector<vector<tuple<int,int,int,int>>> data = sprite->getFrameData(i);
            QJsonArray frame;
            for (int j = 0; j < sprite->getFrameSize(); j++)
            {
                QJsonArray row;
                for (int k = 0; k < sprite->getFrameSize(); k++)
                {
                    tuple<int, int, int, int> colorData = data[j][k];
                    QJsonArray col;
                    col.append(get<0>(colorData));
                    col.append(get<1>(colorData));
                    col.append(get<2>(colorData));
                    col.append(get<3>(colorData));

                    row.append(col);
                }
                frame.append(row);
            }
            frames.append(frame);
        }

        jObject.insert("frames", frames);

        QJsonDocument doc(jObject);
        QString strJson(doc.toJson(QJsonDocument::Indented));
        out << strJson;

        file.close();
    }
}

/**
 * @brief FileHandler::openExistingFile_slot
 * @param foundFileName //
 * @param fileContents
 */
void FileHandler::openExistingFile_slot(QString foundFileName, QByteArray fileContents)
{
    fileName = foundFileName;

    QFile file(fileName);
    QTextStream in(&file);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString strFile = (QString)file.readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(strFile.toUtf8());
    QJsonObject jsonObject = jsonResponse.object();

    int frameSize = jsonObject["height"].toInt();
    int numberOfFrames = jsonObject["numberOfFrames"].toInt();

    sprite->resetFrames(numberOfFrames, frameSize);

    qDebug() << "got here";

    QJsonArray frames = jsonObject["frames"].toArray();

    for (int i = 0; i < numberOfFrames; i++)
    {
        QJsonArray frame = frames[i].toArray();
        for (int j = 0; j < frame.size(); j++)
        {
            QJsonArray row = frame[j].toArray();
            for (int k = 0; k < frame.size(); k++)
            {
                QJsonArray col = row[k].toArray();
                tuple<int, int, int, int> colorData = {col[0].toInt(), col[1].toInt(), col[2].toInt(), col[3].toInt()};
                sprite->setFrameData(i, j, k, colorData);
            }
        }
    }

    sprite = new SpriteLayout();

    file.close();
}
