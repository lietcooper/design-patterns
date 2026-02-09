/**
 * The Visitor design pattern works by separating an algorithm from the objects on which it operates, allowing you to add new operations without changing the existing object structures. Below is how it functions:
 * Step 1: First, you define an interface for the elements (objects) that will accept visitors. This interface usually includes a method for accepting a visitor.
 * Step 2: Then, you create concrete classes that implement the element interface. Each class represents an object in your structure and includes the method to accept a visitor.
 * Step 3: Next, you define a visitor interface that declares a visit method for each concrete element type. This method will be called when a visitor visits a specific element.
 * Step 4: You implement one or more concrete visitor classes, each providing specific operations for the various element types. Each visit method contains the logic for what to do when visiting that element.
 * Step 5: When a visitor is applied to an element, the element calls the appropriate visit method on the visitor, passing itself as an argument. This allows the visitor to operate on the element and perform the desired actions.
 * 
 */

#include <iostream>
#include <memory>
#include <vector>

#define PI 3.14


// Visitor interface
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(class Circle& ci) = 0;
    virtual void visit(class Square& sq) = 0;
};


// Element interface
class Shape {
public:
    virtual ~Shape() = default;
    virtual void accept(Visitor& v) = 0;
};

// Concrete element
class Square : public Shape {
private:
    int _l, _w;

public:
    Square(int l, int w) : _l(l), _w(w) {}

    void accept(Visitor& v) override {
        v.visit(*this);
    }

    int getLength() {
        return _l;
    }

    int getWidth() {
        return _w;
    }
};


// Concrete element
class Circle : public Shape {
private:
    int _r;

public:
    Circle(int r) : _r(r) {}

    void accept(Visitor& v) override {
        v.visit(*this);
    }

    int getRadius() {
        return _r;
    }
};


class AreaCalculatorVisitor : public Visitor {
public:
    virtual void visit( Circle& ci) override {
        std::cout << ci.getRadius() * ci.getRadius() * PI << std::endl;
    }

    virtual void visit( Square& sq) override {
        std::cout << sq.getLength() * sq.getWidth() << std::endl;
    }
};


class Draw {
private:
    std::vector<std::shared_ptr<Shape>> _shapes;

public:
    void addShape(std::shared_ptr<Shape> shape) {
        _shapes.emplace_back(std::move(shape));
    }

    void drawShapes(Visitor& v) {
        for (auto& shape : _shapes)
            shape->accept(v);
    }
};


int main() {
    int N;
    std::cin >> N;
    Draw draw;
    AreaCalculatorVisitor areaCalculator;

    for (int i = 0; i < N; ++i) {
        std::string type;
        std::cin >> type;

        if (type == "Rectangle") {
            int l, w;
            std::cin >> l >> w;
            draw.addShape(std::make_shared<Square>(l, w));
        } else if (type == "Circle") {
            int r;
            std::cin >> r;
            draw.addShape(std::make_shared<Circle>(r));
        }
    }

    draw.drawShapes(areaCalculator);
    return 0;
}
