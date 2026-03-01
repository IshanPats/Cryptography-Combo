#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include "elgamal.h"

using namespace std;

// ------------ Elgamal::takedata (moved from original) ------------
void Elgamal::takedata()
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
}

// ------------ Elgamalpublickeyc1c2::Publickey ------------
void Elgamalpublickeyc1c2::Publickey()
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
}

// ------------ ElgamaDecryption::decryption ------------
void ElgamaDecryption::decryption()
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
}

// ------------ static member definitions ------------
string Elgamal::Sentence;
int Elgamal::x;
