#include <iostream>

using namespace std;

class Visitor;

class Node {
    public: 
    int value;
    Node* next;
    Node() {
        value = 0;
        next = NULL;
    }
    Node(int data){
        value = data;
    }
    void setData(int data) {
        value = data;
    }
    void setNext(Node* next) {
        this->next = next;
    }
    void accept(Visitor* v);
    
};

class Linkedlist {
    protected:
        Node* head;
        Node* curr;
    public:
        Linkedlist() {
            head = NULL;
            curr = NULL;
        }
        Node* getHead() {
            return head;
        }
        void addNode(int data) {
            if (head == NULL) {
                Node* n = new Node();
                n->setData(data);
                head = n;
                curr = n;
            }
            else {
                Node* n = new Node(data);
                curr->setNext(n);
                curr = n;
            }
        }
        Node* getNext() {
            return curr->next;
        }
    
};

class Visitor {
    public:
        string numbers;
        Visitor() {
            numbers = "";
        }
        void visit(Node* n) {
            if (n->value > 0) {
                numbers.append(" + ");
            }
            if (n->value < 0 ) {
                numbers.append(" - ");
            }
            if (n->value == 0) {
                numbers.append(" 0 ");
            }
        }
        string retNumbers() {
            return numbers;
        }
};

class Iter {
    public:
        Node* start;
        Node* curr;
    public:
        Iter() {
            start = NULL;
            curr = NULL;
        }
        void first(Node* start) {
            this->start = start;
            curr = start;
        }
        void next() {
            if (start == NULL) {
                return;
            }
            curr = curr->next;
        }
        bool is_done() {
            if (curr == NULL) {
                return true;
            }
            return false;
        }
        Node* current() {
            return curr;
        }
        void printData() {
            cout << curr->value << endl;
        }
};

void Node::accept(Visitor* v) {
        v->visit(this);
}


int main() {
    Linkedlist l;
    string userInput;
    Visitor* v = new Visitor();

    while (userInput != "d") {
        cout << "choose an Input: " << endl;

        cout << "a. add a node" << endl;
        cout << "b. return the head node" << endl;
        cout << "c. traverse the list and print" << endl;
        cout << "d. quit" << endl;

    
        cin >> userInput;

        if (userInput == "a") {
            cout << "enter an int" << endl;
            int userData;
            cin >> userData;
            l.addNode(userData);
            cout << "data added" << endl;
        }

        if (userInput == "b") {
            Node* n = l.getHead();
            int val = n->value;
            cout << "head node is " << val << endl;
        }

        if (userInput == "c") {
            cout << "traversing through linked list" << endl;
            Iter i;
            for (i.first(l.getHead()); !i.is_done(); i.next()) {
                i.printData();
                Node* n = i.current();
                n->accept(v);
            }
            cout << v->retNumbers() << endl;
        }
    }

}
