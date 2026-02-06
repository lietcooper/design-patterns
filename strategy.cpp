/**
 * 1. Context
 * A class or object known as the Context assigns the task to a strategy object and contains a reference to it.
 * It serves as an intermediary between the client and the strategy, offering an integrated approach for task execution without exposing every detail of the process.
 * The Context maintains a reference to a strategy object and calls its methods to perform the task, allowing for interchangeable strategies to be used.
 * 
 * 2. Strategy Interface
 * An abstract class or interface known as the Strategy Interface specifies a set of methods that all concrete strategies must implement.
 * As a kind of agreement, it guarantees that all strategies follow the same set of rules and are interchangeable by the Context.
 * The Strategy Interface promotes flexibility and modularity in the design by establishing a common interface that enables decoupling between the Context and the specific strategies.
 * 
 * 3. Concrete Strategies
 * Concrete Strategies are the various implementations of the Strategy Interface. Each concrete strategy provides a specific algorithm or behavior for performing the task defined by the Strategy Interface.
 * Concrete strategies encapsulate the details of their respective algorithms and provide a method for executing the task.
 * They are interchangeable and can be selected and configured by the client based on the requirements of the task.
 * 
 * 4. Client
 * The Client is responsible for selecting and configuring the appropriate strategy and providing it to the Context.
 * It knows the requirements of the task and decides which strategy to use based on those requirements.
 * The client creates an instance of the desired concrete strategy and passes it to the Context, enabling the Context to use the selected strategy to perform the task.
 * Communication between the Components
 * 
 * In the Strategy Design Pattern, communication between the components occurs in a structured and decoupled manner. Here's how the components interact with each other:
 * Client -> Context: The client selects and configures a suitable strategy, then passes it to the context to execute the task.
 * Context -> Strategy: The context holds the strategy reference and delegates execution to it via the common interface.
 * Strategy -> Context: The strategy executes its algorithm, returns results, or performs necessary actions for the context to use.
 * Strategy Interface: Defines a contract ensuring all strategies are interchangeable.
 * Decoupling: Context remains unaware of strategy details, enabling flexibility and easy substitution.
 */

#include <iostream>
#include <array>
#include <unordered_map>
#include <cmath>
#include <stdexcept> // For std::runtime_error


// Strategy Interface
class DiscountStrategy {
public:
    virtual int applyDiscount(int price) = 0;
    virtual ~DiscountStrategy() = default;
};

// Concrete Strategy
class DiscountStrategy1 : public DiscountStrategy {
private:
    const double RATE = 0.9;

public:
    int applyDiscount(int price) override {
        return static_cast<int>(std::round(price * RATE));
    }
};


// Concrete Strategy
class DiscountStrategy2 : public DiscountStrategy {
private:
    std::array<int, 4> threshold_ = {100, 150, 200, 300};
    std::array<int, 4> discounts_ = {5, 15, 25, 40};

public:
    int applyDiscount(int price) override {
        for (int i = threshold_.size() - 1; i >= 0; --i) {
            if (price >= threshold_[i]) {
                return price - discounts_[i];
            }
        }
        return price;
    }
};


// context
class DiscountContext {
private:
    DiscountStrategy* discountStrategy_;

public:
    void setDiscountStrategy(DiscountStrategy* discountStrategy) {
        discountStrategy_ = discountStrategy;
    }

    int applyDiscount(int price) {
        return discountStrategy_->applyDiscount(price);
    }
};


int main() {
    int N, p, s;
    std::cin >> N;

    DiscountStrategy1 discountStrategy1;
    DiscountStrategy2 discountStrategy2;
    std::unordered_map<int, DiscountStrategy*> strategies = {
        {1, &discountStrategy1},
        {2, &discountStrategy2}
    };

    DiscountStrategy* strategy;
    DiscountContext discountContext;

    while (N--) {
        std::cin >> p >> s;
        auto it = strategies.find(s);
        if (it == strategies.end()) {
            std::cerr << "Unknown strategy." << std::endl;
            continue;
        }
        strategy = it->second;
        discountContext.setDiscountStrategy(strategy);
        std::cout << discountContext.applyDiscount(p) << std::endl;
    }
    return 0;
}