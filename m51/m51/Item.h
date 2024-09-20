
/*Final Project Milestone 56
Module: Item
Filename: Item.h
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
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include <iostream>
#include "Utils.h"
#include "iProduct.h"

namespace sdds
{
	class Item : public iProduct
	{
		double m_price;
		int m_qty;
		int m_qtyNeeded;
		char* m_itemdesc{};
		bool m_linear;
	protected:
		Status m_stateOfItem;
		int m_SKUNo;
		bool linear() const; // returns m_linear

	public:
		Item();
		Item(const Item& item); // copy constructor
		Item& operator=(const Item& item); // assignment operator
		virtual ~Item(); // destructor
		int qtyNeeded() const;
		int qty() const;
		operator double() const;
		operator bool() const;
		int operator -=(int value);
		int operator +=(int value);
		void linear(bool isLinear);
		void clear();
		bool operator==(int sku)const;
		bool operator==(const char* description)const;
		virtual std::ofstream& save(std::ofstream& ofstr)const;
		virtual std::ifstream& load(std::ifstream& ifstr);
		virtual std::ostream& display(std::ostream& ostr)const;
		virtual int readSku(std::istream& istr);
		virtual std::istream& read(std::istream& istr);




	};
}
#endif //! SDDS_ITEM_H