/*Final Project Milestone 56
Module: Utils
Filename: Utils.h
Version 1.0
Author	Olutoyosi Kuti
Revision History
-----------------------------------------------------------
Date      8th April 2022
2020/?/?  Preliminary release
2020/?/?  Debugged DMA
------------------------------------------------- ----------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
namespace sdds
{
    // Testing date values for application testing and debugging
  // these values must not change at submission time.
    const int sdds_testYear = 2022;
    const int sdds_testMon = 03;
    const int sdds_testDay = 31;
    class Utils
    {
        bool m_testMode = false;
    public:
        // this function will be used to get the current system date or the test date if m_testMode is true
        void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);

        // this function will return the number of days in a month based on the year
        // 1<=mon<=12  year: four digit number (example: 2021)
        int daysOfMon(int mon, int year)const;

        // Puts the system date in test mode, where getSystemDate() function will return 2022, 03, 31
        // or whatever the three constant test dates are set to
        void testMode(bool testmode = true);

        // Safely allocates memory in destination and copies the source into it
        void alocpy(char*& destination, const char* source);

        // displays integer if prompt is not null
        int getint(const char* prompt = nullptr);

        // displays integer if it is within range provided
        int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr);

        double getdouble(const char* prompt);

        double getdouble(double min, double max, const char* prompt, const char* errMes = nullptr);

        // copies src to des
        void strCpy(char* des, const char* src);
        void strCpy(char* des, const char* src, int len)const;

        // returns the length of str
        int strLen(const char* str);

        // returns true if ch is a whitespace character
        int isSpace(char ch);

        // if "find" is found in "str" it will return the addres of the match
    // if not found it will returns nullptr (zero)
        const char* strstr(const char* str, const char* find)const;

        // compares s1 and s2 cStrings upto len characters and returns:
    // > 0 if s1 > s2
    // < 0 if s1 < s3
    // == 0 if s1 == s2
        int strcmp(const char* s1, const char* s2, int len)const;

        // returns the lower case value of a character
        char toLower(char ch);

        // copies the  lower case version of the source into des.
        void toLowerCaseAndCopy(char des[], const char source[]);
    };

    extern Utils ut; // provides global access to the ut instance in the Utils.cpp file
}

#endif // !SDDS_UTILS_H
