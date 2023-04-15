using namespace std;
#include <iostream>
#include "unordered_list.h"

int UnorderedArrayList::find_index(const string & word){
    int i = 0;
    for(; i < size; ++i){
        if(buf[i] == word)
            return i;
    }
    return -1;
}

UnorderedArrayList::UnorderedArrayList(int max_len)
:UnorderedList("UnorderedArrayList"), capacity(max_len), size(0), buf(new string[max_len]){}

void UnorderedArrayList::insert(const string & word){
    buf[++size] = word;
}

bool UnorderedArrayList::find(const string & word){
    return find_index(word) != 1;
}

void UnorderedArrayList::remove(const string & word){
    int i = UnorderedArrayList::find_index(word);
    buf[i] = buf[size--];
}

bool UnorderedArrayList::is_empty(){
    return size <= 0;
}

bool UnorderedArrayList::is_full(){
    return size >= capacity;
}

void UnorderedArrayList::erase(){
    size = 0;
}

void UnorderedArrayList::print(ostream & out){
    for (int i = 0; i < size; ++i){
        out << buf[i] << " ";
    }
    out << endl;
}

UnorderedArrayList::~UnorderedArrayList(){
    delete[] buf;
}

UnorderedLinkedList::UnorderedLinkedList() : UnorderedList("UnorderedLinkedList"), head(nullptr) {}

void UnorderedLinkedList::insert(const string &word) {
    head = new ListNode(word, head);
}

bool UnorderedLinkedList::find(const string &word) {
    return ListNode::find(word, head) != nullptr;
}

void UnorderedLinkedList::remove(const string &word) {
    ListNode::remove(word, head);
}

bool UnorderedLinkedList::is_empty() {
    return head == nullptr;
}

void UnorderedLinkedList::erase() {
    ListNode::delete_list(head);
    head = nullptr;
}

void UnorderedLinkedList::print(ostream &out) {
    ListNode::print(out, head);
}

UnorderedLinkedList::~UnorderedLinkedList() {
    erase();
}

void ListNode::print(ostream &out, ListNode *L) {
    for (ListNode *p = L; p != nullptr; p = p->next) {
        out << p->data << " ";
    }
    out << endl;
}

ListNode *ListNode::find(const string &word, ListNode *L) {
    for (ListNode *p = L; p != nullptr; p = p->next) {
        if (p->data == word) {
            return p;
        }
    }
    return nullptr;
}

void ListNode::remove(const string &word, ListNode *&L) {
    ListNode *prev = nullptr;
    for (ListNode *curr = L; curr != nullptr; prev = curr, curr = curr->next) {
        if (curr->data == word) {
            if (prev == nullptr) {
                L = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            return;
        }
    }
}

void ListNode::delete_list(ListNode *L) {
    for (ListNode *p = L; p != nullptr; ) {
        ListNode *next = p->next;
        delete p;
        p = next;
    }
}