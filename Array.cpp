#include <iostream>
#include <string>
using namespace std;

// Define a structure for Order
struct Order {
    string orderID;    // Order ID (e.g., "ORD1")
    int priority;      // Order Priority (1-5)
    string destination; // Destination Location (e.g., "Location A")
};

class OrderArray {
private:
    Order orders[50];  // Array to store orders, max of 50 orders
    int orderCount;    // Keeps track of number of orders in the array

public:
    // Constructor to initialize the order count
    OrderArray() : orderCount(0) {}

    // Function to add an order at the end of the array
    void addOrder(Order newOrder) {
        if (orderCount < 50) {  // Ensure we don't exceed array size
            orders[orderCount] = newOrder;  // Add the new order to the array
            orderCount++;  // Increment the count of orders
        } else {
            cout << "Array is full! Cannot add more orders." << endl;
        }
    }

    // Function to display all orders in the array
    void displayOrders() {
        cout << "Displaying all orders:" << endl;
        for (int i = 0; i < orderCount; i++) {
            cout << "Order ID: " << orders[i].orderID
                 << ", Priority: " << orders[i].priority
                 << ", Destination: " << orders[i].destination << endl;
        }
    }

    // Function to search for an order by Order ID (Linear Search)
    Order* searchOrder(string orderID) {
        for (int i = 0; i < orderCount; i++) {
            if (orders[i].orderID == orderID) {
                return &orders[i];  // Return pointer to the found order
            }
        }
        return nullptr;  // Return null if order not found
    }

    // Function to remove an order by Order ID
    void removeOrder(string orderID) {
        for (int i = 0; i < orderCount; i++) {
            if (orders[i].orderID == orderID) {
                // Shift all orders after the removed order one position to the left
                for (int j = i; j < orderCount - 1; j++) {
                    orders[j] = orders[j + 1];
                }
                orderCount--;  // Decrement the order count
                cout << "Order " << orderID << " removed successfully." << endl;
                return;
            }
        }
        cout << "Order " << orderID << " not found!" << endl;
    }

    // Function to update an order's details by Order ID
    void updateOrder(string orderID, int newPriority, string newDestination) {
        Order* order = searchOrder(orderID);
        if (order) {
            order->priority = newPriority;
            order->destination = newDestination;
            cout << "Order " << orderID << " updated successfully." << endl;
        } else {
            cout << "Order " << orderID << " not found!" << endl;
        }
    }
};

int main() {
    // Create an instance of OrderArray
    OrderArray orderArray;

    // Test Case 1: Add orders when array is empty
    cout << "Test Case 1: Add orders when array is empty" << endl;
    orderArray.addOrder({"ORD1", 1, "Location A"});
    orderArray.addOrder({"ORD2", 2, "Location B"});
    orderArray.displayOrders();

    // Test Case 2: Remove an order (order exists)
    cout << "\nTest Case 2: Remove an order (order exists)" << endl;
    orderArray.removeOrder("ORD1");
    orderArray.displayOrders();

    // Test Case 3: Search for an order (order exists)
    cout << "\nTest Case 3: Search for an order (order exists)" << endl;
    Order* foundOrder = orderArray.searchOrder("ORD2");
    if (foundOrder) {
        cout << "Found Order: " << foundOrder->orderID << ", " 
             << foundOrder->priority << ", " << foundOrder->destination << endl;
    } else {
        cout << "Order not found!" << endl;
    }

    // Test Case 4: Update an order (order exists)
    cout << "\nTest Case 4: Update an order (order exists)" << endl;
    orderArray.updateOrder("ORD2", 3, "Location C");
    orderArray.displayOrders();

    return 0;
}
