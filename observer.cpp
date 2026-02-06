/**
 * Subject: Maintains a list of observers, provides methods to add/remove them, and notifies them of state changes.
 * Observer: Defines an interface with an update() method to ensure all observers receive updates consistently.
 * ConcreteSubject: A specific subject that holds actual data. On state change, it notifies registered observers (e.g., a weather station).
 * ConcreteObserver: Implements the observer interface and reacts to subject updates (e.g., a weather app showing weather updates).
 */

#include <iostream>
#include <unordered_set>
#include <memory>


// Observer interface
class Observer {
public:
    virtual ~Observer() = default;
    virtual void notified(int time) = 0;
};


// Subject interface
class Subject {
public:
    virtual ~Subject() = default;
    virtual void notify() = 0;
    virtual void registerSubscriber(std::shared_ptr<Observer> subscriber) = 0;
};


// concrete subject
class Clock : public Subject {
private:
    std::unordered_set<std::shared_ptr<Observer>> students_;
    int hour_ = 0;

public:
    // push mode
    void notify() override {
        for (auto& student : students_) {
            student->notified(hour_);
        }
    }

    void registerSubscriber(std::shared_ptr<Observer> student) override {
        students_.insert(student);
    }

    void tick() {
        hour_ = (hour_ + 1) % 24;
        notify();
    }
};


// concrete observer
class Student : public Observer {
private:
    std::string name_;

public:
    Student(std::string name) : name_(name) {}

    // push mode
    void notified(int time) override {
        std:: cout << name_ << " " << time << std::endl;
    }
};


int main() {
    int N, n;
    std::string name;

    std::cin >> N;

    Clock clock;
    while (N--) {
        std::cin >> name;
        clock.registerSubscriber(std::make_shared<Student>(name));
    }

    std::cin >> n;
    while (n--) clock.tick();

    return 0;
}
