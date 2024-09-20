/*Final Project Milestone 56
Module: Date
Filename: Date.h
Version 1.0
Author	Olutoyosi Kuti
Revision History
-----------------------------------------------------------
Date      8th April, 2022
2020/?/?  Preliminary release
2020/?/?  Debugged DMA
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include "Status.h"
namespace sdds
{
	const int MaxYearVal = 2030;
	class Date
	{
		int m_year;
		int m_month;
		int m_day;
		Status m_state;
		bool m_formatted = true;
		bool validate();
		int uniqueDateValue() const;
	public:

		// Constructors
		Date();
		Date(int year, int month, int day);
		~Date();
		// operator overloads for comparison
		bool operator == (const Date& date1) const;
		bool operator != (const Date& date1) const;
		bool operator < (const Date& date1) const;
		bool operator > (const Date& date1) const;
		bool operator <= (const Date& date1) const;
		bool operator >= (const Date& date1) const;

		//state accessor
		const Status& state() const;

		//formatted modifier
		Date& formatted(bool prompt);

		// bool conversion overload
		operator bool()const;

		//prints out the valid date in the style specified (formatted or unformatted)
		std::ostream& write(std::ostream& ostr) const;
		// reads the input from the istream and converts it into a date format into the object if valid
		std::istream& read(std::istream& istr);
	};

	std::istream& operator>>(std::istream& istr, Date& date);
	std::ostream& operator<<(std::ostream& ostr, const Date& date);
}
#endif //! SDDS_DATE_H