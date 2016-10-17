#include <ostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

class Block {

private:
    string id;
    int width, height;
    int remainingSpace;
    list<Block*> over;
    vector< vector<Block*> > matrix;

    pair<int, int> getFitPosition(const Block &block) const;
    bool fitsInPosition(const Block &block, int row, int column) const;

public:
    Block(int width, int height);
    Block(string id, int width, int height);

    int getWidth() const;
    int getHeight() const;
    string getId() const;
    bool fits(const Block &block) const;

    void setId(string id);
    void push(Block *block);

    friend ostream& operator<<(ostream& os, const Block &block);
};
