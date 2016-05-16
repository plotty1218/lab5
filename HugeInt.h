#include <iostream>
#include <string>
#include <iostream>
using namespace std;

class HugeInt{

friend ostream &operator<<(ostream&,HugeInt&);
friend istream &operator>>(istream&,HugeInt&);
public:
	HugeInt();
	HugeInt(int);
	HugeInt(int,int);
	HugeInt(string);
	HugeInt& operator=(const HugeInt&);
	HugeInt operator+(const HugeInt&);
	HugeInt operator-(const HugeInt&);
private:
	int arrsize;
	int *int_arr;
	bool minus;
	string answer;
};
