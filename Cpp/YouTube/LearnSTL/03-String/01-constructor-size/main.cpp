#include <iostream>
#include <string>

using namespace std;

int main() {

    {    
        // 1. Constructors

        string s1("Hello");
        cout << "s1: " << s1 << endl;   // s1: Hello

        string s2("Hello", 3);
        cout << "s2: " << s2 << endl;   // s2: Hel

        string s3(s1, 2);
        cout << "s3: " << s3 << endl;   // s3: llo

        string s4(s1, 2, 2);
        cout << "s4: " << s4 << endl;   // s4: ll

        string s5(5, 'a');
        cout << "s5: " << s5 << endl;   // s5: aaaaa

        string s6({'a', 'b', 'c'});
        cout << "s6: " << s6 << endl;   // s6: abc

        // 2. Size

        s1 = "Goodbye";
        cout << "Size: " << s1.size() << endl;          // 7
        cout << "Length: " << s1.length() << endl;      // 7
        cout << "Capacity: " << s1.capacity() << endl;  // 15

        s1.reserve(100);
        cout << "Size: " << s1.size() << endl;          // 7
        cout << "Capacity: " << s1.capacity() << endl;  // 100

        s1.reserve(5);
        cout << "Size: " << s1.size() << endl;          // 7
        cout << "Capacity: " << s1.capacity() << endl;  // 100

        s1.shrink_to_fit();
        cout << "Size: " << s1.size() << endl;          // 7
        cout << "Capacity: " << s1.capacity() << endl;  // 15

        s1.resize(9);
        cout << "Size: " << s1.size() << endl;          // 9
        cout << "Capacity: " << s1.capacity() << endl;  // 15

        s1.resize(12, 'x');
        cout << "Size: " << s1.size() << endl;          // 12
        cout << "Capacity: " << s1.capacity() << endl;  // 15

        s1.resize(3);
        cout << "s1: " << s1 << endl;                   // s1: Goo
        cout << "Size: " << s1.size() << endl;          // 3
        cout << "Capacity: " << s1.capacity() << endl;  // 15
    }

    return 0;
}