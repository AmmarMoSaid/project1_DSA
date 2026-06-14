#include <iostream>
using namespace std;

class Node {
public:
    char data;
    Node* next;
    Node* prev;

    Node(char ch ) : data(ch), next(nullptr), prev(nullptr) {}
};
class DoublyLinkedList {

private:
    Node* head;
    Node* tail;
    int len = 0;
public:

    DoublyLinkedList() : head(nullptr), tail(nullptr), len(0) {}

    DoublyLinkedList( const string& str) : head(nullptr), tail(nullptr), len(0) {  
        // for عادي
        for (int i = 0; i < str.size(); i++)
            insertPos(len, str[i]);//inserttail

       // for (char ch : str)
         //   insertPos(len, ch);//insertPos
    }
    //
    bool isEmpty() {
        return(head == nullptr);
    }
    //
    bool isfound(char ch) {
        Node* searchptr = head;
        while (searchptr != NULL) {
            if (searchptr->data == ch)
                return true;
            searchptr = searchptr->next;
        }
        return false;
    }
    //
    void display() {
        Node* tmp = head;
        while (tmp != nullptr) {
            cout << tmp->data;
            tmp = tmp->next;
        }
        cout << endl;
    }

    //Insertion
    void InsertHead(char ch) {
        Node* newnode = new Node(ch);
        if (isEmpty()) {
            head = tail = newnode;
        }
        else {
            newnode->next = head;
            head->prev = newnode;
            head = newnode;

        }
        len++;
    }
    void InsertTail(char ch) {
        Node* newnode = new Node(ch);
        if (isEmpty()) {
            head = tail = newnode;
        }
        else {
            tail->next = newnode;
            newnode->prev = tail;
            tail = newnode;
        }
        len++;
    }
    void insertPos(int pos, char ch) {
        if (pos < 0 || pos > len) {
            cout << "Out of Range\n";
            return;
        }

        if (isEmpty() || pos == 0) {
            InsertHead(ch);
            return;
        }
        if (pos == len) {
            InsertTail(ch);
            return;
        }

        Node* newnode = new Node(ch);
        Node* current = head;

        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        //
        newnode->next = current->next;
        newnode->prev = current;
        current->next->prev = newnode;
        current->next = newnode;

        len++;
        cout << "Inserted " << ch << " at position " << pos << endl;
    }
    //
    string toString() const {
        string result;
        Node* temp = head;
        while (temp) {
            result += temp->data;
            temp = temp->next;
        }
        return result;
    }

    // 
    void clear() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        len = 0;
    }
    
    //Deletion
    void removeHead() {
        //1
        if (len == 0) {
            cout << "the list 's empty";
            return;
        }
            
         if (len == 1) {//head==tail
             delete head;
             tail = head = nullptr;
        }
         else {
             Node* delptr = head;
             head = head->next;
             head->prev = nullptr;
             delete delptr;
         }
         len--;
         
    }
    void removeTail() {
        if (len == 0) {
            cout << "the list 's empty";
            return;
        }
        if (len == 1) {//head==tail
            delete head;
            tail = head = nullptr;
        }
        else {
            Node* delptr = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete delptr;
        }
        len--;
    }
    void removepos(int pos) {

        //1
        if (isEmpty()) {
            cout << "the list 's empty";
            return;
        }
        //2
        if (pos < 0 || len <= pos) {
            cout << "Out of Range";
            return;
        }
        
        //3
        if (pos == 0) {
            removeHead();
            return;
        }
         //4
        if (pos == len-1) {
            removeTail();
            return;
         }
        //5
        Node* current = head;
        for (int i = 0; i < pos; i++)
        {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev=current->prev;
        
        delete current;

        len--;
        
    }
    //String Length
    int length() {
        return len;
    }
    //Concatenation
    void concat(DoublyLinkedList &dl2) {
        Node* curr = dl2.head;
        while (curr) {
            insertPos(len, curr->data);
            curr = curr->next;
        }
    }
    //Substring Extraction
    void substring(int index, int length) {
        if (index < 0 || index >= len || length <= 0 || (index + length) > len) {
            cout << "Error: Invalid index or length\n";
            return;
        }

        Node* tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->next;
        }

        for (int i = 0; i < length; i++) {
            cout << tmp->data;
            tmp = tmp->next;
        }
        cout << endl;
    }
    //Search
    int Search(const string& substr) {
        if (substr.empty() || len < substr.length()) {
            return -1;
        }

        Node* start = head;
        for (int i = 0; i <= len - substr.length(); i++) {
            Node* curr = start;
            bool match = true;

            for (char ch : substr) {
                if (curr == nullptr || curr->data != ch) {
                    match = false;
                    break;
                }
                curr = curr->next;
            }

            if (match) {
                return i;  
            }

            start = start->next;
        }

        return -1;  
    }
    //Replacement
    void replace(const string& oldSub, const string& newSub) {
        if (oldSub.empty() || len < oldSub.length()) {
            cout << "Error: Invalid substring for replacement\n";
            return;
        }
        string currentStr = toString();

        size_t pos = 0;
        while ((pos = currentStr.find(oldSub, pos)) != string::npos) {
            currentStr.replace(pos, oldSub.length(), newSub);
            pos += newSub.length();
        }

        clear();
        for (char ch : currentStr) {
            insertPos(len, ch);
        }
    }
};

int main() {
    string s1, s2;
    cout << "Enter string to add to list 1: ";
    cin >> s1;

    cout << "Enter string to add to list 2: ";
    cin >> s2;

    DoublyLinkedList list1(s1);
    DoublyLinkedList list2(s2);

  
    list1.concat(list2);
    cout << "Concatenated Lists: ";
    list1.display();

    int index;
    cout << "\nChoose a character by index to remove: ";
    cin >> index;
    list1.removepos(index);
    cout << "List after removal: ";
    list1.display();

    int start, len;
    cout << "\nEnter index and length to get substring: ";
    cin >> start >> len;
    cout << "Substring: ";
    list1.substring(start, len);
    cout << endl;

    string searchStr;
    cout << "\nSearch for a string in the list: ";
    cin >> searchStr;
    int pos = list1.Search(searchStr);
    if (pos != -1)
        cout << "Found at index " << pos << endl;
    else
        cout << "Not found" << endl;

    string oldSub, newSub;
    cout << "\nEnter 2 substrings to replace one with another: ";
    cin >> oldSub >> newSub;
    list1.replace(oldSub, newSub);
    cout << "List after replacement: ";
    list1.display();
}