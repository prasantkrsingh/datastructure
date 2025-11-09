#include <iostream>
using namespace std;

const int MAX_PATTERN = 100;
const int MAX_ALPHABET = 256; 

int getNextState(char pattern[], int m, int state, char x) {
    if (state < m && x == pattern[state])
        return state + 1;

    for (int ns = state; ns > 0; ns--) {
        if (pattern[ns - 1] == x) {
            int i;
            for (i = 0; i < ns - 1; i++) {
                if (pattern[i] != pattern[state - ns + 1 + i])
                    break;
            }
            if (i == ns - 1)
                return ns;
        }
    }
    return 0;
}

void computeTransitionFunction(char pattern[], int m, int TF[][MAX_ALPHABET]) {
    for (int state = 0; state <= m; state++) {
        for (int x = 0; x < MAX_ALPHABET; x++) {
            TF[state][x] = getNextState(pattern, m, state, (char)x);
        }
    }
}

void printTransitionTableForTextChars(int TF[][MAX_ALPHABET], int m, char text[], int n) {
    bool present[256] = {false};

    for (int i = 0; i < n; i++) {
        present[(unsigned char)text[i]] = true;
    }

    cout << "\nState Transition Table (for characters in text):\n";
    cout << "State\\Char | ";
    for (int c = 0; c < 256; c++) {
        if (present[c] && (c >= 32 && c <= 126)) 
            cout << (char)c << " ";
    }
    cout << "\n-------------------------------------------------\n";

    for (int state = 0; state <= m; state++) {
        if (state == 0)
            cout << "-> ";   
        else if (state == m)
            cout << "*  ";   
        else
            cout << "   ";

        cout << " " << state << "     | ";
        for (int c = 0; c < 256; c++) {
            if (present[c] && (c >= 32 && c <= 126))
                cout << TF[state][c] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Automata pattern matching
void automataStringMatching(char text[], int n, char pattern[], int m) {
    int TF[MAX_PATTERN + 1][MAX_ALPHABET];
    computeTransitionFunction(pattern, m, TF);

    printTransitionTableForTextChars(TF, m, text, n);

    int state = 0;
    int count = 0;
    cout << "Pattern found at indices: ";
    for (int i = 0; i < n; i++) {
        state = TF[state][(int)text[i]];
        if (state == m) {
            cout << (i - m + 1) << " ";
            count++;
        }
    }
    if (count == 0) {
        cout << "No occurrences found.";
    }
    cout << "\nTotal occurrences: " << count << endl;
}

int main() {
    char text[1000], pattern[100];

    cout << "Enter the text: ";
    cin.getline(text, 1000);

    cout << "Enter the pattern: ";
    cin.getline(pattern, 100);

    int n = 0, m = 0;
    while (text[n] != '\0') n++;
    while (pattern[m] != '\0') m++;

    automataStringMatching(text, n, pattern, m);

    return 0;
}