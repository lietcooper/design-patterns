/**
 * 1. Create the Command Interface: Define an interface or abstract class that declares the execute() method. This method will be called to carry out the action.
 * 2. Create Concrete Command Classes: Implement the command interface in multiple classes. Each class will represent a different command and will call the appropriate method on the receiver to perform the specific action.
 * 3. Define the Receiver Class: This class contains the actual logic that needs to be executed. The command objects will call methods on this receiver to perform actions.
 * 4. Create the Invoker Class: The invoker triggers the command’s execute() method but doesn’t know the details of the operation. It simply knows that it needs to call the command.
 * 5. Client Uses the Command: The client creates the concrete command objects and associates them with the receiver. It then assigns commands to the invoker, which will call them when needed.
 */

#include <iostream>
#include <queue>
#include <memory>
#include <string>


// Receiver -- drink maker in this practice
class Receiver {
public:
    void action(const std::string& drink) {
        std::cout << drink << " is ready!" << std::endl;
    }
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

// final, devirtualization
class OrderCommand final : public Command {
private:
    std::string drink_;
    std::shared_ptr<Receiver> receiver_;

public:
    OrderCommand(std::string drink, std::shared_ptr<Receiver> receiver) 
        : drink_(std::move(drink)), receiver_(std::move(receiver)) {}

    void execute() override {
        if (receiver_) {
            receiver_->action(drink_);
        }
    }
};


// Invoker -- order machine that takes order in this practice
class Invoker {
private:
    std::queue<std::unique_ptr<Command>> commandQueue_;

public:
    // rvalue reference indicating that argument is temporary object and needs to move
    void receiveCommand(std::unique_ptr<Command>&& command) {
        commandQueue_.push(std::move(command));
    }

    void executeCommand() {
        while (!commandQueue_.empty()) {
            auto command = std::move(commandQueue_.front());
            commandQueue_.pop();
            command->execute();
        }
    }
};


int main() {
    int N;
    std::cin >> N;

    Invoker orderMachine;
    auto drinkMaker = std::make_shared<Receiver>();

    std::string drink;
    while (N--) {
        std::cin >> drink;
        orderMachine.receiveCommand(std::make_unique<OrderCommand>(drink, drinkMaker));
    }

    orderMachine.executeCommand();
    return 0;
}