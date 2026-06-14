#include <iostream>
using namespace std;
class Node {
public:
    int data;
    int ctr = 0;
    Node* next;
    Node(int d) {
        data = d;
        next = NULL;
        ctr = 1;
    }
    
};
class SLinkedList {
public:
    Node* head;
    SLinkedList() : head(nullptr) {}
    //
    bool IsEmpty() {
        return(head == NULL);
    }
    //
    bool IsFound(int d) {
        Node* searchptr = head;
        while (searchptr != NULL) {
            if (searchptr->data == d)
                return true;
            searchptr = searchptr->next;
        }
        return false;
    }
    //
    void insertHead(int data) {
        Node* NewNode = new Node(data);
        NewNode->next = head;
        head = NewNode;
    }

    //A)
    void addInOrder(int value) {
        //1-the list is empty
        if (IsEmpty()) {
            Node* newnode = new Node(value);
            head = newnode;
            return;
        }
        //2-the value exist in the head
        if (head->data == value) {
            head->ctr++;
            return;
        }
        //3-the value exist before the head
        if (value < head->data) {
            insertHead(value);
            return;
        }
        //4-search the pos
        Node* tmp = head;
        Node* prev = NULL;
        while (tmp != NULL && tmp->data < value)
        {
            prev = tmp;
            tmp = tmp->next;
        }
        //exist 
        if (tmp != NULL && tmp->data == value) {
            tmp->ctr++;
            return;
        }

        Node* newNode = new Node(value);
        newNode->next = tmp;
        prev->next = newNode;
    }
    //B)
    void Display() {
        Node* tmp = head;
        while (tmp) {
            for (int i = 0; i < tmp->ctr; i++)
            {
                cout << tmp->data << " ";
            }
            tmp = tmp->next;
        }
        cout << endl;
    }
    //C)
    void DeleteVal(int val) {
        //1
        if (IsEmpty()) {
            cout << "******Sorry , You are Can't delete from Empty List******\n";
            return;
        }
        //2
        if (!IsFound(val)) {
            cout << "******Sorry , You are Can't found this item in the List******\n";
            return;
        }
        //3

        if (head->data == val) {
            if (head->ctr > 1)
                head->ctr--;
            else {
                Node* delptr = head;
                head = head->next;
                delete delptr;
            }
            return;
        }
        //4
        Node* prev = head;
        Node* tmp = head->next;

        while (tmp != nullptr && tmp->data != val)
        {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp != nullptr && tmp->data == val) {
            if (tmp->ctr > 1)
                tmp->ctr--;
            else {

                prev->next = tmp->next;
                delete tmp;
            }

        }
        cout << "Value " << val << " deleted successfully\n";
    }
    //D)
    void displayDescendingHelper(Node* node) {
        if (node == NULL) return;
        // اذهب للآخر أولاً
        displayDescendingHelper(node->next);
        // ثم اطبع
        for (int i = 0; i < node->ctr; i++) {
            cout << node->data << " ";
        }
    }

    void displayDescending() {
        displayDescendingHelper(head);
        cout << endl;
    }
    //E)
    void removeMax() {
        //
        if (IsEmpty()) {
            cout << "List is empty!\n";
            return;
        }
        //
        if (head->next == NULL) {
            delete head;
            head = NULL;
            return;
        }
        //
        Node* prev = NULL;
        Node* tmp = head;
        while (tmp->next != NULL) {
            prev = tmp;
            tmp = tmp->next;
        }
        if (tmp->ctr > 1) {
            tmp->ctr--; 
        }
        else {
            prev->next = NULL;
            delete tmp;
        }
    }
    //F)
    void generateFromArray(int arr[], int size) {
        for (int i = 0; i < size; i++)
        {
            addInOrder(arr[i]);
        }
    }
    //G)
    void clear() {
       
        while (head != nullptr) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        cout << "List cleared\n";
    }

};
//int main()
//{
//    SLinkedList sll;
//
//    // Test A & B
//    cout << "=== Test addInOrder & Display ===\n";
//    sll.addInOrder(10);
//    sll.addInOrder(5);
//    sll.addInOrder(20);
//    sll.addInOrder(5);   // تكرار -> ctr يزيد
//    sll.addInOrder(10);  // تكرار
//    sll.addInOrder(10);  // تكرار
//    cout << "List: ";
//    sll.Display();  // 5 5 10 10 10 20
//
//    // Test C
//    cout << "\n=== Test DeleteVal ===\n";
//    sll.DeleteVal(10);  // يشيل واحد بس من التكرار
//    cout << "After deleting 10: ";
//    sll.Display();  // 5 5 10 10 20
//
//    sll.DeleteVal(99);  // مش موجود
//
//    // Test D
//    cout << "\n=== Test displayDescending ===\n";
//    cout << "Descending: ";
//    sll.displayDescending();  // 20 10 10 5 5
//
//    // Test E
//    cout << "\n=== Test removeMax ===\n";
//    sll.removeMax();
//    cout << "After removeMax: ";
//    sll.Display();  // 5 5 10 10
//
//    // Test F
//    cout << "\n=== Test generateFromArray ===\n";
//    SLinkedList sll2;
//    int arr[] = { 30, 15, 30, 7, 15 };
//    sll2.generateFromArray(arr, 5);
//    cout << "Generated List: ";
//    sll2.Display();  // 7 15 15 30 30
//
//    // Test G
//    cout << "\n=== Test clear ===\n";
//    sll2.clear();
//    cout << "Is empty after clear? " << (sll2.IsEmpty() ? "Yes" : "No") << endl;
//    return 0;
//}