#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Date.h"
#include "Book.h"

using namespace std;

/* Library class provides function to work with its storage. 
ID function holds the value of the last book in the storage and 
updated automatically when the new book is added. 
Deleted books do not decrement the counter */
class Library {
public:
	Library(int curId = 0);
	void addNewBook();
	void printBookRecords();
	void initialize();
	bool borrowBook(); 
	bool returnBook(); 
private:
	vector<Book>::iterator checkStorage(bool& result, bool flag);
	vector<Book> storage;
	int idCounter;
};

void readOption(int& option);
void printGreet();
void printMenu();

int main()
{
	Library record;
	int option = -1; // Define a neutural default value for user option

	printGreet();

	// Main menu loop
	printMenu();
	readOption(option);
	while (option != 0) {
		switch (option)
		{
		case 1: // Initialize new record and clear the current one
			record.initialize();

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 4: // Add new book to library
			record.addNewBook();
			cout << "\n The book was added to the record." << endl;

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 5: // Borrow a book
			if (record.borrowBook()) {
				cout << "\n The book was borrowed." << endl;
			}

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 6: // Return a book
			if (record.returnBook()) {
				cout << "\n The book was returned." << endl;
			}

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 7: // Print all the records
			record.printBookRecords();

			cout << "\n Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		}

		printMenu();
		readOption(option);
	}
}

/* Read menu option from the user */
void readOption(int& option) 
{
	cout << " Please, choose an option (0 - 10): ";
	while (!(cin >> option) || option < 0 || option > 10) {
		cout << " Error. Please, specify the value in range (0 - 10): ";

		// Clear the input buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	// Clear the '\n' tailer after option selection
	// to avoid skipping the getline function later
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/* Print initial greetings */
void printGreet() 
{
	cout << "\n ================================================\n";
	cout << "\n Library Records v1.0 by Pavel Arefyev (paulbekk)\n";
	cout << "\n ================================================\n";
}

/* Print menu with the option description */
void printMenu() 
{
	cout << "\n 1) Initialize and clear the records" << endl;
	cout << " 2) Save library records" << endl;
	cout << " 3) Read records from the file" << endl;
	cout << " 4) Add a new book to library" << endl;
	cout << " 5) Borrow a book" << endl;
	cout << " 6) Return a book" << endl;
	cout << " 7) Print a report" << endl;
	cout << " 8) Sort by..." << endl;
	cout << " 9) Delete the book from the record" << endl;
	cout << " 10) Extend the deadline for returning" << endl;
	cout << " 0) Exit\n\n";
}

/* Library implementation */
// Constructor
Library::Library(int curId) : storage(), idCounter(curId) { }

/* Print the records of the library.
The storage is sorted so that avaliable books come last 
Partitions are sorted in the way user specified earlier */
void Library::printBookRecords() 
{
	// Sort the storage vector by avaliablity using partition algorithm
	partition(storage.begin(), storage.end(), [](Book element) {
			return element.getBorrowed();
		});

	// Print the header
	cout << endl << " " << "Book Title" << setw(30) << "Book ID" 
		<< setw(10) << "Owner" << setw(40) << "Return Deadline" << endl;
	// Print borrowed books
	for (auto element : storage) {
		cout << element << endl;
	}
}

/* Add new book to the library storage.
id: Automatically calculated value to be assigned to the book. */
void Library::addNewBook()
{
	idCounter++; // Increment the book id value for further assignment
	Book newBook;
	newBook.input(idCounter);

	storage.push_back(newBook); // Book copitd to vector
}

/* Borrow the book and specify the new owner and return deadline.
Returns false if failed. */
bool Library::borrowBook()
{
	bool result = true; // Bool to see the succeff of checkStorage private function
	bool toBorrow = true; // Flag indicates if the book is to be borrowed
	auto it = checkStorage(result, toBorrow);

	if (result) {
		it->ownerInput();
		it->setBorrowed();
	}
	
	return result;
}

/* Return the book back to the library storage. 
Returns false if failed. */
bool Library::returnBook()
{
	bool result = true; // Bool to see the succeff of checkStorage private function
	bool toBorrow = false; // Flag indicates if the book is to be borrowed
	auto it = checkStorage(result, toBorrow);

	if (result) {
		it->setBorrowed();
	}
	
	return result;
}

/* Clear previous records, initialize new storage. 
Reset the ID counter of the library. */
void Library::initialize()
{
	int recondNumber;
	
	cout << " Initializing the storage..." << endl;
	cout << " How many books would you like to add (max 10): ";
	cin >> recondNumber;

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

/* Function returns an iterator to the object with ID, specified by user.
* Flag is used to determine either the storage is checking avaliable or borrowed
* books. Result identifies either the element was found or not */
vector<Book>::iterator Library::checkStorage(bool& result, bool flag) 
{
	int id;
	
	cout << " Enter the id of the book: ";
	cin >> id;
	cin.clear(); // Clean the buffer
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// Try to find the book with the id passed
	auto it = find_if(storage.begin(), storage.end(), [id](const Book element) {
		return element.getId() == id;
		});

	// Check if book is in the storage
	if (it == storage.end()) {
		cout << " Error: No book found in the library." << endl;
		result = false;
	}

	// Check if the book is avaliable for borrowing
	else if (it->getBorrowed() && flag == true) {
		cout << " The book is not avaliable. It will be returned on: " << it->getDate() << endl;
		result = false;
	}

	// Check if the book is avaliable for returning
	else if (!it->getBorrowed() && flag == false) {
		cout << " Error: The book is already in the storage." << endl;
		result = false;
	}

	return it;
}