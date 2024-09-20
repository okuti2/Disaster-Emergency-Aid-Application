/*Final Project Milestone 56
Module: Perishable
Filename: Perishable.cpp
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
#include<iomanip>
#include "Perishable.h"
#include "Date.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
	Perishable::Perishable()
	{
		m_instructions = nullptr;
	}

	Perishable::~Perishable() // destructor
	{
		delete[] m_instructions;
		m_instructions = nullptr;
	}

	Perishable::Perishable(const Perishable& p) // copy constructor
	{
		operator=(p);
	}

	Perishable& Perishable::operator=(const Perishable& p) // assignment operator
	{
		if (this != &p)
		{
			delete[] m_instructions;
			if (p.m_instructions != nullptr) {
				ut.alocpy(m_instructions, p.m_instructions);
			}
			else {
				m_instructions = nullptr;
			}
			m_expiryDate = p.m_expiryDate;
			Item::operator=(p);
		}
		return *this;
	}

	const Date& Perishable::expiry() const // returns the date variable in the perishable object which is the expiry date
	{
		return m_expiryDate;
	}

	int Perishable::readSku(std::istream& istr) // used to read the sku number into perishable
	{
		m_SKUNo = ut.getint(10000, 39999, "SKU: ");
		istr.ignore(1000, '\n'); // ignores newline
		return m_SKUNo;
	}

	std::ofstream& Perishable::save(std::ofstream& ofstr) const // override from Item save function, writes the perishable data into the ofstream into a .dat file
	{
		if (Item::m_stateOfItem) // if the Item is in a good state
		{
			Item::save(ofstr); // Base class save function
			ofstr << '\t';
			if (m_instructions != nullptr) ofstr << m_instructions;
			ofstr << '\t';
			Date expiry_date;
			expiry_date = expiry(); // the function is a query so I need to copy the date object in order to modify
			expiry_date.formatted(false);
			ofstr << expiry_date;
		}

		return ofstr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifstr) // overrid function from item class that reads the data from a into a file
	{
		Item::load(ifstr);
		delete[] m_instructions;
		m_instructions = nullptr;
		char instructions[500];

		ifstr.getline(instructions, 500, '\t'); // reads the instructions
		if (instructions[0] != '\0')
		{
			ut.alocpy(m_instructions, instructions);
		}
		else {
			m_instructions = nullptr;
		}

		ifstr >> m_expiryDate;
		if (ifstr.fail())
		{
			m_stateOfItem = "Input file stream read(perishable) failed!";
		}
		ifstr.ignore(1000, '\n');

		return ifstr;
	}

	std::ostream& Perishable::display(std::ostream& ostr) const // overind from item class and displays the contents of the class on screen if in a good state or prints the error message if in a bad state
	{
		if (m_stateOfItem) {
			if (linear()) { // formatting type
				Item::display(ostr); // base class function is called
				if (m_instructions != nullptr)
				{
					ostr << "*";
				}
				else {
					ostr << " ";
				}
				ostr << m_expiryDate;
			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: " << m_expiryDate;
				if (m_instructions != nullptr)
				{
					ostr << endl << "Handling Instructions: " << m_instructions;
				}
				ostr << endl;
			}
		}
		else {
			ostr << m_stateOfItem;
		}
		return ostr;
	}

	std::istream& Perishable::read(std::istream& istr) // override function of Item object. reads data for the Perishable class from the console
	{
		Item::read(istr);
		char ch;
		delete[] m_instructions;
		m_instructions = nullptr;
		cout << "Expiry date (YYMMDD): ";
		m_expiryDate.read(istr);
		istr.ignore(); // ignore newline
		cout << "Handling Instructions, ENTER to skip: ";
		ch = istr.peek();
		if (ch != '\n')
		{
			char instructions[500];
			istr.get(instructions, 500, '\n');
			ut.alocpy(m_instructions, instructions);
		}
		else {
			m_instructions = nullptr;
		}
		if (istr.fail()) {
			m_stateOfItem = "Perishable console date entry failed!";
		}
		return istr;
	}
}