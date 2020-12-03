#pragma once

#include <iostream>
#include <string>

class Date {
	friend std::ostream& operator<<(std::ostream& out, const Date& targetDate);
	friend std::istream& operator>>(std::istream& in, Date& targetDate);
public:
	Date(std::string month0 = "Undef", int day0 = 0);
	void extend();
private:
	std::string month;
	int day;
};