#include <iostream>
using namespace std;

// Function to calculate and display Rabin-Karp steps
void rabinKarpDetailed(string text, string pattern, int q) {
    int d = 256; // number of possible characters (ASCII)
    int n = text.length();
    int m = pattern.length();
    int p = 0; // hash value for pattern
    int t = 0; // hash value for text
    int h = 1;
    bool found = false;

    // Compute h = pow(d, m-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    cout << "\n--- Rabin-Karp Detailed Steps ---\n";
    cout << "Text: " << text << "\nPattern: " << pattern << "\n";
    cout << "Prime modulus q = " << q << "\n\n";

    // Compute initial hash values for pattern and first window of text
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    cout << "Initial pattern hash (p) = " << p << endl;
    cout << "Initial text window hash (t) = " << t << " (window: " 
         << text.substr(0, m) << ")\n\n";

    // Slide the pattern over the text
    for (int i = 0; i <= n - m; i++) {
        cout << "Window starting at index " << i << ": ";
        cout << "\"" << text.substr(i, m) << "\" (hash = " << t << ")\n";

        // If hash values match, check characters one by one
        if (p == t) {
            cout << " → Hashes match! Checking characters...\n";
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    cout << "   ✗ Mismatch at position " << j 
                         << " ('" << text[i + j] << "' != '" << pattern[j] << "')\n";
                    break;
                }
            }
            if (match) {
                cout << "   ✓ Pattern found at index " << i << "\n";
                found = true;
            }
        } else {
            cout << " → Hashes differ. Skipping detailed check.\n";
        }

        // Calculate hash for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0)
                t = (t + q);
            cout << "Next window hash computed: " << t << "\n\n";
        }
    }

    if (!found)
        cout << "\nPattern not found in the text.\n";
}

// Main program
int main() {
    string text, pattern;
    int q;

    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern to search: ";
    getline(cin, pattern);
    cout << "Enter a prime number for q (e.g. 101): ";
    cin >> q;

    rabinKarpDetailed(text, pattern, q);
    return 0;
}
