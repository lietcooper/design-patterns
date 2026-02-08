/**
 * 1. Iterator Interface/Abstract Class
 * Defines the interface for accessing and traversing elements in the collection. It typically includes methods like hasNext(), next(), and optionally remove().
 * 2. Concrete Iterator
 * Implements the Iterator interface and maintains the current position in the traversal of the aggregate. It provides the actual implementation for the traversal operations defined in the Iterator interface.
 * 3. Aggregate Interface/Abstract Class
 * Defines the interface for creating an Iterator object. It typically includes a method like createIterator() that returns an Iterator object for the collection.
 * 4. Concrete Aggregate
 * Implements the Aggregate interface and represents the collection of objects. It provides the implementation for creating an Iterator object that can traverse its elements.
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>


class Student {
public:
    Student(std::string name, std::string id) : name_(std::move(name)), id_(std::move(id)) {}
    std::string getInfo() const { return name_ + " " + id_; }
private:
    std::string name_;
    std::string id_;
};

// 1. iterator interface
template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

// 2. Aggregate interface
template <typename T>
class StudentAggregate {
public:
    virtual ~StudentAggregate() = default;
    virtual std::unique_ptr<Iterator<T>> createIterator() = 0;
};

// 3. concrete iterator
class StudentIterator : public Iterator<Student> {
private:
    const std::vector<Student>& students_;
    size_t position_ = 0;

public:
    StudentIterator(const std::vector<Student>& students) : students_(students) {}

    bool hasNext() override {
        return position_ < students_.size();
    }

    Student next() override {
        return students_[position_++];
    }
};

// 4. concrete aggregate
class StudentList : public StudentAggregate<Student> {
private:
    std::vector<Student> students_;

public:
    void addStudent(const Student& s) {
        students_.push_back(s);
    }

    std::unique_ptr<Iterator<Student>> createIterator() override {
        return std::make_unique<StudentIterator>(students_);
    }
};

int main() {
    int N;
    if (!(std::cin >> N)) return 0;

    StudentList list;
    for (int i = 0; i < N; ++i) {
        std::string name, id;
        std::cin >> name >> id;
        list.addStudent(Student(name, id));
    }

    auto it = list.createIterator();
    while (it->hasNext()) {
        Student s = it->next();
        std::cout << s.getInfo() << std::endl;
    }

    return 0;
}