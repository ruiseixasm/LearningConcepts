#include <iostream>
#include <fstream>      // std::ifstream

using namespace std;

int main() {
    // Member functions for unformatted IO

    // input
    ifstream inf("MyLog.txt");
    char buf[80];
    inf.get(buf, 80);       // read up to 80 chars and save into buf
    inf.getline(buf, 80);   // read up to 80 chars or until '\n'
    inf.read(buf, 20);      // read 20 chars
    inf.ignore(3);
    inf.peek();
    inf.unget();    // return a char back to the stream
    inf.putback('z');
    inf.get();
    inf.gcount();   // return the number of chars being read by last unformatted read

    // output
    ofstream of("MyLog.txt");
    of.put('c');
    of.write(buf, 6);   // write first 6 chars of buf
    of.flush();

    return 0;
}