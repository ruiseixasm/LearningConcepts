#include <iostream>
#include <fstream>      // std::ofstream
#include <bitset>
#include <complex>

using namespace std;

int main() {

    {
        ofstream of("MyLog.txt");   // Creates a new file for write, if the file didn't exist
        of << "Experience is the mother of wisdom" << endl;
        of << 234 << endl;
        of << 2.3 << endl;

        of << bitset<8>(14) << endl;        // 00001110
        of << complex<int>(2, 3) << endl;   // (2, 3)
    }   // RAII

    {
        //ofstream of("MyLog.txt");           // Open file for write, clear the content of the file
        ofstream of("MyLog.txt", ofstream::app);    // Move the output pointer to the end of the file
        of << "Honesty is the best policy." << endl;
    }

    {                           //         Write          Read
        ofstream of("MyLog.txt", ofstream::in | ofstream::out); // Write in the middle of the file
        of.seekp(10, ios::beg);     // Move the output pointer 10 chars after begin
        of << "12345";      // Overite 5 chars
        of.seekp(-5, ios::end);     // Move the output pointer 5 chars before end
        of << "Nothing ventured, nothing gained." << endl;
        of.seekp(-5, ios::cur);     // Move the output pointer 5 chars before current position
        of << "Current!" << endl;
    }

    return 0;
}