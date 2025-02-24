/*********************
Name: Darren Bowers
Data Structures Assignment 2 (Stacks & Queues)
**********************/

#include <iostream>
#include <limits>
using std::cout;
using std::endl;
using std::cin;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Node
template <typename T>
class SNode {
public:
    T data;
    SNode<T>* next;

    SNode(T val) : data(val), next(nullptr) {}
};
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Singly Linked List

template <typename T>
class LinerSinglyLinkedList {
private:
    SNode<T>* head;
    SNode<T>* tail;
public:
    LinerSinglyLinkedList () : head(nullptr), tail(nullptr) {} // Constructor

    ~LinerSinglyLinkedList(){ // Destructor 
        deleteList();
    }

    bool isEmptyList() { // Checks if list is empty
        return head == nullptr;
    }

    void insertElmAtEnd(T val) { // Adds a new tail
        SNode<T>* newNode = new SNode<T>(val);
        if (isEmptyList()) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void removefromFront() { // Removes head 
        if (!isEmptyList()) {
            SNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    LinerSinglyLinkedList<T> copyList(){ // Copies list into a new list
        LinerSinglyLinkedList<T> newList;
        SNode<T>* current = head;
        while(current != nullptr){
            newList.insertElmAtEnd(current->data);
            current = current->next;
        }
        return newList;
    }

    bool deleteList(){ // Empties out the list
        bool success = false;
        if(!isEmptyList()){
            SNode<T>* current = head;
            while(current != nullptr){
                head = current->next;
                delete current;
                current = head; 
            }
            success = true;
        }
        return success;
    }

    bool nextElm(T* val){ // I wasn't quite sure the intent of this method, so I assumed it was meant to function like peek
        bool success = false;
        if(!isEmptyList()){
            *val = head->data;
            success = true;
        }
        return success;
    }

    void addElmAtFront(T val) { // Adds a new head node
        SNode<T>* newNode = new SNode<T>(val);
        if (isEmptyList()){
            tail = newNode;
        }
        newNode->next = head;
        head = newNode;
    }

    void retrace() { // Exist only for testing purposes
        SNode<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Stack
template <typename T>
class Stack {

private:
    LinerSinglyLinkedList<T> list;

public: 
    Stack() : list() {} // Constructor

    ~Stack(){
        list.deleteList(); // Destructor 
    }

    void push(T val){
        list.addElmAtFront(val); 
    }

    void pop(){
        list.removefromFront();
    }

    bool top(T* val){
        return list.nextElm(val);
    }

    bool isEmpty(){
        return list.isEmptyList();
    }

    void printStack(){
        list.retrace();
    }
};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Queue
template <typename T>
class Queue {

private:
    LinerSinglyLinkedList<T> list;

public:
    Queue() : list() {} // Constructor

    ~Queue(){
        list.deleteList();
    }

    void insert(T val){
        list.insertElmAtEnd(val);
    }

    void remove(){
        list.removefromFront();
    }

    bool next(T* val){
        return list.nextElm(val);
    }

    bool isEmpty(){
        return list.isEmptyList();
    }

    void printQueue(){
        list.retrace();
    }

};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Test Class
class Test {
public:
    template <typename T>
    void storeData(Stack<T>& stack){
        T value;
        char choice = 'y'; 
        while (choice == 'y' || choice == 'Y'){
            cout << "Enter a value to push onto the stack: ";
            if(!(cin >> value)){ // Prevents errors or infinite loops if user input is invalid
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid value" << endl;
            }else {
                stack.push(value);
                cout << "Add another value? (y/n) ";
                cin >> choice;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Prevents excess user input from storing in input buffer
            }
        }
    }

    template <typename T>
    void storeData(Queue<T>& queue){
        T value;
        char choice = 'y'; 
        while (choice == 'y' || choice == 'Y'){
            cout << "Enter a value to insert into the queue: ";
            if(!(cin >> value)){
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid value" << endl;
            }else {
                queue.insert(value);
                cout << "Add another value? (y/n) ";
                cin >> choice;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }    

    template <typename T>
    void printOut(Stack<T>& stack){
        stack.printStack();
    }

    template <typename T>
    void printOut(Queue<T>& queue){
        queue.printQueue();
    }

};


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Main function for testing
int main() {
    // Test Singly Linked List
    cout << "Creating LinkedList test" << endl;
    LinerSinglyLinkedList<int> originalList;
    originalList.addElmAtFront(10);
    originalList.insertElmAtEnd(20);
    originalList.addElmAtFront(5);
    cout << "originalList output is "; 
    originalList.retrace(); // Output: 5 10 20
    LinerSinglyLinkedList<int> copiedList = originalList.copyList();
    cout << "copiedList output is ";
    copiedList.retrace();
    cout << "Deleting first two nodes in originalList" << endl;
    originalList.removefromFront();
    originalList.removefromFront();
    cout << "originalList output is "; 
    originalList.retrace(); // Output: 20
    cout << "copiedList output is ";
    copiedList.retrace();
    if(originalList.deleteList()){
        cout << endl << "Deleted linklist, starting Stack testing" << endl;
    }
    Stack<int> stackTest;
    int topValue;
    if(stackTest.top(&topValue)){
        cout << "Top Value is: " << topValue << endl;
    }else {
        cout << "Stack is empty" << endl;
    } // Output: empty
    stackTest.push(10);
    stackTest.push(20);
    stackTest.push(5);
    if(stackTest.top(&topValue)){
        cout << "Top Value is: " << topValue << endl;
    }else {
        cout << "Stack is empty" << endl;
    } // Output: 5
    stackTest.pop();
        if(stackTest.top(&topValue)){
        cout << "Top Value is: " << topValue << endl;
    }else {
        cout << "Stack is empty" << endl;
    } // Output: 20
    stackTest.pop();
        if(stackTest.top(&topValue)){
        cout << "Top Value is: " << topValue << endl;
    }else {
        cout << "Stack is empty" << endl;
    } // Output: 10
    stackTest.pop();
        if(stackTest.top(&topValue)){
        cout << "Top Value is: " << topValue << endl;
    }else {
        cout << "Stack is empty" << endl;
    } // Output: empty
    stackTest.pop();
    if(stackTest.isEmpty()){
        cout << "isEmpty works!" << endl;
    }

    cout << endl << "Testing stack using class Test storeData and printOut" << endl;
    Test testProgram;
    testProgram.storeData(stackTest);
    cout << "Stack contents: ";
    testProgram.printOut(stackTest);
    cout << "emptying stack using pop method" << endl;
    while(!stackTest.isEmpty()){
        stackTest.pop();
        testProgram.printOut(stackTest);
    }

    
    cout << endl << "Starting Queue Testing" << endl;

    Queue<int> queueTest;
    int frontValue;
    if(queueTest.next(&frontValue)){
        cout << "Front Value is: " << frontValue << endl;
    }else {
        cout << "Queue is empty" << endl;
    } // Output: empty
    queueTest.insert(10);
    queueTest.insert(20);
    queueTest.insert(5);
    if(queueTest.next(&frontValue)){
        cout << "Front Value is: " << frontValue << endl;
    }else {
        cout << "Queue is empty" << endl;
    } //Output 10
    queueTest.remove();
    if(queueTest.next(&frontValue)){
        cout << "Front Value is: " << frontValue << endl;
    }else {
        cout << "Queue is empty" << endl;
    } //Output 20
    queueTest.remove();
    if(queueTest.next(&frontValue)){
        cout << "Front Value is: " << frontValue << endl;
    }else {
        cout << "Queue is empty" << endl;
    } //Output 5
    queueTest.remove();
    if(queueTest.next(&frontValue)){
        cout << "Front Value is: " << frontValue << endl;
    }else {
        cout << "Queue is empty" << endl;
    } //Output empty
    queueTest.remove();
    if(queueTest.isEmpty()){
        cout << "isEmpty works!" << endl;
    }


    cout << endl << "Testing queue using class Test storeData and printOut" << endl;
    testProgram.storeData(queueTest);
    cout << "Queue contents: ";
    testProgram.printOut(queueTest);
    cout << "emptying queue using remove method" << endl;
    while(!queueTest.isEmpty()){
        queueTest.remove();
        testProgram.printOut(queueTest);
    }

    return 0;
};