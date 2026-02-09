/**
 * 1. Mediator
 * The Mediator interface defines the communication contract, specifying methods that concrete mediators should implement to 
 * facilitate interactions among colleagues.. It encapsulates the logic for coordinating and managing the interactions between these objects,
 * promoting loose coupling and centralizing control over their communication.
 * 
 * 2. Colleague
 * Colleague classes are the components or objects that interact with each other. 
 * They communicate through the Mediator, and each colleague class is only aware of the mediator, not the other colleagues. 
 * This isolation ensures that changes in one colleague do not directly affect others.
 * 
 * 3. Concrete Mediator
 * Concrete Mediator is a specific implementation of the Mediator interface. 
 * It coordinates the communication between concrete colleague objects, 
 * handling their interactions and ensuring a well-organized collaboration while keeping them decoupled.
 * 
 * 4. Concrete colleague
 * Concrete Colleague classes are the specific implementations of the Colleague interface. 
 * They rely on the Mediator to communicate with other colleagues, avoiding direct dependencies and promoting a more flexible and maintainable system architecture.
 * 
 * 
 * A Concrete Colleague object sends a message or notification to the Concrete Mediator when it needs to communicate with another colleague.
 * The Concrete Mediator receives the message and determines how to coordinate the interaction between the specific Concrete Colleague objects involved.
 * The Concrete Mediator may then invoke methods on the Concrete Colleague objects to facilitate their communication.
 * Colleague objects interact indirectly through the Concrete Mediator, maintaining loose coupling and avoiding direct dependencies.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <sstream>
#include <stdexcept>


class Colleague {
public:
    virtual ~Colleague() = default;
    virtual void notify(const std::string& message) = 0;
    virtual void notified(const std::string& message) = 0;
    virtual std::string getName() = 0;
};


class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void forward(const std::string& colleague, const std::string& message) = 0;
    virtual void addColleague(std::shared_ptr<Colleague> Colleague) = 0;
};


class User : public Colleague {
private:
    std::string username_;
    std::weak_ptr<Mediator> mediator_;  // weak pointer to solve circular dependency.

public:
    User(std::string username, std::shared_ptr<Mediator> mediator) : username_(std::move(username)), mediator_(mediator) {}

    void notify(const std::string& message) override {
        // upgrade weak pointer to shared pointer
        if (auto mediator = mediator_.lock()) {
            mediator->forward(username_, message);
        } else {
            std::cerr << "Chat room does not exist!" << std:: endl;
        }    
    }

    void notified(const std::string& message) override {
        std::cout << username_ << " received: " << message << std::endl;
    }

    std::string getName() override {
        return username_;
    }
};


class ChatRoom : public Mediator {
private:
    std::vector<std::shared_ptr<Colleague>> users_;

public:
    void forward(const std::string& sender, const std::string& message) override {
        for (auto& user : users_) {
            if (user->getName() != sender) {
                user->notified(message);
            }
        }
    }

    void addColleague(std::shared_ptr<Colleague> colleague) override {
        users_.emplace_back(std::move(colleague));
    } 
};



int main() {
    int N;
    std::cin >> N;
    std::cin.ignore();
    std::string input;
    std::getline(std::cin, input);
    std::istringstream iss(input);
    

    auto mediator = std::make_shared<ChatRoom>();
    std::unordered_map<std::string, std::shared_ptr<Colleague>> users;


    for (int i = 0; i < N; ++i) {
        std::string username;
        iss >> username;
        auto user = std::make_shared<User>(username, mediator);
        users[username] = user;
        mediator->addColleague(user);
    }

    std::string sender, message;
    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        iss >> sender >> message;
        users[sender]->notify(message);
    }

    return 0;
}