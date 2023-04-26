#include "sorted_list.h"
#include <iostream>
#include "Timer.h"
using namespace std;

//int capacity;
//int size;
//string * buf;

int SortedArrayList::find_index(const string & word){
    int low = 0;
    int high = size - 1;
    int mid = (low + high)/2;
    for (; low <= high; mid = (low + high)/2)
        if(buf[mid] < word){
            low = mid + 1;
        }else if(buf[mid] > word){
            high = mid - 1;
        }else if(buf[mid] == word){
            return mid;
        }
    return -1;
    }

void SortedArrayList::copy_down(int hole){
    for (int i = size; i > hole; i--)
        buf[i] = buf[i - 1];
    }
    
void SortedArrayList::copy_up(int hole){
    for (int i = hole; i < size; i++)
        buf[i] = buf[i + 1];
    }

ostream & operator << (ostream & out, SortedList & L){
    L.print(out);
    return out;
}

SortedArrayList::SortedArrayList(int cap)
:SortedList("SAL"), capacity(cap), size(0), buf(new string[cap]){}

void SortedArrayList::insert(const string & word){
    if (is_full()) {
        cout << "The array is full. Cannot insert a new element." << endl;
        return;
    }

    int hole = size;
    while (hole > 0 && word < buf[hole - 1])
    {
        buf[hole] = buf[hole - 1];
        --hole;
    }
    buf[hole] = word;
    ++size;
}

bool SortedArrayList::find(const string & word){
    return SortedArrayList::find_index(word) != -1;
}

void SortedArrayList::remove(const string & word){
    int hole = SortedArrayList::find_index(word);
    if (hole == -1)
        cout << "item not in the list" << endl;
    --size;
    SortedArrayList::copy_up(hole);
}

bool SortedArrayList::is_empty(){
    return size == 0;
}
bool SortedArrayList::is_full(){
    return size == capacity;
}

void SortedArrayList::print(ostream & out){
    for (auto e : *this)
        out << e << ' ';
}

SortedArrayList::~SortedArrayList(){
    delete[] buf;
}

SortedLinkedList::iterator::iterator(ListNode * const ptr) 
    : current(ptr) {}

SortedLinkedList::iterator & SortedLinkedList::iterator::operator ++ () {
    if (current) {
        current = current->next;
    }
    return *this;
}

SortedLinkedList::iterator SortedLinkedList::iterator::operator ++ (int) {
    iterator tmp = *this;
    ++(*this);
    return tmp;
}

SortedLinkedList::iterator::reference SortedLinkedList::iterator::operator *() const {
    return current->data;
}

SortedLinkedList::iterator::pointer SortedLinkedList::iterator::operator->() const {
    return &(current->data);
}

bool SortedLinkedList::iterator::operator == (iterator const & other) const {
    return current == other.current;
}
bool SortedLinkedList::iterator::operator != (iterator const & other) const {
    return current != other.current;
}

SortedLinkedList::iterator SortedLinkedList::begin() {
    return iterator(head);
}

SortedLinkedList::iterator SortedLinkedList::end() {
    return iterator(nullptr);
}

void ListNode::print(ostream & out, ListNode * L){
    for(ListNode * current = L; current; current = current -> next)
        out << current -> data << ' ';
}

void ListNode::insert(const string & word, ListNode * & L) {

    ListNode *newNode = new ListNode(word, nullptr);

    // If the list is empty or the new node should be inserted at the beginning
    if (L == nullptr || L->data > word) {
        newNode->next = L;
        L = newNode;
        return;
    }

    // Traverse the list to find the appropriate position for the new node
    ListNode *current = L;
    while (current->next != nullptr && current->next->data < word) {
        current = current->next;
    }

    // Insert the new node
    newNode->next = current->next;
    current->next = newNode;
}

ListNode * ListNode::find(const string & word, ListNode * L) {

    ListNode *current = L;
    while (current != nullptr && current->data <= word) {
        if (current->data == word) {
            return current;
        }
        current = current->next;
    }
    return nullptr; // Return nullptr if the word is not found in the list
}

void ListNode::delete_list(ListNode * L) {
    ListNode* curr = L;
    while (curr != nullptr) {
        ListNode* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void ListNode::remove(const std::string & word, ListNode * & L) {

    ListNode *prev = nullptr;

    for (ListNode *current = L; current; current = current->next) {
        if (current->data == word) {
            if (prev) {
                prev->next = current->next;
            } else {
                L = current->next;
            }
            delete current;
            break;
        }
        prev = current;
    }
}

SortedLinkedList::SortedLinkedList()
:SortedList("SLL"), head(nullptr) {}

void SortedLinkedList::insert(const std::string & word) {
    ListNode::insert(word, head);
}

bool SortedLinkedList::find(const std::string & word) {
    return ListNode::find(word, head) != nullptr;
}

void SortedLinkedList::remove(const std::string & word) {
    ListNode::remove(word, head);
}

bool SortedLinkedList::is_empty() {
    return !head;
}

bool SortedLinkedList::is_full() {
    return false;
}

void SortedLinkedList::print(std::ostream & out) {
    ListNode::print(out, head);
}

SortedLinkedList::~SortedLinkedList() {
    ListNode::delete_list(head);
}

void error(string word, string msg)
{
    cout << "ERROR: " << word << " " << msg << endl;
}

void insert_all_words(int k, string file_name, SortedList & L){
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

void find_all_words(int k, string file_name, SortedList & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tF = " << eTime << endl;
}

void remove_all_words(int k, string file_name, SortedList & L) {
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.remove(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_UnorderedList_methods(string file_name, SortedList & L){

    cout << L.name << endl;
    int K = 1;
    for (K = 1; K <= 10; ++K){
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K, file_name, L);
        remove_all_words(K, file_name, L);
        if ( !L.is_empty() )
            error(L.name, "is not empty");
    }
}

void measure_lists(string input_file){
    SortedArrayList SAL(NWORDS);
    measure_UnorderedList_methods(input_file, SAL);
    SortedLinkedList SLL;
    measure_UnorderedList_methods(input_file, SLL);
}