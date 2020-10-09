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
#include"Item.h"
using namespace std;
size_t Item::m_widthField = 0;
//namespace ms {
	// - object receives a reference to an unmodifiable std::string. This string contains a single record (one line) that has been retrieved from the input file specified by the user
	Item::Item(const string input) {
		//the constructor uses an Utilities object (created local in the function) to extract each token from the record and populates the Item object accordingly.
		Utilities tu; //tempUtility;
		bool tb; //tempBool
		size_t pos = 0; //start_pos
						
		string array[3];
		for (string& x : array) {
			x = tu.extractToken(input, pos, tb);
			pos += (x.length() + 1);
		}
		m_name = array[0];
		m_serialNumber = stoul(array[1]);
		m_quantity = stoul(array[2]);
		m_description = input.substr(pos);
			
		Item::m_widthField = (m_name.length()<tu.getFieldWidth()) ? tu.getFieldWidth() : m_name.length();
		
		//NAME|SRL|QTY|DESCRIPTION
		
	}
	//const std::string& getName() const - returns the name of the current Item object
	const string& Item::getName() const {
		return m_name;
	}
	//const unsigned int getSerialNumber() – returns the next serial number to be used on the assembly line and increments m_serialNumber
	const unsigned int Item::getSerialNumber() {
		// returns the next serial number to be used on the assembly line and increments m_serialNumber
		return m_serialNumber++;
	}
	//const unsigned int getQuantity() – returns the remaining quantity of the current Item object
	const unsigned int Item::getQuantity() {
		return m_quantity;
	}
	//void updateQuantity() – substracts 1 from the available quantity; should not go below 0.
	void Item::updateQuantity() {
		if (m_quantity >0) m_quantity -= 1;
		//not sure if we need to throw anything or just do nothing.
		else  throw "Not enough in stock";
	}
	//void display(std::ostream& os, bool full) const -- inserts the content of the current object into first parameter.
	void Item::display(ostream& os, bool full) const {
		////inserts the content of the current object into first parameter.
		////if the second parameter is false, 
		////this function inserts only the name and serial number in the format : NAME[######]
		//*	=======================
		//	= Inventory (summary) =
		//	=======================
		//	CPU			  [123456]
		//	Memory		  [654321]
		//	GPU			  [056789]
		//	SSD			  [987654]
		//	Power Supply  [147852]*/
		//	1234567890123456789012
		////				  15	6
		//
		os << setw(m_widthField) << left << m_name << " [" << setw(6) << setfill('0') << right << m_serialNumber << "]" << std::setfill(' ');

		//if the second parameter if true, 
		//this function uses the following format : 
		//NAME[######] Quantity : QTY Description : DESCRIPTION
		//the NAME and QTY fields will use m_widthField characters, 
		//serial number field will use 6 characters; 
		//the DESCRIPTION has no formatting options
		
		//Power Supply [147852] Quantity: 20           Description: Basic AC Power Supply
		if(full) os << " Quantity: " << setw(m_widthField) << left << m_quantity << " Description: " << m_description;
			
		//this function will terminate the printed message with an endline
		os << endl;

	}
//}