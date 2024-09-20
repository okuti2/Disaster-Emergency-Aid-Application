/*Final Project Milestone 56
Module: Item.cpp
Filename: Item.cpp
Version 1.0
Author	Olutoyosi Kuti
Revision History
-----------------------------------------------------------
Date      8th April 2022
2020/?/?  Preliminary release
2020/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "Utils.h"
#include "Item.h"
using namespace std;
namespace sdds
{
	// returns the m_linear flag
	bool Item::linear() const {
		return m_linear;
	}

	Item::Item()
	{
		m_itemdesc = nullptr;
		m_linear = false;
		m_price = 0.0;
		m_qtyNeeded = 0;
		m_qty = 0;
		m_SKUNo = 0;
		m_stateOfItem.clear();
	}

	Item::~Item()
	{
		delete[] m_itemdesc;
		m_itemdesc = nullptr;
	}

	Item::Item(const Item& item)
	{
		*this = item;
	}

	Item& Item::operator=(const Item& item)
	{
		if (this != &item) {
			if (item.m_itemdesc != nullptr) {
				ut.alocpy(m_itemdesc, item.m_itemdesc);
				m_linear = item.m_linear;
				m_price = item.m_price;
				m_qtyNeeded = item.m_qtyNeeded;
				m_qty = item.m_qty;
				m_SKUNo = item.m_SKUNo;
				m_stateOfItem = item.m_stateOfItem;
			}
		}
		return *this;
	}

	// returns the number of products needed
	int Item::qtyNeeded() const
	{
		return m_qtyNeeded;
	}

	// retuns the quantity on hand
	int Item::qty() const
	{
		return m_qty;
	}

	// returns the price of the produce
	Item::operator double() const
	{
		return m_price;
	}

	// returns if the iProduct is in a good state
	Item::operator bool() const
	{
		return bool(m_stateOfItem) && m_SKUNo;
	}

	// to reduce the quantity on hand
	int Item::operator-=(int value)
	{
		return (m_qty -= value) > 0 ? m_qty : m_qty = 0;
	}

	// to increase the quantity on hand
	int Item::operator+=(int value)
	{
		return m_qty += value;
	}

	// determines if the iProduct is displayed in a linear format or descriptive format
	void Item::linear(bool isLinear)
	{
		m_linear = isLinear;
	}

	// sets the state of the Item object back to good
	void Item::clear()
	{
		m_stateOfItem.clear();
	}

	// return true if the sku is a match to the iProduct's sku
	bool Item::operator==(int sku)const {
		return (m_SKUNo == sku);
	}

	// returns true if the description is found in the iPorduct's description
	bool Item::operator==(const char* desc)const {
		bool found = false;
		if (desc != nullptr && m_itemdesc != nullptr) {
			if (ut.strstr(m_itemdesc, desc) != nullptr) found = true;
		}
		return found;
	}

	// saves the iProduct into a file
	std::ofstream& Item::save(std::ofstream& ofstr)const {
		if (m_stateOfItem) {
			ofstr << m_SKUNo << '\t' << m_itemdesc << '\t' << m_qty << '\t' << m_qtyNeeded << '\t';
			ofstr << fixed << setprecision(2) << m_price;
		}
		return ofstr;
	}

	// loads an iProduct from a file
	std::ifstream& Item::load(std::ifstream& ifstr) {
		delete[] m_itemdesc;
		m_itemdesc = nullptr;
		char description[501];

		ifstr >> m_SKUNo;
		ifstr.ignore();
		ifstr.get(description, 500, '\t');
		ut.alocpy(m_itemdesc, description);
		ifstr >> m_qty;
		ifstr.ignore();
		ifstr >> m_qtyNeeded;
		ifstr.ignore();
		ifstr >> m_price;
		ifstr.ignore();

		if (ifstr.fail())
		{
			m_stateOfItem = "Input file stream read failed!";
		}
		return ifstr;
	}

	// displays the iProduct on the screen
	std::ostream& Item::display(std::ostream& ostr)const {
		if (m_stateOfItem) {
			if (m_linear) {
				char* description{};
				description = nullptr;
				if (m_itemdesc != nullptr)
				{
					description = new char[ut.strLen(m_itemdesc) + 1];
					ut.strCpy(description, m_itemdesc, 35); // we only want to display up to the 35th character so a new pointer to hold it is created and then destroyed
				}
				ostr.setf(ios::left);
				ostr << setfill(' ');
				ostr.width(5);
				ostr << m_SKUNo << " | ";
				ostr.width(35);
				ostr << description;
				ostr << " | ";
				ostr.unsetf(ios::left);
				ostr.width(4);
				ostr << m_qty << " | ";
				ostr.width(4);
				ostr << m_qtyNeeded << " | ";
				ostr.width(7);
				ostr << fixed << setprecision(2);
				ostr << m_price << " |";
				delete[] description;
				description = nullptr;
			}
			else {
				ostr << "AMA Item:" << endl;
				ostr << m_SKUNo << ": ";
				ostr << m_itemdesc << endl;
				ostr << "Quantity Needed: " << m_qtyNeeded << endl;
				ostr << "Quantity Available: " << m_qty << endl;
				ostr << "Unit Price: $";
				ostr << fixed << setprecision(2) << m_price << endl;
				ostr << "Needed Purchase Fund: $";
				ostr << fixed << setprecision(2) << (double(m_qtyNeeded) - double(m_qty)) * m_price << endl;
			}
		}
		else {
			ostr << m_stateOfItem;
		}
		return ostr;
	}

	// reads the SKU
	int Item::readSku(std::istream& istr)
	{
		m_SKUNo = ut.getint(40000, 99999, "SKU: ");
		return m_SKUNo;
	}

	// reads the iProduct from the console
	std::istream& Item::read(std::istream& istr) {
		char description[51];
		delete[] m_itemdesc;
		m_itemdesc = nullptr;
		m_stateOfItem.clear();

		cout << "AMA Item:" << endl;
		cout << "SKU: " << m_SKUNo << endl;
		cout << "Description: ";
		istr.get(description, 50, '\n');
		ut.alocpy(m_itemdesc, description);
		m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
		m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");
		m_price = ut.getdouble(0.0, 9999.0, "Unit Price: $");

		if (istr.fail())
		{
			m_stateOfItem = "Console entry failed!";
		}
		return istr;
	}
}