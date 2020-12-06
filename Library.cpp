#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "headers/Library.h"

using namespace std;

// Constructor
Library::Library(int curId, int opt) : storage(), idCounter(curId), sortOption(opt) { }

/* Changing sorting option for output */
void Library::setSortOption(int option)
{
	sortOption = option;
}

/* Print the records of the library.
The storage is sorted according to sortOption value */
void Library::printBookRecords()
{
	// Sort the storage vector by availability using partition algorithm 
	if (sortOption == 1) {
		partition(storage.begin(), storage.end(), [](Book element) {
			return element.getBorrowed();
		});
	}

	// Sort by title
	else if (sortOption == 2) {
		sort(storage.begin(), storage.end(), [](Book first, Book second) {
			return first.getId() < second.getId();
		});
	}

	// Sort by ID
	else {
		sort(storage.begin(), storage.end(), [](Book first, Book second) {
			return first.getTitle() < second.getTitle();
		});
	}

	// Print the header
	cout << endl << " " << "Book Title" << setw(40) << "Book ID"
		<< setw(10) << "Owner" << setw(48) << "Return Deadline" << endl;
	// Print borrowed books
	for (auto element : storage) {
		element.outTable();
		cout << endl;
	}
}

/* Add new book to the library storage.
id: Automatically calculated value to be assigned to the book.
maxLength limits the input length. 20 by default. */
void Library::addNewBook(size_t maxLength)
{
	idCounter++; // Increment the book id value for further assignment
	Book newBook;
	newBook.userInput(idCounter, maxLength);

	storage.push_back(newBook); // Book copitd to vector
}

/* Borrow the book and specify the new owner and return deadline.
Returns false if failed.
maxLength limits the input length. 20 by default. */
bool Library::borrowBook(size_t maxLength)
{
	int id;

	cout << " Enter the id of the book: ";
	cin >> id;
	// Clear the buffer 
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	auto it = checkStorage(id);

	if (it == storage.end()) {
		cout << "\n Error: No book found in the library." << endl;
		return false;
	}

	// Check if the book is availalable for borrowing
	else if (it->getBorrowed()) {
		cout << "\n The book is not avaliable. It will be returned on: " << it->getDate() << endl;
		return false;
	}

	// Borrow is successful
	else {
		it->ownerInput(maxLength);
		it->changeBorrowed();
		return true;
	}
}

/* Return the book back to the library storage.
Returns false if failed. */
bool Library::returnBook()
{
	int id;

	cout << " Enter the id of the book: ";
	cin >> id;
	// Clear the buffer 
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	auto it = checkStorage(id);

	if (it == storage.end()) {
		cout << "\n Error: No book found in the library." << endl;
		return false;
	}

	// Check if the book is borrowed
	else if (!it->getBorrowed()) {
		cout << "\n Error: The book is already in the storage." << endl;
		return false;
	}

	// Returning is successful
	else {
		it->changeBorrowed();
		return true;
	}
}

/* Delete a book by the id specified by user.
Returns false if fails. */
bool Library::deleteBook()
{
	int id;

	cout << " Enter the id of the book: ";
	cin >> id;
	// Clear the buffer 
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	auto it = checkStorage(id);

	// Deleting is successful
	if (it != storage.end()) {
		storage.erase(it);
		return true;
	}

	cout << "\n Error: No book found in the library." << endl;
	return false;
}

/* Clear previous records, initialize new storage.
Reset the ID counter of the library. */
void Library::initialize(int max)
{
	int recondNumber;

	cout << "\n Initializing the storage..." << endl;
	cout << " How many books would you like to add (max " << max << "): ";
	while (!(cin >> recondNumber) || recondNumber <= 0 || recondNumber > max) {
		cout << " Error. Please, specify the value in range (0 - " << max << "): ";

		// Clear the input buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// Clear the buffer
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Reset the storage and id counter
	storage.clear();
	idCounter = 0;

	for (int i = 0; i < recondNumber; i++) {
		addNewBook();
	}

	cout << "\n The library was initialized with new storage. " << endl;
}

/* Write the current storage to a file */
void Library::fileSave(string filename)
{
	ofstream outfile;
	outfile.open(filename);

	for (auto element : storage) {
		outfile << element << endl;
	}
}

/* Upload storage from the file */
bool Library::fileUpload(string filename)
{
	ifstream inputfile(filename);
	string buffer;

	if (!inputfile.is_open()) {
		cout << "\n Error: Unable to open file!" << endl;
		return false;
	}

	// Reset the storage and id counter
	storage.clear();
	idCounter = 0;

	// Reading process
	while (getline(inputfile, buffer)) {
		istringstream stringInput(buffer);

		Book newBook;
		// Check if the id already exists in the storage and if the line is correct
		if (stringInput >> newBook && checkStorage(newBook.getId()) == storage.end()) {
			storage.push_back(newBook);
		}

		// Update the idCounter for the current record
		if (idCounter < newBook.getId()) {
			idCounter = newBook.getId();
		}

	}

	return true;
}

/* Function returns an iterator to the object with ID, passed by a parameter. */
vector<Book>::iterator Library::checkStorage(int id)
{
	// Try to find the book with the id passed
	auto it = find_if(storage.begin(), storage.end(), [id](const Book element) {
					return element.getId() == id;
				});

	return it;
}