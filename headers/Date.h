#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#include <iostream>
#include <string>

class Date {
	friend std::ostream& operator<<(std::ostream& out, const Date& targetDate);
	friend std::istream& operator>>(std::istream& in, Date& targetDate);
public:
	Date(std::string month0 = "Undef", int day0 = 0);
private:
	std::string month;
	int day;
};

#endif