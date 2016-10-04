#include "stdafx.h"
#include "Record_4tile.h"

Record_4tile::Record_4tile()
{
	
}

Record_4tile::Record_4tile(int t1, int t2, int t3, int t4)
{
	itile_number = 4;
	ptile = new int[itile_number];
	ptile[0] = t1;
	ptile[1] = t2;
	ptile[2] = t3;
	ptile[3] = t4;
	for (int i = 0; i < itile_number; i++)
		assert(ptile[i] >= 0 && ptile[i] < 16);
	for (int i = 0 ; i< iUpperBound*iUpperBound*iUpperBound*iUpperBound ; i++)
		Data[i] = 0;
}


Record_4tile::~Record_4tile()
{
	for (int i = 0 ; i< iUpperBound*iUpperBound*iUpperBound*iUpperBound ; i++)
		Data[i] = 0;
	for (int i = 0; i < itile_number; i++)
		ptile[i] = 0;
}

void Record_4tile::setData(Board b, double score){
	int index1 = b.getState(ptile[0]);
	int index2 = b.getState(ptile[1]);
	int index3 = b.getState(ptile[2]);
	int index4 = b.getState(ptile[3]);
	int index = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	Data[index] = score;
}
void Record_4tile::setData(int *index, double score){
	int position = index[0] + index[1]*iUpperBound + index[2] * iUpperBound * iUpperBound + index[3] * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = score;
}

double Record_4tile::getData(int * index){
	int position = index[0] + index[1]*iUpperBound + index[2] * iUpperBound * iUpperBound + index[3] * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];
}

double Record_4tile::getData(Board b){
	int index1 = b.getState(ptile[0]);
	int index2 = b.getState(ptile[1]);
	int index3 = b.getState(ptile[2]);
	int index4 = b.getState(ptile[3]);
	int index = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	return Data[index];
}

int Record_4tile::gettile(int index)
{
	assert(index >= 0 && index <= 3);
	return ptile[index];
	
}

