// Name: Steven Killoran
// Seneca Student ID: 144364189
// Seneca email: skilloran1@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include <vector>
#include "CustomerOrder.h"
#include "Utilities.h"
using namespace std;

size_t CustomerOrder::m_widthField = 1;
CustomerOrder::CustomerOrder():m_name(""), m_product(""), m_cntItem(0){}

CustomerOrder::CustomerOrder(string input) {
	/*a custom constructor that takes as a parameter a reference to a string containing a single record from the input file.
	This constructor uses an Utilities object to extract the tokens and populate the current instance.
	After the extraction is finished, will update CustomerOrder::m_widthField 
	if the value stored there is smaller than the value stored in Utilities::m_widthField.
		fields in the record are(separated by a delimiter) :
		Customer Name
		Order Name
		the list of items making up the order(at least one item)*/
	//Elliott C.|Gaming PC|CPU|Memory|GPU|GPU|GPU|SSD|Power Supply
	Utilities tu; //tempUtility;
	bool tb; //tempBool
	size_t pos = 0, size =0, i = 0;
	size = count(input.begin(), input.end(), tu.getDelimiter()) +1;
	m_cntItem = size - 2;
	if (m_cntItem) {
		
		m_lstItem = new ItemInfo *[m_cntItem];
		
		vector<string> array(size); //holds all the info in different arrays
		for (string& x : array) {
			 
			x = tu.extractToken(input, pos, tb);
			pos += (x.length() + 1);
			if(i>1) m_lstItem[i-2] = new ItemInfo(x);
			i++;
		}

		m_name = array[0];
		m_product = array[1];	
		//After the extraction is finished, will update 
		//CustomerOrder::m_widthField if the value stored 
		//there is smaller than the value stored in Utilities::m_widthField. 
		m_widthField = (m_widthField < tu.getFieldWidth()) ? tu.getFieldWidth() : m_widthField;

	}

}

CustomerOrder::CustomerOrder(const CustomerOrder&) {
	throw string("Copy Not allowed");
}

CustomerOrder::CustomerOrder(CustomerOrder&& obj) noexcept {
	//move constructor. This constructor should "promise" that it doesn't throw exceptions. 
	//Use the noexcept keyword in the prototype
	*this = move(obj);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& obj) {
	//move assignment operator
	if (this != &obj) {
		//take the stuff from obj.
		m_lstItem =	 move(obj.m_lstItem);
		m_name	  =	 move(obj.m_name);
		m_product =	 move(obj.m_product);
		m_cntItem =  move(obj.m_cntItem);
		
		//set the stuff we took to null in obj.
		obj.m_cntItem = 0;
		obj.m_product = "";
		obj.m_name	  = "";
		obj.m_lstItem = nullptr;
	}
	return *this;
}

CustomerOrder::~CustomerOrder() {
	delete[] m_lstItem;
	m_lstItem = nullptr;
}

bool CustomerOrder::getItemFillState(string item) const {
	//returns the ItemInfo::m_fillState of the item specified as a parameter. 
	//If the item doesn't exist in the order, return true
	bool itemFilled = true;
	//loop through item list (ItemInfo** m_lstItem;) look for item because it's an array, so that we can find the item 
	for (unsigned i = 0; i < m_cntItem; i++) if (m_lstItem[i]->m_itemName == item) itemFilled = m_lstItem[i] -> m_fillState;//if (m_lstItem[i]->m_fillState == false) itemFilled = false;
	return itemFilled;
}

bool CustomerOrder::getOrderFillState() const {
	//returns true if all the items in the order have been filled; false otherwise
	bool orderFilled = true;
	//loop order list, if the state is false orderfilled =false.
	for (unsigned i = 0; i < m_cntItem; i++) 
		if (!m_lstItem[i]->m_fillState) orderFilled = m_lstItem[i]->m_fillState;
	return orderFilled;
}

void CustomerOrder::fillItem(Item& item, ostream& os) {
	//fills the item in the current order that corresponds to the item passed into the function (the parameter item represents what is available in the inventory). 
	//if item cannot be found in the current order, this function does nothing
	//if item is found, and the inventory contains at least one element, 
		//then this function substracts 1 from the inventory and updates ItemInfo::m_serialNumber and ItemInfo::m_fillState.
		//Also it prints the message Filled NAME, PRODUCT[ITEM_NAME].
	
	//if item is found, and the inventory is empty, 
		//then this function prints the message Unable to fill NAME, PRODUCT[ITEM_NAME].
	//all messages printed should be terminated by an endline
	
	for (unsigned i = 0; i < m_cntItem; i++) {
		if (m_lstItem[i]->m_itemName == item.getName() && !m_lstItem[i]->m_fillState) {

			if (item.getQuantity()) { //should be true for anything greater than 0
				item.updateQuantity(); //subtracts 1 from total
				m_lstItem[i]->m_serialNumber = item.getSerialNumber(); // sets the number and subtracts to the next serial for the following item that uses this item
				m_lstItem[i]->m_fillState = true;
				os << "Filled " << m_name << ", " << m_product << "[" << item.getName() << "]" << endl; //Filled Mary-Lynn M., Desktop PC[Power Supply]

			}
			else os << "Unable to fill " << m_name << ", " << m_product << "[" << item.getName() << "]" << endl;

		}
	}
}

void CustomerOrder::display(ostream& os) const {
	//displays the state of the current object in the format(see the sample output for details)
	/*
		CUSTOMER_NAME - PRODUCT
		[SERIAL] ITEM_NAME - STATUS
		[SERIAL] ITEM_NAME - STATUS
		...
	*/
	//SERIAL - a field of width 6
	//ITEM_NAME - a field of size m_widthField
	//STATUS is either FILLED or MISSING
	//you will have to use IO manipulators for the output.
	os << m_name << " - " << m_product << endl;
	for (unsigned i = 0; i < m_cntItem; i++) //{
	os << "[" << setw(6) << right <<setfill('0') << m_lstItem[i]->m_serialNumber << "] "
	<< left << setw(m_widthField) << setfill(' ') << m_lstItem[i]->m_itemName << " - "
	<< ((m_lstItem[i]->m_fillState) ? "FILLED" : "MISSING") << endl;

}