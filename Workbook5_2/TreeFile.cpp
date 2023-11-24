#include "TreeFile.h"


#include "FileOperations.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int chooseInd(Node* found, int key)
{
	if (found->lowerKey == key) return found->lowerBinIndex;
	else return found->greaterBinIndex;
}

int TreeFile::findRace(string bin_name, int key)
{
	Node* found = root->searchElem(key);

	if (found == nullptr) return -1;


	obj.print_by_indx_bin(bin_name, chooseInd(found, key));
	return 0;
}

int TreeFile::createStruct(string txt_name, string bin_name)
{
	Node* buffer;
	ifstream txt_file;
	fstream bin_file;

	bin_file.open(bin_name, ios::binary | ios::out);

	Airport flight;
	txt_file.open(txt_name);
	int res = 0;
	int* pres = &res;
	while (!txt_file.eof())
	{
		txt_file >> flight.flight_num;
		txt_file >> flight.settlement_from;
		txt_file >> flight.land_date;
		txt_file >> flight.land_time;
		txt_file >> flight.delay;

		buffer = root->addElem(stoi(flight.flight_num), obj.length, pres);
		if (buffer != nullptr) root = buffer;

		obj.add_note(bin_file, flight);
	}
	cout << *pres;
	bin_file.close();
	txt_file.close();

	return 0;
}

int TreeFile::removeRace(string bin_name, int key)
{
	Node* buffer;
	Node* found = root->searchElem(key);
	if (found == nullptr)
	{
		return -1;
	}

	obj.remove_note(bin_name, chooseInd(found, key));
	buffer = root->removeElem(key);

	if (buffer != nullptr) root = buffer;
	return 0;
}

