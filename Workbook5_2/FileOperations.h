#pragma once
#ifndef FILEOPERATIONS
#define FILEOPERATIONS

#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Airport
{
	char settlement_from[20];
	char flight_num[7];
	char land_date[11];
	char land_time[6];
	char delay[3];
};


struct FileOperations
{
	fstream txt_file, bin_file;
	int length = 0;

	int create_bin(string txt_name, string bin_name);
	int add_note(fstream& bin_file, Airport flight);
	int remove_note(string bin_name, int indx);
	int print_by_indx_bin(string bin_name, int indx);
};


#endif