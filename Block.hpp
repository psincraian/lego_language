#include <ostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

class Block {

private:
    string id;
    int width, height;
    int remainingSpace;
    unordered_set<Block*> over;
    vector< vector<Block*> > matrix;

    pair<int, int> getFitPosition(const Block &block) const;
    bool fitsInPosition(const Block &block, int row, int column) const;
    Block* fitsOver(const Block &block) const;

public:
    Block(int width, int height);
    Block(string id, int width, int height);

    int getWidth() const;
    int getHeight() const;
    string getId() const;
    bool fits(const Block &block) const;
    unordered_set<Block*> blocksOver() const;

    void setId(string id);
    void push(Block *block);
    bool pop(Block *block);

    friend ostream& operator<<(ostream& os, const Block &block);
};
