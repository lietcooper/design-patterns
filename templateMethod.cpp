/**
 * Components：
 *  Abstract Class/Interface: Defines the template method (algorithm skeleton) with some steps implemented and others left abstract or as hooks for customization.
 *  Template Method: Outlines the algorithm’s fixed structure by calling steps in order, often marked final to prevent changes.
 *  Abstract/Hook Methods: Placeholder methods in the abstract class that subclasses implement or optionally override.
 *  Concrete Subclasses: Provide implementations for abstract methods, customizing specific steps while preserving the overall algorithm.
 * 
 * 
 * Implementation of Template Method Design Pattern
 *  Step 1: Create an Abstract Class: Start by making a base or abstract class that defines the overall structure of the algorithm. This class will have a template method to outline the steps
 *  Step 2: Define the Template Method: Inside the abstract class, create a method (the template method) that calls each step of the algorithm in a specific order
 *  Step 3: Implement Core Steps: For each step of the algorithm, create individual methods in the abstract class. Some methods can have default implementations, while others can be abstract to allow customization
 *  Step 4: Create Subclasses: Now, create subclasses that inherit from the abstract class. In each subclass, override the steps that need specific behavior, leaving the rest as they are
 *  Step 5: Use the Template Method: When you run the template method on a subclass instance, it will execute all the steps in the defined order, with customizations in place from the overridden methods.
 * 
 */


#include <iostream>
#include <unordered_map>


class DrinkMaker {
private:
    std::string name_;
public:
    DrinkMaker(const std::string& name) : name_(name) {}

    virtual ~DrinkMaker() = default;

    virtual void makeDrink() {
        std::cout << "Making " << name_ << ":\n";
        grindCoffeeBean();
        brewCoffee();
        addCondiments();
    }

    virtual void grindCoffeeBean() {
        std::cout << "Grinding coffee beans" << std::endl;
    }
    virtual void brewCoffee() {
        std::cout << "Brewing coffee" << std::endl;
    }

    virtual void addCondiments() {
        std::cout << "Adding condiments" << std::endl;
    }
};


class AmericanCoffeeMaker : public DrinkMaker {
public:
    AmericanCoffeeMaker(const std::string& name) : DrinkMaker(name) {}
};


class LatteMaker : public DrinkMaker {
public:
    LatteMaker(const std::string& name) : DrinkMaker(name) {}

    void addCondiments() override {
        std::cout << "Adding milk" << std::endl;
        std::cout << "Adding condiments" << std::endl;
    }
};


int main() {
    AmericanCoffeeMaker americanCoffeeMaker("American Coffee");
    LatteMaker latteMaker("Latte");
    std::unordered_map<int, DrinkMaker*> drinkMakers = {
        {1, &americanCoffeeMaker},
        {2, &latteMaker}
    };

    int choice;
    DrinkMaker* maker;
    while (std::cin >> choice) {
        maker = drinkMakers[choice];
        maker->makeDrink();
        std::cout << std::endl;
    }

    return 0;
}