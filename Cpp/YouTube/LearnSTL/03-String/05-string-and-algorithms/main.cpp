#include <iostream>
#include <string>
#include <algorithm>   // for count

using namespace std;

void printStringIterator(std::string::iterator &itr, std::string &vec)
{
    // ALWAYS CHECK FOR UNDEFINED BEHAVIOR !!!
    if (itr != vec.end())
    {
        cout << "itr = " << *itr << endl;       // 33 (undefined behavior!!)
    }
    else
    {
        cout << "No such char found." << endl;  // Output if no such char exists
    }
}

int main() {

    {
        // String and Algorithms
        // <string>

        //           00        10        20        30        40
        //           012345678901234567890123456789012345678901234
        string s1 = "Variety is the spice of life.";    // <-- s1 string

        int num = count(s1.begin(), s1.end(), 'e');
        cout << "num == " << num << endl;               // 4
        num = count_if(s1.begin(), s1.end(), [](char c){return c <= 'e' && c >= 'a';});
        cout << "num == " << num << endl;               // 6

        s1 = "Goodness is something very good.";
        string::iterator itr = search_n(s1.begin(), s1.begin() + 20, 2, 's');
        printStringIterator(itr, s1);                   // itr = s
        s1.erase(itr, itr + 5);
        cout << "s1 == " << s1 << endl;                 // s1 == Goodne something very good.
        s1.insert(itr, 3, 'x');
        cout << "s1 == " << s1 << endl;                 // s1 == Goodnexxx something very good.
        s1.replace(itr, itr + 3, 3, 'y');   // Replacing substring
        cout << "s1 == " << s1 << endl;                 // s1 == Goodneyyy something very good.

        string s2 = "Some generic string!";

        bool s2_permutation = is_permutation(s1.begin(), s1.end(), s2.begin());
        cout << "s2_permutation == " << s2_permutation << endl; // s2_permutation == 0
        replace(s1.begin(), s1.end(), 'e', ' ');        // Replacing characters
        transform(s1.begin(), s1.end(), s2.begin(),
                [](char c) {
                    if (c < 'n')
                        return 'a';
                    else
                        return 'z';
                });
        cout << "s2 == " << s2 << endl;                 // s2 == azzazazzzazzaazaazaa

        s1 = "abcdefg";
        rotate(s1.begin(), s1.begin() + 3, s1.end());
        cout << "s1 == " << s1 << endl;                 // s1 == defgabc

        // Types of strings
        string s;       // typical string
        u16string s16;  // string char16_t of 16 characters
        u32string s32;  // string char32_t of 32 characters
        wstring sw;     // string wchar_t (wide character)
        sw = to_wstring(129);   // specific to wstring
        wcout << L"sw == " << sw << endl;                // sw == 129
    }

    return 0;
}