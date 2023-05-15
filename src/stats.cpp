#include "stats.h"
#include <cmath>

Stats::Stats(string name, const vector<int> & chain_lengths) : name(name), chain_lengths(chain_lengths) {
    stddev = compute_stddev(chain_lengths);
    mean = compute_mean(chain_lengths);
    find_min_max_entries_chains(chain_lengths);
    //print_histogram(cout);
}


double Stats::compute_mean(const vector<int> &v){
    double sum = 0;
    for (auto &n: v)
        sum += n;
    return sum / v.size();
}

double Stats::compute_stddev(const vector<int> &v){
    double sum_squares = 0;
    double mean = compute_mean(v);
    double len = v.size();
    for (auto n : v){
        double diff = n - mean;
        sum_squares += diff * diff;
    }
    return sqrt(sum_squares / len);
}

void Stats::find_min_max_entries_chains(const vector<int>& v) {
    min = chain_lengths[0];
    size_t e = 0;
    size_t c = 0;
    for (int length : v) {
        if (length < min)
            min = length;
        if (length > max)
            max = length;
        e += length;
        c += 1;
        histogram[length]++;
    }
    entries = e;
    chains = c;
    load_factor = static_cast<double>(e)/c;
}

