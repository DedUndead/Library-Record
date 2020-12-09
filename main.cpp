#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "headers/Date.h"
#include "headers/Book.h"
#include "headers/Library.h"

#define MAINOPTION_MIN 0 // Menu min option value
#define MAINOPTION_MAX 10 // Menu max option value /  max  initializing value
#define SORTOPTION_MIN 1 // Sort menu min option value
#define SORTOPTION_MAX 3  // Sort menu max option value
#define MAXLENGTH 35 // Maximum string input length

using namespace std;

void readOption(int& option, int min, int max);
void printGreet();
void printMenu();
void printSortMenu();
void pressEnter();
// void readAnswer(string& answer); // Safer way to read user answers if needed

int main()
{
	Library record;
	string file;
	string answer;
	int option;

	printGreet();

	// Ask if the user wants to upload any file in the beggining
	cout << "\n Would you like to upload any file (yes): ";
	// void readAnswer(string& answer);
	getline(cin, answer); // Simple getline is used in order to seedup the process. If the input is incorrect, proceed to main menu.
	if (answer == "yes") {
		cout << "\n Enter the name of the file: ";
		getline(cin, file);

		// Check if the file reading was successful
		if (record.fileUpload(file)) {
			cout << "\n File opened successfully. You can now work with the record." << endl;
		}
	}

	// Main menu loop
	printMenu();
	readOption(option, MAINOPTION_MIN, MAINOPTION_MAX);
	while (option != 0) {
		switch (option)
		{
		case 1: // Initialize new record and clear the current one
			record.initialize(MAINOPTION_MAX, MAXLENGTH);

			pressEnter();

			break;
		case 2: // Add new book to library
			record.addNewBook(MAXLENGTH);
			cout << "\n The book was added to the record." << endl;

			pressEnter();

			break;
		case 3: // Borrow a book
			if (record.borrowBook(MAXLENGTH)) {
				cout << "\n The book was borrowed." << endl;
			}

			pressEnter();

			break;
		case 4: // Return a book
			if (record.returnBook()) {
				cout << "\n The book was returned." << endl;
			}

			pressEnter();

			break;
		case 5: // Delete the book from the record
			if (record.deleteBook()) {
				cout << "\n The book was deleted from the record." << endl;
			}

			pressEnter();

			break;
		case 6: // Print all the records
			record.printBookRecords();

			pressEnter();

			break;
		case 7: // Sort menu option
			printSortMenu();
			readOption(option, SORTOPTION_MIN, SORTOPTION_MAX);
			record.setSortOption(option);

			cout << " \n Sort option changed successfully." << endl;
			pressEnter();

			break;
		case 8: // Save current records to file
			cout << " \n Enter the file name: ";
			getline(cin, file);

			if (!file.empty()) {
				record.fileSave(file);
				cout << " \n Writing successful." << endl;
			}
			else {
				cout << " \n Error: File name not specified." << endl;
			}
			pressEnter();

			break;
		case 9: // Upload records from the file
			cout << " \n Enter the file name: ";
			getline(cin, file);

			if (record.fileUpload(file)) {
				cout << " \n Reading successful. You can now work with new record." << endl;
			}
			pressEnter();

			break;
		}

		printMenu();
		readOption(option, MAINOPTION_MIN, MAINOPTION_MAX);
	}

	// Ask if the user wants to save record to file at the end
	cout << "\n Would you like to save the record to file (yes): ";
	// void readAnswer(string& answer);
	getline(cin, answer); // Simple getline is used in order to seedup the process. If the input is incorrect, proceed to exit.
	if (answer == "yes") {
		cout << "\n Enter the name of the file: ";

		getline(cin, file);
		if (!file.empty()) {
			record.fileUpload(file);
			cout << "\n File saved successfully." << endl;
		}
		else {
			cout << " \n Error: File name not specified." << endl;
		}
	}

	cout << "\n Terminating program..." << endl;

	return 0;
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
	cout << " 5) Delete a book" << endl;
	cout << "\n RECORD INTERFACE/OUTPUT: " << endl;
	cout << " 6) Print a report" << endl;
	cout << " 7) Change output sort option" << endl;
	cout << "\n SAVE TO/UPLOAD FROM THE FILE: " << endl;
	cout << " 8) Save library records to a file" << endl;
	cout << " 9) Upload records from the file" << endl;
	cout << " 0) Exit\n\n";
}

/* Print sort options with description */
void printSortMenu()
{
	cout << "\n 1) Sort by availablity" << endl;
	cout << " 2) Sort by ID (oldest to newest)" << endl;
	cout << " 3) Sort by alphabetic order\n" << endl;
}

/* Wait for user to press enter */
void pressEnter()
{
	cout << "\n Press enter to proceed..";
	cin.ignore(80, '\n');
}

/* Safer way to read user answers if needed
void readAnswer(string& answer)
{
	getline(cin, answer);
	while (answer != "no" && answer != "yes") {
		cout << " Is the book borrowed? (no/yes): ";
		getline(cin, answer);
	}
}*/