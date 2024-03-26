#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

struct Color {
  int r, g, b;
};

int R = 0b11110000; //240
int G = 0b00111100; //60
int B = 0b00001111; //15

int pixel = R << 16 | G << 8 | B;
void processHeaderAndPixels(ifstream& plik, int& szerokosc, int& wysokosc, int& maksWartoscKoloru, int& uniqueColorsCount, string& results, string& format);

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
    vector<int> pixels;
    int pixelValue;
    stringstream output;
    string results;
    int uniqueColorsCount = 0;


    getline(plik, format);

    if (format == "P1" || format == "P4") { // Format PBM
        while (getline(plik, line)) {
            if (line[0] == '#')
                continue;
            else {
                stringstream ss(line);
                ss >> szerokosc >> wysokosc;
                processHeaderAndPixels(plik, szerokosc, wysokosc, maksWartoscKoloru, uniqueColorsCount, results,format);
            }
        }
    } else if (format == "P2" || format == "P5") { // Format PGM
        for (int i = 0; i < 3; ++i) {
            getline(plik, line);
            if (line[0] == '#') {
                --i;
                continue;
            }
            stringstream ss(line);
            if (i == 0) {
                ss >> szerokosc >> wysokosc;
            } else if (i == 1) {
                ss >> maksWartoscKoloru;
                processHeaderAndPixels(plik, szerokosc, wysokosc, maksWartoscKoloru, uniqueColorsCount, results,format);
            }
        }
    } else if (format == "P3" || format == "P6") { // Format PPM
        for (int i = 0; i < 3; ++i) {
            getline(plik, line);
            if (line[0] == '#') {
                --i;
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
    cout << "ilosc unikalnych kolorow: " << uniqueColorsCount << " kolory" << "\n" << " i jest ich" << "\n" << results << endl;
    if (format == "P2" || format == "P3" || format == "P5" || format == "P6") {
        cout << "Maksymalna wartosc koloru: " << maksWartoscKoloru << endl;
    }

    plik.close(); // close the file

    cout << "Naciśnij Enter, aby zakończyć...";
    cin.ignore();
    cin.get();

    return 0;
}

void processHeaderAndPixels(ifstream& plik, int& szerokosc, int& wysokosc, int& maksWartoscKoloru, int& uniqueColorsCount, string& results,string& format) {
    string line;
    int pixelValue;
    vector<int> pixels;
    for (int i = 0; i<szerokosc*wysokosc; ++i){
        plik >> pixelValue;
        pixels.push_back(pixelValue);
    }
    set<int> uniqueColors;
    map<int, int> counter;
    for (int pixel : pixels)
    {
        uniqueColors.insert(pixel);
        counter[pixel] += 1;
    }
    uniqueColorsCount = uniqueColors.size();
    stringstream output;
    for (const auto& pair : counter)
    {
        output << pair.first << " - " << pair.second << "\n";
    }
    results = output.str();
}