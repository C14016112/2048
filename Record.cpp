#include "stdafx.h"
#include "Record.h"

Record::Record(){
	//ntablenumber = 14;
	//record_table = new Record_N_tile *[ntablenumber];
	//record_table[0] = new Record_4tile(2, 6, 10, 14);
	//record_table[1] = new Record_4tile(3, 7, 11, 15);
	//record_table[2] = new Record_4tile(0, 4, 8, 12);
	//record_table[3] = new Record_4tile(1, 5, 9, 13);
	//for (int i = 0; i < 4; i++){
	//	int first = 4 * i;
	//	record_table[4 + i] = new Record_4tile(first, first + 1, first + 2, first + 3);
	//}
	//for (int i = 0; i < 3; i++){
	//	record_table[8 + i] = new Record_6tile(i, i + 1, i + 4, i + 5, i + 8, i + 9);
	//}
	//for (int i = 0; i < 3; i++){
	//	record_table[11 + i] = new Record_6tile(i + 4, i + 5, i + 8, i + 9, i + 12, i + 13);
	//}
	ntablenumber = 9;
	nfour_tile_tablenumber = 9;
	record_table = new Record_N_tile *[ntablenumber];
	for (int i = 0 ; i< 3 ; i++){
		for (int j = 0 ; j< 3; j ++){
			record_table[i * 3 + j ] = new Record_4tile( i + j * 4, i + j * 4 + 1, i + j * 4 + 4, i + j * 4 + 5 );
		}
	}
}

Record::~Record(){
	for (int i = 0; i < ntablenumber; i++){
		delete record_table[i];
	}
	delete record_table;
}

double Record::getData(Board b)
{
	double value = 0;
	for (int i = 0; i < ntablenumber; i++){
		value += record_table[i]->getData(b);
	}
	return value;
}
double Record::getData(int * index){
	double value = 0;
	for (int i = 0; i < ntablenumber; i++){
		value += record_table[i]->getData(index);
	}
	return value;
}

double Record::get_onetable_data(int tablenumber, int *index){
	return record_table[tablenumber - 1]->getData(index);
}

double Record::get_onetable_data(int tablenumber, Board b){
	return record_table[tablenumber - 1]->getData(b);
}

void Record::setData(Board b, double value)
{
	for (int i = 0; i < ntablenumber; i++){
		record_table[i]->setData(b, value);
	}
}

void Record::set_onetable_Data(int tablenumber, Board b, double value)
{
	record_table[tablenumber - 1]->setData(b, value);
}

void Record::set_onetable_Data(int tablenumber, int * index, double value)
{
	return record_table[tablenumber - 1]->setData(index, value);
}