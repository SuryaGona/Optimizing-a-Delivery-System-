#include <iostream>
#include <string>
using namespace std;

// Structure to represent each order in a node
struct Order {
    string orderID;
    int priority;
    string destination;
};

// Node structure for the doubly linked list
struct Node {
    Order data;  // Order data
    Node* next;  // Pointer to the next node
    Node* prev;  // Pointer to the previous node
};

// Class to manage a doubly linked list of orders
class DoublyLinkedList {
private:
    Node* head;  // Head pointer to the list
    Node* tail;  // Tail pointer to the list

public:
    // Constructor to initialize an empty list
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Function to add a new order at the end of the list
    void addOrder(Order newOrder) {
        Node* newNode = new Node{newOrder, nullptr, nullptr};  // Create a new node
        if (head == nullptr) {
            head = tail = newNode;  // If the list is empty, set both head and tail
        } else {
            tail->next = newNode;  // Add the new node at the end
            newNode->prev = tail;  // Set the previous pointer of the new node
            tail = newNode;  // Update the tail pointer
        }
    }

    // Function to display all the orders in the list
    void displayOrders() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << "Order ID: " << temp->data.orderID 
                 << ", Priority: " << temp->data.priority 
                 << ", Destination: " << temp->data.destination << endl;
            temp = temp->next;  // Move to the next node
        }
    }

    // Function to display orders in reverse order
    void displayOrdersReverse() {
        Node* temp = tail;
        while (temp != nullptr) {
            cout << "Order ID: " << temp->data.orderID 
                 << ", Priority: " << temp->data.priority 
                 << ", Destination: " << temp->data.destination << endl;
            temp = temp->prev;  // Move to the previous node
        }
    }

    // Function to update the priority of an existing order
    void updatePriority(string orderID, int newPriority) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data.orderID == orderID) {
                temp->data.priority = newPriority;  // Update the priority
                return;
            }
            temp = temp->next;  // Move to the next node
        }
        cout << "Order not found!" << endl;
    }

    // Function to remove an order from the list
    void removeOrder(string orderID) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data.orderID == orderID) {
                if (temp == head) {
                    head = temp->next;  // If the node is the head, move head to the next node
                    if (head != nullptr) {
                        head->prev = nullptr;  // Update the previous pointer of the new head
                    }
                } else if (temp == tail) {
                    tail = temp->prev;  // If the node is the tail, move tail to the previous node
                    if (tail != nullptr) {
                        tail->next = nullptr;  // Update the next pointer of the new tail
                    }
                } else {
                    temp->prev->next = temp->next;  // Bypass the node
                    temp->next->prev = temp->prev;
                }
                delete temp;  // Free the memory of the deleted node
                return;
            }
            temp = temp->next;  // Move to the next node
        }
        cout << "Order not found!" << endl;
    }

    // Function to search for an order by order ID
    Node* searchOrder(string orderID) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data.orderID == orderID) {
                return temp;  // Return the node if found
            }
            temp = temp->next;  // Move to the next node
        }
        return nullptr;  // Return null if order not found
    }
};

// Main function to test the DoublyLinkedList class
int main() {
    DoublyLinkedList doublyList;  // Create an instance of DoublyLinkedList

    // Test Case 1: Add orders to the list
    cout << "Test Case 1: Add orders to the list" << endl;
    doublyList.addOrder({"ORD1", 1, "Location A"});
    doublyList.addOrder({"ORD2", 2, "Location B"});
    doublyList.addOrder({"ORD3", 3, "Location C"});
    doublyList.displayOrders();  // Display all orders

    // Test Case 2: Remove an order from the list
    cout << "\nTest Case 2: Remove an order from the list" << endl;
    doublyList.removeOrder("ORD2");
    doublyList.displayOrders();  // Display all orders after removal

    // Test Case 3: Update an order's priority
    cout << "\nTest Case 3: Update an order's priority" << endl;
    doublyList.updatePriority("ORD1", 4);
    doublyList.displayOrders();  // Display all orders after updating priority

    // Test Case 4: Search for an order in the list
    cout << "\nTest Case 4: Search for an order in the list" << endl;
    Node* foundOrder = doublyList.searchOrder("ORD3");
    if (foundOrder) {
        cout << "Order found: " << foundOrder->data.orderID << ", Priority: " 
             << foundOrder->data.priority << ", Destination: " << foundOrder->data.destination << endl;
    } else {
        cout << "Order not found!" << endl;
    }

    return 0;
}
