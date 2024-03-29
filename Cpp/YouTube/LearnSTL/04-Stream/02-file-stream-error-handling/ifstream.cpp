#include <iostream>
#include <fstream>      // std::ifstream

using namespace std;

int main() {

    try {
        ifstream inf("MyLog.txt");  // inf because if is taken as if!
        int i;

        // Read one word
        if (!(inf >> i)) {  // If fails to read one word (!0)

            // Error status: goodbit, badbit, failbit, eofbit
            // Check if an error occurred
            switch(inf.rdstate()) {
                case ios::eofbit:
                    cout << "End of file reached." << endl;
                    break;
                case ios::failbit:
                    cout << "Failed to read integer value." << endl;    // <-- THE OUTPUT
                    break;
                case ios::badbit:
                    cout << "Error reading file." << endl;
                    break;
                case ios::goodbit:
                    // This case should not happen if an error occurred
                    cout << "Unexpected successful read." << endl;
                    break;
                default:
                    // Handle any other error state
                    cout << "Unknown error occurred." << endl;
                    break;
            }

        } else {
            cout << "Read successfully: " << i << endl;
        }

        cout << "good: " << inf.good() << endl; // Everything is OK (goodbit == 1)
        cout << "bad:  " << inf.bad() << endl;  // Non-recoverable error (badbit == 1)
        cout << "fail: " << inf.fail() << endl; // Failed stream operation (failbit == 1, badbit == 1)
        cout << "eof:  " << inf.eof() << endl;  // End of file (eofbit == 1)

        // Handle the errors with exceptions
        // Equivalent to "if (inf.rdstate() & (ios::badbit | ios::failbit) > 0)"
        inf.exceptions(ios::badbit | ios::failbit); // Setting the exception mask
        // When badbit or failbit set to 1, exceptio of ios::failire will be thrown
        // When eofbit set to 1, no exception
        inf.exceptions(ios::goodbit);   // No exception (default)

        inf.clear();    // Clear all the error status   clear(ios::goodbit)
        inf.clear(ios::badbit); // Sets a new value to the error flag

        inf.rdstate();  // Read the current status flag
        inf.clear(inf.rdstate() & ~ios::failbit);   // Clear only the failbit

        if (inf)
            cout << "Read successfully" << endl;

        if (inf >> i)
            cout << "Read successfully" << endl;

    } catch (const ios_base::failure& e) {
        // Exception caught
        cout << "Exception occurred: " << e.what() << endl;
    }

    return 0;
}