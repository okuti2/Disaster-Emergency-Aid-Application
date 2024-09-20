/*Final Project Milestone 56
Module: Aidman
Filename: Aidman.h
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
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include "Menu.h"
#include "iProduct.h"
namespace sdds
{
	const int sdds_max_num_items = 100;
	class AidMan
	{
		char* m_filename;
		Menu m_mainmenu{ 7, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n" }; // initializes the menu object 
		iProduct* m_iProd[sdds_max_num_items]={};
		int m_NumofItems = 0;
		unsigned menu() const;
	public:
		AidMan();
		AidMan(const AidMan&) = delete; // copy constructor should do nothing
		void operator=(const AidMan&) = delete; // assignment operator should do nothing
		~AidMan(); // destructor
		void run(); // runs the whole application
		void save(); // Not yet implemented
		void deallocate(); // deallocates all pointer arrays in the file
		bool load(); // loads the pointer arrays with appropriate data
		int list(const char* sub_desc = nullptr); // lists the data in iproduct 
		int search(int sku) const; // checks if an sku number is already used in the array
		void remove(int index); // deletes the iproduct at index in iproduct pointers
		void ShipOption();

	};
}
#endif //! SDDS_AIDMAN_H

