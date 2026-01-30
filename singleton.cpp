/**
 * Design a shopping cart manager using singleton.
 * Add items and the quantity to cart and print everything in the cart in the end.
 * 
 * Input:
 * Item name and quantity, separated by whitespace
 * 
 * Output:
 * Print everything added to cart in the format: "itemName quantity"
 * 
 * Example:
 *  Input:
 *  Apple 3
 *  Banana 4
 *  Orange 5
 * 
 *  Output:
 *  Apple 3
 *  Banana 4
 *  Orange 5
 * 
 * 
 * For test in command line, press Ctrl + D to indicate End of File (EOF)
 * or write input in a txt file and pass the file the program by command "./myProgram < input.txt"
 */

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class CartManager {
private:
    unordered_map<string, int> quantities;
    vector<string> items;
    CartManager() {}
    CartManager(const CartManager&) = delete;  // prevent copy
    CartManager& operator=(const CartManager&) = delete;  // prevent assign

public:
    static CartManager& getInstance() {
        static CartManager instance;
        return instance;
    }

    void addToCart(const string& item, int quantity) {
        if (!quantities.count(item)) {
            items.push_back(item);
        }
        quantities[item] += quantity;
    }

    vector<pair<string, int>> viewCart() const {
        vector<pair<string, int>> cart;
        for (const string& s : items) {
            cart.emplace_back(s, quantities.at(s));
        }
        return cart;
    }
};


int main() {
    string item;
    int quantity;
    CartManager& cartManager = CartManager::getInstance();  // reference the instance rather than copy
    while (cin >> item >> quantity) {
        cartManager.addToCart(item, quantity);
    }

    auto cart = cartManager.viewCart();
    for (auto& item : cart) {
        cout << item.first << " " << item.second << endl;
    }

    return 0;
}