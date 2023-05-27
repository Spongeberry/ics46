/*#include <iostream>
#include "sorter.h"

void printArray(const vector<string>& vec, const string& name) {
    cout << name << ": ";
    for (const string& str : vec) {
        cout << str << " ";
    }
    cout << endl;
}

int main() {
    // Define the array
    vector<string> unsortedArray = {"E", "D", "C", "B", "A", "F", "G", "H"};

    // Create a copy of the unsortedArray for the standard sort
    vector<string> sortedArray = unsortedArray;
    std::sort(sortedArray.begin(), sortedArray.end());
    
    // Create sorters
    InsertionSorter insertionSorter;
    QuickSorter quickSorter;
    HeapSorter heapSorter;
    IntroSorter introSorter;
    STLSorter stlSorter;
    StableSorter stableSorter;
    ShellSorter shellSorter;
    
    // Vector of pointers to sorters for easy iteration
    vector<Sorter*> sorters = {
        &insertionSorter, 
        &quickSorter, 
        &heapSorter, 
        &introSorter, 
        &stlSorter, 
        &stableSorter, 
        &shellSorter
    };
    
    // Fill, sort, and print each sorter
    for (Sorter *sorter : sorters) {
        sorter->vec = unsortedArray; // Assuming Sorter::vec is public
        sorter->sort();
        printArray(sorter->vec, sorter->name);
        if (sorter->vec == sortedArray) {
            cout << sorter->name << " sorted correctly.\n";
        } else {
            cout << sorter->name << " did not sort correctly.\n";
        }
    }

    return 0;
}*/



#include "sorter.h"
#include <iostream>

int main()
{
    // measure_sorters("src/shortrandom.txt");
    measure_sorters("src/random.txt");
    // measure_sorters("src/shortsorted.txt");
    measure_sorters("src/sorted.txt");
    
}
