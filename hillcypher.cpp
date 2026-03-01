#include<iostream>
#include<string>
#include<array>
#include<limits>
using namespace std;

class HillCipher
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
}

int main()
{
    string hill_plaintext, hill_to_decrypt;
    int hill_k[3][3]={{1,2,3},{4,5,7},{6,8,9}};
    int hill_choice, hill_keyChoice;

    do
    {
        cout<<endl<<"HILL CIPHER PROGRAM"<<endl;
        cout<<"1. Encrypt text"<<endl;
        cout<<"2. Decrypt text"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>hill_choice;
        clearBuffer();

        if(hill_choice==1 || hill_choice==2)
        {
            cout<<endl<<"1. Use default key matrix"<<endl;
            cout<<"2. Enter your own key matrix"<<endl;
            cout<<"Enter your choice: ";
            cin>>hill_keyChoice;
            clearBuffer();

            if(hill_keyChoice!=1 && hill_keyChoice!=2)
            {
                cout<<"Invalid choice. Using default key matrix."<<endl;
                hill_keyChoice=1;
            }

            bool hill_abort=false;
            if(hill_keyChoice==2)
            {
                bool hill_valid=false;
                do
                {
                    hill_inputKey(hill_k);
                    HillCipher hill_checker(hill_k);
                    if(hill_checker.hill_checkValid(hill_k)==0)
                    {
                        cout<<"Invalid key. Determinant not coprime with 27."<<endl;
                        cout<<"Enter 1 to retry or 0 to use default key: ";
                        int hill_opt; cin>>hill_opt;
                        clearBuffer();
                        if(hill_opt==0)
                        {
                            hill_k[0][0]=1; hill_k[0][1]=2; hill_k[0][2]=3;
                            hill_k[1][0]=4; hill_k[1][1]=5; hill_k[1][2]=7;
                            hill_k[2][0]=6; hill_k[2][1]=8; hill_k[2][2]=9;
                            hill_valid=true;
                            hill_abort=true;
                        }
                    }
                    else
                        hill_valid=true;
                }while(!hill_valid);
            }

            HillCipher hill_temp(hill_k);

            if(hill_choice==1)
            {
                cout<<"Enter plain text to be encrypted: ";
                getline(cin, hill_plaintext);
                string hill_cipher=hill_temp.hill_encrypt(hill_plaintext);
                cout<<"The text on encryption using Hill-Cipher Method is: "<<hill_cipher<<endl;
            }
            else
            {
                cout<<"Enter cipher text to be decrypted: ";
                getline(cin, hill_to_decrypt);
                string hill_decrypted=hill_temp.hill_decrypt(hill_to_decrypt);
                cout<<"The decrypted text is: "<<hill_decrypted<<endl;
            }
        }
        else if(hill_choice!=3)
            cout<<"Invalid choice. Try again."<<endl;

    }while(hill_choice!=3);

return 0;
}