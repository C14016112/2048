#ifndef RECORD_4_TILE_H
#define RECORD_4_TILE_H
#include "Record_N_tile.h"
#pragma once

/*
Class that save the data of strategy, only deal with four tiles one time

*/
class Record_4tile : public Record_N_tile
{
public:
	/*
	The constructor need the index of tiles
	Since this record use four tile, it needs 4 integers to input
	*/
	Record_4tile::Record_4tile();
	Record_4tile(int, int, int, int);
	~Record_4tile();
	void setData(int * index, double score);
	void setData(Board b, double score);
	/*
	get the data at one position
	*/
	double getData(int * index);
	/*
	get the corresopnding data if giving a board
	*/
	double getData(Board);
	int gettile(int);
private:
	double Data[16*16*16*16] ;
};

#endif