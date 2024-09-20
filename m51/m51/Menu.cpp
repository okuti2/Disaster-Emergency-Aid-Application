/*Final Project Milestone 56
Module: Menu
Filename: Menu.cpp
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
#include "Utils.h"
#include "Menu.h"
using namespace std;
namespace sdds
{
	Menu::Menu(unsigned numoptions, const char* menucontext) {
		if (menucontext != nullptr && numoptions <= 15)
		{
			m_optionlist = nullptr;
			ut.alocpy(m_optionlist, menucontext);
			m_numoptions = numoptions;
		}
	}

	Menu::~Menu() {
		delete[] m_optionlist;
		m_optionlist = nullptr;
		m_numoptions = 0;
	}

	// prints out the menu option and only accepts a selection that is in the option number list
	unsigned Menu::run() const {
		cout << m_optionlist << "0- Exit" << endl;
		unsigned selection = ut.getint(0, m_numoptions, "> ");
		return selection;
	}

}