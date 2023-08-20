// C++ Program to Demonstrate
// Operator Overloading
#include <iostream>
#include <string>
#include <list>
#include "LibraryDeclarations.h"

class Complex {
private:
	int real, imag;

public:
	Complex(int r = 0, int i = 0)
	{
		real = r;
		imag = i;
	}

	// This is automatically called when '+' is used with
	// between two Complex objects
	Complex operator+(Complex const& obj)
	{
		Complex res;
		res.real = real + obj.real;
		res.imag = imag + obj.imag;
		return res;
	}
	void print() { std::cout << real << " + i" << imag << '\n'; }
};

void ComplexOperatorOverloading()
{
	Complex c1(10, 5), c2(2, 4);
	Complex c3 = c1 + c2;
	c3.print();
}

struct YouTubeChannel {
	std::string Name;
	int SubscriberCount;
	mutable int debugValue = 0; // marked as mutable allows to be changed inside const methods

	YouTubeChannel(std::string name, int subscribersCount) {
		Name = name;
		SubscriberCount = subscribersCount;
	}
	bool operator==(const YouTubeChannel& channel) const {
		debugValue++; // marked as mutable
		return this->Name == channel.Name;
	}
};

std::ostream& operator<<(std::ostream& COUT, YouTubeChannel& ytChannel) {
	COUT << "Name: " << ytChannel.Name << std::endl;
	COUT << "Subscribers: " << ytChannel.SubscriberCount << std::endl;
	return COUT;
}

struct MyCollection {
	std::list<YouTubeChannel> myChannels;

	void operator+=(YouTubeChannel& channel) {
		this->myChannels.push_back(channel);
	}
	void operator-=(const YouTubeChannel& channel) {
		this->myChannels.remove(channel); // right click on it and click "Go To Definition" (F12)
		// Requires == overloading too (see YouTubeChannel class)
		// 
		//auto remove(const _Ty & _Val) { // erase each element matching _Val
		//	return remove_if([&](const _Ty& _Other) { return _Other == _Val; }); // LAMBDA FUNCION
		//}
	}
};

std::ostream& operator<<(std::ostream& COUT, MyCollection& myCollection) {
	for (YouTubeChannel ytChannel : myCollection.myChannels)
		COUT << ytChannel << std::endl;
	return COUT;
}

void YouTubeOperatorOverloaded() {
	YouTubeChannel yt1 = YouTubeChannel("CodeBeauty", 75000);
	YouTubeChannel yt2 = YouTubeChannel("My second channel", 80000);

	MyCollection myCollection;
	myCollection += yt1;
	myCollection += yt2;
	myCollection -= yt2;
	std::cout << myCollection;

	std::cout << yt1 << yt2;
}