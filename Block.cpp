#include "Block.hpp"

#include <utility>
#include <queue>
#include <unordered_map>
#include <algorithm>

Block::Block(int width, int height)
{
    this->width = width;
    this->height = height;
    remainingSpace = width*height;
    matrix = vector<vector<Block*>>(height, vector<Block*>(width));
}

Block::Block(string id, int width, int height)
{
    this->id = id;
    this->width = width;
    this->height = height;
    remainingSpace = width*height;
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

bool Block::fits(const Block &block, int level) const
{
    if (level < 0)
        return false;

    pair<int, int> pos = getFitPosition(block);
    if (pos.first != -1 and pos.second != -1)
        return true;

    auto it = over.begin();
    bool fits = false;
    int i = 0;
    while (it != over.end() and not fits) {
        fits = (*it)->fits(block, level - 1);
        ++it;
    }

    return fits;
}

int Block::totalHeight() const
{
    int result = 1;
    for (auto it = over.begin(); it != over.end(); ++it)
        result = max(result, (*it)->totalHeight() + 1);

    return result;
}

bool Block::pop(Block *block)
{
    if (block->over.size() > 0)
        throw string("The popped block has blocks over");

    auto it = over.find(block);
    bool deleted = it != over.end();
    if (it != over.end()) {
        over.erase(block);
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                if (matrix[i][j] == block)
                    matrix[i][j] = NULL;
            }
        }
    } else {
        it = over.begin();
        while (it != over.end() && not deleted) {
            deleted = (*it)->pop(block);
            ++it;
        }
    }

    if (deleted)
        remainingSpace += (*block).width * (*block).height;

    return deleted;
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
    over.insert(block);
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
    priority_queue<int> heights;
    unordered_map<Block*, int> blockHeights;
    looked.insert(NULL);
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[0].size(); ++j) {
            auto it = looked.find(matrix[i][j]);
            if (it == looked.end()) {
                looked.insert(matrix[i][j]);
                int height = -matrix[i][j]->totalHeight();
                blockHeights[matrix[i][j]] = height;
                heights.push(height);
            }
        }
    }

    looked.clear();
    looked.insert(NULL);
    while (not heights.empty()) {
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                auto it = looked.find(matrix[i][j]);
                if (it == looked.end() && blockHeights[matrix[i][j]] == heights.top()) {
                    looked.insert(matrix[i][j]);
                    heights.pop();
                    if (matrix[i][j]->fits(block))
                        return matrix[i][j];
                }
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
