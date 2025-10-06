#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MIN_LS = 5, MAX_LS = 20;
const int CHOICES = 15;

class Goat {
private:
    int age;
    string name;
    string color;
    // Default constructor will randomly choose one of these
    string names[CHOICES] = {"Billy", "Nanny", "Gruff", "Daisy", "Molly", "Jack", "Jill", "Luna", "Bella", "Max", "Charlie", "Lucy", "Maggie", "Sadie", "Rocky"};
    string colors[CHOICES] = {"White", "Black", "Brown", "Spotted", "Gray", "Golden", "Cream", "Tan", "Red", "Blue", "Green", "Yellow", "Purple", "Pink", "Orange"};
public:
    // Default constructor
    Goat() {
        age = rand() % 20 + 1; // Age between 1 and 20
        name = names[rand() % CHOICES];
        color = colors[rand() % CHOICES];
    }
    // Parameterized constructor
    Goat(int a, string n, string c) {
        age = a;
        name = n;
        color = c;  
    }
    // Print goat
    void print() {
        cout << "     ";
        cout << name << " (" << color << ", " << age << ")" << endl;
    }
    // Getter for name
    string getName() const { return name; }
};

class DoublyLinkedList {
// Each node is a goat instance
private:
    struct Node {
        Goat goat;
        Node* prev;
        Node* next;
        Node(Goat g=Goat(), Node* p = nullptr, Node* n = nullptr) {
            goat = g; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    // Add node to end
    void push_back(Goat g) {
        Node* newNode = new Node(g);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Add node to beginning
    void push_front(Goat g) {
        Node* newNode = new Node(g);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Insert node
    void insert_after(Goat g, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(g);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    // Delete node by name of goat
    void delete_node(string name) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && !(temp->goat.getName() == name))
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            current->goat.print();
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            current->goat.print();
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {

    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(Goat());
    cout << "List forward: " << endl;
    list.print();

    cout << "List backward: " << endl;
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: " << endl;
    list.print();

    return 0;
}
