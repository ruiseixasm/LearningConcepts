#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {

    // IO operation:
    // formatting data  -- stream
    // communicating data to external devices  -- stream buffer
    cout << 32;
    streambuf* pbuf = cout.rdbuf();

    ostream myCout(pbuf);
    myCout << 34;   // 34 to stdout

    myCout.setf(ios::showpos);
    myCout.width(20);
    myCout << 12 << endl;   //          +12
    cout << 12 << endl;     //12

    ofstream of("MyLog.txt");
    streambuf* origBuf = cout.rdbuf();  // Backup original cout buffer
    cout.rdbuf(of.rdbuf());
    cout << "Hello" << endl;    // MyLog.txt has "Hello"
    // Redirecting

    cout.rdbuf(origBuf);    // Resets original cout buffer

    cout << "Goodbye" << endl;  // stdout: Goodbye

    // Stream buffer iterator - Version 1
    cout << "Version 1" << endl;  // stdout: Version 1
    istreambuf_iterator<char> i(cin);
    ostreambuf_iterator<char> o(cout);
    while (*i != 'x') {
        *o = *i;
        ++o;
        ++i;
    }
    
    // Stream buffer iterator - Version 2
    cout << "Version 2" << endl;  // stdout: Version 2
    copy(
        istreambuf_iterator<char>(cin),     // first    (begin of cin buffer)
        istreambuf_iterator<char>(),        // last     (end of the stream buffer)
        ostreambuf_iterator<char>(cout)     // result   (begin of cout buffer)
    );

    return 0;
}