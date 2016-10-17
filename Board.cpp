#include "Board.hpp"

Board::Board(int x, int y)
{
    this->x = x;
    this->y = y;

    matrix = Matrix(x, vector<string>(y));
}

void Board::push(Block b, int x, int y)
{

}
