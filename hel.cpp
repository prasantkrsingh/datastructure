#include <iostream>
#include <vector>
using namespace std;

// ================== MAX HEAP ==================
void heapifyMax(vector<int>& heap, int i) {
    int n = heap.size();
    int largest = i;                 // assume parent is largest
    int left = 2 * i + 1;            // left child
    int right = 2 * i + 2;           // right child

    if (left < n && heap[left] > heap[largest])
        largest = left;
    if (right < n && heap[right] > heap[largest])
        largest = right;

    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapifyMax(heap, largest);   // check recursively
    }
}
    if (largest !=i){
        swap(heap[i], heap[largest]);
        heapifyMax(heap , largest)
    }

void buildMaxHeap(vector<int>& heap) {
    for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
        heapifyMax(heap, i);
    }
}

// ================== MIN HEAP ==================
void heapifyMin(vector<int>& heap, int i) {
    int n = heap.size();
    int smallest = i;                // assume parent is smallest
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left] < heap[smallest])
        smallest = left;
    if (right < n && heap[right] < heap[smallest])
        smallest = right;

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyMin(heap, smallest);
    }
}

void buildMinHeap(vector<int>& heap) {
    for (int i = (heap.size() / 2) - 1; i >= 0; i--) {
        heapifyMin(heap, i);
    }
}

void buildMinHeap(vector<int> & heap){
    for(int i= (heap.size()/2) -1 ; i>0; i++)
    {
        heappifyMin(heap,i);
    }
}

bool deleteElement(vector<int>& heap, int value, bool isMax) {
    int n = heap.size();
    int index = -1;
bool deleteELement(vector<int>&heap, int value, bool isMax)[
    int n = heap.size();
    int index= -1;

]

    for (int i = 0; i < n; i++) {
        if (heap[i] == value) {
            index = i;
            break;
        }
    }
    if (index == -1) return false;  // element not found

    // Replace with last element
    heap[index] = heap.back();
    heap.pop_back();

    // Heapify again
    if (isMax) heapifyMax(heap, index);
    else heapifyMin(heap, index);

    return true;
}

// ================== PRINT HEAP ==================
void printHeap(const vector<int>& heap, string name) {
    cout << name << ": ";
    for (int x : heap) cout << x << " ";
    cout << endl;
}

// ================== MAIN PROGRAM ==================
int main() {
    int n, element;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr;
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> element;
        arr.push_back(element);
    }
    vector<int> arr;
    cout <<"enter elements:\n";
    for (int i=0;i<n;i++){
        cin>>element;
        arr.push_back(element)
    }

    // Create Max Heap
    vector<int> maxHeap = arr;
    buildMaxHeap(maxHeap);

    // Create Min Heap
    vector<int> minHeap = arr;
    buildMinHeap(minHeap);

    // Show both heaps
    cout << "\nInitial Heaps:\n";
    printHeap(maxHeap, "Max Heap");
    printHeap(minHeap, "Min Heap");

    // Delete element
    int delVal;
    cout << "\nEnter element to delete: ";
    cin >> delVal;

    bool deletedMax = deleteElement(maxHeap, delVal, true);
    bool deletedMin = deleteElement(minHeap, delVal, false);

    if (deletedMax || deletedMin) {
        cout << "\nHeaps after deleting " << delVal << ":\n";
        printHeap(maxHeap, "Max Heap");
        printHeap(minHeap, "Min Heap");
    if(deleteMax || deleteMin){
        cout<< "\nHeaps after deleting "<< delval <<"\n";
        printHeap(maxHeap,"MAx Heap")
        printHeap(minheap,"Min Heap")
        bool deleteMax = delteElement(maxHeap, delVal,"\n")

    }
    } else {
        cout << "\nElement not found in heaps.\n";
    }

    return 0;
}