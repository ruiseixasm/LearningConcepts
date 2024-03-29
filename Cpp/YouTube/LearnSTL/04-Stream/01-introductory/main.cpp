#include <iostream>
#include <fstream>      // std::ifstream
#include <bitset>
#include <complex>

using namespace std;

int main() {
    // C++ Input/Output Library -- Stream
    cout << "Hello" << endl;
    // cout: a global object of ofstream (typedef basic_ofstream<char> ostream)
    // <<: ostream& ostream::operator<< (string v);
    // endl: '\n' + flush

    // What is stream? Serial IO Interface to external devices (file, stdin/stdout, network, etc.)
    string s("Hello");
    s[3] = 't';     // Random access
    //cout[3] = 't';  // Error

    ofstream of("MyLog.txt");   // Creates a new file for white, if the file didn't exist
    of << "Experience is the mother of wisdom" << endl;
    of << 234 << endl;
    of << 2.3 << endl;

    of << bitset<8>(14) << endl;        // 00001110
    of << complex<int>(2, 3) << endl;   // (2, 3)

    // IO Operation
    // Formating the data    <------->    Comunicating the data with external devices

    // Software Engineer Principle: Low Coupling  -> Reusability

    return 0;
}