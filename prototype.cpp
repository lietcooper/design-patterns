/**
 * [Step 1]: Define the Prototype Interface
 * Create an interface or abstract class that declares the clone() method and other common behaviors.
 * [Step 2]: Implement Concrete Prototypes
 * Develop concrete classes (such as Circle) that implement the prototype interface and define how objects are cloned.
 * [Step 3]: Create the Client
 * Write client code that holds a reference to the prototype instead of instantiating objects directly.
 * [Step 4]: Clone and Customize Objects
 * Use the clone() method to create new objects and modify their properties as needed at runtime. 
 */

#include <iostream>
#include <string>
#include <memory>
#include <sstream>


class Shape {
public:
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual std::string getDetails() const = 0;
    virtual ~Shape() = default;
    Shape(const std::string& color): color_(color) {}
    std::string color_;
};

class Rectangle : public Shape {
private:
    int height_, width_;
public:
    // constructor, use const string& for temporary variable
    Rectangle(const std::string& color, int width, int height)
        : Shape(color), height_(height), width_(width) {}

    // copy constructor, can be omitted, the compiler will generate default one
    // Rectangle(const Rectangle&) = default;

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this); // use copy constructor
    }

    std::string getDetails() const override {
        std::ostringstream oss;
        oss << "Color: " << color_ << ", Width: " << width_ << ", Height: " << height_;
        return oss.str();
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string color;
    int width, height;
    std::cin >> color >> width >> height;

    std::unique_ptr<Shape> originalRect = std::make_unique<Rectangle>(color, width, height);


    int n;
    std::cin >> n;
    while (n--) {
        std::unique_ptr<Shape> cloneRect = originalRect->clone();
        std::cout << cloneRect->getDetails() << std::endl;
    }
    return 0;
}
