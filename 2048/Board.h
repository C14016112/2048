#ifndef BOARD_H
#define BOARD_H

#include "stdio.h"
#include "stdlib.h"


#define MOVEUP 1
#define MOVERIGHT 2
#define MOVEDOWN 3
#define MOVELEFT 4

class Board{

private:
	unsigned long long int iState;
	int iBoardSize;

public :
	Board();
	~Board();
	/*
	return all board
	*/
	unsigned long long int getState();
	/*
	return the value of the state on the index
	*/
	unsigned long long int getState(int index);
	/*
	change all board to the state
	*/
	void setState(unsigned long long int);
	/*
	change the number on index to the number "state"
	*/
	void setState(unsigned long long int state, int index);
	void setState(Board);
	void swap(int, int);

	void Rotate();
	void addRandomNumber();
	
	void Print();
	bool isFull();
	
};


#endif