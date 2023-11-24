#include "FileOperations.h"
#include <iostream>

using namespace std;


int FileOperations::create_bin(string txt_name, string bin_name)
{
    txt_file.open(txt_name, ios::in);
    if (!txt_file) return 1;

    bin_file.open(bin_name, ios::binary | ios::out);
    Airport flight;

    while (!txt_file.eof())
    {
        txt_file >> flight.flight_num;
        txt_file >> flight.settlement_from;
        txt_file >> flight.land_date;
        txt_file >> flight.land_time;
        txt_file >> flight.delay;

        length++;

        bin_file.write((char*)&flight, sizeof(flight));
    }

    txt_file.close();
    bin_file.close();

    return 0;
}

int FileOperations::add_note(fstream& bin_file, Airport flight)
{
    bin_file.seekp(length * sizeof(Airport));
    bin_file.write((char*)&flight, sizeof(flight));
    length++;

    return 0;

}


int FileOperations::print_by_indx_bin(string bin_name, int indx)
{
    bin_file.open(bin_name, ios::in | ios::binary);
    if (!bin_file) return 1;

    Airport flight;

    bin_file.seekg(indx * sizeof(Airport));
    bin_file.read((char*)&flight, sizeof(flight));

    cout << flight.flight_num << endl << flight.settlement_from << endl << flight.land_date << endl << flight.land_time << endl << flight.delay << endl;
    bin_file.close();
    return 0;
}

int FileOperations::remove_note(string bin_name, int indx)
{
    Airport note;

    if (indx >= length)
    {
        return 2;
    }

    bin_file.open(bin_name, ios::in | ios::binary | ios::out);
    if (!bin_file) return 1;

    bin_file.seekg((length - 1) * sizeof(Airport), ios::beg);
    bin_file.read((char*)&note, sizeof(Airport));

    bin_file.seekp(indx * sizeof(Airport), ios::beg);
    bin_file.write((char*)&note, sizeof(Airport));

    fstream temporary_file;
    temporary_file.open("temporary.bin", ios::binary | ios::out);

    bin_file.seekg(0);
    length--;
    for (int i = 0; i < length; i++)
    {
        bin_file.read((char*)&note, sizeof(note));
        temporary_file.write((char*)&note, sizeof(note));
    }

    bin_file.close();
    temporary_file.close();

    remove(bin_name.c_str());
    rename("temporary.bin", bin_name.c_str());

    return 0;
}
