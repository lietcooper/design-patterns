/**
 * Client: The client initiates the process by requesting the Originator to perform some operation that may modify its state or require the state to be saved. For example, the client might trigger an action like "save state" or "restore state."
 * Originator: The Originator either produces a Memento to save its current state (if the request is to save state) or retrieves a Memento to restore its prior state (if the request is to restore state).
 * Caretaker: The Caretaker acts as an intermediary between the client and the Originator, managing the Memento objects.
 * 
 * The caretaker calls the createMemento() method on the originator asking the originator to pass it a memento object.
 * At this point the originator creates a memento object saving its internal state and passes the memento to the caretaker.
 * The caretaker maintains the memento object and performs the operation. In case of the need to undo the operation, the caretaker calls the setMemento() method on the originator passing the maintained memento object.
 * The originator would accept the memento, using it to restore its previous state.
 */

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>


// Memento
class Memento {
private:
    int state_;

public:
    Memento(int state) : state_(state) {}

    int getState() {
        return state_;
    }
};


// Caretaker
class History {
private:
    std::vector<std::shared_ptr<Memento>> undos_;
    std::vector<std::shared_ptr<Memento>> redos_;

public:
    void addUndo(std::shared_ptr<Memento> op) {
        redos_.clear();
        undos_.emplace_back(std::move(op));
    }

    void addRedo(std::shared_ptr<Memento> op) {
        redos_.emplace_back(op);
    }

    std::shared_ptr<Memento> undo() {
        auto op = std::move(undos_.back());
        undos_.pop_back();
        return op;
    }

    std::shared_ptr<Memento> redo() {
        auto op = std::move(redos_.back());
        redos_.pop_back();
        return op;
    }
};


// Originator
class Counter {
private:
    int state_;
    std::unique_ptr<History> history_;

public:
    Counter(std::unique_ptr<History> history) : state_(0), history_(std::move(history)) {}

    void showState() {
        std::cout << state_ << std::endl;
    }

    std::shared_ptr<Memento> createMemento() {
        return std::make_shared<Memento>(state_);
    }

    void increment() {
        history_->addUndo(createMemento());
        state_++;
    }

    void decrement() {
        history_->addUndo(createMemento());
        state_--;
    }

    void undo() {
        auto op = history_->undo();
        history_->addRedo(createMemento());
        state_ = op->getState();
    }

    void redo() {
        auto op = history_->redo();
        history_->addUndo(createMemento());
        state_ = op->getState();
    }
    
};


int main() {
    Counter counter(std::make_unique<History>());
    
    std::string op;
    while (std::cin >> op) {
        if (op == "Increment") {
            counter.increment();
        } else if (op == "Decrement") {
            counter.decrement();
        } else if (op == "Undo") {
            counter.undo();
        } else if (op == "Redo") {
            counter.redo();
        } else {
            std::cerr << "Unknow operation." << std::endl;
        }

        counter.showState();
    }

    return 0;
}