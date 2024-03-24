#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string filename;

    cout << "Podaj nazwe pliku: " << endl;
    cin >> filename;

    ifstream plik(filename);
    if (!plik.is_open())
    {
        cerr << "Nie udalo sie otworzyc pliku!" << endl;
        return 1;
    }

    string format;
	std::string comment;
	int szerokosc, wysokosc;
	int pixelValue;
    int maksWartoscKoloru;

	getline(plik, format);

    if (format == "P1" || format == "P4") { // Format PBM
        getline(plik, comment);
        plik >> szerokosc >> wysokosc;
    } else if (format == "P2" || format == "P5") { // Format PGM
        getline(plik, comment);
        plik >> szerokosc >> wysokosc >> maksWartoscKoloru;
    } else if (format == "P3" || format == "P6") { // Format PPM
        getline(plik, comment);
        plik >> szerokosc >> wysokosc >> maksWartoscKoloru;
    } else {
        cerr << "Nieznany format pliku!" << endl;
        plik.close(); // Close the file before exiting the program in case of an error
        return 1;
    }
    cout << "Format pliku: " << format << endl;
    cout << "Szerokosc obrazu: " << szerokosc << endl;
    cout << "Wysokosc obrazu: " << wysokosc << endl;
    if (format == "P2" || format == "P3" || format == "P5" || format == "P6") {
        cout << "Maksymalna wartosc koloru: " << maksWartoscKoloru << endl;
    }

    plik.close(); // close file

    return 0;
}