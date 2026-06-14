//// TaskDataStructure&Algorithim.cpp :
// Mohamed eid sayed ali          code:240386
// Ammar Mohamed Sayed Abdulhamid code:240265 
#include <iostream>
using namespace std;

class ULLNode {
public:
    int data;
    int ctr = 1;
    ULLNode* next;

    ULLNode(int data, ULLNode* nextNode = 0) {
        this->data = data;
        this->next = nextNode;
    }
};

class ULL {
    ULLNode* head = 0, * tail = 0;

public:
    void addInOrder(int val) {
        if (head == 0) { // if list is empty
            head = tail = new ULLNode(val);
            return;
        }
        /*
        5 Cases
        1- val < head
        2- val == head
        3- val in list and found
        4- val's postion in list and val not found
        5- val not in list
        */
        if (val < head->data)
            head = new ULLNode(val, head);

        if (val == head->data)
            head->ctr++;

        ULLNode* pred = head, * temp = head->next;
        while (temp != 0 && temp->data < val) {
            temp = temp->next;
            pred = pred->next;
        }
        if (temp != 0 && temp->data == val)
            temp->ctr++;

        if (temp != 0 && temp->data > val)
            pred->next = new ULLNode(val, temp);

        if (temp == 0) {
            tail->next = new ULLNode(val);
            tail = tail->next;
        }
    };

    void display() {
        if (head == 0) {
            cout << "List is empty" << endl;
            return;
        }
        ULLNode* temp = head;
        while (temp != 0) {
            for (int i = 0; i < temp->ctr; i++)
                cout << temp->data << " ";
            temp = temp->next;
        }
    };

    void deleteValue(int val) {
        if (head == 0) {
            cout << "List is empty" << endl;
            return;
        }
        /*
        5 Cases
        1- val is found and ctr > 1
        2- val is found and ctr = 1, val = head
        3- val is found and ctr = 1, val in middle
        4- val is found and ctr = 1, val tail
        5- val not found
        */
        ULLNode* temp = head, * pred = 0;
        while (temp != 0 && temp->data != val) {
            pred = temp;
            temp = temp->next;
        };

        if (temp != 0 && temp->ctr > 1) {
            temp->ctr--;
            return;
        }

        if (temp != 0 && temp == head) {
            ULLNode* nextNode = head->next;
            delete head;
            head = nextNode;
            return;
        }

        if (temp != 0 && temp != head && temp != tail) {
            pred->next = temp->next;
            delete temp;
            return;
        }

        if (temp != 0 && temp == tail) {
            delete tail;
            tail = pred;
            tail->next = 0;
            return;
        }

        if (temp == 0) {
            cout << "Value not found";
            return;
        }
    };

    void displayDescending() {
        if (head == 0) {
            cout << "List is empty" << endl;
            return;
        }

        ULLNode* pred = head, * temp = tail;

        for (int i = 0; i < temp->ctr; i++)
            cout << temp->data << " ";

        while (temp != head) {
            while (pred->next != temp)
                pred = pred->next;

            for (int i = 0; i < pred->ctr; i++)
                cout << pred->data << " ";

            temp = pred;
            pred = head;
        }
        // to make the function speed complexity = O(1), we must use doubly
        // linked-list
    }

    void removeMax() {
        if (head == 0) {
            cout << "List is empty" << endl;
            return;
        }
        /*
        2 Cases
        1- list has one element
        2- list has more than one element
        */

        if (head == tail) {
            delete head;
            head = tail = 0;
            return;
        }

        else {
            ULLNode* temp = head;
            while (temp->next != tail)
                temp = temp->next;
            delete tail;
            tail = temp;
            tail->next = 0;
            return;
        }
    }

    void generateFromArray(int arr[], int arrSize) {
        for (int i = 0; i < arrSize; i++) {
            addInOrder(arr[i]);
        }
    }

    void deleteList() {
        if (head == 0) {
            cout << "List is empty" << endl;
            return;
        }

        ULLNode* temp = head, * nextNode = head->next;
        while (temp != 0) {
            delete temp;
            temp = nextNode;
            if (nextNode != 0)
                nextNode = nextNode->next;
        }
        tail = head = 0;
    }

    ~ULL() {
        ULLNode* temp = head;
        while (temp != 0) {
            ULLNode* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        tail = head = 0;
    }
};

//int main() { return 0; }
