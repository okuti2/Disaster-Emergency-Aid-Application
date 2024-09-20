/*Final Project Milestone 56
Module: Status
Filename: Status.h
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
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
namespace sdds
{
	class Status
	{
		char* m_errorcode{};
		int m_statuscode = 0;
		void setEmpty();
	public:
		//constructors
		Status();
		Status(const char* error);

		//Rule of three
		Status(const Status& status); // copy contstructor
		Status& operator=(const Status& status); // assignment operator
		~Status(); // destructor;

		//Assignment operator overloads
		Status& operator=(const int statuscode);
		Status& operator=(const char* errorcode);

		//TypeConversion Overloads;
		operator int() const;
		operator const char* () const;
		operator bool()const;

		//clears the object and deallocates
		Status& clear();


	};
	// insertion operator overload
	std::ostream& operator<<(std::ostream& ostr, const Status& status);

}
#endif //! SDDS_STATUS_H