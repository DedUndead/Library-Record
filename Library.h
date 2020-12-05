#pragma once

#include <string>
#include <vector>
#include "Book.h"

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
	void sortBy(int option);
	bool borrowBook();
	bool returnBook();
	bool deleteBook();
	void fileSave(std::string filename);
	bool fileUpload(std::string filename);
private:
	std::vector<Book>::iterator checkStorage(int id);
	std::vector<Book> storage;
	int idCounter;
};