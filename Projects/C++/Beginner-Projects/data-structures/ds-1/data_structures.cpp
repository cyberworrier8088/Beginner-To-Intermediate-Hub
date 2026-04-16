/*
 * C++ Data Structures - Level 4: Advanced Container Implementation
 * 
 * Welcome to the world of data structures! This is where algorithms meet efficiency.
 * Learn how to implement and use fundamental data structures in modern C++.
 * 
 * Key concepts you'll learn:
 * - Template programming for generic data structures
 * - Dynamic memory management with smart pointers
 * - Algorithm complexity and Big O notation
 * - STL container internals and custom implementations
 * - Iterator patterns and range-based loops
 * - Performance optimization techniques
 * - Human-like code with detailed explanations!
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <chrono>

using namespace std;

// Forward declarations
template<typename T>
class LinkedList;

template<typename T>
class Stack;

template<typename T>
class Queue;

template<typename T>
class BinaryTree;

// Node class for linked structures
template<typename T>
class Node {
private:
    T data;
    shared_ptr<Node<T>> next;
    shared_ptr<Node<T>> prev;
    weak_ptr<Node<T>> parent;
    
public:
    Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    
    // Getters and setters
    T getData() const { return data; }
    void setData(const T& value) { data = value; }
    
    shared_ptr<Node<T>> getNext() const { return next; }
    void setNext(shared_ptr<Node<T>> node) { next = node; }
    
    shared_ptr<Node<T>> getPrev() const { return prev; }
    void setPrev(shared_ptr<Node<T>> node) { prev = node; }
    
    shared_ptr<Node<T>> getParent() const { return parent.lock(); }
    void setParent(weak_ptr<Node<T>> node) { parent = node; }
    
    // For tree nodes
    shared_ptr<Node<T>> left;
    shared_ptr<Node<T>> right;
    
    Node() : left(nullptr), right(nullptr) {}
};

// LinkedList implementation
template<typename T>
class LinkedList {
private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> tail;
    size_t size;
    
public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Add element to front
    void push_front(const T& value) {
        auto newNode = make_shared<Node<T>>(value);
        newNode->setNext(head);
        
        if (head) {
            head->setPrev(newNode);
        } else {
            tail = newNode;
        }
        
        head = newNode;
        size++;
        
        cout << "Added " << value << " to front of list" << endl;
    }
    
    // Add element to back
    void push_back(const T& value) {
        auto newNode = make_shared<Node<T>>(value);
        
        if (tail) {
            tail->setNext(newNode);
            newNode->setPrev(tail);
        } else {
            head = newNode;
        }
        
        tail = newNode;
        size++;
        
        cout << "Added " << value << " to back of list" << endl;
    }
    
    // Remove element from front
    T pop_front() {
        if (!head) {
            throw runtime_error("Cannot pop from empty list!");
        }
        
        T value = head->getData();
        head = head->getNext();
        
        if (head) {
            head->setPrev(nullptr);
        } else {
            tail = nullptr;
        }
        
        size--;
        cout << "Removed " << value << " from front of list" << endl;
        return value;
    }
    
    // Remove element from back
    T pop_back() {
        if (!tail) {
            throw runtime_error("Cannot pop from empty list!");
        }
        
        T value = tail->getData();
        tail = tail->getPrev();
        
        if (tail) {
            tail->setNext(nullptr);
        } else {
            head = nullptr;
        }
        
        size--;
        cout << "Removed " << value << " from back of list" << endl;
        return value;
    }
    
    // Find element
    bool contains(const T& value) const {
        auto current = head;
        while (current) {
            if (current->getData() == value) {
                return true;
            }
            current = current->getNext();
        }
        return false;
    }
    
    // Get size
    size_t getSize() const { return size; }
    
    // Check if empty
    bool isEmpty() const { return size == 0; }
    
    // Display list
    void display() const {
        cout << "LinkedList[";
        auto current = head;
        while (current) {
            cout << current->getData();
            if (current->getNext()) {
                cout << " -> ";
            }
            current = current->getNext();
        }
        cout << "] (Size: " << size << ")" << endl;
    }
    
    // Clear list
    void clear() {
        head = nullptr;
        tail = nullptr;
        size = 0;
        cout << "LinkedList cleared" << endl;
    }
};

// Stack implementation using LinkedList
template<typename T>
class Stack {
private:
    LinkedList<T> list;
    
public:
    // Push element
    void push(const T& value) {
        list.push_front(value);
        cout << "Pushed " << value << " onto stack" << endl;
    }
    
    // Pop element
    T pop() {
        T value = list.pop_front();
        cout << "Popped " << value << " from stack" << endl;
        return value;
    }
    
    // Peek at top element
    T peek() const {
        if (list.isEmpty()) {
            throw runtime_error("Stack is empty!");
        }
        // In a real implementation, we'd need to access the head
        return T(); // Placeholder
    }
    
    // Check if empty
    bool isEmpty() const {
        return list.isEmpty();
    }
    
    // Get size
    size_t getSize() const {
        return list.getSize();
    }
    
    // Display stack
    void display() const {
        cout << "Stack[";
        list.display();
    }
};

// Queue implementation using LinkedList
template<typename T>
class Queue {
private:
    LinkedList<T> list;
    
public:
    // Enqueue element
    void enqueue(const T& value) {
        list.push_back(value);
        cout << "Enqueued " << value << " to queue" << endl;
    }
    
    // Dequeue element
    T dequeue() {
        T value = list.pop_front();
        cout << "Dequeued " << value << " from queue" << endl;
        return value;
    }
    
    // Peek at front element
    T peek() const {
        if (list.isEmpty()) {
            throw runtime_error("Queue is empty!");
        }
        return T(); // Placeholder
    }
    
    // Check if empty
    bool isEmpty() const {
        return list.isEmpty();
    }
    
    // Get size
    size_t getSize() const {
        return list.getSize();
    }
    
    // Display queue
    void display() const {
        cout << "Queue[";
        list.display();
    }
};

// Binary Tree implementation
template<typename T>
class BinaryTree {
private:
    shared_ptr<Node<T>> root;
    size_t size;
    
    // Helper function for insertion
    shared_ptr<Node<T>> insertHelper(shared_ptr<Node<T>> node, const T& value) {
        if (!node) {
            size++;
            return make_shared<Node<T>>(value);
        }
        
        if (value < node->getData()) {
            node->left = insertHelper(node->left, value);
            if (node->left) {
                node->left->setParent(node);
            }
        } else if (value > node->getData()) {
            node->right = insertHelper(node->right, value);
            if (node->right) {
                node->right->setParent(node);
            }
        }
        
        return node;
    }
    
    // Helper function for in-order traversal
    void inOrderHelper(shared_ptr<Node<T>> node, vector<T>& result) const {
        if (!node) return;
        
        inOrderHelper(node->left, result);
        result.push_back(node->getData());
        inOrderHelper(node->right, result);
    }
    
    // Helper function for pre-order traversal
    void preOrderHelper(shared_ptr<Node<T>> node, vector<T>& result) const {
        if (!node) return;
        
        result.push_back(node->getData());
        preOrderHelper(node->left, result);
        preOrderHelper(node->right, result);
    }
    
    // Helper function for post-order traversal
    void postOrderHelper(shared_ptr<Node<T>> node, vector<T>& result) const {
        if (!node) return;
        
        postOrderHelper(node->left, result);
        postOrderHelper(node->right, result);
        result.push_back(node->getData());
    }
    
    // Helper function for height calculation
    int heightHelper(shared_ptr<Node<T>> node) const {
        if (!node) return 0;
        
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);
        
        return max(leftHeight, rightHeight) + 1;
    }
    
    // Helper function for search
    bool searchHelper(shared_ptr<Node<T>> node, const T& value) const {
        if (!node) return false;
        
        if (node->getData() == value) return true;
        
        if (value < node->getData()) {
            return searchHelper(node->left, value);
        } else {
            return searchHelper(node->right, value);
        }
    }
    
public:
    BinaryTree() : root(nullptr), size(0) {}
    
    // Insert value
    void insert(const T& value) {
        root = insertHelper(root, value);
        cout << "Inserted " << value << " into binary tree" << endl;
    }
    
    // Search for value
    bool contains(const T& value) const {
        bool found = searchHelper(root, value);
        cout << "Searching for " << value << ": " << (found ? "Found" : "Not found") << endl;
        return found;
    }
    
    // Get size
    size_t getSize() const { return size; }
    
    // Check if empty
    bool isEmpty() const { return size == 0; }
    
    // Get height
    int getHeight() const {
        int height = heightHelper(root);
        cout << "Tree height: " << height << endl;
        return height;
    }
    
    // In-order traversal
    vector<T> inOrder() const {
        vector<T> result;
        inOrderHelper(root, result);
        cout << "In-order traversal: ";
        for (const auto& val : result) {
            cout << val << " ";
        }
        cout << endl;
        return result;
    }
    
    // Pre-order traversal
    vector<T> preOrder() const {
        vector<T> result;
        preOrderHelper(root, result);
        cout << "Pre-order traversal: ";
        for (const auto& val : result) {
            cout << val << " ";
        }
        cout << endl;
        return result;
    }
    
    // Post-order traversal
    vector<T> postOrder() const {
        vector<T> result;
        postOrderHelper(root, result);
        cout << "Post-order traversal: ";
        for (const auto& val : result) {
            cout << val << " ";
        }
        cout << endl;
        return result;
    }
    
    // Display tree structure (simplified)
    void display() const {
        cout << "BinaryTree[";
        vector<T> values = inOrder();
        for (size_t i = 0; i < values.size(); i++) {
            cout << values[i];
            if (i < values.size() - 1) {
                cout << ", ";
            }
        }
        cout << "] (Size: " << size << ", Height: " << getHeight() << ")" << endl;
    }
};

// Hash Table implementation (simplified)
template<typename K, typename V>
class HashTable {
private:
    static const size_t TABLE_SIZE = 10;
    
    struct HashNode {
        K key;
        V value;
        shared_ptr<HashNode> next;
        
        HashNode(const K& k, const V& v) : key(k), value(v), next(nullptr) {}
    };
    
    vector<shared_ptr<HashNode>> table;
    size_t size;
    
    // Simple hash function
    size_t hash(const K& key) const {
        return hash<K>{}(key) % TABLE_SIZE;
    }
    
public:
    HashTable() : table(TABLE_SIZE), size(0) {}
    
    // Insert key-value pair
    void insert(const K& key, const V& value) {
        size_t index = hash(key);
        auto newNode = make_shared<HashNode>(key, value);
        
        if (!table[index]) {
            table[index] = newNode;
        } else {
            // Handle collision with chaining
            auto current = table[index];
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        
        size++;
        cout << "Inserted (" << key << ", " << value << ") at index " << index << endl;
    }
    
    // Get value by key
    V get(const K& key) const {
        size_t index = hash(key);
        auto current = table[index];
        
        while (current) {
            if (current->key == key) {
                cout << "Found value " << current->value << " for key " << key << endl;
                return current->value;
            }
            current = current->next;
        }
        
        throw runtime_error("Key not found in hash table!");
    }
    
    // Check if key exists
    bool contains(const K& key) const {
        size_t index = hash(key);
        auto current = table[index];
        
        while (current) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        
        return false;
    }
    
    // Get size
    size_t getSize() const { return size; }
    
    // Display hash table
    void display() const {
        cout << "HashTable[" << TABLE_SIZE << "]:" << endl;
        for (size_t i = 0; i < TABLE_SIZE; i++) {
            cout << "  [" << i << "]: ";
            auto current = table[i];
            while (current) {
                cout << "(" << current->key << ", " << current->value << ")";
                if (current->next) {
                    cout << " -> ";
                }
                current = current->next;
            }
            if (!table[i]) {
                cout << "empty";
            }
            cout << endl;
        }
        cout << "Size: " << size << endl;
    }
};

// Performance testing utilities
class PerformanceTester {
public:
    template<typename Func>
    static void measureTime(const string& testName, Func func) {
        auto start = chrono::high_resolution_clock::now();
        func();
        auto end = chrono::high_resolution_clock::now();
        
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        cout << testName << " took " << duration.count() << " microseconds" << endl;
    }
    
    static void testLinkedListPerformance() {
        cout << "\n=== LINKED LIST PERFORMANCE TEST ===" << endl;
        
        LinkedList<int> list;
        
        measureTime("Insert 1000 elements", [&]() {
            for (int i = 0; i < 1000; i++) {
                list.push_back(i);
            }
        });
        
        measureTime("Search 1000 elements", [&]() {
            for (int i = 0; i < 1000; i++) {
                list.contains(i);
            }
        });
        
        measureTime("Remove 1000 elements", [&]() {
            while (!list.isEmpty()) {
                list.pop_back();
            }
        });
    }
    
    static void testBinaryTreePerformance() {
        cout << "\n=== BINARY TREE PERFORMANCE TEST ===" << endl;
        
        BinaryTree<int> tree;
        
        measureTime("Insert 1000 elements", [&]() {
            for (int i = 0; i < 1000; i++) {
                tree.insert(i);
            }
        });
        
        measureTime("Search 1000 elements", [&]() {
            for (int i = 0; i < 1000; i++) {
                tree.contains(i);
            }
        });
        
        measureTime("In-order traversal", [&]() {
            tree.inOrder();
        });
    }
};

// Interactive demonstration
void demonstrateDataStructures() {
    cout << "=== DATA STRUCTURES DEMONSTRATION ===" << endl;
    
    // LinkedList demo
    cout << "\n--- LINKED LIST ---" << endl;
    LinkedList<string> stringList;
    stringList.push_back("Hello");
    stringList.push_back("World");
    stringList.push_front("Start");
    stringList.display();
    
    cout << "Contains 'World': " << (stringList.contains("World") ? "Yes" : "No") << endl;
    cout << "Contains "Python": " << (stringList.contains("Python") ? "Yes" : "No") << endl;
    
    stringList.pop_front();
    stringList.display();
    
    // Stack demo
    cout << "\n--- STACK ---" << endl;
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    
    intStack.pop();
    intStack.display();
    
    // Queue demo
    cout << "\n--- QUEUE ---" << endl;
    Queue<string> stringQueue;
    stringQueue.enqueue("First");
    stringQueue.enqueue("Second");
    stringQueue.enqueue("Third");
    stringQueue.display();
    
    stringQueue.dequeue();
    stringQueue.display();
    
    // Binary Tree demo
    cout << "\n--- BINARY TREE ---" << endl;
    BinaryTree<int> intTree;
    intTree.insert(50);
    intTree.insert(30);
    intTree.insert(70);
    intTree.insert(20);
    intTree.insert(40);
    intTree.insert(60);
    intTree.insert(80);
    
    intTree.display();
    intTree.inOrder();
    intTree.preOrder();
    intTree.postOrder();
    
    cout << "Contains 40: " << (intTree.contains(40) ? "Yes" : "No") << endl;
    cout << "Contains 90: " << (intTree.contains(90) ? "Yes" : "No") << endl;
    
    // Hash Table demo
    cout << "\n--- HASH TABLE ---" << endl;
    HashTable<string, int> studentGrades;
    studentGrades.insert("Alice", 95);
    studentGrades.insert("Bob", 87);
    studentGrades.insert("Charlie", 92);
    studentGrades.insert("David", 78);
    studentGrades.insert("Eve", 89);
    
    studentGrades.display();
    
    try {
        int aliceGrade = studentGrades.get("Alice");
        cout << "Alice's grade: " << aliceGrade << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    
    cout << "Contains 'Bob': " << (studentGrades.contains("Bob") ? "Yes" : "No") << endl;
    cout << "Contains 'Frank': " << (studentGrades.contains("Frank") ? "Yes" : "No") << endl;
}

// Interactive menu system
void interactiveMenu() {
    cout << "\n=== INTERACTIVE DATA STRUCTURES MENU ===" << endl;
    cout << "Choose a data structure to test:" << endl;
    cout << "1. LinkedList" << endl;
    cout << "2. Stack" << endl;
    cout << "3. Queue" << endl;
    cout << "4. Binary Tree" << endl;
    cout << "5. Hash Table" << endl;
    cout << "6. Performance Tests" << endl;
    cout << "7. Exit" << endl;
    
    while (true) {
        cout << "\nEnter choice (1-7): ";
        string choice;
        getline(cin, choice);
        
        if (choice == "1") {
            LinkedList<string> list;
            cout << "LinkedList created. Enter strings to add (or 'done' to finish):" << endl;
            
            while (true) {
                cout << "Enter string: ";
                string input;
                getline(cin, input);
                
                if (input == "done") break;
                list.push_back(input);
                list.display();
            }
            
        } else if (choice == "2") {
            Stack<int> stack;
            cout << "Stack created. Enter numbers to push (or 'done' to finish):" << endl;
            
            while (true) {
                cout << "Enter number: ";
                string input;
                getline(cin, input);
                
                if (input == "done") break;
                try {
                    int num = stoi(input);
                    stack.push(num);
                    stack.display();
                } catch (...) {
                    cout << "Invalid number!" << endl;
                }
            }
            
        } else if (choice == "3") {
            Queue<string> queue;
            cout << "Queue created. Enter strings to enqueue (or 'done' to finish):" << endl;
            
            while (true) {
                cout << "Enter string: ";
                string input;
                getline(cin, input);
                
                if (input == "done") break;
                queue.enqueue(input);
                queue.display();
            }
            
        } else if (choice == "4") {
            BinaryTree<int> tree;
            cout << "Binary Tree created. Enter numbers to insert (or 'done' to finish):" << endl;
            
            while (true) {
                cout << "Enter number: ";
                string input;
                getline(cin, input);
                
                if (input == "done") break;
                try {
                    int num = stoi(input);
                    tree.insert(num);
                    tree.display();
                } catch (...) {
                    cout << "Invalid number!" << endl;
                }
            }
            
        } else if (choice == "5") {
            HashTable<string, string> phoneBook;
            cout << "Phone Book created. Enter name and number (or 'done' to finish):" << endl;
            
            while (true) {
                cout << "Enter name: ";
                string name;
                getline(cin, name);
                
                if (name == "done") break;
                
                cout << "Enter number: ";
                string number;
                getline(cin, number);
                
                phoneBook.insert(name, number);
                phoneBook.display();
            }
            
        } else if (choice == "6") {
            PerformanceTester::testLinkedListPerformance();
            PerformanceTester::testBinaryTreePerformance();
            
        } else if (choice == "7") {
            break;
        } else {
            cout << "Invalid choice! Please enter 1-7." << endl;
        }
    }
}

int main() {
    cout << "========================================" << endl;
    cout << "    C++ DATA STRUCTURES - LEVEL 4" << endl;
    cout << "========================================" << endl;
    cout << "Learn advanced data structures in modern C++!" << endl;
    cout << "This program demonstrates:" << endl;
    cout << "- Template programming for generic containers" << endl;
    cout << "- Smart pointers for memory management" << endl;
    cout << "- Algorithm complexity and Big O notation" << endl;
    cout << "- Custom data structure implementations" << endl;
    cout << "- Performance testing and optimization" << endl;
    cout << "- Human-like code with detailed explanations!" << endl;
    cout << "========================================" << endl;
    
    // Run demonstration
    demonstrateDataStructures();
    
    // Interactive menu
    interactiveMenu();
    
    cout << "\n========================================" << endl;
    cout << "    DATA STRUCTURES DEMO COMPLETE!" << endl;
    cout << "========================================" << endl;
    cout << "You've learned:" << endl;
    cout << "1. Template programming fundamentals" << endl;
    cout << "2. Smart pointers and memory management" << endl;
    cout << "3. LinkedList implementation and operations" << endl;
    cout << "4. Stack and Queue data structures" << endl;
    cout << "5. Binary Search Tree operations" << endl;
    cout << "6. Hash Table with collision handling" << endl;
    cout << "7. Algorithm complexity analysis" << endl;
    cout << "8. Performance testing techniques" << endl;
    cout << "9. Modern C++ best practices" << endl;
    cout << "10. Human-readable, maintainable code!" << endl;
    
    cout << "\nKey takeaways:" << endl;
    cout << "- Templates enable generic, reusable code" << endl;
    cout << "- Smart pointers prevent memory leaks automatically" << endl;
    cout << "- Different data structures have different trade-offs" << endl;
    cout << "- Performance matters in real-world applications" << endl;
    cout << "- Clean code is as important as correct code" << endl;
    
    return 0;
}
