#include "stdafx.h"
#include"Board.h"

Board::Board()
{
	iBoardSize = 4;
	iState = 0x000000000000000;
}

Board::~Board(){

}
unsigned long long int Board::getState(){
	return iState;
}
unsigned long long int Board::getState(int index){
	if (index < 0 || index > 15) { return NULL; }
	else {
		return (iState >> (index * 4) ) & 0xf;
	}
}
void Board::setState(unsigned long long int state){
	iState = state; 
}
void Board::setState(unsigned long long int state, int index){
	assert( index >= 0 && index < 16 && state >= 0 && state <= 15);
	iState = iState + ( (-1 * getState(index) + state) << 4 * index );
}
void Board::setState(Board b){
	iState = b.getState();
}
void Board::swap(int index1, int index2)
{
	unsigned long long int tmpstate1;
	unsigned long long int tmpstate2;
	tmpstate1 = getState(index1); 
	tmpstate2 = getState(index2);
	setState(tmpstate1, index2);
	setState(tmpstate2, index1);
}

void Board::addRandomNumber(){
	int nZeroNumber = 0;
	int iRandPosition;
	
	for (int i = 0; i < iBoardSize * iBoardSize ; i++){
		if (getState(i) == 0) nZeroNumber++;
	}
	if (nZeroNumber == 0){
		printf("the board is full, game over!");
		exit(1);
	}
	iRandPosition = rand() % nZeroNumber;
	for (int i = 0; i < iBoardSize * iBoardSize; i++){
		if (iRandPosition == 0 && getState(i) == 0){
			if (rand() % 10 == 0)
				setState(2, i);
			else
				setState(1, i);
			return;
		}
		if (getState(i) == 0) iRandPosition--;
	}
}

void Board::Print(){	
	for (int i = 0; i < 16; i++){
		printf("  %d  ", getState(i));
		if (i % 4 == 3) printf("\n");
	}	
	printf("\n");
}

bool Board::isFull(){
	
	for (int i = 0; i < 16; i++){
		if (getState(i) == 0) return false;
	}
	return true;
}


