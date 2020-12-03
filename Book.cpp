#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"

using namespace std;

/* Book implementation */
// Constructor
Book::Book(string title0, int currentId, string owner0, string month, int day, bool state) :
	title(title0), id(currentId), owner(owner0),
	date(month, day), borrowed(state) { }

/* Function for user input of the book.
The information is asked part by part, therefore it is decided to use
the separate function instead of overloading >> operator
currentId: ID value of the book that is assigned automatically */
void Book::input(int currentId)
{
	string answer;

	cout << "\n Specify the title: ";
	getline(cin, title);

	cout << " Is the book borrowed? (no/yes): ";
	getline(cin, answer);
	while (answer != "no" && answer != "yes") {
		cout << " Is the book borrowed? (no/yes): ";
		getline(cin, answer);
	}

	if (answer == "yes") {
		borrowed = true;

		ownerInput();
	}

	id = currentId;
}

/* Getter to return avaliability */
bool Book::getBorrowed() const
{
	return borrowed;
}

/* Getter to return id */
int Book::getId() const
{
	return id;
}

/* Function with the interface for the user to
specify the book ownership and return deadline */
void Book::ownerInput()
{
	cout << " Enter the owner's name: ";
	getline(cin, owner);

	cout << " Enter the deadline for returning (Day:Month): ";
	while (!(cin >> date)) {
		// Clear the input buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << " Enter the deadline for returning (Day:Month): ";
	}

	cin.clear(); 
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/* Getter function to return date */
Date Book::getDate() const
{
	return date;
}

void Book::setBorrowed()
{
	borrowed = !borrowed;
}

/* Overload of << operator, mainly for printing the main book
infrormation in the table of records. */
std::ostream& operator<<(std::ostream& out, const Book& targetBook)
{
	out << " " << left << setw(33) << targetBook.title
		<< right << setw(7) << targetBook.id;

	if (targetBook.borrowed == true) {
		out << setw(5) << " " << left << setw(27) << targetBook.owner
			<< right << setw(15) << targetBook.date;
	}
	else {
		out << setw(5) << " " << left << setw(27) << "Book is avaliable"
			<< right << setw(18) << "N/A";
	}

	return out;
}