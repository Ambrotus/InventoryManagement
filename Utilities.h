#ifndef utilities_H
#define utilities_H
// Name: Steven Killoran
// Seneca Student ID: 144364189
// Seneca email: skilloran1@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

//Parsing string data from input files is performed the same for all objects within the system. 
//The Utilities type provides the basic functionality required for all objects in the assembly line system.

#include <string>
using namespace std;
//namespace ms {
	class Utilities {
		//m_widthField -- specifying the length of the token extracted; used for display purpose later; default value is 1.
		size_t m_widthField=0;
		//m_delimiter -- separates the tokens from a given std::string.All Utilities objects share the same delimiter.
		static char m_delimiter;
	public:
		//void setFieldWidth(size_t) -- sets the field width of the current object to the value of the parameter
		void setFieldWidth(size_t);
		//size_t getFieldWidth() const -- returns the field width of the current object
		size_t getFieldWidth() const;
		//const std::string extractToken(const std::string& str, size_t& next_pos, bool& more) -- extracts tokens from the first parameter 
		const string extractToken(const string& str, size_t& next_pos, bool& more);
		//static void setDelimiter(const char) -- sets the delimiter for this class to the character received
		static void setDelimiter(const char);
		//const char getDelimiter() const --returns the delimiter character of the current object.
		const char getDelimiter() const;
	};
	
//}

#endif // !utilities_H




