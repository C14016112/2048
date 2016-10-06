#include "stdafx.h"
#include "Record_4tile_Outside.h"

Record_4tile_Outside::Record_4tile_Outside()
{
	for (int i = 0 ;i < 4 ; i++){
		index[0][i] = i;
		index[1][i] = 15 - i;
		index[2][i] = 12 - 4 * i;
		index[3][i] = 4 * i + 3;
		index[4][i] = 3 - i;
		index[5][i] = 4 * i;
		index[6][i] = 12 + i;
		index[7][i] = 15 - 4 * i;
	}
	for (int i = 0 ; i< 16 * 16 * 16 * 16; i++){
		Data[i] = 0;
	}
	iUpperBound = 16;
	
}

Record_4tile_Outside::~Record_4tile_Outside()
{
}

void Record_4tile_Outside::setScore(int inputindex[4], double score){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = score;
}

double Record_4tile_Outside::getScore(int inputindex[4]){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];
}

double Record_4tile_Outside::getScore(Board b){
	double value = 0;
	for (int i = 0 ; i< 8 ; i++){
		int index1 = b.getState(index[i][0]);
		int index2 = b.getState(index[i][1]);
		int index3 = b.getState(index[i][2]);
		int index4 = b.getState(index[i][3]);
		int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
		value = value + Data[position];
	}
	return value;
}


double Record_4tile_Outside::get_OneFeature_Score(Board b, int no)
{
	assert(no >= 0 && no < 8);
	int index1 = b.getState(index[no][0]);
	int index2 = b.getState(index[no][1]);
	int index3 = b.getState(index[no][2]);
	int index4 = b.getState(index[no][3]);
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];
	
}

void Record_4tile_Outside::set_OneFeature_Score(Board b, int no, double value)
{
	assert(no >= 0 && no < 8);
	int index1 = b.getState(index[no][0]);
	int index2 = b.getState(index[no][1]);
	int index3 = b.getState(index[no][2]);
	int index4 = b.getState(index[no][3]);
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = value;

}

