/**
 * Building Block factory
 *  Square block
 *  Circle block
 * 
 */
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Block {
public:
    virtual void produce() = 0;
    virtual ~Block() = default;
};

class SquareBlock : public Block {
public:
    void produce() override {
        cout << "Square Block" << endl;
    }
};

class CircleBlock : public Block {
public:
    void produce() override {
        cout << "Circle Block" << endl;
    }
};

class BlockFactory {
public:
    virtual unique_ptr<Block> createBlock() = 0;
    virtual ~BlockFactory() = default;
};

class CircleBlockFactory : public BlockFactory {
public:
    unique_ptr<Block> createBlock() override {
        return make_unique<CircleBlock>();
    }
};

class SquareBlockFactory : public BlockFactory {
public:
    unique_ptr<Block> createBlock() override {
        return make_unique<SquareBlock>();
    }
};

class BlockFactorySystem {
private:
    vector<unique_ptr<Block>> blocks;
public:
    void produceBlock(BlockFactory& blockFactory, int quantity) {
        for (int i = 0; i < quantity; ++i) {
            unique_ptr<Block> block = blockFactory.createBlock();
            block->produce();
            blocks.push_back(std::move(block));
        }
    }
};

int main() {
    BlockFactorySystem factorySystem;
    CircleBlockFactory circleBlockFactory;
    SquareBlockFactory squareBlockFactory;

    string type;
    int quantity;
    while (cin >> type >> quantity) {
        if (type == "Circle") {
            factorySystem.produceBlock(circleBlockFactory, quantity);
        } else {
            factorySystem.produceBlock(squareBlockFactory, quantity);
        }
    }

    return 0;
}