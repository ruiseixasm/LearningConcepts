#include <iostream>
#include <string>

using namespace std;

int main() {

    {
        // 1. Single Element Access

        string s1 = "Goodbye";
        cout << "s1[2]: " << s1[2] << endl;     // s1[2]: o
        s1[2] = 'x';        // Goxdbye
        cout << "s1: " << s1 << endl;
        s1.at(2) = 'o';     // Goodbye
        cout << "s1: " << s1 << endl;
        // s1.at(20);          // throw an exception of out_of_range
        // s1[20];             // undefined behavior

        s1.front();         // 'G'
        s1.back();          // 'e'
        s1.push_back('z');  // Goodbyez
        cout << "s1: " << s1 << endl;
        s1.pop_back();      // Goodbye
        cout << "s1: " << s1 << endl;
        s1.begin();         // 0 iterator
        s1.end();           // n iterator
        // Like vector, string doesn't have push_front() and pop_front()

        string s3(s1.begin(), s1.begin() + 3);   // s3: Goo
        cout << "s3: " << s3 << endl;

        // 2. Ranged Access
        // assing, append, insert, replace

        string s2 = "Dragon Land";

        s1.assign(s2);          // s1 = s2
        cout << "s1: " << s1 << endl;
        s1.assign(s2, 2, 4);    // s1: agon
        cout << "s1: " << s1 << endl;
        s1.assign("Wisdom");    // s1: Wisdom
        cout << "s1: " << s1 << endl;
        s1.assign("Wisdom", 3); // s1: Wis
        cout << "s1: " << s1 << endl;
        s1.assign(s2, 3);       // s1: gon Land
        cout << "s1: " << s1 << endl;

        s1.assign(3, 'x');
        s1.assign({'a', 'b', 'c'});
        cout << "s1: " << s1 << endl;   // s1: abc

        s1.append(" def");
        cout << "s1: " << s1 << endl;   // s1: abc def
        s1.insert(2, "mountain", 4);
        cout << "s1: " << s1 << endl;   // s1: abmounc def
        s1.replace(2, 5, s2, 3, 3);
        cout << "s1: " << s1 << endl;   // s1: abgon def

        s1.erase(1, 4);
        cout << "s1: " << s1 << endl;   // s1: a def
        s1 = s2.substr(2, 4);
        cout << "s1: " << s1 << endl;   // s1: agon

        s1 = "abc";
        s1.c_str();             // "abc\0"
        s1.data();              // "abc"
        cout << "s1: " << s1 << endl;   // s1: abc

        s1.swap(s2);
        cout << "s1: " << s1 << endl;   // s1: Dragon Land
        cout << "s2: " << s2 << endl;   // s2: abc
    }

    return 0;
}