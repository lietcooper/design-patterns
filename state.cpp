/**
 * Purpose – Lets an object change behavior based on its state, avoiding complex conditionals by using separate state classes.
 * Context – The object whose behavior varies (e.g., media player: Playing, Paused, Stopped).
 * State Interface – Defines common actions all states must implement.
 * Concrete States – Implement the interface, each defining behavior for a specific state.
 * Context Class – Holds the current state and delegates actions to it, enabling dynamic state switching at runtime.
 */

#include <iostream>
#include <unordered_map>
#include <string>

// State interface
class State {
protected:
    State() = default;

public:
    virtual ~State() = default;
    virtual void handleRequest() = 0;
};


class OnState : public State {
public:
    void handleRequest() {
        std::cout << "Light is ON\n";
    }
};


class OffState : public State {
public:
    void handleRequest() override {
        std::cout << "Light is OFF\n";
    }
};


class BlinkState : public State {
public:
    void handleRequest() override {
        std::cout << "Light is Blinking\n";
    }
};


// Context
class Light {
private:
    State* state_;

public:
    void setState(State* state) {
        state_ = state;
    }

    void request() {
        state_->handleRequest();
    }
};


int main() {
    int N;
    std::cin >> N;
    
    OnState on;
    OffState off;
    BlinkState blink;
    std::unordered_map<std::string, State*> states = {
        {"ON", &on},
        {"OFF", &off},
        {"BLINK", &blink}
    };

    Light light;
    State* state;
    std::string s;
    while (N--) {
        std::cin >> s;
        state = states[s];
        light.setState(state);
        light.request();
    }
    return 0;
}
