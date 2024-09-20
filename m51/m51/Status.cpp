/*Final Project Milestone 56
Module: Status
Filename: Status.cpp
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
#include "Utils.h"
using namespace std;
namespace sdds
{
	void Status::setEmpty() {
		m_errorcode = nullptr;
		m_statuscode = 0;
	}
	Status::Status() {
		setEmpty();
	}

	Status::Status(const char* error) {
		if (error != nullptr) {
			delete[] m_errorcode;
			setEmpty();
			ut.alocpy(m_errorcode, error);
			/*m_errorcode = new char[strLen(error) + 1];
			strCpy(m_errorcode, error);*/
		}
	}

	//Copy constructor
	Status::Status(const Status& status) {
		if (status.m_errorcode != nullptr)
		{
			setEmpty();
			*this = status;
		}
	}

	// assignment operator
	Status& Status::operator=(const Status& status)
	{
		if (this != &status) {
			if (status.m_errorcode != nullptr) {
				ut.alocpy(m_errorcode, status.m_errorcode);
				m_statuscode = status.m_statuscode;
			}
			else {
				delete[] m_errorcode;
				setEmpty();
			}
		}
		return *this;
	}
	//destructor
	Status::~Status() {
		delete[] m_errorcode;
		m_errorcode = nullptr;
	}

	// assignment operator = overloaded to add an integer into the m_statuscode member in the object
	Status& Status::operator=(const int statuscode) {
		m_statuscode = statuscode;
		return *this;
	}

	// assignent operator = overloaded to add char into the m_errorcode member in the object
	Status& Status::operator=(const char* errorcode) {
		if (errorcode != nullptr) {
			ut.alocpy(m_errorcode, errorcode);
		}
		return *this;
	}

	// returns the status code in the object
	Status::operator int() const {
		return m_statuscode;
	}

	// returns the errorcode
	Status::operator const char* () const {
		return m_errorcode;
	}

	// returns if the object is in a false state
	Status:: operator bool() const {
		return (m_errorcode == nullptr);
	}

	//clears and deallocates the current object
	Status& Status::clear() {
		delete[] m_errorcode;
		m_errorcode = nullptr;
		m_statuscode = 0;
		return *this;
	}

	// insertion operator << overload prints out the status or the errorcode
	ostream& operator<<(ostream& ostr, const Status& status) {
		if (!status)
		{
			if (int(status) != 0) ostr << "ERR#" << int(status) << ": ";
			ostr << status.operator const char* ();
		}
		return ostr;
	}

}