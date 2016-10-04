#include "stdafx.h"
#include "Record_6tile.h"

Record_6tile::Record_6tile()
{

}

Record_6tile::Record_6tile(int t1, int t2, int t3, int t4, int t5, int t6)
{
	itile_number = 6;
	ptile = new int[itile_number];
	ptile[0] = t1;
	ptile[1] = t2;
	ptile[2] = t3;
	ptile[3] = t4;
	ptile[4] = t5;
	ptile[5] = t6;
	for (int i = 0; i < itile_number; i++)
		assert(ptile[i] >= 0 && ptile[i] < 16);

	
}


Record_6tile::~Record_6tile()
{
	
	for (int i = 0; i < itile_number; i++)
		ptile[i] = 0;
}

void Record_6tile::setData(Board b, double score){
	int index1 = (int)b.getState(ptile[0]);
	int index2 = (int)b.getState(ptile[1]);
	int index3 = (int)b.getState(ptile[2]);
	int index4 = (int)b.getState(ptile[3]);
	int index5 = (int)b.getState(ptile[4]);
	int index6 = (int)b.getState(ptile[5]);
	int index = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	index += index5 * iUpperBound * iUpperBound * iUpperBound * iUpperBound + index6 * iUpperBound * iUpperBound * iUpperBound * iUpperBound * iUpperBound;
	Data[index] = score;
}
void Record_6tile::setData(int *index, double score){
	int position = index[0] + index[1]*iUpperBound + index[2] * iUpperBound * iUpperBound + index[3] * iUpperBound * iUpperBound * iUpperBound;
	position += index[4] * iUpperBound * iUpperBound * iUpperBound * iUpperBound + index[5] * iUpperBound * iUpperBound * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = score;
}

double Record_6tile::getData(int *index){
	int position = index[0] + index[1]*iUpperBound + index[2] * iUpperBound * iUpperBound + index[3] * iUpperBound * iUpperBound * iUpperBound;
	position += index[4] * iUpperBound * iUpperBound * iUpperBound * iUpperBound + index[5] * iUpperBound * iUpperBound * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];
}

double Record_6tile::getData(Board b){
	int index1 = (int)b.getState(ptile[0]);
	int index2 = (int)b.getState(ptile[1]);
	int index3 = (int)b.getState(ptile[2]);
	int index4 = (int)b.getState(ptile[3]);
	int index5 = (int)b.getState(ptile[4]);
	int index6 = (int)b.getState(ptile[5]);
	int index = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	index += index5 * iUpperBound * iUpperBound * iUpperBound * iUpperBound + index6 * iUpperBound * iUpperBound * iUpperBound * iUpperBound * iUpperBound;
	return Data[index];
}

int Record_6tile::gettile(int index)
{
	assert(index >= 0 && index <= 5);
	return ptile[index];

}

