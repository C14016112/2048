#ifndef RECORD_N_TILE_H
#define RECORD_N_TILE_H
#include "assert.h"
#include "Board.h"

#pragma once
class Record_N_tile
{
public:
	Record_N_tile();
	~Record_N_tile();

	/*
	The constructor need the index of tiles
	Since this record use four tile, it needs 4 integers to input
	*/
	virtual void setData(int * index, double score);
	virtual void setData(Board b, double score);
	/*
	get the data at one position
	*/
	virtual double getData(int * index);
	/*
	get the corresopnding data if giving a board
	*/
	virtual double getData(Board);
	virtual int gettile(int);
	//void operator=(Record_4tile R);
protected:
	int iUpperBound;
	int itile_number;
	/*
	The index of tiles
	*/
	int *ptile;
};

#endif