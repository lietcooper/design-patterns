/**
 * Step 1: The client initiates a request by calling a method on the adapter via the target interface.
 * Step 2: The adapter maps or transforms the client's request into a format that the adaptee can understand using the adaptee's interface.
 * Step 3: The adaptee does the actual job based on the translated request from the adapter.
 * Step 4: The client receives the results of the call, remaining unaware of the adapter's presence or the specific details of the adaptee.
 */
#include <iostream>
#include <memory>

// Target interface
class TypeC {
public:
    virtual void chargeWithTypeC() = 0;
    virtual ~TypeC() = default;
};


// concrete Target
class NativeTypeC : public TypeC {
public:
    void chargeWithTypeC() override {
        std::cout << "TypeC" << std::endl;
    }
};


// Adaptee
class USB {
public:
    void chargeWithUSB() {
        std::cout << "USB Adapter" << std::endl;
    }
};


// Adapter
class USBToTypeCAdapter : public TypeC {
public:
    void chargeWithTypeC() override {
       usb.chargeWithUSB();
    }

private:
    USB usb;
};


// Client
class Computer {
public:
    Computer(std::unique_ptr<TypeC> typeCCharger) : typeCCharger(std::move(typeCCharger)) {}
    void charge() {
        typeCCharger->chargeWithTypeC();
    }
private:
    std::unique_ptr<TypeC> typeCCharger;
};


int main() {
    
    int N, n;
    std::cin >> N;
    std::cin.ignore();  // consume new line
    
    while (N--) {
        std::cin >> n;
        if (n == 1) {
            Computer computer(std::make_unique<NativeTypeC>());
            computer.charge();
        } else if (n == 2) {
            Computer computer(std::make_unique<USBToTypeCAdapter>());
            computer.charge();
        }
    }

    return 0;
}


