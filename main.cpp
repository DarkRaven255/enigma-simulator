#include <iostream>
#include <fstream>

using namespace std;

string line, orderRotors, key, sboard1, sboard2, output;
int noReflector;

char alphabet[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char rotors[5][27]=
{
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ", ///0
    "AJDKSIRUXBLHWTMCQGZNPYFVOE", ///1
    "BDFHJLCPRTXVZNYEIWGAKMUSQO", ///2
    "ESOVPZJAYQUIRHXLNFTGKDCMWB", ///3
    "VZBRGITYUPSDNHLXAWMJQOFECK", ///4
};
char reflector[4][27]=
{
    "YRUHQSLDPXNGOKMIEBFZCWVJAT", ///0
    "FVPJIAOYEDRZXWGCTKUQSBNMHL", ///1
    "ENKQAUYWJICOPBLMDXZVFTHRGS", ///2
    "RDOBJNTKVEHMLFCWZAXGYIPSUQ"  ///3
};


void openfile(string path)
{
    ifstream fin;
    fin.open(path);
    if(fin.good())
    {
        fin>>line;
        fin>>noReflector;
        fin>>orderRotors;
        fin>>key;
        fin>>sboard1;
        fin>>sboard2;
        noReflector--;
    }
    else cout<<"Blad odczytu pliku";
}

/// Funkcja przewijajaca zakresy rotorow
int mod(int a)
{
  return (a+26)%26;
}

/// Pozycja litery w tablicach kodujacych
int lp(char l)
{
  return l-65;
}

/// Znajdowanie pozycji znaku w danym rotorze
int pos(string tab, char a)
{
  return tab.find_last_of(a);
}

/// "Lacznica kablowa"
string switchboard(string lin)
{
    for(int i=0;i<lin.size();i++)
    {
        for(int j=0;j<sboard1.size();j++)
        {
            if(lin[i]==sboard1[j]) lin[i]=sboard2[j];
            else if(lin[i]==sboard2[j]) lin[i]=sboard1[j];
        }
    }
    return lin;
}

void rotate1(int &R, int &M)
{

    int position=orderRotors[orderRotors.size()-1]-49;

    if(position==0)
    {
        if((alphabet[R])=='R') M=mod(M+1);
    }
    else if(position==1)
    {
        if((alphabet[R])=='F') M=mod(M+1);
    }
    else if(position==2)
    {
        if((alphabet[R])=='W') M=mod(M+1);
    }
    else if(position==3)
    {
        if((alphabet[R])=='K') M=mod(M+1);
    }
    else if(position==4)
    {
        if((alphabet[R])=='A') M=mod(M+1);
    }


}

bool rotate2(int &M, int &L)
{
    int position=orderRotors[orderRotors.size()-2]-49;

    if(position==0)
    {
        if((alphabet[M])=='R')
        {
            //M=mod(M+1);
            L=mod(L+1);
        }

    }
    else if(position==1)
    {
        if((alphabet[M])=='F')
        {
            //M=mod(M+1);
            L=mod(L+1);
        }
    }
    else if(position==2)
    {
        if((alphabet[M])=='W')
        {
            //M=mod(M+1);
            L=mod(L+1);
        }
    }
    else if(position==3)
    {
        if((alphabet[M])=='K')
        {
            //M=mod(M+1);
            L=mod(L+1);
        }
    }
    else if(position==4)
    {
        if((alphabet[M])=='A')
        {
            //M=mod(M+1);
            L=mod(L+1);
        }
    }
}


/// Glowny szyfrator
string crypt(void)
{
    ///Ustawienie klucza
    int L=lp(key[0]);
    int M=lp(key[1]);
    int R=lp(key[2]);

    cout<<endl<<alphabet[L]<<L<<" L"<<endl;
    cout<<alphabet[M]<<M<<"  M"<<endl;
    cout<<alphabet[R]<<R<<" R"<<endl;
    bool g=false,g2=false;

    char a,b,c,f,ref;
    int  d,e;
    line=switchboard(line);
    cout<<endl;
    for (int i=0;i<line.size();i++)
    {
        int letter=lp(line[i]);

        /// Obrot rotorow
        //cout<<rotors[0][mod(R+letter)]<<" R"<<endl;
        //cout<<orderRotors[orderRotors.size()-1]-49<<" TEST"<<endl;

        //if(R==22) M=mod(M+1);
        //cout<<alphabet[L]<<alphabet[M]<<alphabet[R]<<" - Przed"<<endl;
        R=mod(R+1);
        //if(L==16)M=mod(M+1);
        //if(R==22)M=mod(M+1);
        //if(M==5)L=mod(L+1);
        //if(g==true){M=mod(M+1);L=mod(L+1);g2=true;}
        rotate1(R,M);
        //cout<<endl<<alphabet[M]<<M<<" pierwsze"<<endl;
        rotate2(M,L);

        cout<<endl<<alphabet[letter];
        cout<<endl<<alphabet[L]<<L<<" L"<<endl;
        cout<<alphabet[M]<<M<<"  M"<<endl;
        cout<<alphabet[R]<<R<<" R"<<endl;
        //cout<<endl<<alphabet[M]<<M<<" pierwsze"<<endl;
       // cout<<M<<" pierwsze"<<endl;
        //if(M==5) {M=mod(M+1);g=false;}
        //if(R==22) {M=mod(M+1); g=true;}
        //if(g==true) {M=mod(M+1);L=mod(L+1);g=false;}

        //cout<<M<<" drugie"<<endl;

        //cout<<alphabet[L]<<alphabet[M]<<alphabet[R]<<" - Po"<<endl;

        //cout<<R<<" -R1"<<endl;
        //cout<<letter<<" -letter"<<endl;
        //cout<<rotors[1][R];
        //cout<<rotors[orderRotors[orderRotors.size()-1]-49][25];

        // Pass through rotors
        a = rotors[orderRotors[orderRotors.size()-1]-49][mod(R + letter)];
        b = rotors[orderRotors[orderRotors.size()-2]-49][mod(M + lp(a) - R)];
        c = rotors[orderRotors[orderRotors.size()-3]-49][mod(L + lp(b) - M)];

        //cout<<endl<<a<<" - a"<<endl;
        //cout<<b<<" - b"<<endl;
        //cout<<c<<" - c"<<endl;

        // Pass through reflector
        ref = reflector[noReflector][mod(lp(c) - L)];

        // Inverse rotor pass
        d = mod(pos(rotors[orderRotors[orderRotors.size()-3]-49], alphabet[mod(lp(ref) + L)]) - L);
        e = mod(pos(rotors[orderRotors[orderRotors.size()-2]-49], alphabet[mod(d + M)]) - M);
        f = alphabet[mod(pos(rotors[orderRotors[orderRotors.size()-1]-49], alphabet[mod(e + R)]) - R)];

        //cout<<d<<" - d"<<endl;
        //cout<<e<<" - e"<<endl;
        //cout<<f<<" - f"<<endl;
        //cout<<output;

        output += f;
  }
  output=switchboard(output);
  return output;
}

void start(void)
{
    cout<<"Enigma simulator 2017"<<endl<<endl;
    cout<<"KOD DO ZA/ODSZYFROWANIA (bez spacji)"
    <<endl<<"NUMER REFLEKTORA (1-4)"
    <<endl<<"KOLEJNOSC ROTOROW (Z ZAKR. 1-5 (3 cyfry)"
    <<endl<<"KLUCZ SZYFUJACY (3 znaki)"
    <<endl<<"PIERWSZA LITERA PARY LACZNICY KABLOWEJ NP: AK"
    <<endl<<"DRUGA    LITERA PARY LACZNICY KABLOWEJ NP: NC, gdzie (AN)(KC)-pary"
    <<endl<<" - w przypadku nie uzywania lacznicy, nie wprowadzaj nic"
    <<endl<<" - wszystkie dane wprowadzaj duzymi literami"
    <<endl<<endl;
    cout<<"Wprowadz sciezke do pliku przygotowanego wedlug powyzszego schematu: ";
}

int main ()
{
    start();
    string path="tst.txt";
    //cin>>path;
    openfile(path);
    cout<<endl<<endl<<orderRotors<<" - Kolejnosc rotorow"<<endl;
    cout<<key<<" - Klucz szyfrujacy"<<endl<<endl;
    cout<<"Wejscie: "<<line;
    cout<<"Wyjscie: "<<crypt()<<endl<<endl;

    //system("pause");
  return 0;
}
