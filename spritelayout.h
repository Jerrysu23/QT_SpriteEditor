#ifndef SPRITELAYOUT_H
#define SPRITELAYOUT_H

#include <QObject>
#include <tuple>
#include <vector>
#include "frame.h"

using namespace std;

class SpriteLayout : public QObject
{
    Q_OBJECT
private:
    vector<Frame> frames;
    int currFrames = 0;
public:
    vector<vector<tuple<int, int, int, int>>> getFrameData();
    vector<vector<tuple<int, int, int, int>>> getFrameData(int);
    void setFrameData(int frameIndex, int row, int column, tuple<int, int, int, int> colorData);
    int getFrameSize();
    int getNumberOfFrames();
    void resetFrames(int newNumberOfFrames, int newFrameSize);
    int getCurrentFrame();
public slots:
    void setGridSize_slot(int);
    void updateNumberOfFrames_slot();
    void updateCurrFrame_slot(int);
    void removeFrames_slot();
signals:
    void drawGrid_signal();
    void currFramesChange_signal();
    void removeFrameButtonClicked_signal();
};

#endif // SPRITELAYOUT_H
