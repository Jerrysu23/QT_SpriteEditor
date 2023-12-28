#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <tuple>

using namespace std;

class Frame
{
public:
    vector<vector<tuple<int, int, int, int>>> pixelGrid;
    Frame(int gridSize);
};

#endif // FRAME_H
