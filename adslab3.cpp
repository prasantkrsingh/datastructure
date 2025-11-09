//Implement dynamic arrays using array doubling method and incremental method.Determine the cost in both the cases (doubling and incremental method) based on insertion & copy operations.
//Also specify the complexity in both cases
//program work for atleast 200 element,Anlayse which is working perfectly.

#include <iostream>
using namespace std;

class IncrementalArray {
    int *arr;
    int capacity;
    int size;
    int copyCost, insertCost;
    int increment;   

public:
    IncrementalArray(int inc) {   
        capacity = 1;
        size = 0;
        increment = inc;
        arr = new int[capacity];
        copyCost = 0;
        insertCost = 0;
    }

    void insert(int val) {
        insertCost++;
        if (size == capacity) {
            int *newArr = new int[capacity + increment]; 
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
                copyCost++;
            }
            delete[] arr;
            arr = newArr;
            capacity += increment;
        }
        arr[size++] = val;
    }

    void printCosts() {
        cout << "\n Incremental Method (With +" << increment << " growth)\n";
        cout << "Insertion cost = " << insertCost << endl;
        cout << "Copy cost      = " << copyCost << endl;
        cout << "Total cost     = " << insertCost + copyCost << endl;
    }
};

class DoublingArray {
    int *arr;
    int capacity;
    int size;
    int copyCost, insertCost;

public:
    DoublingArray() {
        capacity = 1;
        size = 0;
        arr = new int[capacity];
        copyCost = 0;
        insertCost = 0;
    }

    void insert(int val) {
        insertCost++;
        if (size == capacity) {
            int *newArr = new int[capacity * 2];
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
                copyCost++;
            }
            delete[] arr;
            arr = newArr;
            capacity *= 2;
        }
        arr[size++] = val;
    }

    void printCosts() {
        cout << "\n Doubling Method\n";
        cout << "Insertion cost = " << insertCost << endl;
        cout << "Copy cost      = " << copyCost << endl;
        cout << "Total cost     = " << insertCost + copyCost << endl;
    }
};

int main() {
    int n, k, choice;
    cout << "Enter number of elements to insert: ";
    cin >> n;

    cout << "Enter the increment constant for Incremental Method: ";
    cin >> k;

    cout << "\nCHOOSE:\n";
    cout << "1. Enter elements manually\n";
    cout << "2. Auto insert elements from 1 to "<<n<<" \n";
    cout << "Enter your choice: ";
    cin >> choice;

    IncrementalArray inc(k); 
    DoublingArray dbl;        

    if (choice == 1) {
        cout << "Enter " << n << " elements:\n";
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            inc.insert(val);
            dbl.insert(val);
        }
    } else {
        cout << "Auto inserting values from 1 to  " <<  n << endl;
        for (int i = 1; i <= n; i++) {
            inc.insert(i);
            dbl.insert(i);
        }
    }


    inc.printCosts();
    dbl.printCosts();

    return 0;
}
