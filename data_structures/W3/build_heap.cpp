//
// Created by Duy Bui on 6/5/2023.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdlib.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
using namespace std;


class HeapBuilder {
private:
    vector<int> data_;
    vector< pair<int, int> > swaps_;
    int size_;

    void WriteResponse() const {
        cout << swaps_.size() << "\n";
        for (int i = 0; i < swaps_.size(); ++i) {
            cout << swaps_[i].first << " " << swaps_[i].second << "\n";
        }
    }

    void ReadData() {
        int n;
        cin >> n;
        data_.resize(n);
        for(int i = 0; i < n; ++i)
            cin >> data_[i];
        size_ = data_.size();
    }
    int parent(int i) {
        return floor(abs(i-1) /2);
    }

    static int left(int i) {
        return 2*i +1;
    }

    static int right(int i) {
        return 2*i +2;
    }

    void SiftDown(int i) {
        int min_heap = i;
        int l = left(i);
        if (l < size_ && data_[l] < data_[min_heap]) min_heap = l;
        int r = right(i);
        if (r < size_ && data_[r] < data_[min_heap]) min_heap = r;
        if (i != min_heap) {
            swap(data_[i], data_[min_heap]);
            swaps_.push_back(make_pair(i, min_heap));
            SiftDown(min_heap);
        }
    }

    void GenerateSwaps() {
        swaps_.clear();
        // The following naive implementation just sorts
        // the given sequence using selection sort algorithm
        // and saves the resulting sequence of swaps.
        // This turns the given array into a heap,
        // but in the worst case gives a quadratic number of swaps.
        //
        // TODO: replace by a more efficient implementation
//        for (int i = 0; i < data_.size(); ++i)
//            for (int j = i + 1; j < data_.size(); ++j) {
//                if (data_[i] > data_[j]) {
//                    swap(data_[i], data_[j]);
//                    swaps_.push_back(make_pair(i, j));
//                }
//            }
        for (int i = floor(size_/2); i >=0; i--) {
            SiftDown(i);
        }
    }

public:
    void Solve() {
        ReadData();
        GenerateSwaps();
        WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    HeapBuilder heap_builder;
    heap_builder.Solve();
    return 0;
}
