#include "spritelayout.h"

using namespace std;

/**
 * @brief SpriteLayout::setGridSize_slot sets frame size, and is called when a user inputs the frame size on UI
 * @param size
 */
void SpriteLayout::setGridSize_slot(int size)
{
    Frame startingFrame(size);
    frames.push_back(startingFrame);
    emit drawGrid_signal();
}

/**
 * @brief SpriteLayout::getFrameData returns the current frames data
 * @return
 */
vector<vector<tuple<int, int, int, int>>> SpriteLayout::getFrameData()
{
    return frames[currFrames].pixelGrid;
}

/**
 * @brief SpriteLayout::getFrameData returns the data of a frame at a specified index
 * @param index is the index of the frame data to return
 * @return
 */
vector<vector<tuple<int, int, int, int>>> SpriteLayout::getFrameData(int index)
{
    return frames[index].pixelGrid;
}

/**
 * @brief SpriteLayout::setFrameData sets a pixel color in the corresponding frame
 * @param row first vector location
 * @param column second vector location
 * @param colorData color to be input into vector
 */
void SpriteLayout::setFrameData(int frameIndex, int row, int column, tuple<int, int, int, int> colorData)
{
    frames[frameIndex].pixelGrid[row][column] = colorData;
}

/**
 * @brief SpriteLayout::getFrameSize returns the size of the current frame
 * @return
 */
int SpriteLayout::getFrameSize()
{
    return frames[currFrames].pixelGrid.size();
}

/**
 * @brief SpriteLayout::getNumberOfFrames returns the number of frames in the current sprite
 * @return
 */
int SpriteLayout::getNumberOfFrames()
{
    return frames.size();
}

/**
 * @brief SpriteLayout::updateNumberOfFrames_slot when the number of frames changes, this gets called to update the backend data
 */
void SpriteLayout::updateNumberOfFrames_slot()
{
    Frame startingFrame(SpriteLayout::getFrameSize());
    frames.push_back(startingFrame);
}

/**
 * @brief SpriteLayout::updateCurrFrame_slot updates the current frame when the user views another frame
 * @param input
 */
void SpriteLayout::updateCurrFrame_slot(int input)
{
    currFrames = input;
    emit currFramesChange_signal();
}

/**
 * @brief SpriteLayout::removeFrames_slot removes a frame from the current sprite
 */
void SpriteLayout::removeFrames_slot()
{
    if (SpriteLayout::getNumberOfFrames() > 1)
    {
        frames.erase(frames.begin() + currFrames);
        emit removeFrameButtonClicked_signal();
    }
}

void SpriteLayout::resetFrames(int newNumberOfFrames, int newFrameSize)
{
    frames.clear();
    for (int i = 0; i < newNumberOfFrames; i++)
    {
        Frame frame(newFrameSize);
        frames.push_back(frame);
    }
}

int SpriteLayout::getCurrentFrame()
{
    return currFrames;
}
