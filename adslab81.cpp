#include <iostream>
using namespace std;

// ===============================
// Function: Naive String Matching
// ===============================
void naiveSearch(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    bool found = false;

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j])
                break;
        }
        if (j == m) {
            cout << "Pattern found at index " << i << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Pattern not found in the text.\n";
}

// ===============================
// Function: Rabin-Karp Algorithm
// ===============================
void rabinKarpSearch(string text, string pattern, int q) {
    int d = 256; // number of characters in input alphabet
    int n = text.length();
    int m = pattern.length();
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;
    bool found = false;

    // The value of h = pow(d, m-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate initial hash values for pattern and first window of text
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                cout << "Pattern found at index " << i << endl;
                found = true;
            }
        }

        // Compute hash for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t = (t + q);
        }
    }

    if (!found)
        cout << "Pattern not found in the text.\n";
}

// ===============================
// Main Program (Menu Driven)
// ===============================
int main() {
    string text, pattern;
    int choice;

    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern to search: ";
    getline(cin, pattern);

    do {
        cout << "\n===== STRING MATCHING MENU =====";
        cout << "\n1. Naive Approach";
        cout << "\n2. Rabin-Karp Approach";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            naiveSearch(text, pattern);
            break;

        case 2: {
            int q;
            cout << "Enter a prime number for q: ";
            cin >> q;
            rabinKarpSearch(text, pattern, q);
            break;
        }

        case 3:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 3);

    return 0;
}
