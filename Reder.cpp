#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string filename;

    cout << "Podaj nazwe pliku: " << endl;
    cin >> filename;

    ifstream plik(filename);
    if (!plik.is_open()) {
        cerr << "Nie udalo sie otworzyc pliku!" << endl;
        return 1;
    }

    string format;
    string line;
    int szerokosc, wysokosc;
    int maksWartoscKoloru;

    getline(plik, format);

    if (format == "P1" || format == "P4") { // Format PBM
        while (getline(plik, line)) {
            if (line[0] == '#')
                continue;
            else {
                stringstream ss(line);
                ss >> szerokosc >> wysokosc;
                break; // brake the loop after
            }
        }
    } else if (format == "P2" || format == "P5") { // Format PGM
        for (int i = 0; i < 3; ++i) {
            getline(plik, line);
            if (line[0] == '#') {
                continue;
            }
            stringstream ss(line);
            if (i == 0) {
                ss >> szerokosc >> wysokosc;
            } else if (i == 1) {
                ss >> maksWartoscKoloru;
            }
        }
    } else if (format == "P3" || format == "P6") { // Format PPM
        for (int i = 0; i < 3; ++i) {
            getline(plik, line);
            if (line[0] == '#') {
                continue;
            }
            stringstream ss(line);
            if (i == 0) {
                ss >> szerokosc >> wysokosc;
            } else if (i == 1) {
                ss >> maksWartoscKoloru;
            }
        }
    } else {
        cerr << "Nieznany format pliku!" << endl;
        plik.close(); // Close the file before exiting the program if this occurs
        return 1;
    }

    cout << "Format pliku: " << format << endl;
    cout << "Szerokosc obrazu: " << szerokosc << endl;
    cout << "Wysokosc obrazu: " << wysokosc << endl;
    if (format == "P2" || format == "P3" || format == "P5" || format == "P6") {
        cout << "Maksymalna wartosc koloru: " << maksWartoscKoloru << endl;
    }

    plik.close(); // close the file

    return 0;
}
