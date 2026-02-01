/**
 * Create the Product Class: Define the object (product) that will be built. This class contains all the fields that make up the object.
 * Create the Builder Class: This class will have methods to set the different parts of the product. Each method returns the builder itself to allow method chaining.
 * Add a Build Method: In the builder class, add a method called build() (or similar) that assembles the product and returns the final object.
 * Use the Director (Optional): If needed, you can create a director class to control the building process and decide the order in which parts are constructed.
 * Client Uses the Builder: The client will use the builder to set the desired parts step by step and call the build() method to get the final product.
 * 
 * Example: build mountain bicycle and road bicycle.
 */

#include <iostream>
#include <unordered_map>

class Bike {
public:
    void setFrame(const std::string& frame) {
        this->frame = frame;
    }
    void setTire(const std::string& tire) {
        this->tire = tire;
    }
    
    void display() {
        std::cout << this->frame << " " << this->tire << std::endl;
    }

    // overload operator <<  (toString())
    // access private member; or use getter without friend keyword
    friend std::ostream& operator<<(std::ostream& os, const Bike& bike) {
        os << bike.frame << " " << bike.tire << std::endl;
        return os;
    }

private:
    std::string frame;
    std::string tire;
};


class BikeBuilder {
protected:
    Bike bike;
public:
    virtual BikeBuilder& buildFrame() = 0;
    virtual BikeBuilder& buildTire() = 0;
    virtual Bike getResult() {
        return std::move(this->bike); // solved non-empty status for creating new ones and avoided overheads of copying to new object.
    }
    virtual ~BikeBuilder() = default;
};

class MountainBikeBuilder : public BikeBuilder {

public:
    BikeBuilder& buildFrame() override {
        this->bike.setFrame("Aluminum Frame");
        return *this;
    }
    BikeBuilder& buildTire() override {
        this->bike.setTire("Knobby Tires");
        return *this;
    }
};

class RoadBikeBuilder : public BikeBuilder {
public:
    BikeBuilder& buildFrame() override {
        this->bike.setFrame("Carbon Frame");
        return *this;
    }
    BikeBuilder& buildTire() override {
        this->bike.setTire("Slim Tires");
        return *this;
    }
};

class Director {
public:
    Bike construct(BikeBuilder& bikeBuilder) {
        bikeBuilder.buildFrame();
        bikeBuilder.buildTire();
        return bikeBuilder.getResult();
    }
};

int main () {
    int N;
    std::cin >> N;
    
    MountainBikeBuilder mountainBikeBuilder;
    RoadBikeBuilder roadBikeBuilder;

    std::unordered_map<std::string, BikeBuilder*> bikeBuilders = {
        {"mountain", &mountainBikeBuilder},
        {"road", &roadBikeBuilder}
    };

    // Optional
    // Director director;

    while (N--) {
        std::string type;
        std::cin >> type;
        
        BikeBuilder* bikeBuilder;
        bikeBuilder = bikeBuilders[type];

        // Bike bike = director.construct(*bikeBuilder); // build with director

        Bike bike = bikeBuilder->buildFrame().buildTire().getResult();  // build using chaining

        
        bike.display();
        // cout << bike << std::endl;
    }

    return 0;
}