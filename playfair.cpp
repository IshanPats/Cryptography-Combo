#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>   // for isalpha, toupper
using namespace std;

// 5x5 matrix creation
class PlayfairCipher {
private:
    char p_matrix[5][5];
    string p_keyword;

    void p_createMatrix() {
        cout << "Creating a 5x5 Matrix..." << endl;
        string p_processedKey = "";

        // remove duplicate letters out of keyword, replace 'J' with 'I'
        for (char p_ch : p_keyword) {
            p_ch = toupper(static_cast<unsigned char>(p_ch));
            if (p_ch == 'J') {
                p_ch = 'I';
            }
            if (isalpha(static_cast<unsigned char>(p_ch)) && p_processedKey.find(p_ch) == string::npos) {
                p_processedKey += p_ch;
            }
        }

        // Adding remaining letters to 5x5 matrix (skip J)
        for (char p_ch = 'A'; p_ch <= 'Z'; ++p_ch) {
            if (p_ch == 'J') continue;
            if (p_processedKey.find(p_ch) == string::npos) {
                p_processedKey += p_ch;
            }
        }

        // Filling matrix with processed keyword
        int p_index = 0;
        for (int p_i = 0; p_i < 5; ++p_i)
            for (int p_j = 0; p_j < 5; ++p_j)
                p_matrix[p_i][p_j] = p_processedKey[p_index++];
    }

    // Find the row and column of a character in the matrix
    pair<int, int> p_findPosition(char p_ch) {
        if (p_ch == 'J') {
            p_ch = 'I';
        }
        for (int p_i = 0; p_i < 5; ++p_i)
            for (int p_j = 0; p_j < 5; ++p_j)
                if (p_matrix[p_i][p_j] == p_ch)
                    return {p_i, p_j};
        return {-1, -1};
    }

    // Prepare the text by splitting it into digraphs
    vector<pair<char, char>> p_processText(string p_text, bool p_forEncryption = true) {
        vector<pair<char, char>> p_digraphs;

        // Remove non-letter characters
        p_text.erase(remove_if(p_text.begin(), p_text.end(), [](char p_c) { return !isalpha(static_cast<unsigned char>(p_c)); }), p_text.end());

        // Convert to uppercase and replace 'J' with 'I'
        for (char& p_ch : p_text) {
            p_ch = toupper(static_cast<unsigned char>(p_ch));
            if (p_ch == 'J') {
                p_ch = 'I';
            }
        }

        // Creating digraphs
        for (size_t p_i = 0; p_i < p_text.length(); ++p_i) {
            char p_first = p_text[p_i];
            char p_second;

            if (p_i + 1 < p_text.length()) {
                p_second = p_text[p_i + 1];
                if (p_first == p_second) {
                    // If pair has same letters, insert 'X' as second and do not skip the next letter
                    p_second = 'X';
                } else {
                    // use the next character as second and skip it in the next iteration
                    ++p_i;
                }
            } else {
                // odd-length: pad with 'X'
                p_second = 'X';
            }

            p_digraphs.push_back({p_first, p_second});
        }

        return p_digraphs;
    }

public:
    PlayfairCipher() {
        p_keyword = "KEYWORD";
        p_createMatrix();
    }

    PlayfairCipher(string p_key) {
        p_keyword = p_key;
        p_createMatrix();
    }

    void p_displayMatrix() {
        cout << "\nPlayfair Matrix (Keyword: " << p_keyword << ")\n";
        for (int p_i = 0; p_i < 5; ++p_i) {
            for (int p_j = 0; p_j < 5; ++p_j)
                cout << p_matrix[p_i][p_j] << ' ';
            cout << endl;
        }
    }

    string p_encrypt(string p_plaintext) {
        cout << "Encrypting plaintext to ciphertext..." << endl;
        vector<pair<char, char>> p_digraphs = p_processText(p_plaintext, true);
        string p_ciphertext = "";

        for (auto& p_pair : p_digraphs) {
            auto pr1 = p_findPosition(p_pair.first);
            auto pr2 = p_findPosition(p_pair.second);
            int p_r1 = pr1.first, p_c1 = pr1.second;
            int p_r2 = pr2.first, p_c2 = pr2.second;

            if (p_r1 == p_r2) {
                // Same row → take the next letters in the row
                p_ciphertext += p_matrix[p_r1][(p_c1 + 1) % 5];
                p_ciphertext += p_matrix[p_r2][(p_c2 + 1) % 5];
            } else if (p_c1 == p_c2) {
                // Same column → take the letters below
                p_ciphertext += p_matrix[(p_r1 + 1) % 5][p_c1];
                p_ciphertext += p_matrix[(p_r2 + 1) % 5][p_c2];
            } else {
                // Rectangle → swap columns
                p_ciphertext += p_matrix[p_r1][p_c2];
                p_ciphertext += p_matrix[p_r2][p_c1];
            }
        }

        return p_ciphertext;
    }

    string p_decrypt(string p_ciphertext) {
        cout << "Decrypting ciphertext to plaintext..." << endl;
        // For decryption, treat ciphertext as letter-pairs (no duplicate-letter splitting logic needed)
        vector<pair<char, char>> p_digraphs = p_processText(p_ciphertext, false);
        string p_plaintext = "";

        for (auto& p_pair : p_digraphs) {
            auto pr1 = p_findPosition(p_pair.first);
            auto pr2 = p_findPosition(p_pair.second);
            int p_r1 = pr1.first, p_c1 = pr1.second;
            int p_r2 = pr2.first, p_c2 = pr2.second;

            if (p_r1 == p_r2) {
                // Same row → take the previous letters in the row
                p_plaintext += p_matrix[p_r1][(p_c1 + 4) % 5];
                p_plaintext += p_matrix[p_r2][(p_c2 + 4) % 5];
            } else if (p_c1 == p_c2) {
                // Same column → take the letters above
                p_plaintext += p_matrix[(p_r1 + 4) % 5][p_c1];
                p_plaintext += p_matrix[(p_r2 + 4) % 5][p_c2];
            } else {
                // Rectangle → swap columns
                p_plaintext += p_matrix[p_r1][p_c2];
                p_plaintext += p_matrix[p_r2][p_c1];
            }
        }

        return p_plaintext;
    }
};

int main() {
    int p_n;
    cout << "Enter number of keywords to test: ";
    cin >> p_n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<PlayfairCipher> p_ciphers;
    p_ciphers.reserve(p_n);

    for (int p_i = 0; p_i < p_n; ++p_i) {
        string p_key;
        cout << "\nEnter keyword #" << (p_i + 1) << ": ";
        getline(cin, p_key);

        // Create cipher with given keyword and display matrix
        p_ciphers.emplace_back(p_key);
        p_ciphers.back().p_displayMatrix();

        string p_plaintext;
        cout << "Enter plaintext to encrypt: ";
        getline(cin, p_plaintext);

        string p_encrypted = p_ciphers.back().p_encrypt(p_plaintext);
        cout << "Encrypted text: " << p_encrypted << endl;

        string p_decrypted = p_ciphers.back().p_decrypt(p_encrypted);
        cout << "Decrypted text: " << p_decrypted << endl;
    }

    return 0;
}
