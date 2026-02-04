/**
 * The Bridge design pattern allows you to separate the abstraction from the implementation. It is a structural design pattern. 
 * 
 * Abstraction – core of the bridge design pattern and defines the crux. Contains a reference to the implementer.
 * Refined Abstraction – Extends the abstraction takes the finer detail one level below. Hides the finer elements from implementers.
 * Implementer – It defines the interface for implementation classes. This interface does not need to correspond directly to the abstraction interface and can be very different. Abstraction imp provides an implementation in terms of operations provided by the Implementer interface.
 * Concrete Implementation – Implements the above implementer by providing the concrete implementation. 
 * */

#include <iostream>
#include <sstream>
#include <memory>


// Implementation
class TV {
public:
    virtual void turnOn() {
        std::cout << this->_brand << " TV is ON" << std::endl;
    }

    virtual void turnOff() {
        std::cout << this->_brand << " TV is OFF" << std::endl;
    }

    virtual void switchChannel() {
        std::cout << "Switching " << this->_brand << " TV channel" << std::endl;
    }

    virtual ~TV() = default;

protected:
    TV(std::string brand) : _brand(brand) {}

private:
    const std::string _brand;
};


class SonyTV : public TV {
public:
    SonyTV() : TV("Sony"){}
};


class TclTV : public TV {
public:
    TclTV() : TV("TCL") {}
};


// Abstraction
class RemoteControl {
public:
    virtual void perform() = 0;
    virtual ~RemoteControl() = default;
protected:
    RemoteControl(std::unique_ptr<TV> tv) : _tv(std::move(tv)) {}
    std::unique_ptr<TV> _tv;
};


class PowerOperation : public RemoteControl {
public:
    PowerOperation(std::unique_ptr<TV> tv) : RemoteControl(std::move(tv)) {}
    void perform() override {
        _tv->turnOn();
    }
};


class OffOperation : public RemoteControl {
public:
    OffOperation(std::unique_ptr<TV> tv) : RemoteControl(std::move(tv)) {}
    void perform() override {
        _tv->turnOff();
    }
};


class SwitchChannelOperation : public RemoteControl {
public:
    SwitchChannelOperation(std::unique_ptr<TV> tv) : RemoteControl(std::move(tv)) {}
    void perform() override {
        _tv->switchChannel();
    }
};


int main() {
    int N;
    std::cin >> N;
    
    while (N--) {

        int brand, operation;
        std::cin >> brand >> operation;

        std::unique_ptr<TV> tv;
        if (brand == 0) {
            tv = std::make_unique<SonyTV>();
        } else {
            tv = std::make_unique<TclTV>();
        }

        std::unique_ptr<RemoteControl> rc;
        if (operation == 2) {
            rc = std::make_unique<PowerOperation>(std::move(tv));
        } else if (operation == 3) {
            rc = std::make_unique<OffOperation>(std::move(tv));
        } else {
            rc = std::make_unique<SwitchChannelOperation>(std::move(tv));
        }

        rc->perform();
    }
    return 0;
}
