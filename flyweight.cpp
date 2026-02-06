/**
 * Step 1: Identify Shared and Unique Data: Arrange the data in your objects first. Determine which information is specific to each object (known as extrinsic data) and which can be shared across objects (known as intrinsic data).
 * Step 2: Create a Flyweight Class: This class will hold the intrinsic (shared) data. All instances of this class represent objects with similar data.
 * Step 3: Build a Flyweight Factory: This factory class manages instances of the Flyweight objects. When a new object is needed, the factory checks if an object with the
 *  same shared data already exists. If it does, it reuses that object; if not, it creates a new one.
 * Step 4: Pass Unique Data as Needed: The extrinsic data, or data specific to that instance(extrinsic data), should be passed as a parameter when using an object. In this *   manner, the object can act in a unique way without storing all of the data.
 * Step 5: Use Flyweights Instead of Creating New Objects: Now, instead of creating new objects directly, always request them through the factory. The factory will manage
 *  all shared instances and reuse them where possible.
 */


#include <iostream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <memory>


enum ShapeType {
    CIRCLE, RECTANGLE, TRIANGLE
};

std::string shapeTypeToString(ShapeType type) {
    switch (type) {
        case CIRCLE:
            return "CIRCLE";
        case RECTANGLE:
            return "RECTANGLE";
        case TRIANGLE:
            return "TRIANGLE";
        default:
            return "EMPTY";
    }
}


class IShape {
public:
    virtual std::string draw(int x, int y) = 0;
    virtual ~IShape() = default;
};


class Shape : public IShape {
public:
    Shape(ShapeType type) : _type(type) {} 

    std::string draw(int x, int y) override {
        std::ostringstream oss;
        oss << "at (" << x << ", " << y << ")" << std::endl;
        return oss.str();  // concatenate result string in the proccessCommand method later
    } 

private:
    // DO NOT record whether a shaped is created or not. Leave it to factory.
    ShapeType _type;
};


class ShapeFactory {
public:
    std::pair<std::shared_ptr<IShape>, bool> getShape(ShapeType type) {
        bool shared = true;
        if (shapes.find(type) == shapes.end()) {
            shapes[type] = std::make_shared<Shape>(type);
            shared = false;
        }
        return {shapes[type], shared};
    }

private:
    std::unordered_map<ShapeType, std::shared_ptr<IShape>> shapes;
};


void processCommand(ShapeFactory& factory, const std::string& command) {
    std::istringstream iss(command);
    std::string shapeTypeStr;
    int x, y;

    iss >> shapeTypeStr >> x >>y;

    ShapeType type;
    if (shapeTypeStr == "CIRCLE") {
        type = CIRCLE;
    } else if (shapeTypeStr == "RECTANGLE") {
        type = RECTANGLE;
    } else if (shapeTypeStr == "TRIANGLE") {
        type = TRIANGLE;
    } else {
        std::cerr << "Invalid shape type: " << shapeTypeStr << std::endl;
        return;
    }

    // concatenate result string.
    std::ostringstream oss;
    oss << shapeTypeToString(type);
    auto result = factory.getShape(type);
    if (result.second) {
        oss << " shared ";
    } else {
        oss << " drawn ";
    }

    oss << result.first->draw(x, y);
    std::cout << oss.str();
}


int main() {
    ShapeFactory factory;
    std::string command;

    while (std::getline(std::cin, command)) {
        processCommand(factory, command);
    }

    return 0;
}
