# Library Records
Metropolia University of Applied Sciences, C++ Programming in IoT devices project by Pavel Arefyev.

## Concept
The program provides functionality to create library records, including the titles, avaliability, current owner's names and return deadlines.
User interact with the program using a simple menu. The details of interaction may be found in UserMannual.pdf.

## File handling
User is able to save and open previously saved files through the program's intefrace. However, if necessary, user may create a file for further reading himself.
Each line of the file should be in the following format:

> ID;Title;FLAG;owner;Day Month

FLAG indicates book's avaliability: A - avaliable, B - borrowed.
Examples of correct files:

> 2131;The Lord of The Rings;A;

> 22;Harry Potter and the Goblet of Fire;B;John Brown;31 January

Note, that the record will take the highest ID counter mentioned in the file, that will be further used for assignments. 

