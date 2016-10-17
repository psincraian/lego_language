#include <vector>
#include <map>

#include "Block.hpp"

using namespace std;

typedef vector<vector<string>> Matrix;

class Board
{
    map<string, Block> blocks;
    Matrix matrix;
    int x;
    int y;
    int z;

    Board(int x, int y);

    void push(Block b, int x, int y);
};
