/*Final Project Milestone 56
Module: iProduct.cpp
Filename: iProduct.cpp
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
#include "Status.h"
#include "iProduct.h"
using namespace std;
namespace sdds
{
	ostream& operator<<(std::ostream& ostr, const iProduct& IP)
	{
		IP.display(ostr);
		return ostr;
	}

	istream& operator>>(std::istream& istr, iProduct& IP)
	{
		IP.read(istr);
		return istr;
	}
}