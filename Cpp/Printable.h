#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <string>
#include <iostream>

class Printable {
public:
	const std::string& toString() {
		std::string text = "text";
		return text;
	}
};


#endif /* PRINTABLE_H */