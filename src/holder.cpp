#include "holder.h"
#include <iostream>
#include "Timer.h"
using namespace std;

ostream & operator << (ostream & out, Stack & L){
    L.print(out);
    return out;
}

//ArrayStack
ArrayStack::ArrayStack(int cap)
:Stack("ArrayStack"), capacity(cap), size(0), buf(new string[cap]){}

void ArrayStack::push(const string & word){
    buf[size++] = word;
}

void ArrayStack::pop(){
    if (is_empty())
        error(name, "the Stackarray is empty");
    --size;
}

string ArrayStack::top(){
    if (is_empty())
        error(name, "the Stackarray is empty");
    return buf[size - 1];
}

bool ArrayStack::is_empty(){
    return size <= 0;
}

bool ArrayStack::is_full(){
    return size >= capacity;
}

void ArrayStack::print(ostream & out){
    for (int i = 0; i != size; ++i)
        out << buf[i] << " ";
}

ArrayStack::~ArrayStack(){
    delete[] buf;
}

//ListNode
void ListNode::print(ostream & out, ListNode * L){
    for (; L; L = L -> next)
        out << (L -> data);
}

void ListNode::delete_list(ListNode * L){
    for (ListNode * temp = L; temp; ){
        temp = L -> next;
        delete L;
        L = temp;
    }
}

//LinkedStack
LinkedStack::LinkedStack()
:Stack("LinkedStack"), head(nullptr){}

void LinkedStack::push(const string & word){
    head = new ListNode(word, head);
}

void LinkedStack::pop(){
    ListNode * temp = head;
    head = head -> next;
    delete temp;
}

string LinkedStack::top(){
    return head -> data;
}

bool LinkedStack::is_empty(){
    return !head;
}

bool LinkedStack::is_full(){
    return false;
}

void LinkedStack::print(ostream & out){
    ListNode::print(out, head);
}

LinkedStack::~LinkedStack(){
    ListNode::delete_list(head);
}

//ArrayQueue
ArrayQueue::ArrayQueue(int cap)
:Queue("ArrayQueue"), capacity(cap + 1), front(0), rear(0), buf(new string[cap + 1]){}

void ArrayQueue::enq(const string & word){
    buf[rear] = word;
    rear = (rear + 1) % capacity;
}

void ArrayQueue::deq(){
    front = (front + 1) % capacity;
}

string ArrayQueue::next(){
    return buf[front];
}

bool ArrayQueue::is_empty(){
    return rear == front;
}

bool ArrayQueue::is_full(){
    return (rear + 1) % capacity == front;
}

void ArrayQueue::print(ostream & out){
    for (int i = front; i != rear; i = (i + 1) % capacity)
        out << buf[i] << " ";
}

ArrayQueue::~ArrayQueue(){
    delete[] buf;
}

//LinkedQueue
LinkedQueue::LinkedQueue()
:Queue("LinkedQueue"), head(nullptr), tail(nullptr){}

void LinkedQueue::enq(const string & word){
    ListNode * newNode = new ListNode(word, nullptr);
        if (tail) {
            tail -> next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
}

void LinkedQueue::deq(){
    if (!head) return;
    ListNode * temp = head;
    head = head -> next;
    delete temp;
    if (!head) tail = nullptr;
}

string LinkedQueue::next(){
    return head -> data;
}

bool LinkedQueue::is_empty(){
    return head == nullptr;
}

bool LinkedQueue::is_full(){
    return false;
}

void LinkedQueue::print(ostream &out){
    for(ListNode* temp = head; temp; temp = temp->next) {
        out << temp -> data << " ";
    }
}

LinkedQueue::~LinkedQueue() {
    for(; head; ) {
        ListNode* temp = head;
        head = head -> next;
        delete temp;
    }
}

void error(string word, string msg){
    cout << word << msg << endl;
}

void insert_all_words(int k, string file_name, Holder & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.insert(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void remove_all_words(int k, string file_name, Holder & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.remove();
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_holder(string file_name, Holder & L){
    cout << L.name << endl;
    int K = 1;
    for (K = 1; K <= 10; ++K){
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if ( !L.is_empty() )
            error(L.name, "is not empty");
    }
}

void measure_holders(string input_file){
    ArrayStack AS(NWORDS);
    measure_holder(input_file, AS);
    LinkedStack LS;
    measure_holder(input_file, LS);
    ArrayQueue AQ(NWORDS);
    measure_holder(input_file, AQ);
    LinkedQueue LQ;
    measure_holder(input_file, LQ);
}
