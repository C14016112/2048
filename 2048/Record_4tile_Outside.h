#ifndef RECORD_4_TILE_OUTSIDE_H
#define RECORD_4_TILE_OUTSIDE_H
#pragma once
#include "Board.h"
#include "assert.h"
/*
Class that save the data of strategy, only deal with four tiles one time

*/
class Record_4tile_Outside
{
public:
	/*
	The constructor need the index of tiles
	Since this record use four tile, it needs 4 integers to input
	*/
	Record_4tile_Outside();
	~Record_4tile_Outside();
	void setScore(int index[4], double score);
	void setScore(Board b, double score);
	/*
	get the data at one position
	*/
	double getScore(int index[4]);
	/*
	get the corresopnding data if giving a board
	*/
	double getScore(Board);
	double get_OneFeature_Score(Board b, int no);
	void set_OneFeature_Score(Board b, int no, double value);
private:
	double Data[16*16*16*16] ;
	int index[8][4];
	int iUpperBound;
};

#endif