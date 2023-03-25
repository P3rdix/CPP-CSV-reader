# C++ CSV Reader

### Summary:
* This is a project to implement a csv reader in C++
* As of this moment, it simply aims to create a class Frame which is a container for data read from a .csv file.
* This readme documents the files in the project and their functionalities
* This project was made on linux, and while I'm fairly sure it should work just fine on a Mac or Windows system, further testing is required



### Frame.hpp :

#### Classes:

* Frame

##### Frame:

##### constructors:

1. Complete:
* Frame (string) : Constructor taking simple filename, and returns a Frame with the required dataframe or throws the FileNotFoundError if the file isn't present

2. Incomplete:
* Frame(Frame, string[]) : Constructor takes a Frame as well as a list of columns and creates a new Frame using this 

##### Attributes:

* Dimensions: 2D array containing the number of columns and rows
* Names: Array of strings containing list of names of columns
* Columns: A pointer to a series of column class objects which each holds the name as well as the data of the column

##### Member functions:
1. Complete:

2. Incomplete:
* Append(Frame): appends a frame to the current one
* At(String, int): Returns the value at said position
* iAt(int,int): Returns the value at given position
* getCols(String[]): returns a new Frame containing  



