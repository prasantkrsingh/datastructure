#include <iostream>
using namespace std;

struct Node {
    int key, height;
    Node *left, *right;
};

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node* bstInsert(Node* root, int key) {
    if (root == NULL) return newNode(key);
    if (key < root->key) root->left = bstInsert(root->left, key);
    else if (key > root->key) root->right = bstInsert(root->right, key);
    return root;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* bstDelete(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->key) root->left = bstDelete(root->left, key);
    else if (key > root->key) root->right = bstDelete(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = bstDelete(root->right, temp->key);
    }
    return root;
}

bool bstSearch(Node* root, int key) {
    if (root == NULL) return false;
    if (root->key == key) return true;
    else if (key < root->key) return bstSearch(root->left, key);
    else return bstSearch(root->right, key);
}


int height(Node* n) { return (n == NULL) ? 0 : n->height; }
int getBalance(Node* n) { return (n == NULL) ? 0 : height(n->left) - height(n->right); }

Node* rightRotate(Node* y) {

    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* avlInsert(Node* node, int key) {
    if (node == NULL) return newNode(key);

    if (key < node->key)
        node->left = avlInsert(node->left, key);
    else if (key > node->key)
        node->right = avlInsert(node->right, key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* avlDelete(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->key) root->left = avlDelete(root->left, key);
    else if (key > root->key) root->right = avlDelete(root->right, key);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root; root = NULL;
            } else *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = avlDelete(root->right, temp->key);
        }
    }

    if (root == NULL) return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

bool avlSearch(Node* root, int key) {
    if (root == NULL) return false;
    if (root->key == key) return true;
    else if (key < root->key) return avlSearch(root->left, key);
    else return avlSearch(root->right, key);
}

void inorder(Node* root) {
    if (root) { inorder(root->left); cout << root->key << " "; inorder(root->right); }
}
void preorder(Node* root) {
    if (root) { cout << root->key << " "; preorder(root->left); preorder(root->right); }
}
void postorder(Node* root) {
    if (root) { postorder(root->left); postorder(root->right); cout << root->key << " "; }
}

void showTraversals(Node* root) {
    cout << "\nInorder   : "; inorder(root);
    cout << "\nPreorder  : "; preorder(root);
    cout << "\nPostorder : "; postorder(root);
    cout << "\n";
}


int main() {
    Node* root = NULL;
    int choice, n, val, op;
    while(true){
        cout << "\nChoose Tree:\n1. Binary Search Tree \n2. AVL Tree\n3. Exit Program \nEnter Choice: ";
        cin >> choice;
        if(choice==3){
            cout<<"Exiting Program..\n";
            break;
    
        }

        if (choice == 1) {
            cout << "Enter number of elements: ";
            cin >> n;
            cout << "Enter " << n << " elements: ";
            int arr[100];
            for (int i = 0; i < n; i++) cin >> arr[i];
            for (int i = 0; i < n; i++) root = bstInsert(root, arr[i]);
            cout << "\nBinary Search Tree Created :- ";
            showTraversals(root);


            do {
                cout << "\nOperations:\n1. Insertion\n2. Deletion\n3. Traversing\n4. Searching\n5. Exit\nChoose for Another Operation: ";
                cin >> op;
                
                switch (op) {
                    case 1: cout << "Enter value to insert: "; cin >> val;
                            root = bstInsert(root, val);
                            cout << "After Insertion:"; showTraversals(root); break;
                    case 2: cout << "Enter value to delete: "; cin >> val;
                            root = bstDelete(root, val);
                            cout << "After Deletion:"; showTraversals(root); break;
                    case 3: showTraversals(root); break;
                    case 4: cout << "Enter value to search: "; cin >> val;
                            cout << (bstSearch(root, val) ? "Element is Found\n" : "Element is Not Found\n"); break;
                }
            } while (op != 5);
        }
        else if (choice == 2) {
            cout << "Enter number of elements: ";
            cin >> n;
            cout << "Enter " << n << " elements: ";
            int arr[100];
            for (int i = 0; i < n; i++) cin >> arr[i];
            for (int i = 0; i < n; i++) root = avlInsert(root, arr[i]);
            cout << "\nAVL Tree Created:-";
            showTraversals(root);

            do {
                cout << "\nOperations:\n1. Insertion\n2. Deletion\n3. Traversing\n4. Searching\n5. Exit\nChoose for Another Operation: ";
                cin >> op;
                switch (op) {
                    case 1: cout << "Enter value to insert: "; cin >> val;
                            root = avlInsert(root, val);
                            cout << "After Insertion:"; showTraversals(root); break;
                    case 2: cout << "Enter value to delete: "; cin >> val;
                            root = avlDelete(root, val);
                            cout << "After Deletion:"; showTraversals(root); break;
                    case 3: showTraversals(root); break;
                    case 4: cout << "Enter value to search: "; cin >> val;
                            cout << (avlSearch(root, val) ?"Element is Found\n" : "Element is Not Found\n");break;
                }
            } while (op != 5);
        }
    }

        return 0;
    }
