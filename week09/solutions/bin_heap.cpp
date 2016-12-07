#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class Heap {
    vector<T> arr;
    
    void heapify();
    void bubbleUp(int);
    void bubbleDown(int);

public:
    Heap();
    Heap(vector<T> const&);
    
    T getMin() const;
    void deleteMin();
    void insert(T const&);
    bool empty() const;
};

template <typename T>
Heap<T>::Heap() {
}

template <typename T>
Heap<T>::Heap(vector<T> const& v) : arr(v) {
    heapify();
}

template <typename T>
void Heap<T>::heapify() {
    for (int i = arr.size() - 1; i >= 0; i--)
        bubbleDown(i);
}

template <typename T>
void Heap<T>::bubbleUp(int index) {
    int parent = (index - 1) / 2;

    if (parent >= 0) {
        if (arr[index] < arr[parent]) {
            swap(arr[index], arr[parent]);
            bubbleUp(parent);
        }
    }
}

template <typename T>
void Heap<T>::bubbleDown(int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    
    if (left >= arr.size())
        return;
    
    int min = index;
    
    if (arr[left] < arr[index])
        min = left;
    if (right < arr.size() && arr[right] < arr[min])
        min = right;
    
    if (min != index) {
        swap(arr[min], arr[index]);
        bubbleDown(min);
    }
}

template <typename T>
T Heap<T>::getMin() const {
    return arr[0];
}

template <typename T>
void Heap<T>::deleteMin() {
    swap(arr[0], arr[arr.size() - 1]);
    arr.pop_back();
    bubbleDown(0);
}

template <typename T>
void Heap<T>::insert(T const& elem) {
    arr.push_back(elem);
    bubbleUp(arr.size() - 1);
}

template <typename T>
bool Heap<T>::empty() const {
    return arr.empty();
}

template <typename T>
T kthLowestElement(vector<T> const& v, int k) {
    Heap<T> h(v);
    
    for (int i = 0; i < k - 1; i++)
        h.deleteMin();
    
    return h.getMin();
}


int main() {
    // Тестване на пирамидата
    int arr[] = {5, 1, 7, 10, 2, 14, 25, 20};
    vector<int> v(arr, arr + 8);
    Heap<int> h(v);
    
    while (!h.empty()) {
        cout << h.getMin() << " ";
        h.deleteMin();
    }
    
    // Тестване на първата задача
    cout << endl << kthLowestElement(v, 3);
}
