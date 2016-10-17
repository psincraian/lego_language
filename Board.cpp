#include "Board.hpp"

Board::Board(int width, int height)
{
    this->width = width;
    this->height = height;

    matrix = Matrix(width, vector<Block*>(height));
}

void Board::push(Block *b, int row, int column)
{
    if (fitsInPosition(*b, row, column)) {
        int finalRow = row + b->getHeight();
        int finalColumn = row + b->getWidth();
        for (int i = row; i < finalRow; ++i) {
            for (int j = column; j < finalColumn; ++j)
                matrix[i][j] = b;
        }
    } else {
        string msg = "Can't put " + b->getId() + " at " +
            to_string(row) + "x" + to_string(column);
        throw msg;
    }
}

bool Board::fitsInPosition(const Block &block, int row, int column) const
{
    bool fits = true;

    if (row + block.getHeight() > height or column + block.getWidth() > width)
        return false;

    int i = row;
    while (i < block.getHeight() && fits) {
        int j = column;
        while (j < block.getWidth() && fits) {
            fits = matrix[i][j] == NULL;
            ++j;
        }

        ++i;
    }

    return fits;
}
