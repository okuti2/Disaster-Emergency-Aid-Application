/*Final Project Milestone 56
Module: Date
Filename: Date.cpp
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
#include "Date.h"
#include "Status.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
	// validates the year month and days and sets the error messages if necessary
	bool Date::validate() {
		int currentYear;
		ut.getSystemDate(&currentYear);
		int maxdays = ut.daysOfMon(m_month, m_year);

		if (m_year > MaxYearVal || m_year < currentYear) {
			m_state = "Invalid year in date";
			m_state = 1;
		}
		else if (m_month < 1 || m_month > 12) {
			m_state = "Invalid month in date";
			m_state = 2;
		}
		else if (m_day < 1 || m_day > maxdays) {
			m_state = "Invalid day in date";
			m_state = 3;
		}
		else {
			m_state.clear();
		}
		if (bool(m_state)) {
			return true;
		}
		else {
			return false;
		}
	}

	// makes a unique integer value from the date 
	int Date::uniqueDateValue() const {
		int result = (m_year * 372) + (m_month * 31) + m_day;
		return result;
	}

	//contstructor
	Date::Date() {
		ut.getSystemDate(&m_year, &m_month, &m_day);
	}

	// constructor with all the parameters provided
	Date::Date(int year, int month, int day) {
		m_day = day;
		m_month = month;
		m_year = year;
		validate();
	}

	// destructor
	Date::~Date() {
		m_state.clear();
		m_day = 0;
		m_month = 0;
		m_year = 0;
	}

	//
	bool Date::operator==(const Date& date1) const {
		return uniqueDateValue() == date1.uniqueDateValue();
	}

	bool Date::operator !=(const Date& date1) const {
		return uniqueDateValue() != date1.uniqueDateValue();
	}

	bool Date::operator <(const Date& date1) const {
		return uniqueDateValue() < date1.uniqueDateValue();
	}

	bool Date::operator >(const Date& date1) const {
		return uniqueDateValue() > date1.uniqueDateValue();
	}

	bool Date::operator <=(const Date& date1) const {
		return uniqueDateValue() <= date1.uniqueDateValue();
	}

	bool Date::operator >=(const Date& date1) const {
		return uniqueDateValue() >= date1.uniqueDateValue();
	}

	// returns the status of the date should return a const reference of the state of the date but might be wrong
	const Status& Date::state() const {
		return m_state;
	}

	// sets the formatting option of the object
	Date& Date::formatted(bool prompt)
	{
		m_formatted = prompt;
		return *this;
	}

	// returns the state of the date, what is the difference between the state()
	Date::operator bool()const {
		return m_state;
	}

	//prints out the valid date in the style specified (formatted or unformatted)
	ostream& Date::write(ostream& ostr) const {

		if (m_formatted == false) {
			ostr << m_year % 100;
			ostr << std::setfill('0') << setw(2);
			ostr << m_month << m_day;
		}
		else {
			ostr << m_year << "/";
			ostr << std::setfill('0') << setw(2);
			ostr << m_month << "/";
			ostr << std::setfill('0') << setw(2);
			ostr << m_day;
		}
		return ostr;
	}

	// reads the input from the istream and converts it into a date format into the object if valid
	istream& Date::read(istream& istr) {
		m_state.clear();
		int date;
		istr >> date;
		if (istr) {
			m_day = date % 100;
			date /= 100;
			m_month = date % 100;
			date /= 100;
			if (date == 0)
			{
				ut.getSystemDate(&m_year);
			}
			else {
				m_year = 2000 + (date % 100);
			}
			if (!validate()) {
				istr.setstate(ios::badbit);
			}
		}
		else {
			m_state = "Invalid date value";
		}
		return istr;
	}

	istream& operator>>(istream& istr, Date& date) {
		return date.read(istr);
	}

	ostream& operator<<(ostream& ostr, const Date& date) {
		if (bool(date)) {
			date.write(ostr);
		}
		return ostr;
	}


}