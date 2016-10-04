#ifndef RECORD_H
#define RECORD_H

#include "Record_4tile.h"
#include "Record_6tile.h"
#pragma once
class Record
{
public:
	Record();
	~Record();
	double getData(Board b);
	double getData(int * index);
	double get_onetable_data(int tablenumber, int * index);
	double get_onetable_data(int tablenumber, Board b);
	void setData(Board b, double value);
	void set_onetable_Data(int tablenumber, Board b, double value);
	void set_onetable_Data(int tablenumber, int * index, double value);
	int get_tablenumber(){ return ntablenumber; }
	int get_four_tile_tablenumber(){ return nfour_tile_tablenumber; }
	
private:
	int ntablenumber;
	int nfour_tile_tablenumber;
	Record_N_tile **record_table;
};

#endif