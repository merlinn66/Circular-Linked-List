#include <iostream>

using namespace std;

class CircularLinkedList {
private:
    class Node {
    public:
        int data;
        Node* next;

        Node(int d) {
            data = d;
            next = nullptr;
        }
    };
    Node* head;

public:

    CircularLinkedList() {
        head = nullptr;
    }

    void append(int d);
    void addend(int d);
    void display();
    int count();
    void erase(int d);

    ~CircularLinkedList() {
        // Corrected destructor to delete circular linked list nodes properly
        if (head == nullptr) return;
        Node* temp = head;
        do {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head); // Stop when we reach back to head
    }
};

int main() {

    CircularLinkedList list;
    list.append(10);
    list.append(20);
    list.append(30);
    list.addend(5);
    list.display();
    cout << "Node count: " << list.count() << endl;

    cout << "After erasure:" << endl;

    list.erase(5);
    list.display();
    cout << "Node count: " << list.count() << endl;

    return 0;
}

void CircularLinkedList::append(int d) {
    Node* newNode = new Node(d);

    if (head == nullptr) {
        head = newNode;
        head->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
}

void CircularLinkedList::display() {

    if (head == nullptr) {
        cout << "List is empty" << endl;
        return;
    } else {
        Node* temp = head;
        do {
            cout << temp->data << "<->";  // Display current node
            temp = temp->next;            // Move to the next node
        } while (temp != head);         // Stop when we return to the head node

        cout << "(back to head)" << endl;  // Indicate circular nature
    }
}

int CircularLinkedList::count() {

    int counter = 0;
    if (head == nullptr) {
        return 0;
    } else {
        Node* temp = head;
        do {
            counter++;
            temp = temp->next;
        } while (temp != head);  // Keep looping until we get back to head
    }
    return counter;
}

void CircularLinkedList::addend(int d) {
    Node* newNode = new Node(d);
    if (head == nullptr) {
        head = newNode;
        newNode->next = head;
    } else {
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }
}

void CircularLinkedList::erase(int d) {
    if (head == nullptr) { // If the list is empty
        return;
    }

    if (head->data == d) { // If the head node contains the target
        Node* temp = head;
        if (head->next == head) { // If there's only one node in the list
            head = nullptr; // List is now empty
        } else {
            head = head->next; // Move head forward
        }
        delete temp; // Delete the target node
        return; // End the function
    }

    Node* temp = head;
    while (temp->next != head && temp->next->data != d) {
        temp = temp->next; // Traverse the list
    }

    if (temp->next != head) { // If target value is in the middle or end
        Node* target = temp->next;
        temp->next = target->next; // Remove target from the list

        if (target == head) {
            head = temp->next; // If we removed the head node
        }
        delete target; // Delete the target node
    }
}

