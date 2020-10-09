#ifndef customerorder_H
#define customerorder_H
#include <string>
#include <iostream>
#include "Item.h"
// Name: Steven Killoran
// Seneca Student ID: 144364189
// Seneca email: skilloran1@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

using namespace std;

struct ItemInfo {
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {
	string m_name{};
	string m_product{};
	unsigned m_cntItem{};
	ItemInfo** m_lstItem =nullptr;
	static size_t m_widthField;
public:
	//default constructor
	CustomerOrder();
	//cust constructor references to a string containing a single record from the input file.
	//This constructor uses an Utilities object to extract the tokens and populate the current instance.
	CustomerOrder(string input);
	//a CustomerOrder object should not allow copy operations. 
	//The copy constructor should throw an exception if called and the copy operator= should be deleted.
	CustomerOrder& operator=(const CustomerOrder& obj) = delete; //instantly default to delete when called 
	CustomerOrder(const CustomerOrder&); //copy constructor
	//move constructor.This constructor should "promise" that it doesn't throw exceptions. Use the noexcept keyword in the prototype.
	CustomerOrder(CustomerOrder&& obj) noexcept;
	//move assignment operator
	CustomerOrder& operator=(CustomerOrder&& obj);
	//a destructor
	~CustomerOrder();
	//returns the ItemInfo::m_fillState of the item specified as a parameter. 
	//If the item doesn't exist in the order, return true
	bool getItemFillState(string item) const;
	//returns true if all the items in the order have been filled; false otherwise
	bool getOrderFillState() const;
	//fills the item in the current order that corresponds to the item passed into the function (the parameter item represents what is available in the inventory)
	void fillItem(Item& item, ostream& os);
	//displays the state of the current object in the format (see the sample output for details) 
	void display(std::ostream&) const;
};






#endif // !customerorder_H
