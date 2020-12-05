#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
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
void Book::userInput(int currentId)
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

	cout << " Enter the deadline for returning (Day Month): ";
	while (!(cin >> date)) {
		// Clear the input buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << " Enter the deadline for returning (Day Month): ";
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

string Book::getTitle() const
{
	return title;
}

/* Output alliged for the record table */
void Book::outTable()
{
	ostringstream tableOut;

	tableOut << " " << left << setw(43) << title
		<< right << setw(7) << id;

	if (borrowed == true) {
		tableOut << setw(5) << " " << left << setw(26) << owner
			<< right << setw(27) << date;
	}
	else {
		tableOut << setw(5) << " " << left << setw(26) << "Book is avaliable"
			<< right << setw(27) << "N/A";
	}

	cout << tableOut.str();
}

/* Overload of << operator.
Used specifically for file writing */
ostream& operator<<(ostream& out, const Book& targetBook)
{
	out << targetBook.id << ";" << targetBook.title << ";";
	
	// Set the appropriate flag for avaliability
	if (targetBook.borrowed == true) {
		out << "B;"; // B indicates "Borrowed"
		out << targetBook.owner << ";" << targetBook.date;
	}
	else {
		out << "A;"; // A indicates "Avaliable"
	}

	return out;
}

/* Overload of >> operator.
Used specifically for file reading*/
istream& operator>>(istream& in, Book& targetBook)
{
	// Read the first part of the input line
	// Make sure reading was successful and ID is specified as a number
	string tempId;
	if (getline(in, tempId, ';') && getline(in, targetBook.title, ';') &&
		!tempId.empty() && tempId.find_first_not_of("0123456789") == std::string::npos) {
		targetBook.id = stoi(tempId);
	}
	else {
		in.setstate(ios_base::failbit);
	}

	string flag = "NA"; // Set buffer for flag to a neutural value
	
	// Check if the correct flag is set in the line
	getline(in, flag, ';');
	
	// If the book is borrowed, check for the correct owner information 
	if (flag == "B") {
		if (getline(in, targetBook.owner, ';') && in >> targetBook.date) {
			targetBook.borrowed = true;
		}
		else {
			in.setstate(ios_base::failbit);
		}
	}

	// If the book is borrowed, indicate it
	else if (flag == "A") {
		targetBook.borrowed = false;
	}

	// Flag is incorrect
	else {
		in.setstate(ios_base::failbit);
	}

	return in;
}