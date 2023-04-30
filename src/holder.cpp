#include "holder.h"
#include <iostream>
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









void error(string word, string msg){
    cout << word << msg << endl;
}