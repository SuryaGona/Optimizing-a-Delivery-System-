#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Structure to represent each order in a node
struct Order {
    string orderID;
    int priority;
    string destination;
};

// Skip list node structure
struct SkipNode {
    Order data;  // Order data
    SkipNode** forward;  // Array of forward pointers
    int level;  // Level of the node
};

// Class to manage the skip list of orders
class SkipList {
private:
    SkipNode* header;  // Header pointer to the skip list
    int maxLevel;  // Maximum level of the skip list
    int level;  // Current level of the skip list

    // Function to create a new node with a specific level
    SkipNode* createNode(int level, Order order) {
        SkipNode* newNode = new SkipNode;
        newNode->data = order;
        newNode->level = level;
        newNode->forward = new SkipNode*[level + 1];  // Allocate space for forward pointers
        for (int i = 0; i <= level; i++) {
            newNode->forward[i] = nullptr;
        }
        return newNode;
    }

    // Function to generate a random level for a new node
    int randomLevel() {
        int level = 0;
        while ((rand() % 2) == 1) {
            level++;
        }
        return level;
    }

public:
    // Constructor to initialize the skip list
    SkipList(int maxLevel) : maxLevel(maxLevel), level(0) {
        header = new SkipNode;  // Create the header node
        header->level = maxLevel;
        header->forward = new SkipNode*[maxLevel + 1];
        for (int i = 0; i <= maxLevel; i++) {
            header->forward[i] = nullptr;
        }
    }

    // Function to insert an order into the skip list
    void insertOrder(Order newOrder) {
        SkipNode* update[maxLevel + 1];  // Array to store the update path
        SkipNode* current = header;

        // Traverse the skip list to find the insertion point
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->data.orderID < newOrder.orderID) {
                current = current->forward[i];  // Move forward at this level
            }
            update[i] = current;  // Save the last node at each level
        }

        // Check if the order already exists
        current = current->forward[0];
        if (current != nullptr && current->data.orderID == newOrder.orderID) {
            return;  // Order already exists, no need to insert
        }

        // Generate a random level for the new node
        int newLevel = randomLevel();
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++) {
                update[i] = header;  // Update the header's forward pointers
            }
            level = newLevel;  // Update the current level
        }

        // Create the new node and insert it into the skip list
        SkipNode* newNode = createNode(newLevel, newOrder);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }

    // Function to search for an order by its Order ID
    SkipNode* searchOrder(string orderID) {
        SkipNode* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->data.orderID < orderID) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];  // Move to the next level's node
        if (current != nullptr && current->data.orderID == orderID) {
            return current;  // Return the node if found
        }
        return nullptr;  // Return nullptr if order not found
    }

    // Function to delete an order from the skip list
    void deleteOrder(string orderID) {
        SkipNode* update[maxLevel + 1];
        SkipNode* current = header;

        // Traverse the skip list to find the deletion point
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->data.orderID < orderID) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current != nullptr && current->data.orderID == orderID) {
            // Remove the node from the skip list
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }

            // Adjust the level if necessary
            while (level > 0 && header->forward[level] == nullptr) {
                level--;
            }

            delete current;  // Free the memory of the deleted node
        }
    }
};

// Main function to test the SkipList class
int main() {
    srand(time(0));  // Seed for random level generation
    SkipList skipList(4);  // Create a skip list with a maximum level of 4

    // Test Case 1: Insert orders into the skip list
    cout << "Test Case 1: Insert orders into the skip list" << endl;
    skipList.insertOrder({"ORD1", 1, "Location A"});
    skipList.insertOrder({"ORD2", 2, "Location B"});
    skipList.insertOrder({"ORD3", 3, "Location C"});
    SkipNode* foundSkipNode = skipList.searchOrder("ORD2");
    if (foundSkipNode) {
        cout << "Found Order in Skip List: " << foundSkipNode->data.orderID << endl;
    }

    // Test Case 2: Search for an order in the skip list
    cout << "\nTest Case 2: Search for an order in the skip list" << endl;
    foundSkipNode = skipList.searchOrder("ORD1");
    if (foundSkipNode) {
        cout << "Found Order in Skip List: " << foundSkipNode->data.orderID << endl;
    } else {
        cout << "Order not found!" << endl;
    }

    // Test Case 3: Delete an order from the skip list
    cout << "\nTest Case 3: Delete an order from the skip list" << endl;
    skipList.deleteOrder("ORD2");
    foundSkipNode = skipList.searchOrder("ORD2");
    if (!foundSkipNode) {
        cout << "Order ORD2 not found after deletion." << endl;
    }

    // Test Case 4: Attempt to delete a non-existing order
    cout << "\nTest Case 4: Attempt to delete a non-existing order" << endl;
    skipList.deleteOrder("ORD4");
    foundSkipNode = skipList.searchOrder("ORD4");
    if (!foundSkipNode) {
        cout << "Order ORD4 not found after deletion attempt." << endl;
    }

    return 0;
}
