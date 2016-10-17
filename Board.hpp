#include <vector>
#include <map>

#include "Block.hpp"

using namespace std;

typedef vector<vector<Block*>> Matrix;

class Board
{
private:
    map<string, Block> blocks;
    Matrix matrix;
    int width;
    int height;

    bool fitsInPosition(const Block &block, int row, int column) const;

public:
    Board(int x, int y);

    void push(Block *b, int row, int column);
};
