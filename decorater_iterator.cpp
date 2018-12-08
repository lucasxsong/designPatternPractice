#include <iostream>
#include <vector>

using namespace std;

class Visitor;

class Command;

class addNode;

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
    public:
        Node* head;
        Node* curr;
        vector<Command* > commands;
        int commandIndex;
        Linkedlist() {
            head = NULL;
            curr = NULL;
        }
        Node* getHead() {
            return head;
        }
        void addNode();
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

class Command {
    public: 
    Linkedlist* l;

    Command() {

    }

    Command(Linkedlist* l) {
        this->l = l;
    }
    virtual void execute() {

    }
    virtual void unexecute() {

    }
};

class addNode : public Command {
    public:
    Linkedlist* l;
    addNode();
    addNode(Linkedlist l) {
        this->l = &l;
    }

    void execute() {
        int userData;
        cout << "enter a value" << endl;
        cin >> userData;
        if (l.head == NULL) {
            Node* n = new Node();
            n->setData(userData);
            l.head = n;
            l.curr = n;
        }
        else {
            Node* n = new Node();
            n->setData(userData);
            l.curr = n;
        }
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

class Decorater {
    public: 
        void printAsDouble(Node* n) {
            double d = n->value * 2;
            cout << d << endl;
        }
};

void Node::accept(Visitor* v) {
        v->visit(this);
}

void Linkedlist::addNode() {
    addNode* a = new addNode(this);
    a->execute();
    commands.push_back(a);
}


int main() {
    Linkedlist l;
    string userInput;
    Visitor* v = new Visitor();
    Decorater d;

    while (userInput != "d") {
        cout << "choose an Input: " << endl;

        cout << "a. add a node" << endl;
        cout << "b. return the head node" << endl;
        cout << "c. traverse the list and print as int" << endl;
        cout << "d. traverse the list and print as double" << endl;
        cout << "e. traverse the list and print the signs" << endl;
        cout << "q. quit" << endl;

    
        cin >> userInput;

        if (userInput == "a") {
            l.addNode();
        }

        if (userInput == "b") {
            Node* n = l.getHead();
            int val = n->value;
            cout << "head node is " << val << endl;
        }

        if (userInput == "c") {
            cout << "traversing through linked list, printing as int" << endl;
            Iter i;
            for (i.first(l.getHead()); !i.is_done(); i.next()) {
                i.printData();
            }
        }

        if (userInput == "d") {
            cout << "traversing through linked list, printing as double" << endl;
            Iter i;
            for (i.first(l.getHead()); !i.is_done(); i.next()) {
                Node* n = i.current();
                d.printAsDouble(n);
            }
        }

        if (userInput == "e") {
            cout << "traversing through linked list, printing the signs" << endl;
            Iter i;
            for (i.first(l.getHead()); !i.is_done(); i.next()) {
                Node* n = i.current();
                v->visit(n);
            }
            cout << v->retNumbers() << endl;
        }
    }

}
