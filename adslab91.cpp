#include <iostream>
using namespace std;

// Function to create LPS array
void computeLPS(char pattern[], int m, int lps[]) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search Function
void KMPSearch(char text[], char pattern[]) {
    int n = 0, m = 0;

    while (text[n] != '\0') n++;      // text length
    while (pattern[m] != '\0') m++;  // pattern length

    int lps[m];
    computeLPS(pattern, m, lps);

    // Print LPS Array
    cout << "\nLPS Array: ";
    for (int i = 0; i < m; i++) {
        cout << lps[i] << " ";
    }
    cout << endl << endl;

    int i = 0, j = 0;
    int totalOccurrences = 0;
    int matchIndexes[100];  // store indexes (adjust size as needed)

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            matchIndexes[totalOccurrences] = i - j;
            totalOccurrences++;
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    // Print match indexes side by side
    if (totalOccurrences > 0) {
        cout << "Pattern found at indexes: ";
        for (int k = 0; k < totalOccurrences; k++) {
            cout << matchIndexes[k];
            if (k != totalOccurrences - 1) cout << " | ";
        }
        cout << endl;
    } else {
        cout << "Pattern not found in text." << endl;
    }

    cout << "Total Occurrences: " << totalOccurrences << endl;
}

int main() {
    char text[200], pattern[100];

    cout << "Enter Text: ";
    cin.getline(text, 200);

    cout << "Enter Pattern: ";
    cin.getline(pattern, 100);

    KMPSearch(text, pattern);
    return 0;
}
