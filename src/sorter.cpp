#include "sorter.h"
#include "timer.h"
#include <fstream>
#include <iostream>
#include <cassert>

void Sorter::fill(int count, string file_name){
    ifstream file(file_name);
    string word;
    for (int i = 0; i < count && file >> word; i++)
        vec.push_back(word);
    file.close();
}

void Sorter::print(ostream & out){
    for (auto s : vec)
        out << s << " ";
}

bool Sorter::verify_sorted(){
    int j = (vec.size() - 1);
    for (int i = 0; i < j; ++i)
        if (vec[i] > vec[i + 1])
            return false;
    return true;
}

void InsertionSorter::insertionsort(vector<string>& vec, int low, int high){
    for (int i = low; i <= high; ++i){
        string key = vec[i];
        int j = i - 1;
            while (j >= low && key < vec[j]){
                vec[j + 1] = vec[j];
                --j;
            }
        vec[j + 1] = key;
    }
}

void InsertionSorter::sort(){
    insertionsort(vec, 0, vec.size() - 1);
}

string QuickSorter::select_pivot(vector<string>& vec, int low, int high){
    int mid = (low + high) / 2;
    if ( vec[mid] < vec[low] ) swap( vec[low], vec[mid] );
    if ( vec[high] < vec[low] ) swap( vec[low], vec[high] );
    if ( vec[mid] < vec[high] ) swap( vec[mid], vec[high] );
    return vec[high];
}

int QuickSorter::partition(vector<string>& vec, int low, int high){
    string pivot = select_pivot(vec, low, high);
    for (int j = low; j < high; j++) {
        if (vec[j] <= pivot) {
            swap(vec[low], vec[j]);
            ++low;
        }
    }
    swap(vec[low], vec[high]);
    return low;
}


void QuickSorter::quicksort(vector<string>& vec, int low, int high){
    if ( low < high )
    {
        int pivot_index = partition( vec, low, high );
        quicksort( vec, low, pivot_index-1 );
        quicksort( vec, pivot_index+1, high );
    }
}

void QuickSorter::sort(){
    quicksort(vec, 0, vec.size() - 1);
}

void HeapSorter::heapify(vector<string>& vec, int high, int root){
    int largest = root;  // Initialize largest as root
    int left = 2 * root + 1;  // Left child
    int right = 2 * root + 2;  // Right child
    int size = high;
    // If left child is larger than root
    if (left < size && vec[left] > vec[largest])
        largest = left;
    // If right child is larger than largest so far
    if (right < size && vec[right] > vec[largest])
        largest = right;
    // If largest is not root
    if (largest != root) {
        swap(vec[root], vec[largest]);
        // Recursively heapify the affected sub-tree
        heapify(vec, size, largest);  // only take one path - the largest
    }
}

void HeapSorter::heapsort(vector<string>& vec, [[maybe_unused]] int low, int high){
    for (int i = high / 2 - 1; i >= 0; --i) {
        heapify(vec, high, i);
    }

    for (int i = high - 1; i >= 0; --i) {
        swap(vec[0], vec[i]);
        heapify(vec, i, 0);
    }
}

void HeapSorter::sort(){
    heapsort(vec, 0, vec.size());
}

void IntroSorter::introsort(vector<string>& vec, int low, int high, int depth_limit) {
    if (high - low <= 0)
        return;

    if (depth_limit == 0) {
        // Switch to heapsort when the maximum depth is reached
        HeapSorter::heapsort(vec, low, high);
        return;
    }

    int pivot = QuickSorter::partition(vec, low, high);
    introsort(vec, low, pivot - 1, depth_limit - 1);
    introsort(vec, pivot + 1, high, depth_limit - 1);
}

void IntroSorter::introsort(vector<string>& vec, int low, int high) {
    // Calculate the maximum depth
    int depth_limit = 2 * static_cast<int>(log(high - low + 1));

    introsort(vec, low, high, depth_limit);
}

void IntroSorter::sort() {
    introsort(vec, 0, vec.size() - 1);
}

void STLSorter::sort() {
    std::sort(vec.begin(), vec.end());
}

void StableSorter::sort() {
    std::stable_sort(vec.begin(), vec.end());
}

void ShellSorter::gapInsertionSort(vector<string> & avector, int start, int gap) {
    int w = avector.size();
    for (int i = start + gap; i < w; i += gap) {
        string key = avector[i];
        int j = i - gap;
        while (j >= start && avector[j] > key) {
            avector[j + gap] = avector[j];
            j -= gap;
        }
        avector[j + gap] = key;
    }
}

void ShellSorter::shellSort(vector<string> & avector) {
    for (int gap = avector.size() / 2; gap > 0; gap /= 2) {
        for (int i = 0; i < gap; i++) {
            gapInsertionSort(avector, i, gap);
        }
    }
}

void ShellSorter::sort() {
    shellSort(vec);
}

ostream & operator << (ostream & out, Sorter & L){
    L.print(out);
    return out;
}

void error(string word, string msg){
    cout << "Error: " << word << " " << msg << endl;
}

void measure_partition(int k, string file_name, Sorter & L){
    Timer t;
    double eTime;
    ifstream in(file_name);
    int limit = k * NWORDS / 10;
    L.fill(limit, file_name);
    t.start();
    L.sort();
    t.elapsedUserTime(eTime);
    in.close();
    cout << "\t\tSort time = " << eTime << endl;
    cout << L.verify_sorted();
    L.vec.clear();
}



void measure_partitions(string file_name, Sorter & L){
    cout << L.name << endl;
    int K = 1;
    for (K = 1; K <= 10; ++K){
        cout << "\tK = " << K << endl;
        measure_partition(K, file_name, L);
    }
}


void measure_sorters(string input_file){
    //InsertionSorter isorter;
    //measure_partitions(input_file, isorter);

    QuickSorter qsorter;
    measure_partitions(input_file, qsorter);

    HeapSorter hsorter;
    measure_partitions(input_file, hsorter);

    //IntroSorter itoorter;
    //measure_partitions(input_file, itoorter);

    STLSorter ssorter;
    measure_partitions(input_file, ssorter);

    StableSorter sbsorter;
    measure_partitions(input_file, sbsorter);

    ShellSorter shsorter;
    measure_partitions(input_file, shsorter);
}