#include "Board.hpp"

Board::Board()
{

}

Board::Board(int width, int height)
{
    this->width = width;
    this->height = height;

    matrix = Matrix(width, vector<Block*>(height));
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

void Board::setBlock(Block *b, int row, int column)
{
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

ostream& operator<<(ostream& os, const Board &board)
{
    os << "Board " + to_string(board.height) + "x" + to_string(board.width) << endl;

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
