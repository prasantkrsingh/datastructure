/**implement the menu driven program to perform the following operations on A binomial
1 inserting n elements
2 - traversing
3- delete min
after the deleting min what will be the final binomial tree after deleting min**/
#include <iostream>
using namespace std;

struct Node {
    int data, degree;
    Node *parent, *child, *sibling;

    Node(int val) {
        data = val;
        degree = 0;
        parent = child = sibling = NULL;
    }
};

// Merge two Binomial Trees of same degree
Node* mergeTrees(Node* b1, Node* b2) {
    if (b1->data > b2->data)
        swap(b1, b2);

    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

// Merge root lists
Node* mergeHeaps(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    Node* head = NULL;
    Node* tail = NULL;

    while (h1 && h2) {
        Node* smaller;
        if (h1->degree <= h2->degree) {
            smaller = h1;
            h1 = h1->sibling;
        } else {
            smaller = h2;
            h2 = h2->sibling;
        }

        if (!head) {
            head = smaller;
            tail = smaller;
        } else {
            tail->sibling = smaller;
            tail = smaller;
        }
    }

    if (h1) tail->sibling = h1;
    if (h2) tail->sibling = h2;

    return head;
}

// Adjust heap to maintain binomial heap property
Node* adjust(Node* heap) {
    if (!heap || !heap->sibling) return heap;

    Node* prev = NULL;
    Node* curr = heap;
    Node* next = heap->sibling;

    while (next) {
        if ((curr->degree != next->degree) ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else {
            if (curr->data <= next->data) {
                curr->sibling = next->sibling;
                curr = mergeTrees(curr, next);
            } else {
                if (!prev) heap = next;
                else prev->sibling = next;
                curr = mergeTrees(next, curr);
            }
        }
        next = curr->sibling;
    }
    return heap;
}

// Insert new key
Node* insert(Node* heap, int key) {
    Node* newNode = new Node(key);
    Node* temp = mergeHeaps(heap, newNode);
    return adjust(temp);
}

// Utility to print a single node info
void printNode(Node* node) {
    if (!node) return;
    cout << "Node(" << node->data << ", deg=" << node->degree;
    if (node->child) cout << ", child=" << node->child->data;
    else cout << ", child=NULL";
    if (node->sibling) cout << ", sibling=" << node->sibling->data;
    else cout << ", sibling=NULL";
    cout << ")";
}

// Print entire binomial tree starting from root
void printTree(Node* root, int indent = 0) {
    if (!root) return;
    
    for (int i = 0; i < indent; i++) cout << "  ";
    printNode(root);
    cout << endl;

    // Recursively print children with increased indent
    printTree(root->child, indent + 1);

    // Siblings are printed at same indent level
    printTree(root->sibling, indent);
}

// Print heap as a single structure
void printHeap(Node* heap) {
    if (!heap) {
        cout << "Heap is empty.\n";
        return;
    }

    cout << "\n--- Binomial Heap Structure ---\n";
    printTree(heap, 1);
}

// Get minimum node
Node* getMinNode(Node* heap) {
    if (!heap) return NULL;

    Node* minNode = heap;
    int mn = heap->data;

    for (Node* t = heap; t; t = t->sibling) {
        if (t->data < mn) {
            mn = t->data;
            minNode = t;
        }
    }
    return minNode;
}

// Delete min node
Node* deleteMin(Node* heap) {
    if (!heap) return NULL;

    Node* minNode = getMinNode(heap);

    // Remove minNode from root list
    Node* prev = NULL;
    Node* curr = heap;
    while (curr != minNode) {
        prev = curr;
        curr = curr->sibling;
    }
    if (prev) prev->sibling = curr->sibling;
    else heap = curr->sibling;

    // Reverse child list of minNode
    Node* child = minNode->child;
    Node* revChild = NULL;
    while (child) {
        Node* next = child->sibling;
        child->sibling = revChild;
        child->parent = NULL;
        revChild = child;
        child = next;
    }

    // Merge remaining heap and reversed children
    Node* temp = mergeHeaps(heap, revChild);
    heap = adjust(temp);

    // Show deleted element
    cout << "\nDeleted Min: " << minNode->data << "\n";
    return heap;
}

// ---------------- MAIN ----------------
int main() {
    Node* heap = NULL;

    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        heap = insert(heap, x);
    }

    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Show Binomial Heap Structure\n";
        cout << "2. Delete Min\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            printHeap(heap);
            break;
        case 2:
            if (!heap) {
                cout << "Heap is empty. Cannot delete min.\n";
            } else {
                heap = deleteMin(heap); // shows deleted min internally
                printHeap(heap);        // then print updated heap
            }
            break;
        case 3:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
