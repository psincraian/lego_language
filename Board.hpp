#include <vector>
#include <map>

#include "Block.hpp"

using namespace std;

typedef vector< vector<Block*> > Matrix;

class Board
{
private:
    map<string, Block*> blocks;
    Matrix matrix;
    int width;
    int height;

    bool fitsInPosition(const Block &block, int row, int column) const;
    void setBlock(Block *b, int row, int column);

public:
    Board();
    Board(int x, int y);

    void push(Block *b, int row, int column);
    void equal(string id, Block *b);
    Block* place(int row, int column, int width, int height);

    friend ostream& operator<<(ostream& os, const Board &board);
};
