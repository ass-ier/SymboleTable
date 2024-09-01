//
//  main.cpp
//  SymbolTree
//
//  Created by Assier Anteneh Alemu on 22/08/2024.
//

#include <iostream>
#include <vector>
#include <string>
#include <map>

class Symbol {
public:
    std::string name;
    std::vector<int> argTypes;  // Vector to store types of arguments (represented as integers)

    Symbol(std::string name, std::vector<int> argTypes)
        : name(name), argTypes(argTypes) {}

    bool operator<(const Symbol& other) const {
        return name < other.name || (name == other.name && argTypes < other.argTypes);
    }
};

class TreeNode {
public:
    Symbol symbol;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Symbol symbol)
        : symbol(symbol), left(nullptr), right(nullptr) {}
};

class SymbolTable {
private:
    TreeNode* root;

    // Utility function to insert a node in the BST
    TreeNode* insert(TreeNode* node, Symbol symbol) {
        if (!node) {
            return new TreeNode(symbol); //If current node is empty it creates a treenode
        }

        //Recursive insertion function
        if (symbol < node->symbol) {
            node->left = insert(node->left, symbol);
        } else if (node->symbol < symbol) {
            node->right = insert(node->right, symbol);
        }

        return node;
    }

    // Utility function to search for a symbol in the BST
    TreeNode* search(TreeNode* node, Symbol symbol) {
        if (!node || (node->symbol.name == symbol.name && node->symbol.argTypes == symbol.argTypes)) {
            return node;
        }

        /* moves left if the Symbol being searched for is less than the current node's symbol, and right if it's greater. */
        if (symbol < node->symbol) {
            return search(node->left, symbol);
        } else {
            return search(node->right, symbol);
        }
    }

public:
    SymbolTable() : root(nullptr) {}

    // Function to insert a new symbol into the table
    void insert(std::string name, std::vector<int> argTypes) {
        Symbol newSymbol(name, argTypes);
        root = insert(root, newSymbol);
    }

    // Function to search for a symbol
    bool search(std::string name, std::vector<int> argTypes) {
        Symbol symbol(name, argTypes);
        TreeNode* result = search(root, symbol);
        return result != nullptr; //If nullPointer, return false otherwise true
    }
};

int main() {
    SymbolTable table;

    // Insert overloaded functions
    table.insert("foo", {1, 2}); // foo(int, float)
    table.insert("foo", {1});    // foo(int)
    table.insert("bar", {1, 2, 3}); // bar(int, float, double)

    // Search for specific overloads
    std::cout << "Searching for foo(int, float): " << table.search("foo", {1, 2}) << std::endl; // Expected output: 1 (true)
    std::cout << "Searching for foo(int): " << table.search("foo", {1}) << std::endl; // Expected output: 1 (true)
    std::cout << "Searching for foo(float): " << table.search("foo", {2}) << std::endl; // Expected output: 0 (false)
    std::cout << "Searching for bar(int, float, double): " << table.search("bar", {1, 2, 3}) << std::endl; // Expected output: 1 (true)

    return 0;
}

