#include "hashtable.h"
#include "Timer.h"
#include <fstream>

//string data;
//ListNode * next;
ListNode * ListNode::find(string key, ListNode * L){
    for (ListNode * temp = L; temp; temp = temp -> next){
        if (temp -> data == key)
            return temp;
    }
    return nullptr;
}

ListNode * ListNode::insert(string key, ListNode * L){
    return new ListNode(key, L);
}

ListNode * ListNode::remove(string key, ListNode * L){
    ListNode * prev = nullptr;
    ListNode * current = L;
    for(; current; prev = current, current = current -> next){
        if(current -> data == key){
            if (prev == nullptr){
                L = current -> next;
            } else {
                prev -> next = current -> next;
            }
            delete current;
            break;
        }
    }
    return L;
}

void ListNode::print(ostream & out, ListNode * L){
    for(ListNode * temp = L; temp; temp = temp -> next)
        out << temp -> data << " ";
}

int ListNode::length(ListNode * L){
    int i = 0;
    for(ListNode * temp = L; temp; temp = temp -> next){
        ++i;
    }
    return i;
}

void ListNode::delete_list(ListNode * L){
    for(ListNode * temp = L; L; ){
        temp = L;
        L = L -> next;
        delete temp;
    }
}


//HashTable
/*  
    const Hasher & hasher;
    const size_t capacity;
    ListNode * * buf;
    const string name; 
*/
void HashTable::insert( const string & word){
    size_t i = hasher.hash(word, capacity);
    buf[i] = ListNode::insert(word, buf[i]);
}

bool HashTable::find( const string & word){
    size_t i = hasher.hash(word, capacity);
    return ListNode::find(word, buf[i]) != nullptr;
}

void HashTable::remove( const string & word){
    size_t i = hasher.hash(word, capacity);
    buf[i] = ListNode::remove(word, buf[i]);
}

bool HashTable::is_empty(){
    for (size_t i = 0; i < capacity; ++i){
        if (buf[i] != nullptr){
            return false;
        }
    }
    return true;
}

bool HashTable::is_full(){
    return false;
}

void HashTable::print(ostream & out){
    for (size_t i = 0; i < capacity; ++i){
        ListNode::print(out, buf[i]);
    }
}

HashTable::~HashTable(){
    for (size_t i = 0; i < capacity; ++i) {
        ListNode::delete_list(buf[i]);
    }
    delete[] buf;
}

size_t HashTable::number_of_entries(){
    size_t count = 0;
    for (size_t i = 0; i < capacity; ++i){
        count += ListNode::length(buf[i]);
    }
    return count;
}

size_t HashTable::number_of_chains(){
    return capacity;
}

void HashTable::get_chain_lengths(vector<int> & v){
    for (size_t i = 0; i < capacity; ++i){
        v.push_back(ListNode::length(buf[i]));
    }
}

void error(string word, string msg){
    cout << word << msg;
}

void insert_all_words(string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.insert(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tI = " << eTime << endl;
}

void find_all_words(string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.find(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tF = " << eTime << endl;
}

void remove_all_words(string file_name, HashTable & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = NWORDS;
    t.start();
    for (string word; (in >> word) && limit > 0; --limit)
        L.remove(word);
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tR = " << eTime << endl;
}

void measure_hashtable(string file_name, HashTable & L){
    cout << L.get_name() << endl;
    insert_all_words(file_name, L);

    vector<int> chain_lengths;
    L.get_chain_lengths(chain_lengths);
    Stats stats(L.get_name(), chain_lengths);
    stats.print(cout);

    find_all_words(file_name, L);
    remove_all_words(file_name, L);
    if ( !L.is_empty() )
        error(L.get_name(), "is not empty");
}

void measure_hashtables(string input_file){
    Hasher * H[] = {
        new ChatGPTHasher{},
        new GoodrichHasher{},
        new MultHasher{},
        new PreissHasher{},
        new PJWHasher{},
        new STLHasher{},
        new SumHasher{}, 
        new Weiss1Hasher{},
        new Weiss2Hasher{},
        new WeissHasher{},
        new MyHasher{},
    };

    int S[] = {
        10000,
        1000,
        100,
        10,
        1,
    };

    for (auto size : S)
        for (auto h : H){
            HashTable ht(*h, size);
            measure_hashtable(input_file, ht);
        }
}