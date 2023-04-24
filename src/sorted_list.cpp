#include "sorted_list.h"
#include <iostream>
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

SortedArrayList::SortedArrayList(int cap = NWORDS)
:UnorderedList("SAL"), capacity(cap), size(0), buf(new string[cap]){}

void SortedArrayList::insert(const string & word){
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
    return SortedArrayList::find_index(word) != 1;
}

void SortedArrayList::remove(const string & word){
    int hole = SortedArrayList::find_index(word);
    if (hole == -1):
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

