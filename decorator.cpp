/**
 * Define a component interface that both the core object and decorators implement.
 * Create a concrete component that implements the interface.
 * Create decorator classes that also implement the interface and have a reference to a component object.
 * Decorator classes add or override behavior by delegating to the wrapped object.
 */


#include <iostream>
#include <memory>

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
    std::unique_ptr<Coffee> _coffee;  // use smart pointer in case of stack object passed in and cannot delete in destructor.
public:
    Decorator(std::unique_ptr<Coffee> coffee) : _coffee(std::move(coffee)) {}

    void brew() const override {
        _coffee->brew();
    }
};


// concrete decorator
class MilkDecorator : public Decorator {
public:
    MilkDecorator(std::unique_ptr<Coffee> coffee) : Decorator(std::move(coffee)) {}

    void brew() const override {
        Decorator::brew();
        std::cout << "Adding Milk" << std::endl;
    }
};


// concrete decorator
class SugarDecorator : public Decorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> coffee) : Decorator(std::move(coffee)) {}

    void brew() const override {
        Decorator::brew();
        std::cout << "Adding Sugar" << std::endl;
    }
};


int main() {
    int type, add;
    while (std::cin >> type >> add) {
        std::unique_ptr<Coffee> coffee;
        if (type == 1) {
            coffee = std::make_unique<BlackCoffee>();
        } else {
            coffee = std::make_unique<Latte>();
        }

        if (add == 1) {
            coffee = std::make_unique<MilkDecorator>(std::move(coffee));
        } else {
            coffee = std::make_unique<SugarDecorator>(std::move(coffee));
        }

        // can nest forever because they all extends Coffee; Based on this, we can add up price and topping info as well.
        // coffee = std::make_unique<MilkDecorator>(std::move(coffee));
        // coffee = std::make_unique<SugarDecorator>(std::move(coffee));
        // coffee = std::make_unique<MilkDecorator>(std::move(coffee));
        // coffee = std::make_unique<SugarDecorator>(std::move(coffee));

        coffee->brew();
    }
}