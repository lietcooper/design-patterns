/**
 * Component: The Component is the common interface for all objects in the composition. It defines the methods that are common to both leaf and composite objects.
 * Leaf: The Leaf is the individual object that does not have any children. It implements the component interface and provides the specific functionality for individual objects.
 * Composite: The Composite is the container object that can hold Leaf objects as well as the other Composite objects. It implements the Component interface and provides methods for adding, removing and accessing children.
 * Client: The Client is responsible for using the Component interface to work with objects in the composition. It treats both Leaf and Composite objects uniformly.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <stack>

// ==================== Composite Pattern Core Classes ====================

// component interface
class Component {
public:
    virtual ~Component() = default;
    virtual void display(int depth) const = 0;
    virtual std::string getName() const = 0;
};

// composite
class Department : public Component {
private:
    std::string name_;
    std::vector<std::shared_ptr<Component>> children_;

public:
    Department(const std::string& name) : name_(name) {}

    std::string getName() const override {
        return name_;
    }

    void add(std::shared_ptr<Component> component) {
        children_.push_back(component);
    }

    void display(int depth) const override {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
        std::cout << name_ << std::endl;

        for (const auto& child : children_) {
            child->display(depth + 1);
        }
    }
};

// leaf
class Employee : public Component {
private:
    std::string name_;

public:
    Employee(const std::string& name) : name_(name) {}

    std::string getName() const override {
        return name_;
    }

    void display(int depth) const override {
        for (int i = 0; i < depth; ++i) {
            std::cout << "  ";
        }
        std::cout << name_ << std::endl;
    }
};

// client
class Company {
private:
    std::shared_ptr<Department> root_;

public:
    Company(const std::string& name) {
        root_ = std::make_shared<Department>(name);
    }

    std::shared_ptr<Department> getRoot() const {
        return root_;
    }

    void display() const {
        std::cout << "Company Structure:" << std::endl;
        root_->display(0);
    }
};

// ==================== Parser and Tree builder ====================

// DTO
struct NodeInfo {
    std::string type;
    std::string name;
    int depth;
};

// Parser
class Parser {
public:
    std::vector<NodeInfo> parse(std::istream& input, int n) {
        std::vector<NodeInfo> nodes;

        for (int i = 0; i < n; ++i) {
            std::string line;
            std::getline(input, line);

            int spaces = countLeadingSpaces(line);
            int depth = spaces / 2;
            std::string content = line.substr(spaces);

            std::istringstream iss(content);
            std::string type;
            std::string name;
            iss >> type;
            std::getline(iss, name);
            
            if (!name.empty()) {
                size_t start = name.find_first_not_of(" ");
                if (start != std::string::npos) {
                    name = name.substr(start);
                }
            }

            nodes.push_back({type, name, depth});
        }

        return nodes;
    }

private:
    int countLeadingSpaces(const std::string& s) {
        int count = 0;
        for (char c : s) {
            if (c == ' ') {
                count++;
            } else {
                break;
            }
        }
        return count;
    }
};

// Tree Builder
class TreeBuilder {
public:
    void build(Company& company, const std::vector<NodeInfo>& nodes) {
        std::stack<std::shared_ptr<Department>> departmentStack;
        departmentStack.push(company.getRoot());
        
        // for newly added departments
        std::shared_ptr<Department> lastDepartment = company.getRoot();

        for (const auto& node : nodes) {
            if (node.depth == 0) {
                // top node, add to root
                if (node.type == "D") {
                    auto dept = std::make_shared<Department>(node.name);
                    company.getRoot()->add(dept);
                    lastDepartment = dept;
                    
                    // reset stack
                    while (departmentStack.size() > 1) {
                        departmentStack.pop();
                    }
                    departmentStack.push(dept);
                } 
                else if (node.type == "E") {
                    // add employee to most recent dep
                    auto emp = std::make_shared<Employee>(node.name);
                    lastDepartment->add(emp);
                }
            } 
            else {
                // non-top node, find parent node by depth
                while (static_cast<size_t>(node.depth) < departmentStack.size() - 1) {
                    departmentStack.pop();
                }
                auto parent = departmentStack.top();

                if (node.type == "D") {
                    auto dept = std::make_shared<Department>(node.name);
                    parent->add(dept);
                    departmentStack.push(dept);
                    lastDepartment = dept;
                } 
                else if (node.type == "E") {
                    auto emp = std::make_shared<Employee>(node.name);
                    parent->add(emp);
                }
            }
        }
    }
};

// ==================== Entry ====================

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Read company name
    std::string companyName;
    std::getline(std::cin, companyName);
    Company company(companyName);

    // Read number of nodes
    int n;
    std::cin >> n;
    std::cin.ignore();

    Parser parser;
    TreeBuilder builder;

    auto nodes = parser.parse(std::cin, n);
    builder.build(company, nodes);
    company.display();

    return 0;
}