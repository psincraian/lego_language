#include "Block.hpp"

#include <utility>
#include <unordered_set>

Block::Block(int width, int height)
{
    this->width = width;
    this->height = height;
    remainingSpace = width*height;
    over = list<Block*>();
    matrix = vector<vector<Block*>>(width, vector<Block*>(height));
}

Block::Block(string id, int width, int height)
{
    this->id = id;
    this->width = width;
    this->height = height;
    remainingSpace = width*height;
    over = list<Block*>();
    matrix = vector<vector<Block*>>(width, vector<Block*>(height));
}

int Block::getHeight() const
{
    return height;
}

int Block::getWidth() const
{
    return width;
}

string Block::getId() const
{
    return id;
}

bool Block::fits(const Block &block) const
{
    if (remainingSpace < block.width*block.height)
        return fitsOver(block);

    pair<int, int> fits = getFitPosition(block);
    if (fits.first != -1 and fits.second != -1)
        return true;
    else
        return fitsOver(block);
}

list<Block*> Block::blocksOver() const
{

}

void Block::setId(string id)
{
    this->id = id;
}

void Block::push(Block *block)
{
    pair<int, int> position = getFitPosition(*block);
    if (position.first == -1 and position.second == -1) {
        Block *over = fitsOver(*block);
        if (over == NULL)
            throw "Don't have enough space to push block";
        over->push(block);
        return;
    }

    remainingSpace -= block->width*block->height;
    over.push_back(block);
    int finalRow = position.first + block->height;
    int finalColumn = position.second + block->width;
    for (int i = position.first; i < finalRow; ++i) {
        for (int j = position.second; j < finalColumn; ++j)
            matrix[i][j] = block;
    }
}

pair<int, int> Block::getFitPosition(const Block &block) const
{
    pair<int, int> result = make_pair(-1, -1);

    bool fits = false;
    int i = 0;
    while (i < width && not fits) {
        int j = 0;
        while (j < height && not fits) {
            fits = matrix[i][j] == NULL && fitsInPosition(block, i, j);
            if (fits)
                result = make_pair(i, j);
            ++j;
        }

        ++i;
    }

    return result;
}

bool Block::fitsInPosition(const Block &block, int row, int column) const
{
    bool fits = true;

    if (row + block.height > height or column + block.width > width)
        return false;

    int i = row;
    while (i < block.height && fits) {
        int j = column;
        while (j < block.width && fits) {
            fits = matrix[i][j] == NULL;
            ++j;
        }

        ++i;
    }

    return fits;
}

Block* Block::fitsOver(const Block &block) const
{
    unordered_set<Block*> looked;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            auto it = looked.find(matrix[i][j]);
            if (it == looked.end()) {
                looked.insert(matrix[i][j]);
                if (matrix[i][j]->fits(block))
                    return matrix[i][j];
            }
        }
    }

    return NULL;
}

ostream& operator<<(ostream& os, const Block &block)
{
    os << block.id << "(" << block.width << "x" << block.height << ") over: ";
    for (auto it = block.over.begin(); it != block.over.end(); ++it)
        os << (*it)->id << " ";

    os << endl;

    for (int i = 0; i < block.matrix.size(); ++i) {
        for (int j = 0; j < block.matrix[0].size(); ++j) {
            if (block.matrix[i][j] != NULL) {
                string id = block.matrix[i][j]->id;
                if (id != "")
                    os << id;
                else os << block.matrix[i][j]->getWidth() << "x" << block.matrix[i][j]->getHeight();
            }
            else
                os << "-";
            os << "\t";
        }
        os << endl;
    }

    return os;
}
