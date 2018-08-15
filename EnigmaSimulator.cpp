// EnigmaSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <conio.h>

using namespace std;
string Txt, orgTxt, orderRotors, key, sboard1, sboard2, output;
int noReflector=0;
bool ifrot1 = false, ifrot2 = false;

char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char rotors[5][27] =
{
	"EKMFLGDQVZNTOWYHXUSPAIBRCJ", ///0
	"AJDKSIRUXBLHWTMCQGZNPYFVOE", ///1
	"BDFHJLCPRTXVZNYEIWGAKMUSQO", ///2
	"ESOVPZJAYQUIRHXLNFTGKDCMWB", ///3
	"VZBRGITYUPSDNHLXAWMJQOFECK", ///4
};
char reflector[4][27] =
{
	"YRUHQSLDPXNGOKMIEBFZCWVJAT", ///0
	"FVPJIAOYEDRZXWGCTKUQSBNMHL", ///1
	"ENKQAUYWJICOPBLMDXZVFTHRGS", ///2
	"RDOBJNTKVEHMLFCWZAXGYIPSUQ"  ///3
};

/// Funkcja przewijajaca zakresy rotorow
int mod(int a)
{
	return (a + 26) % 26;
}

/// Pozycja litery w tablicach kodujacych
int lp(char l)
{
	return l - 65;
}

/// Znajdowanie pozycji znaku w danym rotorze
int pos(string tab, char a)
{
	return tab.find_last_of(a);
}

/// "Lacznica kablowa"
string switchboard(string lin)
{
	for (int i = 0; i<lin.size(); i++)
	{
		for (int j = 0; j<sboard1.size(); j++)
		{
			if (lin[i] == sboard1[j]) lin[i] = sboard2[j];
			else if (lin[i] == sboard2[j]) lin[i] = sboard1[j];
		}
	}
	return lin;
}

///Rotacja rotora 1 i 2
void rotate1(int &R, int &M)
{

	R = mod(R + 1);
	int position = orderRotors[orderRotors.size() - 1] - 49;
	int position2 = orderRotors[orderRotors.size() - 2] - 49;

	if ((position == 0) && (alphabet[R]) == 'R')
	{
		if (!ifrot1)M = mod(M + 1);
		if ((position2 == 0) && (alphabet[M] == 'Q')) ifrot2 = true;
		else if ((position2 == 1) && (alphabet[M] == 'E')) ifrot2 = true;
		else if ((position2 == 2) && (alphabet[M] == 'V')) ifrot2 = true;
		else if ((position2 == 3) && (alphabet[M] == 'J')) ifrot2 = true;
		else if ((position2 == 4) && (alphabet[M] == 'Z')) ifrot2 = true;
	}
	else if ((position == 1) && (alphabet[R]) == 'F')
	{
		if (!ifrot1)M = mod(M + 1);
		if ((position2 == 0) && (alphabet[M] == 'Q')) ifrot2 = true;
		else if ((position2 == 1) && (alphabet[M] == 'E')) ifrot2 = true;
		else if ((position2 == 2) && (alphabet[M] == 'V')) ifrot2 = true;
		else if ((position2 == 3) && (alphabet[M] == 'J')) ifrot2 = true;
		else if ((position2 == 4) && (alphabet[M] == 'Z')) ifrot2 = true;
	}
	else if ((position == 2) && (alphabet[R]) == 'W')
	{
		if (!ifrot1)M = mod(M + 1);
		if ((position2 == 0) && (alphabet[M] == 'Q')) ifrot2 = true;
		else if ((position2 == 1) && (alphabet[M] == 'E')) ifrot2 = true;
		else if ((position2 == 2) && (alphabet[M] == 'V')) ifrot2 = true;
		else if ((position2 == 3) && (alphabet[M] == 'J')) ifrot2 = true;
		else if ((position2 == 4) && (alphabet[M] == 'Z')) ifrot2 = true;
	}
	else if ((position == 3) && (alphabet[R]) == 'K')
	{
		if (!ifrot1)M = mod(M + 1);
		if ((position2 == 0) && (alphabet[M] == 'Q')) ifrot2 = true;
		else if ((position2 == 1) && (alphabet[M] == 'E')) ifrot2 = true;
		else if ((position2 == 2) && (alphabet[M] == 'V')) ifrot2 = true;
		else if ((position2 == 3) && (alphabet[M] == 'J')) ifrot2 = true;
		else if ((position2 == 4) && (alphabet[M] == 'Z')) ifrot2 = true;
	}
	else if ((position == 4) && (alphabet[R]) == 'A')
	{
		if (!ifrot1)M = mod(M + 1);
		if ((position2 == 0) && (alphabet[M] == 'Q')) ifrot2 = true;
		else if ((position2 == 1) && (alphabet[M] == 'E')) ifrot2 = true;
		else if ((position2 == 2) && (alphabet[M] == 'V')) ifrot2 = true;
		else if ((position2 == 3) && (alphabet[M] == 'J')) ifrot2 = true;
		else if ((position2 == 4) && (alphabet[M] == 'Z')) ifrot2 = true;
	}
}

///Rotacja rotora 2 i 3
void rotate2(int &M, int &L)
{
	int position = orderRotors[orderRotors.size() - 2] - 49;
	if (position == 0)
	{
		if ((alphabet[M]) == 'Q')
		{
			M = mod(M + 1);
			L = mod(L + 1);
		}
	}
	else if (position == 1)
	{
		if ((alphabet[M]) == 'E')
		{
			M = mod(M + 1);
			L = mod(L + 1);
		}
	}
	else if (position == 2)
	{
		if ((alphabet[M]) == 'V')
		{
			M = mod(M + 1);
			L = mod(L + 1);
		}
	}
	else if (position == 3)
	{
		if ((alphabet[M]) == 'J')
		{
			M = mod(M + 1);
			L = mod(L + 1);
		}
	}
	else if (position == 4)
		if ((alphabet[M]) == 'Z')
		{
			{
				M = mod(M + 1);
				L = mod(L + 1);
			}
		}
}

/// Glowny szyfrator
void crypt(void)
{
	///Ustawienie klucza podanego przez uzytkownika
	int L = lp(key[0]);
	int M = lp(key[1]);
	int R = lp(key[2]);
	char a, b, c, f, ref;
	int  d, e, i = 0;

	///Aktywacja lacznicy kablowej (zamiana odpowiednich liter)
	Txt = switchboard(Txt);

	///Glowna petla wykonawcza
	do
	{
		int letter = lp(Txt[i]);

		///Obrot rotora 2 i 3, w przypadku, gdy rotor M znajduje sie na zebie w pozycji poczatkowej
		if (i == 0)
		{
			if ((orderRotors[orderRotors.size() - 2] - 49 == 0) && (alphabet[M] == 'Q'))
			{
				rotate2(M, L);
				ifrot1 = true; /// Zmienna blokujaca dodatkowy drugi obrot rotora M przez rotor R w przypadku zeba w pozycji poczatkowej rotora M
			}
			else if ((orderRotors[orderRotors.size() - 2] - 49 == 1) && (alphabet[M] == 'E'))
			{
				rotate2(M, L);
				ifrot1 = true;
			}
			else if ((orderRotors[orderRotors.size() - 2] - 49 == 2) && (alphabet[M] == 'V'))
			{
				rotate2(M, L);
				ifrot1 = true;
			}
			else if ((orderRotors[orderRotors.size() - 2] - 49 == 3) && (alphabet[M] == 'J'))
			{
				rotate2(M, L);
				ifrot1 = true;
			}
			else if ((orderRotors[orderRotors.size() - 2] - 49 == 4) && (alphabet[M] == 'Z'))
			{
				rotate2(M, L);
				ifrot1 = true;
			}
		}


		/// Obrot rotora R lub w przypadku spelniena warunku - rotora M
		rotate1(R, M);

		/// Przejscie przez rotory
		a = rotors[orderRotors[orderRotors.size() - 1] - 49][mod(R + letter)];
		b = rotors[orderRotors[orderRotors.size() - 2] - 49][mod(M + lp(a) - R)];
		c = rotors[orderRotors[orderRotors.size() - 3] - 49][mod(L + lp(b) - M)];

		/// Reflektor
		ref = reflector[noReflector][mod(lp(c) - L)];

		/// Ponowne przejscie przez rotory (odwrotnie)
		d = mod(pos(rotors[orderRotors[orderRotors.size() - 3] - 49], alphabet[mod(lp(ref) + L)]) - L);
		e = mod(pos(rotors[orderRotors[orderRotors.size() - 2] - 49], alphabet[mod(d + M)]) - M);
		f = alphabet[mod(pos(rotors[orderRotors[orderRotors.size() - 1] - 49], alphabet[mod(e + R)]) - R)];
		output += f;

		///obrot rotora M i L w przypadku spotkania zeba na rotorze M podczas obracania rotora R
		if (ifrot2)
		{
			rotate2(M, L);
			ifrot2 = false;
		}
		ifrot1 = false;
		i++;
	} while (i<Txt.size());

	///Aktywacja lacznicy kablowej (zamiana odpowiednich liter)
	output = switchboard(output);
}

void openfile(string path)
{
	ifstream fin;
	fin.open(path);
	if (fin.good())
	{
		fin >> noReflector;
		fin >> orderRotors;
		fin >> key;
		fin >> sboard1;
		fin >> sboard2;
		noReflector--;
		cout << "Current settings:\n"
			<< orderRotors << " - order of rotors\n"
			<< key << " - encrypting key\n"
			<< noReflector + 1 << " - numer of reflector\n\n";
	}
	else cout << "Error reading file!\n";
}

void start(void)
{
	system("cls");
	cout << "EnigmaSimulator 2018\n\n";
	string path = "settings.txt";
	openfile(path);
	cout << "Enter text to encode: ";
	cin >> Txt;
	for (int i = 0; i < Txt.size(); i++) 
		Txt[i] = toupper(Txt[i]);
	orgTxt = Txt;
}

void export_result(void)
{
	ofstream fout;
	fout.open("result.txt");
	if (fout.good())
	{
		fout << "Current settings:\n"
			 << orderRotors << " - order of rotors\n"
		   	 << key << " - encrypting key\n"
			 << noReflector + 1 << " - numer of reflector\n\n"
			 << "Input: " << orgTxt << endl
			 << "Output: " << output << endl;

		cout << "Encoded text: " << output << endl << endl
			 << "Result written in result.txt\n";
	}
	else cout << "Error writing file!\n";

	fout.close();
}

///TEMP!!!///
void zero(void)
{
	Txt = "";
	orgTxt = "";
	orderRotors = "";
	key = "";
	sboard1 = "";
	sboard2 = "";
	output = "";
	noReflector=0;
	ifrot1 = false;
	ifrot2 = false;
}

int main()
{
	//string Txt, orgTxt, orderRotors, key, sboard1, sboard2, output;
	char z='a';
	do
	{
		zero();
		start();
		crypt();
		export_result();

		cout << "Do you want to leave? [y/n]\n";
		cin.clear();
		z = toupper(_getch());
	} while (z != 'Y');
	return 0;
}
