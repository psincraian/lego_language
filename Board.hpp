#include <vector>
#include <map>

#include "Block.hpp"

using namespace std;

typedef vector< vector<Block*> > Matrix;

class Board
{
private:
    map<string, Block*> blocks;
    map< Block*, pair<int, int> > positions;
    Matrix matrix;
    int width;
    int height;

    bool fitsInPosition(const Block &block, int row, int column) const;
    void setBlock(Block *b, int row, int column);
    void moveSouthOrEast(int row, int col, int units, string direction);
    void moveNorthOrWest(int row, int col, int units, string direction);
    void deleteBlock(Block *b);

public:
    string NORTH = "NORTH";
    string EAST = "EAST";
    string WEST = "WEST";
    string SOUTH = "SOUTH";

    Board();
    Board(int x, int y);

    Block* find(string id) const;

    Block* push(Block *a, Block *b);
    Block* pop(Block *base, Block *over);
    void equal(string id, Block *b);
    void move(string id, string direction, int units);
    Block* place(int row, int column, int width, int height);

    friend ostream& operator<<(ostream& os, const Board &board);
};
