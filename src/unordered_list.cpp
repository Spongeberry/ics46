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

