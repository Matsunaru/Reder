#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

string getFilenameFromUser();//geting user file name
void processImageFile(const string& filename);//main logic of program
void processHeaderAndPixels(ifstream& plik, int& szerokosc, int& wysokosc, int& maksWartoscKoloru, int& uniqueColorsCount, string& results, string& format);//main calculations
void clearConsole() //clear to don't have to much on screan
{
    cout << "\033[2J\033[1;1H";
}

int main()//main program
 {
    string answer;
    do {
        clearConsole();
        string filename = getFilenameFromUser();
        processImageFile(filename);//passing filename to main logic
        cout << "Do you want to load another file (yes/no): ";
        cin >> answer;
    } while (answer == "yes" || answer == "Yes" || answer == "YES");//checking if loop still should go on, or should end the program
    cout << "End of program. " << endl;
    return 0;
}

string getFilenameFromUser()//filename handler
{
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;
    return filename;
}

void processImageFile(const string& filename)//main logic of the program
{
    ifstream plik(filename);
    if (!plik.is_open())// Attempt to open the file; exit program if unsuccessful
    {
        cerr << "Failed to open the file!" << endl;
        exit(1);
    }
    // Variables for storing image file information and processing results
    string format; // Format of the image file (PBM, PGM, PPM)
    string line;   // Temporary variable for reading lines from the file
    int szerokosc, wysokosc; // Width and height of the image
    int maksWartoscKoloru; // Maximum color value in the image
    vector<int> pixels; // Vector to store pixel values
    int pixelValue; // Temporary variable to hold pixel values
    stringstream output; // String stream for generating output
    string results; // String to store processing results
    int uniqueColorsCount = 0; // Count of unique colors in the image

    getline(plik, format);

    if (format == "P1" || format == "P4") { // Format PBM
        while (getline(plik, line))//loops to read lines from the file
        {
            if (line[0] == '#')//If the line starts with '#' (comment), skip it
                continue;
            else// Process the line using a string stream to extract width and height
            {
                stringstream ss(line);
                ss >> szerokosc >> wysokosc;
                // Call a function to process the header and pixels of the image
                processHeaderAndPixels(plik, szerokosc, wysokosc, maksWartoscKoloru, uniqueColorsCount, results, format);
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
                processHeaderAndPixels(plik, szerokosc, wysokosc, maksWartoscKoloru, uniqueColorsCount, results, format);
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
                processHeaderAndPixels(plik, szerokosc, wysokosc, maksWartoscKoloru, uniqueColorsCount, results, format);
            }
        }
    } else// If the format is not recognized
    {
        cerr << "Unknown file format!" << endl; // Display an error message indicating an unknown file format
        plik.close(); // Close the file before exiting the program and Exit the program with an error code
        exit(1);
    }

    cout << "File format: " << format << endl; // Output the format of the file
    cout << "Image width: " << szerokosc << endl; // Output the width of the image
    cout << "Image height: " << wysokosc << endl; // Output the height of the image
    cout << "Number of unique colors: " << uniqueColorsCount << " colors" << endl; // Output the number of unique colors in the image
    cout << "Color details:" << endl << results << endl; // Output the results, i.e., detailed information about colors and their frequencies
    if (format == "P2" || format == "P3" || format == "P5" || format == "P6")//If the format is P2, P3, P5, or P6, output the maximum color value
    {
        cout << "Maximum color value: " << maksWartoscKoloru << endl;
    }

    plik.close(); // close the file
}

void processHeaderAndPixels(ifstream& plik, int& szerokosc, int& wysokosc, int& maksWartoscKoloru, int& uniqueColorsCount, string& results,string& format)
{// Variables
    string line;// Temporary variable to store each line read from the file
    int pixelValue;// Combined RGB value for each pixel
    vector<int> pixels;// Vector to store all pixel values
    set<int> uniqueColors;// Set to store unique pixel values
    map<int, int> counter;// Map to count occurrences of each pixel value
    stringstream output;// String stream to build the output string
    int temp_r, temp_g, temp_b; //Temporary variable to hold RGB value
    if(format == "P3" || format == "P6")// Process RGB values if the file format
    {
        for (int i = 0; i<szerokosc*wysokosc; ++i)// Loop through each pixel in the image
        {
        plik >> temp_r >> temp_g >> temp_b;// Read RGB values from the file
        pixelValue = (temp_r << 16) | (temp_g << 8) | temp_b;// Combine RGB values into a single pixel value
        pixels.push_back(pixelValue);// Store the pixel value in the pixels vector
        uniqueColors.insert(pixelValue);// Insert the pixel value into the uniqueColors set
        counter[pixelValue] += 1;// Increment the counter for this pixel value
        }
        
        uniqueColorsCount = uniqueColors.size();// Calculate the count of unique colors
        for (const auto& pair : counter)// Iterate through the counter map to build the results string
        {
            int pixelValue = pair.first;// Extract the pixel value
            int r = (pixelValue >> 16) & 0xFF;// Extract individual RGB components from the pixel value
            int g = (pixelValue >> 8) & 0xFF;
            int b = pixelValue & 0xFF;
            output << r << " " << g << " " << b << " - " << pair.second << "\n"; // Append RGB components, count
        }
        results = output.str();// Convert the output stringstream to a string and assign it to the results variable
    }
    else
    {
        for (int i = 0; i<szerokosc*wysokosc; ++i)
        {
            // Read pixel value from the file and store it in the pixels vector
            plik >> pixelValue;
            pixels.push_back(pixelValue);
        }
        for (int pixel : pixels)// Count unique colors and their occurrences
        {
            uniqueColors.insert(pixel);// Insert each pixel value into the uniqueColors set
            counter[pixel] += 1;// Increment the count for the pixel value in the counter map
        }
        uniqueColorsCount = uniqueColors.size();// Calculate the number of unique colors
        for (const auto& pair : counter)// Iterate through the counter map to build the results string
        {
            output << pair.first << " - " << pair.second << "\n";// Append the pixel value, count, and newline character to the output stringstream
        }
        results = output.str();// Convert the output stringstream to a string and assign it to the results variable
    }
}