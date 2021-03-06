#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

#include <iostream>
#include <string>
#include "Date.h"

class Book {
	friend std::ostream& operator<<(std::ostream& out, const Book& targetBook);
	friend std::istream& operator>>(std::istream& in, Book& targetBook);
public:
	Book(std::string title0 = "Undef", int currentId = 0,
		std::string owner0 = "Undef", std::string month = "Undef",
		int day = 0, bool state = false);
	
	// Getter function
	Date getDate() const;
	std::string getTitle() const;
	bool getBorrowed() const;
	int getId() const;

	void changeBorrowed();
	void userInput(int currentId, size_t maxLength = 20);
	void outTable();
	void ownerInput(size_t maxLength = 20);
private:
	std::string title;
	int id;
	std::string owner;
	Date date;
	bool borrowed;
};

#endif