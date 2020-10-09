// Name: Steven Killoran
// Seneca Student ID: 144364189
// Seneca email: skilloran1@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include<iostream>
#include <iomanip>
#include <string>
#include"Utilities.h"

//Parsing string data from input files is performed the same for all objects within the system. 
//The Utilities type provides the basic functionality required for all objects in the assembly line system.

using namespace std;
char Utilities::m_delimiter = ',';
//namespace ms {
	//Utilities::m_delimiter ='/0'
	//void setFieldWidth(size_t) -- sets the field width of the current object to the value of the parameter
	void Utilities::setFieldWidth(size_t width) {
		m_widthField = width;
	}
	//size_t getFieldWidth() const -- returns the field width of the current object
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}
	//const std::string extractToken(const std::string& str, size_t& next_pos, bool& more) -- extracts tokens from the first parameter 
	const string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		more = false;
		//This function uses the delimiter to extract the next token from str starting at next_pos.
		string token;
		
		token = (str.substr(next_pos, (str.find(m_delimiter, next_pos) - next_pos)));
		auto pos = str.find(m_delimiter);
		if (pos!=string::npos)
			more = true;
		//We think in generalities, but we live in details.
		//If successful, it returns the extracted token found and sets more to true; false otherwise.
		//This function reports an exception if there are two delimiters with no token between them.
		if (token == "") {
			more = false;
			throw "Field Token Is Empty";
		}
		//This function updates the current object's m_widthField data member 
		//if its current value is less than the size of the token extracted.
		//Note: str represents a single line read from an input file
		
		if (m_widthField < token.length()) setFieldWidth(token.length());
		
		
		return token;




	}
	//static void setDelimiter(const char) -- sets the delimiter for this class to the character received
	void Utilities::setDelimiter(const char delim) {
		m_delimiter = delim;
	}
	//const char getDelimiter() const --returns the delimiter character of the current object.
	const char Utilities::getDelimiter() const {
		return m_delimiter;
	}
//}

