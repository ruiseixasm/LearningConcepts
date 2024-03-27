#include <iostream>
#include <string>

using namespace std;

int main() {

    {
        // Member Function Algorithms: copy, find, compare

        string s1 = "abcdefg";
        char buf[20];

        size_t len = s1.copy(buf, 3);   // buf: abc     len == 3
        len = s1.copy(buf, 4, 2);       // buf: cdef    len == 4

        //    00        10        20        30        40
        //    012345678901234567890123456789012345678901234
        s1 = "If a job is worth doing, it's woth doing well";   // <-- s1 string

        size_t found = s1.find("doing");        // found == 18
        cout << "found == " << found << endl;
        found = s1.find("doing", 20);           // found == 35
        found = s1.find("doing well", 0);       // found == 35
        found = s1.find("doing well", 0, 5);    // found == 18

        found = s1.find_first_of("doing");          // found == 6
        found = s1.find_first_of("doing", 10);      // found == 13
        cout << "found == " << found << endl;
        found = s1.find_first_of("doing", 10, 1);   // found == 18

        found = s1.find_last_of("doing");           // found == 39
        found = s1.find_first_not_of("doing");      // found == 0
        found = s1.find_last_not_of("doing");       // found == 44

        string s2 = "Some generic string";

        int result = s1.compare(s2);    // (+) if (s1 > s2), (-) if (s1 < s2) and (0) if (s1 == s2)
        cout << "result == " << result << endl;     // result == -10
        if (s1 > s2) {}     // if (s1.compare(s2) > 0)
        result = s1.compare(3, 2, s2);
        cout << "result == " << result << endl;     // result == 897201

        string ss = s1 + s2;
        cout << "ss == " << ss << endl;             // ss == If a job is worth doing, it's woth doing wellSome generic string

    }

    return 0;
}