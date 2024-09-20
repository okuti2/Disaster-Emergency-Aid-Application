/*Final Project Milestone 56
Module: AidMan
Filename: AidMan.cpp
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
#include <cstring>
#include <fstream>
#include "AidMan.h"
#include "Menu.h"
#include "Date.h"
#include "Perishable.h"
#include "Item.h"
using namespace std;
namespace sdds
{
	// The header is printed and the selectioln is chosen
	unsigned AidMan::menu() const {
		cout << "Aid Management System" << endl;
		cout << "Date: " << Date() << endl;
		cout << "Data file: " << (m_filename == nullptr ? "No file" : m_filename);
		cout << endl;
		cout << "---------------------------------" << endl;
		unsigned selection = m_mainmenu.run(); // calls the run function for the menu module
		return selection;
	}

	// default constructor
	AidMan::AidMan() {
		m_filename = nullptr;
	}

	// destructor
	AidMan::~AidMan() {
		delete[] m_filename;
		m_filename = nullptr;
		deallocate();
	}

	// runs the whole application for the menu selection
	void AidMan::run() {
		int result;
		int itemFound = 0; // If the sku number is found in the data
		iProduct* temp; // for sorting
		temp = nullptr;
		do {
			result = menu();
			if (m_filename == nullptr && result != 0 && result != 7) result = 7;
			switch (result) {
			case 1:
				cout << endl << "****List Items****" << endl;
				itemFound = list();
				if (itemFound > 0) {
					cout << "Enter row number to display details or <ENTER> to continue:" << endl;
					cout << "> ";
					char c;
					cin.ignore(1000, '\n');
					c = cin.peek();
					if (c != '\n') {
						int ans = 0;
						ans = ut.getint(1, itemFound);
						m_iProd[ans - 1]->linear(false);
						cout << *m_iProd[ans - 1] << endl;
					}
				}
				cout << endl;
				break;
			case 2:
				cout << endl << "****Add Item****" << endl;

				if (m_NumofItems < sdds_max_num_items) {
					int option = 0;
					cout << "1- Perishable" << endl;
					cout << "2- Non-Perishable" << endl;
					cout << "-----------------" << endl;
					cout << "0- Exit" << endl;
					option = ut.getint(0, 2, "> ");
					int sku = 0; // sku number read from console
					int ans = 0; // if the sku number is found then ans != -1
					switch (option) {
					case 0:
						cout << "Aborted" << endl;
						break;
					case 1: // Perishables
						m_iProd[m_NumofItems] = new Perishable;
						sku = m_iProd[m_NumofItems]->readSku(cin);
						ans = search(sku);
						if (ans != -1) {
							cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl;
							delete m_iProd[m_NumofItems];
							m_iProd[m_NumofItems] = nullptr;
						}
						else {
							cin >> *m_iProd[m_NumofItems];
							if (m_iProd[m_NumofItems]) {
								m_NumofItems++;
							}
							else {
								cout << *m_iProd[m_NumofItems];
								delete m_iProd[m_NumofItems];
								m_iProd[m_NumofItems] = nullptr;
							}
						}
						break;

					case 2: // Non-perishables
						m_iProd[m_NumofItems] = new Item;
						sku = m_iProd[m_NumofItems]->readSku(cin);
						ans = search(sku);
						if (ans != -1) {
							cout << "Sku: " << sku << " is already in the system, try updating quantity instead." << endl;
							delete m_iProd[m_NumofItems];
							m_iProd[m_NumofItems] = nullptr;
						}
						else {
							cin.ignore(1000, '\n');
							cin >> *m_iProd[m_NumofItems];
							if (m_iProd[m_NumofItems]) {
								m_NumofItems++;
							}
							else {
								cout << *m_iProd[m_NumofItems];
								delete m_iProd[m_NumofItems];
								m_iProd[m_NumofItems] = nullptr;
							}
						}
						break;
					}
				}
				else {
					cout << "Database full!" << endl;
				}
				cout << endl;
				break;
			case 3:
				cout << endl << "****Remove Item****" << endl;
				cout << "Item description: ";
				cin.ignore(1000, '\n');
				char description[200];
				cin.get(description, 200, '\n');
				itemFound = list(description); // checks if the desciption is found in the data 

				if (itemFound > 0) { //
					int skuNo, index = 0;
					skuNo = ut.getint("Enter SKU: ");
					index = search(skuNo);

					if (index == -1) {
						cout << "SKU not found!" << endl;
					}
					else {
						int optionSelected = -1;
						cout << "Following item will be removed: " << endl;
						m_iProd[index]->linear(false);
						cout << *m_iProd[index] << endl;
						cout << "Are you sure?\n1- Yes!\n0- Exit" << endl;
						optionSelected = ut.getint(0, 1, "> ");
						if (optionSelected == 1) {
							remove(index);
							cout << "Item removed!" << endl;
						}
						else if (optionSelected == 0) {
							cout << "Aborted!" << endl;
						}
					}
				}
				cout << endl;
				break;
			case 4:
				cout << endl << "****Update Quantity****" << endl;
				cout << "Item description: ";
				cin.ignore(1000, '\n');
				char updateDesc[200];
				cin.get(updateDesc, 200, '\n');
				itemFound = list(updateDesc); // checks if the desciption is found in the data
				if (itemFound > 0) {
					int skuNo, index = 0;
					skuNo = ut.getint("Enter SKU: ");
					index = search(skuNo);

					if (index == -1) {
						cout << "SKU not found!" << endl;
					}
					else {
						int qty = 0; // hold the m_qty of the current object
						int qtyNeeded = 0; // holds the m_qtyNeeded of the current object
						int optionSelected = -1; // Add, reduce or exit option chosen
						int Amount = 0; // amount to be added of removed
						cout << "1- Add\n2- Reduce\n0- Exit" << endl;
						optionSelected = ut.getint(0, 2, "> ");
						qty = m_iProd[index]->qty();
						qtyNeeded = m_iProd[index]->qtyNeeded();
						if (optionSelected == 0) {
							cout << "Aborted!" << endl;
						}
						else if (optionSelected == 1) {

							if (qty < qtyNeeded) {
								Amount = ut.getint(1, qtyNeeded, "Quantity to add: ");
								if (Amount <= (qtyNeeded - qty)) {
									m_iProd[index]->operator+=(Amount);
								}
								else {
									Amount = qtyNeeded - qty;
									m_iProd[index]->operator+=(Amount);
								}
								cout << Amount << " items added!" << endl;
							}
							else {
								cout << "Quantity Needed already fulfilled!" << endl;
							}
						}
						else if (optionSelected == 2) {

							if (qty > 0) {
								Amount = ut.getint(1, qty, "Quantity to reduce: ");
								if (Amount <= qty) {
									m_iProd[index]->operator-=(Amount);
								}
								else {
									Amount = qty;
									m_iProd[index]->operator-=(Amount);
								}
								cout << Amount << " items removed!" << endl;
							}
							else {
								cout << "Quantity on hand is zero!" << endl;
							}
						}
					}
				}
				else {
					cout << "No matches found!" << endl;
				}
				cout << endl;
				break;
			case 5:
				cout << endl << "****Sort****" << endl;

				for (int i = 1; i < m_NumofItems; i++) {
					int difference = 0;
					int difference2 = 0;
					difference = (m_iProd[i]->qtyNeeded() - m_iProd[i]->qty());
					for (int j = 0; j < m_NumofItems; j++) {
						difference2 = (m_iProd[j]->qtyNeeded() - m_iProd[j]->qty());
						if (difference > difference2) {
							temp = m_iProd[j];
							m_iProd[j] = m_iProd[i];
							m_iProd[i] = temp;
						}
					}
				}

				cout << "Sort completed!" << endl;
				cout << endl;
				break;
			case 6:
				cout << endl << "****Ship Items****" << endl;
				ShipOption();
				cout << endl;
				break;
			case 7:
				cout << endl << "****New/Open Aid Database****" << endl;
				cout << "Enter file name: ";
				delete[] m_filename;
				m_filename = nullptr;
				if (load()) {
					cout << m_NumofItems << " records loaded!" << endl;
				}
				cout << endl;
				break;
			default:
				cout << "Exiting Program!" << endl;
				break;
			}
		} while (result != 0);

		save();
	}

	// saves data into the file 
	void AidMan::save()
	{
		if (m_filename != nullptr)
		{
			ofstream file(m_filename);
			for (int i = 0; i < m_NumofItems; i++) {
				m_iProd[i]->save(file) << endl;
			}
		}
	}

	// deallocates all the pointers in the array
	void AidMan::deallocate()
	{
		for (int i = 0; i < m_NumofItems; i++) {
			delete m_iProd[i];
			m_iProd[i] = nullptr;
		}
		delete[] m_filename;
		m_filename = nullptr;
		m_NumofItems = 0;
	}

	bool AidMan::load()
	{
		save();
		deallocate();
		bool loaded = false;
		ifstream ifstr;
		char ch;
		cin.ignore(1000, '\n');
		ch = std::cin.peek();
		delete[] m_filename;
		if (ch != '\n')
		{
			char filename[50];
			cin.get(filename, 50, '\n'); // reads the instructions
			ut.alocpy(m_filename, filename);
		}
		else {
			m_filename = nullptr;
		}
		ifstr.open(m_filename, ifstream::in);
		if (!ifstr.is_open()) {
			cout << "Failed to open " << m_filename << " for reading!" << endl;
			ifstr.close();
			cout << "Would you like to create a new data file?" << endl;
			cout << "1- Yes!" << endl;
			cout << "0- Exit" << endl;
			int option = 0;
			option = ut.getint("> ");
			if (option == 1) {
				ifstr.open(m_filename, std::ifstream::out);
				ifstr.close();
			}
			else {
				delete[] m_filename;
				m_filename = nullptr;
			}
		}
		else {
			do {
				char ch;
				ch = ifstr.peek();
				if (ch == '1' || ch == '2' || ch == '3') { // perishable
					delete[] m_iProd[m_NumofItems];
					m_iProd[m_NumofItems] = new Perishable;
				}
				else if (ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9') {//regular item
					delete[] m_iProd[m_NumofItems];
					m_iProd[m_NumofItems] = new Item;
				}
				else {
					ifstr.setstate(ios::failbit);
				}

				if (ifstr) {
					m_iProd[m_NumofItems]->load(ifstr);
					if (m_iProd[m_NumofItems]) {
						loaded = true;
						m_NumofItems++;
					}
					else {
						delete m_iProd[m_NumofItems];
					}
				}
			} while (!ifstr.eof());

			//for (int i = 0; i < sdds_max_num_items; i++)
			//{
			//	ch = ifstr.peek();

			//	if (ch == '1' || ch == '2' || ch == '3')
			//	{
			//		m_iProd[i] = new Perishable;
			//	}
			//	else if (ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')
			//	{
			//		m_iProd[i] = new Item;
			//	}
			//	else
			//	{
			//		ifstr.setstate(ios::failbit);
			//	}

			//	if (ifstr)
			//	{
			//		m_iProd[i]->load(ifstr);

			//		if (m_iProd[i])
			//		{
			//			loaded = true;
			//			m_NumofItems++;
			//			//ifstr.ignore(2000, '\n');
			//		}
			//		else
			//		{
			//			delete m_iProd[i];
			//		}
			//	}


			//}
			//ifstr.clear();
			//ifstr.close();
		}

		return loaded;
	}

	int AidMan::list(const char* sub_desc)
	{
		int result = 0;
		if (m_iProd)
		{
			if (sub_desc == nullptr) {
				cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
				cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
				for (int i = 0; i < m_NumofItems; i++) {
					m_iProd[i]->linear(true);
					cout << setfill(' ');
					cout.width(4);
					cout << i + 1 << " | ";
					cout << *m_iProd[i] << endl;
					result = i;
				}
				cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
				result++; // index starts from 0 so add one to get the actual length
			}
			else {
				bool once = true;
				for (int i = 0; i < m_NumofItems; i++) {
					if (*m_iProd[i] == sub_desc) {
						if (once) {
							cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
							cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
							once = false;
						}
						m_iProd[i]->linear(true);
						cout << setfill(' ');
						cout.width(4);
						cout << i + 1 << " | ";
						cout << *m_iProd[i] << endl;
						result++;
					}
				}
				if (result > 0) {
					cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
				}
			}
		}
		else {
			result = 0;
		}
		return result;
	}

	int AidMan::search(int sku) const {
		bool found = false;
		int result = -1;
		for (int i = 0; i < m_NumofItems && !found; i++) {
			if (*m_iProd[i] == sku) {
				found = true;
				result = i;
			}
		}
		return result;
	}

	void AidMan::remove(int index)
	{
		if (index >= 0 && index <= m_NumofItems)
		{
			delete m_iProd[index];
			m_iProd[index] = nullptr;

			for (int i = index; i < m_NumofItems; i++) {
				m_iProd[i] = m_iProd[i + 1];
			}
			m_NumofItems--;
		}
	}

	void AidMan::ShipOption()
	{
		int num_removed = 0;
		ofstream file("shippingOrder.txt");
		Date date;
		file << "Shipping Order, Date: " << date << endl;
		file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		for (int i = 0; i < m_NumofItems; i++) {
			if (m_iProd[i]->qty() == m_iProd[i]->qtyNeeded()) {
				m_iProd[i]->linear(true);
				file << setfill(' ');
				file.width(4);
				file << num_removed + 1 << " | ";
				file << *m_iProd[i] << endl;
				remove(i);
				i--;
				num_removed++;
			}
		}
		file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		cout << "Shipping Order for " << num_removed << " times saved!" << endl;
	}
}