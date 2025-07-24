#include <iostream>
#include <string>
using namespace std;

// Define a structure for Order
struct Order {
    string orderID;    // Order ID (e.g., "ORD1")
    int priority;      // Order Priority (1-5)
    string destination; // Destination Location (e.g., "Location A")
};

// Define a node for the singly linked list
struct Node {
    Order data;        // Data (Order)
    Node* next;        // Pointer to the next node in the list
};

// Define the SinglyLinkedList class
class SinglyLinkedList {
private:
    Node* head;        // Head pointer to the linked list

public:
    // Constructor to initialize the head of the list
    SinglyLinkedList() : head(nullptr) {}

    // Function to add an order at the end of the list
    void addOrder(Order newOrder) {
        Node* newNode = new Node{newOrder, nullptr};  // Create a new node with the order data
        if (!head) {
            head = newNode;  // If list is empty, set head to the new node
        } else {
            Node* temp = head;
            while (temp->next) {  // Traverse to the end of the list
                temp = temp->next;
            }
            temp->next = newNode;  // Link the new node at the end
        }
    }

    // Function to display all orders in the list
    void displayOrders() {
        Node* temp = head;
        cout << "Displaying orders in Singly Linked List:" << endl;
        while (temp) {
            cout << "Order ID: " << temp->data.orderID
                 << ", Priority: " << temp->data.priority
                 << ", Destination: " << temp->data.destination << endl;
            temp = temp->next;  // Move to the next node
        }
    }

    // Function to search for an order by Order ID
    Node* searchOrder(string orderID) {
        Node* temp = head;
        while (temp) {
            if (temp->data.orderID == orderID) {
                return temp;  // Return the node if found
            }
            temp = temp->next;
        }
        return nullptr;  // Return null if not found
    }

    // Function to remove an order by Order ID
    void removeOrder(string orderID) {
        if (!head) {
            cout << "List is empty, cannot remove order!" << endl;
            return;
        }
        
        // Handle removal of the head node
        if (head->data.orderID == orderID) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Order " << orderID << " removed successfully." << endl;
            return;
        }
        
        // Traverse to find the node to remove
        Node* temp = head;
        while (temp->next && temp->next->data.orderID != orderID) {
            temp = temp->next;
        }

        if (temp->next) {
            Node* nodeToRemove = temp->next;
            temp->next = temp->next->next;
            delete nodeToRemove;
            cout << "Order " << orderID << " removed successfully." << endl;
        } else {
            cout << "Order " << orderID << " not found!" << endl;
        }
    }

    // Function to update an order's details by Order ID
    void updateOrder(string orderID, int newPriority, string newDestination) {
        Node* order = searchOrder(orderID);
        if (order) {
            order->data.priority = newPriority;
            order->data.destination = newDestination;
            cout << "Order " << orderID << " updated successfully." << endl;
        } else {
            cout << "Order " << orderID << " not found!" << endl;
        }
    }
};

int main() {
    // Create an instance of SinglyLinkedList
    SinglyLinkedList singlyList;

    // Test Case 1: Add orders
    cout << "Test Case 1: Add orders to the list" << endl;
    singlyList.addOrder({"ORD1", 1, "Location A"});
    singlyList.addOrder({"ORD2", 2, "Location B"});
    singlyList.addOrder({"ORD3", 3, "Location C"});
    singlyList.displayOrders();

    // Test Case 2: Remove an order
    cout << "\nTest Case 2: Remove an existing order" << endl;
    singlyList.removeOrder("ORD2");
    singlyList.displayOrders();

    // Test Case 3: Search for an order (order exists)
    cout << "\nTest Case 3: Search for an existing order" << endl;
    Node* foundOrder = singlyList.searchOrder("ORD1");
    if (foundOrder) {
        cout << "Found Order: " << foundOrder->data.orderID << endl;
    } else {
        cout << "Order not found!" << endl;
    }

    return 0;
}
