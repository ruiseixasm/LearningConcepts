#include <iostream>
#include <string>
#include <limits>   // for numeric_limits

using namespace std;

int main() {

    {
        // Non-member functions

        //           00        10        20        30        40
        //           012345678901234567890123456789012345678901234
        string s1 = "If a job is worth doing, it's woth doing well";   // <-- s1 string

        cout << s1 << endl;
        cout << "1. Type enter to finish" << endl;
        cin >> s1;
        // Clears the cin state and ignore any remaining input
        //cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "2. Type enter to finish" << endl;
        getline(cin, s1);
        cout << "3. Type ';' to finish" << endl;
        getline(cin, s1, ';');      // delimeter is ';'
        cout << "s1 == " << s1 << endl;

        // Convert a number into a string
        s1 = to_string(8);      // decinal 8
        s1 = to_string(2.3e7);  // 23000000.000000
        s1 = to_string(0xa4);   // hexadecimal 164
        s1 = to_string(034);    // octal 28

        // Convert a string to a number
        s1 = "190";
        int i = stoi(s1);   // i == 190     (stoi - String to Integer)

        s1 = "190 monkeys";
        size_t pos;
        i = stoi(s1, &pos);     // i == 190     pos == 3

        s1 = "a monkey";
        //i = stoi(s1, &pos);   // exception of invalid_argument    (10 decimal base, default)
        i = stoi(s1, &pos, 16); // i == 10      pos == 1            (16 hexadecimal base)
        cout << "i == " << i << endl;
        cout << "pos == " << pos << endl;

        // stol, stod, stof, etc
        // stringstream
        // lexical_cast()
    }

    return 0;
}