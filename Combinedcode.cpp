#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include<array>
#include<limits>
#include <vector>
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace std;


// El gamal Ishan Patankar Start
class Elgamal
{
    private:
    static string Sentence;

    static int x;
    
    public:
    
    int m[45],count=0,f=0,check=0,p,one,y,h,C1[45],C2[45],Cyphertext[90],a,count2=0,ishan_x=1,ishan_y=1;
    void takedata()
    {
        while ( check==0)   // check the p
        {
        cout<<endl<<"Enter the Prime 'p' which will be used in the Public Key:";
        cin>>p;
        for(int i=2;i<p-1;i++)
        {
            if (p % i==0)
            {
                f=1;
                check=1;
            break;
            }

        }
        if(f==1)
        {
            cout<<endl<<"p is not a prime number, please correctly enter p.";
        }
        if(f==0)
        check=1;
        }
        cout<<endl<<"Enter value for x which is Private and only the Sender and Reciever must use it:";
        cin>>one;
        x=one;
        cout<<endl<<"Enter the Data string thet you want to Encrypt:"; // Sentence gets protected in private while converting to numerical text in m
        cin>>Sentence;
        
        for (char c : Sentence)
        {
        m[count] = (int)c;          // char → ASCII
        count++;
        }
        cout<<endl<<"Message has been converted into neumerical data which will be used for Encryption";

        ofstream egFile("elgamal_history.txt", ios::app);
        if(egFile.is_open())
        {
            egFile<<"Input Sentence: "<<Sentence<<endl;
            egFile.close();
        }
    }

};
class Elgamalpublickeyc1c2: public Elgamal
{  
    private:
   int lower;
   int upper;
   
   public:
   
    void Publickey()
    {
         int lower= 2;
   int upper = static_cast<int>(0.7 * p);
    std::srand(std::time(0)); // Seed the random number generator

    int g = (lower + std::rand() % (upper - lower + 1))%p;
    ishan_y=g;
    for(int i=0;i<one;i++)
        {
            ishan_x=(ishan_x*ishan_y)%p;
        }
    one= ishan_x; //hiding x 
    cout<<"g="<<g<<" the Generator which is a part of Public key has been calculated !";
    h = one %p ; // h = g^x mod p
    cout<<"h which is a part of Public key has been calculated !";

    cout<<endl<<"The Public key (p,g,h)=("<<p<<","<<g<<","<<h<<")"; // printing public key
    cout<<endl<<"Enter Ephermal Y so that 1<= Y <= p-2:";
    cin>> y;

    cout<<endl<<"Calculation of Cyphertext C1,C2:";
    
    g=g%p;
    h=h%p;
    for(int i=0;i<count;i++)
    {   
        ishan_y=1;
        ishan_x=1;
        for(int v=0;v<y;v++)
        {
            ishan_y=(ishan_y*g)%p;
        }
        C1[i]=ishan_y%p;

        for(int l=0;l<y;l++)
        {
            ishan_x=(ishan_x*h)%p;
        }
        C2[i]=(m[i]*(ishan_x))%p;
    }
    for (int i = 0; i < count; i++) {
    Cyphertext[2*i]   = C1[i];  // even index
    Cyphertext[2*i+1] = C2[i];  // odd index
    }

    
    cout<<endl<<"Ciphertext generated (C1,C2):";
    for(int k=0;k<(count*2);k++)
    {
    cout<<"("<<Cyphertext[k]<<","<<Cyphertext[k+1]<<")";
    k=k+1; // for correction
    }

    ofstream egFile("elgamal_history.txt", ios::app);
    if(egFile.is_open())
    {
        egFile<<"Ciphertext: ";
        for(int k=0;k<(count*2);k++)
        {
            egFile<<"("<<Cyphertext[k]<<","<<Cyphertext[k+1]<<")";
            k=k+1;
        }
        egFile<<endl;
        egFile.close();
    }

    ifstream egIn("elgamal_history.txt");
    if(egIn.is_open())
    {
        cout<<endl<<"ElGamal History from file:"<<endl;
        string line;
        while(getline(egIn,line))
        {
            cout<<line<<endl;
        }
        egIn.close();
    }
    
} 
};
class ElgamaDecryption
{  public:
    
    int ishan_num,ishan_x,D1[45],D2[45],p,g,h,D[45],use;
     void decryption()   
    {
        cout<<endl<<"Welcome to Decryption of Cipher text generated via El gamal Encription"<<endl<<"Enter the number of Characters in your Message:";
        cin>>ishan_num;
        cout<<endl<<"Enter the sectret x that only the sender and reciever should know:";
        cin>>ishan_x;
        cout<<endl<<"Enter the cyphertext pairs in correct order:";
        for(int i=0;i<ishan_num;i++)
        {
           cout<<endl<<"Enter C1 of pair number"<<"\t"<<i+1<<"\t"<<":";
           cin>>  D1[i] ;
           cout<<endl<<"Enter C2 of pair number"<<"\t"<<i+1<<"\t"<<":";
           cin>>  D2[i] ; 
        }

        cout<<endl<<"Enter the Public key :"<<endl<<"Enter p:";
        cin>>p;
        cout<<endl<<"Enter g:";
        cin>>g;
        cout<<endl<<"Enter h:";
        cin>>h;

        cout<<endl<<"Now Decryption will begin:";

        for(int j=0;j<ishan_num;j++)
        {
            use=1;
         D2[j]=D2[j]%p;
         D1[j]=D1[j]%p;
         for(int k=0;k<ishan_x;k++)
         {
            use=(use*D1[j])%p  ;       
         }
         
         int s_inv = -1;
        for(int i = 1; i < p; i++)
        {
            if((use * i) % p == 1)
            {
                s_inv = i;
                break;
            }
        }

        if(s_inv == -1)
        {
            cout << "Error: modular inverse not found for C1^x mod p!" << endl;
            return;
    
        }
         D[j]=(D2[j]*s_inv)%p;
         //D[j]=D[j]+46;
        }
        cout <<endl<< "Decrypted message: ";

        for(int j = 0; j < ishan_num; j++)
        {
        //cout<<D[j];
        cout << (char)D[j];
        }

        string decrypted_msg="";
        for(int j=0;j<ishan_num;j++)
        {
            decrypted_msg+= (char)D[j];
        }

        ofstream egFileOut("elgamal_history.txt", ios::app);
        if(egFileOut.is_open())
        {
            egFileOut<<"Decrypted Message: "<<decrypted_msg<<endl;
            egFileOut.close();
        }

        string original_line="";
        ifstream egFileIn("elgamal_history.txt");
        if(egFileIn.is_open())
        {
            string line;
            while(getline(egFileIn,line))
            {
                if(line.find("Input Sentence: ")==0)
                {
                    original_line=line;
                }
            }
            egFileIn.close();
        }

        if(original_line!="")
        {
            string original_msg = original_line.substr(16);
            if(decrypted_msg==original_msg)
            {
                cout<<endl<<"Decrypted message matches original input (ElGamal)."<<endl;
            }
            else
            {
                cout<<endl<<"Decrypted message does NOT match original input (ElGamal)."<<endl;
            }
        }

    }
    
}; // El- Gamal ends


//-------------------------//

class HillCipher // Hill Cypher starts - Anannya Patil
{
    int hill_key[3][3];
    int hill_invkey[3][3];

    int hill_mod27(int x)
    {
        x%=27;
        if(x<0)x+=27;
        return x;
    }

    int hill_c2n(char c)
    {
        if(c==' ')
            return 0;
        else
            return c-'A'+1;
    }

    char hill_n2c(int n)
    {
        n = hill_mod27(n);
        if(n==0)
            return ' ';
        else
            return char(n+'A'-1);
    }

    string hill_cleanUpper(string s)
    {
        string t = "";
        for(int i=0; s[i]!='\0'; i++)
        {
            if((s[i]==' ') || ((s[i]>=65)&&(s[i]<=90)) || ((s[i]>=97)&&(s[i]<=122)))
            {
                if((s[i]>=97)&&(s[i]<=122))
                    s[i] = s[i]-32;
                t = t + s[i];
            }
        }
        return t;
    }

    string hill_pad3(string s)
    {
        while(s.size()%3 != 0)
            s += 'X';
        return s;
    }

    int hill_det(int a[3][3])
    {
        int det = a[0][0]*(a[1][1]*a[2][2]-a[1][2]*a[2][1])
                - a[0][1]*(a[1][0]*a[2][2]-a[1][2]*a[2][0])
                + a[0][2]*(a[1][0]*a[2][1]-a[1][1]*a[2][0]);
        return hill_mod27(det);
    }

    int hill_multInv(int det)
    {
        det = hill_mod27(det);
        for(int i=1; i<27; i++)
        {
            if((det*i)%27==1)
                return i;
        }
        return -1;
    }

    void hill_inverse()
    {
        int det = hill_det(hill_key);
        int det_inv = hill_multInv(det);

        hill_invkey[0][0] = hill_mod27((hill_key[1][1]*hill_key[2][2] - hill_key[1][2]*hill_key[2][1]) * det_inv);
        hill_invkey[0][1] = hill_mod27(-(hill_key[0][1]*hill_key[2][2] - hill_key[0][2]*hill_key[2][1]) * det_inv);
        hill_invkey[0][2] = hill_mod27((hill_key[0][1]*hill_key[1][2] - hill_key[0][2]*hill_key[1][1]) * det_inv);
        
        hill_invkey[1][0] = hill_mod27(-(hill_key[1][0]*hill_key[2][2] - hill_key[1][2]*hill_key[2][0]) * det_inv);
        hill_invkey[1][1] = hill_mod27((hill_key[0][0]*hill_key[2][2] - hill_key[0][2]*hill_key[2][0]) * det_inv);
        hill_invkey[1][2] = hill_mod27(-(hill_key[0][0]*hill_key[1][2] - hill_key[0][2]*hill_key[1][0]) * det_inv);
        
        hill_invkey[2][0] = hill_mod27((hill_key[1][0]*hill_key[2][1] - hill_key[1][1]*hill_key[2][0]) * det_inv);
        hill_invkey[2][1] = hill_mod27(-(hill_key[0][0]*hill_key[2][1] - hill_key[0][1]*hill_key[2][0]) * det_inv);
        hill_invkey[2][2] = hill_mod27((hill_key[0][0]*hill_key[1][1] - hill_key[0][1]*hill_key[1][0]) * det_inv);
    }

    public:

    HillCipher(int k[3][3])
    {
        for(int i=0; i<3; i++)
            for(int j=0; j<3; j++)
                hill_key[i][j] = k[i][j];
        hill_inverse();
    }

    int hill_checkValid(int k[3][3])
    {
        int det = hill_det(k);
        int inv = hill_multInv(det);
        if(inv==-1)
            return 0;
        return 1;
    }

    string hill_encrypt(string plaintext)
    {
        string p = hill_cleanUpper(plaintext);
        p = hill_pad3(p);

        string c = "";
        for(int k=0; k<p.size(); k+=3)
        {
            char in[3] = {p[k],p[k+1],p[k+2]};
            char out[3];
            for(int i=0;i<3;i++)
            {
                int sum=0;
                for(int j=0;j<3;j++)
                    sum += hill_key[i][j] * hill_c2n(in[j]);
                out[i] = hill_n2c(sum);
            }
            c+= out[0]; c+= out[1]; c+= out[2];
        }
        return c;
    }

    string hill_decrypt(string ciphertext)
    {
        string c = hill_cleanUpper(ciphertext);
        string p = "";
        for(int k=0; k<c.size(); k+=3)
        {
            char in[3] = {c[k],c[k+1],c[k+2]};
            char out[3];
            for(int i=0;i<3;i++)
            {
                int sum=0;
                for(int j=0;j<3;j++)
                    sum += hill_invkey[i][j] * hill_c2n(in[j]);
                out[i] = hill_n2c(sum);
            }
            p+= out[0]; p+= out[1]; p+= out[2];
        }
        return p;
    }
};

void hill_inputKey(int k[3][3])
{
    cout<<"Enter your 3x3 key matrix (row by row): "<<endl;
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            cin>>k[i][j];
}

void clearBuffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}// Hill Cypher ends 

//-------------------------//

class RSA { // rsa Starts here - Aniket Patankar
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
}// Rsa Ends here

//-------------------------//

class PlayfairCipher { // playfair starts here - Parth Khadiwala

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
};// playfair ends 


//-------------------------//

string Elgamal::Sentence; // El-Gamal
int Elgamal::x; // El-Gamal


//-------------------------// Int main starts here
int main()
{
    int ans1 = 1, ans2, opt1, opt2;

    cout << "WELCOME TO CRYPTOGRAPHY COMBO" << endl << endl << endl
         << "All in one Place to Encrypt and Decrypt Data using multiple methods !" << endl;

    while (ans1 == 1)
    {
        cout << endl << "What would you like to do ? " << endl
             << "(1) Encrypt" << endl
             << "(2) Decrypt" << endl;
        cin >> opt1;

        ans2 = 1;

        while (ans2 == 1)
        {
            switch (opt1)
            {
                case 1:
                    cout << "Encryption Menu:" << endl << endl
                         << "(1) Hill Cypher" << endl
                         << "(2) El-Gamal" << endl
                         << "(3) Rivest Shamir Adleman (RSA)" << endl
                         << "(4) Playfair Cypher" << endl;
                    cin >> opt2;

                    switch (opt2)
                    {


                        case 1:
                            {
    // --- Hill Cipher Encryption calls (fixed to follow reference behavior) ---
    string hill_plaintext;
    int hill_k[3][3] = { {1,2,3}, {4,5,7}, {6,8,9} };
    int hill_keyChoice;
    cout << "Hill Cipher selected." << endl;
    cout << "1. Use default key matrix" << endl;
    cout << "2. Enter your own key matrix" << endl;
    cout << "Enter your choice: ";
    cin >> hill_keyChoice;
    clearBuffer();

    if (hill_keyChoice != 1 && hill_keyChoice != 2) {
        cout << "Invalid choice. Using default key matrix." << endl;
        hill_keyChoice = 1;
    }

    if (hill_keyChoice == 2) {
        bool hill_valid = false;
        do
        {
            hill_inputKey(hill_k);
            HillCipher hill_checker(hill_k);
            if (hill_checker.hill_checkValid(hill_k) == 0)
            {
                cout << "Invalid key. Determinant not coprime with 27." << endl;
                cout << "Enter 1 to retry or 0 to use default key: ";
                int hill_opt;
                cin >> hill_opt;
                clearBuffer();
                if (hill_opt == 0)
                {
                    hill_k[0][0]=1; hill_k[0][1]=2; hill_k[0][2]=3;
                    hill_k[1][0]=4; hill_k[1][1]=5; hill_k[1][2]=7;
                    hill_k[2][0]=6; hill_k[2][1]=8; hill_k[2][2]=9;
                    hill_valid = true;
                }
            }
            else
            {
                hill_valid = true;
                // clear leftover newline from the last numeric matrix input
                clearBuffer();
            }
        }while(!hill_valid);
    }

    HillCipher hill_obj(hill_k);

    cout << "Enter plain text to be encrypted: ";
    getline(cin, hill_plaintext);
    string hill_cipher = hill_obj.hill_encrypt(hill_plaintext);
    cout << "The text on encryption using Hill-Cipher Method is: " << hill_cipher << endl;

    ofstream hillFile("hill_history.txt", ios::app);
    if(hillFile.is_open())
    {
        hillFile<<"Input: "<<hill_plaintext<<endl;
        hillFile<<"Encrypted: "<<hill_cipher<<endl;
        hillFile.close();
    }

    ifstream hillIn("hill_history.txt");
    if(hillIn.is_open())
    {
        cout<<endl<<"Hill Cipher History from file:"<<endl;
        string line;
        while(getline(hillIn,line))
        {
            cout<<line<<endl;
        }
        hillIn.close();
    }
    // --- end Hill Cipher Encryption calls ---
}
break;


                        case 2:
                        {
                            Elgamalpublickeyc1c2 obj1;
                            obj1.takedata();
                            cout << endl << "Primary key Generation and Ciphertext :" << endl;
                            obj1.Publickey();
                            break;
                        }

                        case 3:

                            {
    // --- RSA: Encryption calls (insert into Encryption menu case 3) ---
    RSA rsa_obj;
    cout << endl << "RSA selected." << endl;
    cout << "Generating keys for this RSA instance..." << endl;
    rsa_obj.generateKeys();

    // After keys generated, offer encrypt option (keeps behavior identical to original RSA program)
    string message;
    cout << endl << "Enter message to encrypt: ";
    cin >> message;

    int encrypted[100];
    int length = 0;
    rsa_obj.encrypt(message, encrypted, length);

    cout << endl << "Encrypted Message: ";
    for (int j = 0; j < length; j++) {
        cout << encrypted[j] << " ";
    }
    cout << "\n";

    ofstream rsaFile("rsa_history.txt", ios::app);
    if(rsaFile.is_open())
    {
        rsaFile<<"Input Message: "<<message<<endl;
        rsaFile<<"Encrypted: ";
        for (int j = 0; j < length; j++) {
            rsaFile<<encrypted[j]<<" ";
        }
        rsaFile<<endl;
        rsaFile.close();
    }

    ifstream rsaIn("rsa_history.txt");
    if(rsaIn.is_open())
    {
        cout<<endl<<"RSA History from file:"<<endl;
        string line;
        while(getline(rsaIn,line))
        {
            cout<<line<<endl;
        }
        rsaIn.close();
    }
}
break;


                        case 4:
                            {
    // --- Playfair: Encryption (insert into Encryption menu case 4) ---
    cout << "Playfair Cipher selected." << endl;

    // read keyword
    cout << "Enter Playfair keyword: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline
    string pf_key;
    getline(cin, pf_key);

    // create cipher and show matrix
    PlayfairCipher pf_cipher(pf_key);
    pf_cipher.p_displayMatrix();

    // read plaintext and encrypt
    cout << "Enter plaintext to encrypt: ";
    string pf_plain;
    getline(cin, pf_plain);

    string pf_encrypted = pf_cipher.p_encrypt(pf_plain);
    cout << "Encrypted text: " << pf_encrypted << endl;

    ofstream pfFile("playfair_history.txt", ios::app);
    if(pfFile.is_open())
    {
        pfFile<<"Input: "<<pf_plain<<endl;
        pfFile<<"Encrypted: "<<pf_encrypted<<endl;
        pfFile.close();
    }

    ifstream pfIn("playfair_history.txt");
    if(pfIn.is_open())
    {
        cout<<endl<<"Playfair History from file:"<<endl;
        string line;
        while(getline(pfIn,line))
        {
            cout<<line<<endl;
        }
        pfIn.close();
    }
}
break;


                        default:
                            cout << "Invalid choice!" << endl;
                    }

                    cout << endl << "Would you like to exit or keep Encrypting?" << endl
                         << "(1) Exit" << endl
                         << "(2) Keep working" << endl;
                    cin >> ans2;

                    if(ans2==1)
                    {
                        ofstream hillClear("hill_history.txt", ios::trunc);
                        if(hillClear.is_open())
                        {
                            hillClear.close();
                        }
                        ofstream pfClear("playfair_history.txt", ios::trunc);
                        if(pfClear.is_open())
                        {
                            pfClear.close();
                        }
                        ofstream egClear("elgamal_history.txt", ios::trunc);
                        if(egClear.is_open())
                        {
                            egClear.close();
                        }
                        ofstream rsaClear("rsa_history.txt", ios::trunc);
                        if(rsaClear.is_open())
                        {
                            rsaClear.close();
                        }
                        ans2 = 0; // <<< so it leaves Encryption loop and goes back up
                    }

                    break;

                case 2:
                    cout << "Decryption Menu:" << endl << endl
                         << "(1) Hill Cypher" << endl
                         << "(2) El-Gamal" << endl
                         << "(3) Rivest Shamir Adleman (RSA)" << endl
                         << "(4) Playfair Cypher" << endl;
                    cin >> opt2;

                    switch (opt2)
                    {

                        case 1:
                        {
    // --- Hill Cipher Decryption calls (fixed to follow reference behavior) ---
    string hill_to_decrypt;
    int hill_k[3][3] = { {1,2,3}, {4,5,7}, {6,8,9} };
    int hill_keyChoice;
    cout << "Hill Cipher selected." << endl;
    cout << "1. Use default key matrix" << endl;
    cout << "2. Enter your own key matrix" << endl;
    cout << "Enter your choice: ";
    cin >> hill_keyChoice;
    clearBuffer();

    if (hill_keyChoice != 1 && hill_keyChoice != 2) {
        cout << "Invalid choice. Using default key matrix." << endl;
        hill_keyChoice = 1;
    }

    if (hill_keyChoice == 2) {
        bool hill_valid = false;
        do
        {
            hill_inputKey(hill_k);
            HillCipher hill_checker(hill_k);
            if (hill_checker.hill_checkValid(hill_k) == 0)
            {
                cout << "Invalid key. Determinant not coprime with 27." << endl;
                cout << "Enter 1 to retry or 0 to use default key: ";
                int hill_opt;
                cin >> hill_opt;
                clearBuffer();
                if (hill_opt == 0)
                {
                    hill_k[0][0]=1; hill_k[0][1]=2; hill_k[0][2]=3;
                    hill_k[1][0]=4; hill_k[1][1]=5; hill_k[1][2]=7;
                    hill_k[2][0]=6; hill_k[2][1]=8; hill_k[2][2]=9;
                    hill_valid = true;
                }
            }
            else
            {
                hill_valid = true;
                // clear leftover newline from the last numeric matrix input
                clearBuffer();
            }
        }while(!hill_valid);
    }

    HillCipher hill_obj(hill_k);

    cout << "Enter cipher text to be decrypted: ";
    getline(cin, hill_to_decrypt);
    string hill_decrypted = hill_obj.hill_decrypt(hill_to_decrypt);
    cout << "The decrypted text is: " << hill_decrypted << endl;

    ofstream hillFile("hill_history.txt", ios::app);
    if(hillFile.is_open())
    {
        hillFile<<"Cipher Input: "<<hill_to_decrypt<<endl;
        hillFile<<"Decrypted: "<<hill_decrypted<<endl;
        hillFile.close();
    }

    ifstream hillIn("hill_history.txt");
    if(hillIn.is_open())
    {
        cout<<endl<<"Hill Cipher History from file:"<<endl;
        string line;
        while(getline(hillIn,line))
        {
            cout<<line<<endl;
        }
        hillIn.close();
    }
    // --- end Hill Cipher Decryption calls ---
}
break;


                        case 2:
                        {
                            ElgamaDecryption obj2;
                            obj2.decryption();
                            break;
                        }

                        case 3:

                            {
    // --- RSA: Decryption calls (insert into Decryption menu case 3) ---
    RSA rsa_obj;
    cout << endl << "RSA selected." << endl;
    cout << "Generating keys for this RSA instance..." << endl;
    rsa_obj.generateKeys();

    int length;
    cout << endl << "Enter number of encrypted values: ";
    cin >> length;

    int encrypted[100];
    cout << "Enter encrypted values: ";
    for (int j = 0; j < length; j++) {
        cin >> encrypted[j];
    }

    string decrypted;
    rsa_obj.decrypt(encrypted, length, decrypted);
    cout << "Decrypted Message: " << decrypted << endl;

    ofstream rsaFile("rsa_history.txt", ios::app);
    if(rsaFile.is_open())
    {
        rsaFile<<"Decrypted: "<<decrypted<<endl;
        rsaFile.close();
    }

    string lastInput="";
    ifstream rsaIn("rsa_history.txt");
    if(rsaIn.is_open())
    {
        string line;
        while(getline(rsaIn,line))
        {
            if(line.find("Input Message: ")==0)
            {
                lastInput=line;
            }
        }
        rsaIn.close();
    }

    if(lastInput!="")
    {
        string orig = lastInput.substr(15);
        if(orig==decrypted)
        {
            cout<<endl<<"Decrypted message matches original input (RSA)."<<endl;
        }
        else
        {
            cout<<endl<<"Decrypted message does NOT match original input (RSA)."<<endl;
        }
    }
}
break;


                        case 4:
                            {
    // --- Playfair: Decryption (insert into Decryption menu case 4) ---
    cout << "Playfair Cipher selected." << endl;

    // read keyword
    cout << "Enter Playfair keyword: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline
    string pf_key;
    getline(cin, pf_key);

    // create cipher and show matrix
    PlayfairCipher pf_cipher(pf_key);
    pf_cipher.p_displayMatrix();

    // read ciphertext and decrypt
    cout << "Enter ciphertext to decrypt: ";
    string pf_ciphertext;
    getline(cin, pf_ciphertext);

    string pf_decrypted = pf_cipher.p_decrypt(pf_ciphertext);
    cout << "Decrypted text: " << pf_decrypted << endl;

    ofstream pfFile("playfair_history.txt", ios::app);
    if(pfFile.is_open())
    {
        pfFile<<"Cipher Input: "<<pf_ciphertext<<endl;
        pfFile<<"Decrypted: "<<pf_decrypted<<endl;
        pfFile.close();
    }

    ifstream pfIn("playfair_history.txt");
    if(pfIn.is_open())
    {
        cout<<endl<<"Playfair History from file:"<<endl;
        string line;
        while(getline(pfIn,line))
        {
            cout<<line<<endl;
        }
        pfIn.close();
    }
}
break;


                        default:
                            cout << "Invalid choice!" << endl;
                    }

                    cout << endl << "Would you like to exit or keep Decrypting?" << endl
                         << "(1) Exit" << endl
                         << "(2) Keep working" << endl;
                    cin >> ans2;

                    if(ans2==1)
                    {
                        ofstream hillClear("hill_history.txt", ios::trunc);
                        if(hillClear.is_open())
                        {
                            hillClear.close();
                        }
                        ofstream pfClear("playfair_history.txt", ios::trunc);
                        if(pfClear.is_open())
                        {
                            pfClear.close();
                        }
                        ofstream egClear("elgamal_history.txt", ios::trunc);
                        if(egClear.is_open())
                        {
                            egClear.close();
                        }
                        ofstream rsaClear("rsa_history.txt", ios::trunc);
                        if(rsaClear.is_open())
                        {
                            rsaClear.close();
                        }
                        ans2 = 0; // <<< so it leaves Decryption loop and returns to outer while
                    }

                    break;

                default:
                    cout << "Invalid option!" << endl;
                    ans2 = 0;
                    break;
            }
        }

        cout << endl << "Would you like to go back to main menu?" << endl
             << "(1) Yes" << endl
             << "(2) No" << endl;
        cin >> ans1;
    }

    ofstream hillClear("hill_history.txt", ios::trunc);
    if(hillClear.is_open())
    {
        hillClear.close();
    }
    ofstream pfClear("playfair_history.txt", ios::trunc);
    if(pfClear.is_open())
    {
        pfClear.close();
    }
    ofstream egClear("elgamal_history.txt", ios::trunc);
    if(egClear.is_open())
    {
        egClear.close();
    }
    ofstream rsaClear("rsa_history.txt", ios::trunc);
    if(rsaClear.is_open())
    {
        rsaClear.close();
    }

    cout << "Exiting program..." << endl;
    return 0;
}
