#include "frame.h"

/**
 * @brief Frame::Frame creates a frame. This data structure is held in the spriteLayout so we can access all available frames and their data.
 * Each frame consists of a number of rows and columns, but holds color values so they can be painted correctly on the UI
 * @param gridSize
 */
Frame::Frame(int gridSize)
{
    vector<int> v;
    pixelGrid.resize(gridSize);
    for (int i = 0; i < gridSize; i++)
    {
        for (int j = 0; j < gridSize; j++)
        {
            pixelGrid.at(i).push_back({0, 0, 0, 0});
        }
    }
}
