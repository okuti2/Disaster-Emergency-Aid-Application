/*Final Project Milestone 56
Module: Perishable
Filename: Perishable.h
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
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"
namespace sdds
{
	class Perishable : public Item
	{
		Date m_expiryDate;
		char* m_instructions{};
	public:
		Perishable();
		//Rule of three
		virtual ~Perishable();
		Perishable(const Perishable& p); // copy constructor
		Perishable& operator=(const Perishable& p); // assignment operator
		const Date& expiry() const;
		int readSku(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr)const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};

}
#endif //! SDDS_PERISHABLE_H