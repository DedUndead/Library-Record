#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include <string>
#include <vector>
#include "Book.h"

/* Library class provides function to work with its storage.
ID function holds the value of the last book in the storage and
updated automatically when the new book is added.
Deleted books do not decrement the counter 
sortOption is used for the output sorting:
1 - Default, avaliablity 
2 - ID
3 - title */
class Library {
public:
	Library(int curId = 0, int opt = 1);
	void setSortOption(int option);
	void printBookRecords();
	void addNewBook(size_t maxLength = 20);
	void initialize(int max, size_t maxLength = 20);
	bool borrowBook(size_t maxLength = 20);
	bool returnBook();
	bool deleteBook();
	void fileSave(const std::string& filename);
	bool fileUpload(const std::string& filename);
private:
	std::vector<Book>::iterator checkStorage(int id);
	std::vector<Book> storage;
	int idCounter;
	int sortOption;
};

#endif