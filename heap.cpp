#include <iostream>
#include <vector>
using namespace std;

void heapifyDownMax(vector<int>& heap, int index) {
    int n = heap.size();
    while (true) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < n && heap[left] > heap[largest])
            largest = left;
        if (right < n && heap[right] > heap[largest])
            largest = right;

        if (largest != index) {
            swap(heap[index], heap[largest]);
            index = largest;
        } else break;
    }
}






void buildMaxHeap(vector<int>& heap) {
    for (int i = (heap.size() / 2) - 1; i >= 0; i--)
        heapifyDownMax(heap, i);
}


bool deleteElement(vector<int>& heap, int value, bool isMax) {
    int n = heap.size(), index = -1;

    for (int i = 0; i < n; i++) {
        if (heap[i] == value) {
            index = i;
            break;
        }
    }

    if (index == -1) return false;

    heap[index] = heap.back();
    heap.pop_back();

    if (index < heap.size()) {
        if (isMax) heapifyDownMax(heap, index);
        else heapifyDownMin(heap, index);
    }
    return true;
}


void printHeap(const vector<int>& heap, string name) {
    cout << name << ": ";
    for (int val : heap) cout << val << " ";
    cout << endl;
}

int main() {
    int n, element;
    cout << "Enter the size of Heap: ";
    cin >> n;

    vector<int> arr;
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> element;
        arr.push_back(element);
    }

    
    vector<int> maxHeap = arr;
    buildMaxHeap(maxHeap);

    
    cout << "\nBinary Heap:\n";
    printHeap(maxHeap, "Max Heap");
  

    
    int delVal;
    cout << "\nEnter Element To Deleted From Heap :";
    cin >> delVal;

    bool deletedMax = deleteElement(maxHeap, delVal, true);
    

    if (deletedMax || deletedMin) {
        cout << "\nHeaps after deleting " << delVal << ":\n";
        printHeap(maxHeap, "Max Heap");
    
    } else {
        cout << "\nElement " << delVal << " not found in either heap!\n";
    }

    return 0;
}