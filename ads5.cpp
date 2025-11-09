#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int npl; // null path length
};

// Manual swap
void swapNode(Node*& a, Node*& b) {
    Node* temp = a;
    a = b;
    b = temp;
}

// Get NPL
int getNPL(Node* node) {
    if (node == nullptr) return -1;
    return node->npl;
}

// Merge two leftist heaps
Node* merge(Node* h1, Node* h2) {
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;

    // Ensure h1 has smaller key
    if (h1->key > h2->key) swapNode(h1, h2);

    // Merge h2 into right child of h1
    h1->right = merge(h1->right, h2);

    // Maintain leftist property
    if (getNPL(h1->left) < getNPL(h1->right))
        swapNode(h1->left, h1->right);

    h1->npl = getNPL(h1->right) + 1;
    return h1;
}

// Queue-based build: pairwise merging
Node* buildHeapUsingQueue(vector<int>& arr) {
    queue<Node*> q;

    // Create singleton heaps
    for (int val : arr) {
        Node* newNode = new Node{val, nullptr, nullptr, 0};
        q.push(newNode);
    }

    // Merge until only one heap remains
    while (q.size() > 1) {
        Node* h1 = q.front(); q.pop();
        Node* h2 = q.front(); q.pop();
        Node* merged = merge(h1, h2);
        q.push(merged);
    }

    return q.empty() ? nullptr : q.front();
}

// Traversals
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->key << " ";
}

// Show heap traversals
void showHeap(Node* root) {
    cout << "(In-order): "; inorder(root); cout << "\n";
    cout << "(Pre-order): "; preorder(root); cout << "\n";
    cout << "(Post-order): "; postorder(root); cout << "\n";
}

// Extract minimum element
Node* extractMin(Node* root) {
    if (root == nullptr) return nullptr;
    cout << "\nMinimum element extracted: " << root->key << "\n";
    Node* left = root->left;
    Node* right = root->right;
    delete root;
    return merge(left, right);
}

// Main
int main() {
    Node* heap1 = nullptr;
    Node* heap2 = nullptr;
    int n1, n2;

    // Heap 1 input
    cout << "Enter number of elements in Heap 1: ";
    cin >> n1;
    vector<int> arr1(n1);
    cout << "Enter elements for Heap 1:\n";
    for (int i = 0; i < n1; i++) cin >> arr1[i];
    heap1 = buildHeapUsingQueue(arr1);

    cout << "\nLeftist Heap 1 traversals:\n";
    showHeap(heap1);

    // Heap 2 input
    cout << "\nEnter number of elements in Heap 2: ";
    cin >> n2;
    vector<int> arr2(n2);
    cout << "Enter elements for Heap 2:\n";
    for (int i = 0; i < n2; i++) cin >> arr2[i];
    heap2 = buildHeapUsingQueue(arr2);

    cout << "\nLeftist Heap 2 traversals:\n";
    showHeap(heap2);

    // Merge Heap1 and Heap2
    cout << "\nAfter merging both Leftist heaps:\n";
    heap1 = merge(heap1, heap2);
    showHeap(heap1);

    // Extract min
    heap1 = extractMin(heap1);

    cout << "\nLeftist Heap after extracting minimum:\n";
    showHeap(heap1);

    return 0;
}
