/*Final Project Milestone 56
Module: Utils
Filename: Utils.cpp
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
#include <iomanip>
#include <cstdio>
#include <ctime>
#include "Utils.h"
using namespace std;
namespace sdds
{
    // The ut object of type Utils that is accessible to any file including "Utils.h" to call the Utils
   // methods
    Utils ut;
    void Utils::testMode(bool testmode) {
        m_testMode = testmode;
    }
    void Utils::getSystemDate(int* year, int* mon, int* day) {
        if (m_testMode) {
            if (day) *day = sdds_testDay;
            if (mon) *mon = sdds_testMon;
            if (year) *year = sdds_testYear;
        }
        else {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) *day = lt.tm_mday;
            if (mon) *mon = lt.tm_mon + 1;
            if (year) *year = lt.tm_year + 1900;
        }
    }
    int Utils::daysOfMon(int month, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    void Utils::alocpy(char*& destination, const char* source) {
        delete[] destination;
        destination = nullptr;
        if (source != nullptr)
        {
            destination = new char[strLen(source) + 1];
            strCpy(destination, source);
        }

    }

    int Utils::getint(const char* prompt) {
        int number;
        bool flag = true;
        if (prompt != nullptr)
        {
            cout << prompt;
        }
        do {
            cin >> number;
            if (!cin)
            {
                cout << "Invalid Integer, retry: ";
                cin.clear();
                cin.ignore(1000, '\n');
                flag = false;
            }
            else {
                flag = true;
            }
        } while (!flag);

        return number;
    }

    int Utils::getint(int min, int max, const char* prompt, const char* errMes)
    {
        int num;
        do
        {
            num = getint(prompt);
            if (num < min || num > max)
            {
                prompt = nullptr;
                if (errMes != nullptr)
                {
                    cout << errMes << ", retry: " << endl;
                }
                else {
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                }
            }
        } while (num < min || num > max);
        return num;
    }

    double Utils::getdouble(const char* prompt) {
        double number;
        bool flag = true;
        if (prompt != nullptr)
        {
            cout << prompt;
        }
        do {
            cin >> number;
            if (!cin)
            {
                cout << "Invalid number, retry: ";
                cin.clear();
                cin.ignore(1000, '\n');
                flag = false;
            }
            else {
                flag = true;
            }
        } while (!flag);

        return number;
    }

    double Utils::getdouble(double min, double max, const char* prompt, const char* errMes)
    {
        double num;
        do
        {
            num = getdouble(prompt);
            if (num < min || num > max)
            {
                prompt = nullptr;
                if (errMes != nullptr)
                {
                    cout << errMes << ", retry: " << endl;
                }
                else {
                    cout << fixed << setprecision(2);
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
                }
            }
        } while (num < min || num > max);
        return num;
    }

    // copies src to des
    void Utils::strCpy(char* des, const char* src) {
        int i;
        for (i = 0; src[i]; i++) des[i] = src[i];
        des[i] = 0;
    }

    void Utils::strCpy(char* des, const char* src, int len)const {
        int i;
        for (i = 0; i < len && src[i]; i++) des[i] = src[i];
        des[i] = 0; // unlike strncpy, this function null terminates
    }

    // returns the length of str
    int Utils::strLen(const char* str) {
        int len;
        for (len = 0; str[len]; len++);
        return len;
    }

    // returns true if ch is a whitespace character
    int Utils::isSpace(char ch) {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
    }

    // if "find" is found in "str" it will return the addres of the match
    // if not found it will returns nullptr (zero)
    const char* Utils::strstr(const char* str, const char* find)const {
        char new_str[500];
        char temp_find[500];
        ut.toLowerCaseAndCopy(new_str, str);
        ut.toLowerCaseAndCopy(temp_find, find);
        const char* faddress = nullptr;
        int i, flen = ut.strLen(temp_find), slen = ut.strLen(new_str);
        for (i = 0; i <= slen - flen && strcmp(&new_str[i], temp_find, flen); i++);
        if (i <= slen - flen) faddress = &new_str[i];
        return faddress;
    }

    // compares s1 and s2 cStrings upto len characters and returns:
    // > 0 if s1 > s2
    // < 0 if s1 < s3
    // == 0 if s1 == s2
    int Utils::strcmp(const char* s1, const char* s2, int len)const {
        int i = 0;
        while (i < len - 1 && s1[i] && s2[i] && s1[i] == s2[i]) {
            i++;
        }
        return s1[i] - s2[i];
    }

    // returns the lower case value of a character
    char Utils::toLower(char ch) {
        if (ch >= 'A' && ch <= 'Z') ch += ('a' - 'A');
        return ch;
    }

    // copies the  lower case version of the source into des.
    void Utils::toLowerCaseAndCopy(char des[], const char source[]) {
        int i = 0, j = 0;
        for (; source[i] != 0; i++) {
            des[j++] = toLower(source[i]);
        }
        des[j] = 0;
    }
}