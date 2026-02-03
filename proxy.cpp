/**
 * Create the Real Object Interface: Define an interface or abstract class that represents the operations the real object will provide. Both the real object and proxy will implement this interface.
 * Create the Real Object: This class implements the interface and contains the actual logic or operation that the client wants to use.
 * Create the Proxy Class: The proxy class also implements the same interface as the real object. It holds a reference to the real object and controls access to it. The proxy can add extra logic like logging, caching, or security checks before calling the real object's methods.
 * Client Uses the Proxy: Instead of creating the real object directly, the client interacts with the proxy. The proxy decides when and how to forward the client’s request to the real object.
 */

#include <iostream>
#include <memory>


// abstract subject
class House {
public:
    virtual int getArea() const = 0;
    virtual void show() const = 0;
    virtual ~House() = default;
};


// real subject
class RealHouse : public House {
public:
    RealHouse(int area) : _area(area) {}

    int getArea() const override {
        return this->_area;
    }

    void show() const override  {
        std::cout << "YES" << std::endl;
    }
    
private:
    int _area;
};


// proxy
class Proxy : public House{
private:
    static constexpr int SIZE = 100;
    std::unique_ptr<House> _house;
public:
    // Dependency injection, Proxy only uses house, not create house; The house type depends on injection
    Proxy(std::unique_ptr<House> house) : _house(std::move(house)) {}  // move from argument to member variable

    int getArea() const override {
        return this->_house->getArea();
    }

    void show() const override {
        if (_house->getArea() >= SIZE) {
            _house->show();
        } else {
            std::cout << "NO" << std::endl;
        }
    }
};


int main() {
    int N, n;
    std::cin >> N;

    while (N--) {
        std::cin >> n;
        auto house = std::make_unique<RealHouse>(n);
        Proxy proxy(std::move(house));  // move resource to argument
        proxy.show();
    }
    return 0;
}