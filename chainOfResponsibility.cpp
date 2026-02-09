/**
 * Implementation of Chain of Responsibility Design Pattern
 * Below are the main steps for how to implement chain of responsibility design pattern:
 *
 * Step 1: Define the Handler Interface: Create an interface with methods for setting the next handler and processing requests.
 * Step 2: Create Concrete Handlers: Implement the handler interface in multiple classes, each handling specific requests and passing unhandled requests to the next handler.
 * Step 3: Set Up the Chain: Create instances of your handlers and link them together by setting the next handler for each one.
 * Step 4: Send Requests: Use the first handler in the chain to send requests, allowing each handler to decide whether to process it or pass it along.
 * 
 * Practice:
 * In Jack's company, leave requests need to be submitted through the OA system. 
 * The entire request process involves multiple handlers, each responsible for processing different ranges of leave days. 
 * If a handler cannot process the request, it is passed on to the next handler.  
 * Please implement the Chain of Responsibility pattern to find the appropriate handler based on the number of leave days requested.
 * 
 * The approval chain of responsibility consists of a Supervisor, a Manager, and a Director, 
 * who can handle leave requests of 3 days, 7 days, and 10 days respectively.  Requests exceeding 10 days will be rejected.
 */


/**
 * Implementation of Chain of Responsibility Design Pattern
 * Below are the main steps for how to implement chain of responsibility design pattern:
 *
 * Step 1: Define the Handler Interface: Create an interface with methods for setting the next handler and processing requests.
 * Step 2: Create Concrete Handlers: Implement the handler interface in multiple classes, each handling specific requests and passing unhandled requests to the next handler.
 * Step 3: Set Up the Chain: Create instances of your handlers and link them together by setting the next handler for each one.
 * Step 4: Send Requests: Use the first handler in the chain to send requests, allowing each handler to decide whether to process it or pass it along.
 * 
 * Practice:
 * In Jack's company, leave requests need to be submitted through the OA system. 
 * The entire request process involves multiple handlers, each responsible for processing different ranges of leave days. 
 * If a handler cannot process the request, it is passed on to the next handler.  
 * Please implement the Chain of Responsibility pattern to find the appropriate handler based on the number of leave days requested.
 * 
 * The approval chain of responsibility consists of a Supervisor, a Manager, and a Director, 
 * who can handle leave requests of 3 days, 7 days, and 10 days respectively.  Requests exceeding 10 days will be rejected.
 */


#include <iostream>
#include <memory>
#include <string>

// Handler interface
class Handler {
private:
    std::shared_ptr<Handler> _nextHandler;

public:
    virtual ~Handler() = default;
    virtual void setNextHandler(std::shared_ptr<Handler> handler) {
        _nextHandler = std::move(handler);
    }

    virtual std::shared_ptr<Handler> getNextHandler() {
        return _nextHandler;
    }

    virtual void handleRequest(std::string name, int days) = 0;

protected:
    Handler() = default;
};


class Supervisor final : public Handler {
private:
    const std::string TITLE = "Supervisor";
    const int MAX_DAY = 3;

public:
    void handleRequest(std::string name, int days) override {
        if (days <= MAX_DAY) {
            std::cout << name << " Approved by " << TITLE << ".\n";
        } else {
            getNextHandler()->handleRequest(std::move(name), days);
        }
    }
};

class Manager final : public Handler {
private:
    const std::string TITLE = "Manager";
    const int MAX_DAY = 7;

public:
    void handleRequest(std::string name, int days) override {
         if (days <= MAX_DAY) {
            std::cout << name << " Approved by " << TITLE << ".\n";
        } else {
            getNextHandler()->handleRequest(std::move(name), days);
        }
    }
};

class Director final : public Handler {
private:
    const std::string TITLE = "Director";
    const int MAX_DAY = 10;

public:
    void handleRequest(std::string name, int days) override {
         if (days <= MAX_DAY) {
            std::cout << name << " Approved by " << TITLE << ".\n";
        } else {
            std::cout << name << " Denied by " << TITLE << ".\n";
        }
    }
};


int main() {
    int N;
    std::cin >> N;

    std::string name;
    int days;

    auto supervisor = std::make_shared<Supervisor>();
    auto manager = std::make_shared<Manager>();
    auto director = std::make_shared<Director>();

    supervisor->setNextHandler(manager);
    manager->setNextHandler(director);

    while (std::cin >> name >> days) {
        supervisor->handleRequest(name, days);
    }
    return 0;
}