#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "headers/Book.h"

using namespace std;

// Constructor
Book::Book(string title0, int currentId, string owner0, string month, int day, bool state) :
	title(title0), id(currentId), owner(owner0),
	date(month, day), borrowed(state) { }

/* Getter function to obtain avaliability */
bool Book::getBorrowed() const
{
	return borrowed;
}

/* Getter function to obtain id */
int Book::getId() const
{
	return id;
}

/* Getter function to obtain date */
Date Book::getDate() const
{
	return date;
}

/* Getter function to obtain title */
string Book::getTitle() const
{
	return title;
}

/* Change the borrowed state */
void Book::changeBorrowed()
{
	borrowed = !borrowed;
}

/* Function for user input of the book.
The information is asked part by part
currentId: ID value of the book that is assigned automatically 
maxLength limits the input length. 20 by default. */
void Book::userInput(int currentId, size_t maxLength)
{
	string answer;

	cout << "\n Specify the title: ";
	getline(cin, title);
	while (title.length() > maxLength || title.empty()) {
		cout << " Title is too long or empty. Max " << maxLength <<" characters. Specify the title: ";
		getline(cin, title);
	}
	
	cout << " Is the book borrowed? (no/yes): ";
	getline(cin, answer);
	while (answer != "no" && answer != "yes") {
		cout << " Is the book borrowed? (no/yes): ";
		getline(cin, answer);
	}

	if (answer == "yes") {
		borrowed = true;

		ownerInput(maxLength);
	}

	id = currentId;
}

/* Function with the interface for the user to
specify the book ownership and return deadline.
maxLength limits the input length. 20 by default. */
void Book::ownerInput(size_t maxLength)
{
	cout << " Enter the owner's name: ";
	getline(cin, owner);
	while (owner.length() > maxLength || owner.empty()) {
		cout << " Name is too long or empty. Max " << maxLength << " characters. Specify the name: ";
		getline(cin, owner);
	}

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

/* Output alliged for the record table */
void Book::outTable()
{
	ostringstream tableOut;

	tableOut << " " << left << setw(43) << title
		<< right << setw(7) << id;

	if (borrowed == true) {
		tableOut << setw(5) << " " << left << setw(38) << owner
			<< right << setw(15) << date;
	}
	else {
		tableOut << setw(5) << " " << left << setw(38) << "Book is avaliable"
			<< right << setw(15) << "N/A";
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
		out << "A;"; // A indicates "Available"
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

	// If the book is available, indicate it
	else if (flag == "A") {
		targetBook.borrowed = false;
	}

	// Flag is incorrect
	else {
		in.setstate(ios_base::failbit);
	}

	return in;
}