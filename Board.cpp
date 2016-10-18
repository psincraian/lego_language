#include "Board.hpp"
#include <utility>
#include <iostream>

Board::Board()
{

}

Board::Board(int width, int height)
{
    this->width = width;
    this->height = height;

    matrix = Matrix(height, vector<Block*>(width));
}

void Board::push(Block *b, int row, int column)
{
    if (fitsInPosition(*b, row, column)) {
        setBlock(b, row, column);
    } else {
        string msg = "Can't put " + b->getId() + " at " +
            to_string(row) + "," + to_string(column);
        throw msg;
    }
}

void Board::equal(string id, Block *block)
{
    blocks[id] = block;
    block->setId(id);
}

Block* Board::place(int row, int column, int width, int height)
{
    Block *block = new Block(width, height);
    if (fitsInPosition(*block, row, column)) {
        setBlock(block, row, column);
    } else {
        delete block;
        string msg = "Can't put " + to_string(width) + "x" + to_string(height) +
            " at " + to_string(row) + "," + to_string(column);
        throw msg;
    }

    return block;
}

void Board::move(string id, string direction, int units)
{
    auto itBlock = blocks.find(id);
    if (itBlock == blocks.end())
        throw "Can't find block " + id;

    auto it = positions.find(itBlock->second);
    int row = (it->second).first;
    int col = (it->second).second;
    if (direction == NORTH or direction == WEST)
        moveNorthOrWest(row, col, units, direction);
    else if (direction == SOUTH or direction == EAST)
        moveSouthOrEast(row, col, units, direction);
    else
        throw "Direction " + direction + " is invalid";
}

void Board::setBlock(Block *b, int row, int column)
{
    positions[b] = make_pair(row, column);

    int finalRow = row + b->getHeight();
    int finalColumn = column + b->getWidth();
    for (int i = row; i < finalRow; ++i) {
        for (int j = column; j < finalColumn; ++j)
            matrix[i][j] = b;
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

void Board::moveSouthOrEast(int row, int col, int units, string direction)
{
    int width = (matrix[row][col])->getWidth();
    int height = (matrix[row][col])->getHeight();

    int finalRow = row, finalCol = col;
    if (direction == SOUTH)
        finalRow += units;
    else
        finalCol += units;

    if (finalCol > this->width or finalRow > this->height)
        throw "MOVE " + to_string(units) + direction + " is outside the Grid";

    for (int i = height - 1; i >= 0; --i) {
        for (int j = width - 1; j >= 0; --j) {
            Block *newBlock = matrix[finalRow + i][finalCol + j];
            if (newBlock != NULL)
                throw "There is a block in final position while MOVE " + to_string(units) + " " + direction;
            swap(matrix[row + i][col + j], matrix[finalRow + i][finalCol + j]);
        }
    }

    positions[matrix[finalRow][finalCol]] = make_pair(finalRow, finalCol);
}

void Board::moveNorthOrWest(int row, int col, int units, string direction)
{
    int width = (matrix[row][col])->getWidth();
    int height = (matrix[row][col])->getHeight();

    int finalRow = row, finalCol = col;
    if (direction == WEST)
        finalCol -= units;
    else
        finalRow -= units;

    if (finalCol < 0 or finalRow < 0)
        throw "MOVE " + to_string(units) + direction + "  is outside the Grid";

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Block *newBlock = matrix[finalRow + i][finalCol + j];
            if (newBlock != NULL)
                throw "There is a block in final position while MOVE " + to_string(units) + " " + direction;
            swap(matrix[row + i][col + j], matrix[finalRow + i][finalCol + j]);
        }
    }

    positions[matrix[finalRow][finalCol]] = make_pair(finalRow, finalCol);
}

ostream& operator<<(ostream& os, const Board &board)
{
    os << "Board " + to_string(board.width) + "x" + to_string(board.height) << endl;

    for (int i = 0; i < board.matrix.size(); ++i) {
        for (int j = 0; j < board.matrix[0].size(); ++j) {
            if (board.matrix[i][j] != NULL) {
                if ((board.matrix[i][j])->getId() != "")
                    os << (board.matrix[i][j])->getId();
                else
                    os << (board.matrix[i][j])->getHeight() << " + " << (board.matrix[i][j])->getWidth();
            } else
                os << "-";
            os << "\t";
        }
        os << endl;
    }

    return os;
}
