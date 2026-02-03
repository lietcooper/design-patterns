/**
 * Define a component interface that both the core object and decorators implement.
 * Create a concrete component that implements the interface.
 * Create decorator classes that also implement the interface and have a reference to a component object.
 * Decorator classes add or override behavior by delegating to the wrapped object.
 */


#include <iostream>


// component interface
class Coffee {
public:
    virtual void brew() const = 0;
    virtual ~Coffee() = default;
};


// concrete component
class BlackCoffee : public Coffee {
public:
    void brew() const override {
        std::cout << "Brewing Black Coffee" << std::endl;
    }
};


// concrete component
class Latte : public Coffee {
public:
    void brew() const override {
        std::cout << "Brewing Latte" << std::endl;
    }
};


// decorator interface
class Decorator : public Coffee {
protected:
    Coffee* _coffee;
public:
    Decorator(Coffee* coffee) : _coffee(coffee) {}

    void brew() const override {
        _coffee->brew();
    }

    virtual ~Decorator() {
        if (_coffee) {
            delete _coffee;
        }
    }
};


// concrete decorator
class MilkDecorator : public Decorator {
public:
    MilkDecorator(Coffee* coffee) : Decorator(coffee) {}

    void brew() const override {
        Decorator::brew();
        std::cout << "Adding Milk" << std::endl;
    }
};


// concrete decorator
class SugarDecorator : public Decorator {
public:
    SugarDecorator(Coffee* coffee) : Decorator(coffee) {}

    void brew() const override {
        Decorator::brew();
        std::cout << "Adding Sugar" << std::endl;
    }
};


int main() {
    int type, add;
    while (std::cin >> type >> add) {
        Coffee* coffee;
        if (type == 1) {
            coffee = new BlackCoffee();
        } else {
            coffee = new Latte();
        }

        if (add == 1) {
            coffee = new MilkDecorator(coffee);
        } else {
            coffee = new SugarDecorator(coffee);
        }

        coffee->brew();
        delete coffee;
    }
}