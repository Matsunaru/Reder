#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string filename;

int main() {
    cout << "Podaj nazwe pliku: " << endl;
    cin >> filename;

    ifstream plik(filename);
    if (!plik.is_open())
    {
        cerr << "Nie udalo sie otworzyc pliku!" << endl;
        return 1;
    }
    plik.close();

    return 0;
}