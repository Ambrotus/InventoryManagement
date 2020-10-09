#ifndef item_H
#define item_H
// Name: Steven Killoran
// Seneca Student ID: 144364189
// Seneca email: skilloran1@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

//An Item object manages a single item on the assembly line.
#include <string>
using namespace std;
//namespace ms {
	class Item {
		string m_name;// – the name of the Item
		string m_description;// – description of the item
		unsigned m_serialNumber;// – the next serial number to be assigned on the assembly line
		unsigned m_quantity;// – the number of current items left in stock
		static size_t m_widthField;// – the maximum characters to be displayed for a field
		//Note : All Item objects share the same m_widthField
	public:
		Item(const string input);// - object receives a reference to an unmodifiable std::string. This string contains a single record (one line) that has been retrieved from the input file specified by the user
		//const std::string& getName() const - returns the name of the current Item object
		const string& getName() const;
		//const unsigned int getSerialNumber() – returns the next serial number to be used on the assembly line and increments m_serialNumber
		const unsigned int getSerialNumber();
		//const unsigned int getQuantity() – returns the remaining quantity of the current Item object
		const unsigned int getQuantity();
		//void updateQuantity() – substracts 1 from the available quantity; should not go below 0.
		void updateQuantity();
		//void display(std::ostream& os, bool full) const -- inserts the content of the current object into first parameter.
		void display(ostream& os, bool full) const;

	};
	
//}
#endif // !item_H
