#include <iostream>
#include <string>
using namespace std;

class RSA {
    int p, q, n, phi, e, d;
    static int count;

public:
    RSA() {
        p = q = n = phi = e = d = 0;
        count++;
    }

    RSA(RSA &r) {
        p = r.p;
        q = r.q;
        n = r.n;
        phi = r.phi;
        e = r.e;
        d = r.d;
        count++;
    }

    ~RSA() {
        cout << "\nRSA object destroyed.\n";
    }

    bool isPrime(int num) {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    int modExp(int base, int exp, int mod) {
        int result = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp % 2 == 1)
                result = (result * base) % mod;
            base = (base * base) % mod;
            exp = exp / 2;
        }
        return result;
    }

    int modInverse(int eVal, int phiVal) {
        int t = 0, newT = 1;
        int r = phiVal, newR = eVal;
        while (newR != 0) {
            int q = r / newR;
            int temp = newT;
            newT = t - q * newT;
            t = temp;

            temp = newR;
            newR = r - q * newR;
            r = temp;
        }
        if (r > 1) return -1;
        if (t < 0) t += phiVal;
        return t;
    }

    void generateKeys() {
        cout << "Enter two prime numbers (p and q): ";
        cin >> p >> q;

        if (!isPrime(p) || !isPrime(q)) {
            cout << "Error: Both numbers must be prime!\n";
            return;
        }

        n = p * q;
        phi = (p - 1) * (q - 1);

        cout << "Enter public exponent e (coprime with " << phi << "): ";
        cin >> e;

        if (gcd(e, phi) != 1) {
            cout << "Error: e is not coprime with phi(n)!\n";
            return;
        }

        d = modInverse(e, phi);

        cout << "\nKeys generated successfully!\n";
        cout << "Public Key: (" << n << ", " << e << ")\n";
        cout << "Private Key: (" << n << ", " << d << ")\n";
    }

    void encrypt(string message, int encrypted[], int &length) {
        length = message.length();
        for (int i = 0; i < length; i++) {
            int asciiVal = (int)message[i];
            encrypted[i] = modExp(asciiVal, e, n);
        }
    }

    void decrypt(int encrypted[], int length, string &decrypted) {
        decrypted = "";
        for (int i = 0; i < length; i++) {
            int decryptedVal = (int)modExp(encrypted[i], d, n);
            decrypted += (char)decryptedVal;
        }
    }

    static void showCount() {
        cout << "\nTotal RSA objects created: " << count << "\n";
    }
};

int RSA::count = 0;

void welcomeMessage() {
    cout << "Welcome to Beginner-Friendly RSA System" << endl;
}

int main() {
    welcomeMessage();

    int n;
    cout << "Enter number of RSA users you want to create (max 10): ";
    cin >> n;

    if (n <= 0 || n > 10) {
        cout << "Invalid number of users. Please enter between 1 and 10." << endl;
        return 1;
    }

    RSA users[10];   

    for (int i = 0; i < n; i++) {
        cout << endl << "Generating keys for User " << i + 1 << endl;
        users[i].generateKeys();

        int choice;
        cout << endl << "Choose an option for User " << i + 1 << ":" << endl;
        cout << "1. Encrypt a message" << endl;
        cout << "2. Decrypt a message" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string message;
                cout << endl << "Enter message to encrypt: ";
                cin >> message;

                int encrypted[100];
                int length = 0;
                users[i].encrypt(message, encrypted, length);

                cout << endl << "Encrypted Message (User " << i + 1 << "): ";
                for (int j = 0; j < length; j++) {
                    cout << encrypted[j] << " ";
                }
                cout << "\n";
                break;
            }
            case 2: {
                int length;
                cout << endl << "Enter number of encrypted values: ";
                cin >> length;

                int encrypted[100];
                cout << "Enter encrypted values: ";
                for (int j = 0; j < length; j++) {
                    cin >> encrypted[j];
                }

                string decrypted;
                users[i].decrypt(encrypted, length, decrypted);
                cout << "Decrypted Message (User " << i + 1 << "): " << decrypted << endl;
                break;
            }
            default:
                cout << "Invalid choice." << endl;
        }
    }

    RSA::showCount();

    RSA rsaCopy(users[0]);  
    cout << endl << "A copy of User 1's RSA object was created." << endl;
    RSA::showCount();

return 0;
}
