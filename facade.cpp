/**
 * Step 1: First, determine the complex subsystems or components that the client needs to interact with.
 * Step 2: Build a facade class that serves as the middle layer between the client and the subsystems. This class should offer simplified methods that wrap the interactions with the subsystems.
 * Step 3: Expose a clear, high-level interface in the facade class. This interface will include the methods that the client will use, hiding the internal complexity.
 * Step 4: Inside the facade methods, delegate the requests to the appropriate subsystem classes to perform the actual operations.
 * Step 5: The client now interacts only with the facade, which manages the underlying calls to the subsystems, simplifying the client’s experience.
 */

 #include <iostream>
#include <memory>

class Appliance {
public:
    virtual std::string getName() const {
        return this->_name;
    }
    virtual void turnOff() const {
        std::cout << this->getName() << " is turned off." << std::endl;
    }
    virtual ~Appliance() = default;

protected:
    Appliance(std::string name) : _name(name) {}

private:
    std::string _name;
};


class AC : public Appliance {
public:
    AC() : Appliance("Air Conditioner") {}
};


class Lamp : public Appliance {
public:
    Lamp() : Appliance("Desk Lamp") {}
};


class Television : public Appliance {
public:
    Television() : Appliance("Television") {}
};



class FacadeControl {
public:
    void setAC(std::unique_ptr<Appliance> ac) {
        _ac = std::move(ac);
    }

    void setLamp(std::unique_ptr<Appliance> lamp) {
        _lamp = std::move(lamp);
    }

    void setTV(std::unique_ptr<Appliance> tv) {
        _tv = std::move(tv);
    }

    void turnOffDevice(int choice) {
        switch (choice) {
            case 1:
                _ac->turnOff();
                break;
            case 2:
                _lamp->turnOff();
                break;
            case 3:
                _tv->turnOff();
                break;
            case 4:  // turn off all devices
                _ac->turnOff();
                _lamp->turnOff();
                _tv->turnOff();
                std::cout << "All devices are off." << std::endl;
                break;
            default:
                std::cout << "Invalid device code." << std::endl;      
        }
    }

private:
    std::unique_ptr<Appliance> _ac;
    std::unique_ptr<Appliance> _lamp;
    std::unique_ptr<Appliance> _tv;
};


int main() {
    int N, n;
    std::cin >> N;

    FacadeControl fc;
    fc.setAC(std::make_unique<AC>());
    fc.setLamp(std::make_unique<Lamp>());
    fc.setTV(std::make_unique<Television>());

    while (N--) {
        std::cin >> n;
        fc.turnOffDevice(n);
    }

    return 0;
}