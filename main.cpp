#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Date.h"
#include "Book.h"
#include "Library.h"

#define MAINOPTION_MIN 0
#define MAINOPTION_MAX 10
#define SORTOPTION_MIN 1
#define SORTOPTION_MAX 2

using namespace std;

void readOption(int& option, int min, int max);
void printGreet();
void printMenu();
void printSortMenu();

int main()
{
	Library record;
	string file;
	int option = -1; // Define a neutural default value for user option

	printGreet();

	// Main menu loop
	printMenu();
	readOption(option, MAINOPTION_MIN, MAINOPTION_MAX);
	while (option != 0) {
		switch (option)
		{
		case 1: // Initialize new record and clear the current one
			record.initialize();

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 2: // Add new book to library
			record.addNewBook();
			cout << "\n The book was added to the record." << endl;

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 3: // Borrow a book
			if (record.borrowBook()) {
				cout << "\n The book was borrowed." << endl;
			}

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 4: // Return a book
			if (record.returnBook()) {
				cout << "\n The book was returned." << endl;
			}

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 5: // Delete the book from the record
			if (record.deleteBook()) {
				cout << "\n The book was deleted from the record." << endl;
			}

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 7: // Print all the records
			record.printBookRecords();

			cout << "\n Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 9: // Save current records to file
			cout << " \n Enter the file name: ";
			getline(cin, file);

			record.fileSave(file);

			cout << " \n Writing successful." << endl;
			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		case 10: // Upload records from the file
			cout << " \n Enter the file name: ";
			getline(cin, file);

			if (record.fileUpload(file)) {
				cout << " \n Reading successful. You can now work with new record." << endl;
			}
			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;
		/*case 8: // Sort menu option
			printSortMenu();
			readOption(option, SORTOPTION_MIN, SORTOPTION_MAX);
			record.sortBy(option);
			
			cout << " \n Sorted successfully." << endl;

			cout << " Press enter to proceed..";
			cin.ignore(80, '\n');

			break;*/
		}

		printMenu();
		readOption(option, MAINOPTION_MIN, MAINOPTION_MAX);
	}
}

/* Read menu option from the user */
void readOption(int& option, int min, int max) 
{
	cout << " Please, choose an option (" << min << " - " << max << "): ";
	while (!(cin >> option) || option < min || option > max) {
		cout << " Error. Please, specify the value in range (" << min << " - " << max << "): ";

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
	cout << "\n STORAGE MANIPULATIONS: " << endl;
	cout << " 1) Initialize and clear the records" << endl;
	cout << " 2) Add a new book to library" << endl;
	cout << " 3) Borrow a book" << endl;
	cout << " 4) Return a book" << endl;
	cout << " 5) Delete a book from the record" << endl;
	cout << " 6) Extend the deadline for returning" << endl;
	cout << "\n RECORD INTERFACE/OUTPUT: " << endl;
	cout << " 7) Print a report" << endl;
	cout << " 8) Sort by..." << endl;
	cout << "\n SAVE TO/UPLOAD FROM THE FILE: " << endl;
	cout << " 9) Save library records to a file" << endl;
	cout << " 10) Upload records from the file" << endl;
	cout << " 0) Exit\n\n";
}

void printSortMenu()
{
	cout << "\n 1) Sort by ID (oldest to newest)" << endl;
	cout << " 2) Sort by alphabetic order\n" << endl;
}