/*Final Project Milestone 56
Module: Menu
Filename: Menu.h
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
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
namespace sdds
{
	class Menu
	{
		char* m_optionlist{};
		unsigned m_numoptions =0;

	public:
		Menu(unsigned numoptions, const char* menucontext);
		Menu(const Menu&) = delete; // copy constructor should do nothing
		void operator=(const Menu&) = delete; // assignment operator should do nothing
		~Menu();
		unsigned run()const;
	};
}
#endif //! SDDS_MENU_H