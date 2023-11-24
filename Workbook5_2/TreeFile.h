#pragma once
#ifndef TREEFILE
#define TREEFILE

#include "FileOperations.h"
#include "SearchTree.h"

struct TreeFile
{
	FileOperations obj;
	Node* root = new Node(-1, -1);
	fstream bin_file;


	int createStruct(string txt_name, string bin_name);
	int removeRace(string bin_name, int key);
	int findRace(string bin_name, int key);
};


#endif