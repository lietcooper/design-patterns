/**
 * Use unorderd_map for factory selection
 * 
 */
#include <iostream>
#include <memory>
#include <unordered_map>
using namespace std;

class Furniture {
public:
    virtual void info() = 0;
    virtual ~Furniture() = default;
};

// chair interface
class Chair : public Furniture{
};

class ModernChair : public Chair {
public:
    void info() override {
        cout << "modern chair" << endl;
    }
};

class ClassicalChair : public Chair {
public: 
    void info() override {
        cout << "classical chair" << endl;
    }
};

// sofa interface
class Sofa : public Furniture {
};

class ModernSofa : public Sofa {
public:
    void info() override {
        cout << "modern sofa" << endl;
    }
};

class ClassicalSofa : public Sofa {
public:
    void info() override {
        cout << "classical sofa" << endl;
    }
};

// factory interface
class Factory {
public:
    virtual unique_ptr<Chair> createChair() = 0;
    virtual unique_ptr<Sofa> createSofa() = 0;
    virtual ~Factory() = default;
};

class ModernFactory : public Factory {
public:
    unique_ptr<Chair> createChair() override {
        return make_unique<ModernChair>();
    }
    unique_ptr<Sofa> createSofa() override {
        return make_unique<ModernSofa>();
    }
};

class ClassicalFactory : public Factory {
public: 
    unique_ptr<Chair> createChair() override {
        return make_unique<ClassicalChair>();
    }
    unique_ptr<Sofa> createSofa() override {
        return make_unique<ClassicalSofa>();
    }
};

int main() {
    int n;
    cin >> n;
    ModernFactory modernFactory;
    ClassicalFactory classicalFactory;

    unordered_map<string, Factory*> factories = {
        {"modern", &modernFactory},
        {"classical", &classicalFactory}
    };


    for (int i = 0; i < n; ++i) {
        string style;
        cin >> style;
        
        Factory* factory = factories[style];
        auto chair = factory->createChair();
        auto sofa = factory->createSofa();
        chair->info();
        sofa->info();
    }
    return 0;
}