#include "stdafx.h"
#include"Board.h"
#include"time.h"
#include"stdlib.h"
#include"stdio.h"
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
		unsigned long long int basenumber = 1;
		for (int i = 0; i< index; i++){ basenumber *= 16; }
		return (iState / basenumber) % 16;
	}
}
void Board::setState(unsigned long long int state){
	iState = state; 
}
void Board::setState(unsigned long long int state, int index){
	if (index > 15 || index < 0 || state < 0 || state > 15) { return; }
	else{
		unsigned long long int basenumber = 1;
		for (int i = 0; i< index; i++) basenumber *= 16;
		iState = iState + (-1 * getState(index) + state) * basenumber;
	}
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
//void Board::MoveUp(){
//	for (int i = 0; i < 3; i++) Rotate();
//	MoveLeft();
//	Rotate();
//}
//void Board::MoveDown(){
//	Rotate();
//	MoveLeft();
//	for (int i = 0; i < 3; i++)	Rotate();
//}
//void Board::MoveLeft(){
//
//}
//void Board::MoveRight(){
//	for (int i = 0; i < 2; i++) Rotate();
//	MoveLeft();
//	for (int i = 0; i < 2; i++) Rotate();
//}
void Board::Rotate(){
	swap(0, 3);
	swap(0, 15);
	swap(0, 12);
	swap(1, 7);
	swap(1, 14);
	swap(1, 8);
	swap(2, 11);
	swap(2, 13);
	swap(2, 4);
	swap(5, 6);
	swap(5, 10);
	swap(5, 9);
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

//void Board::Move(int action){
//	if (action == MOVEDOWN){
//		MoveDown();
//	}
//	else if (action == MOVEUP){
//		MoveUp();
//	}
//	else if (action == MOVERIGHT){
//		MoveRight();
//	}
//	else if (action == MOVELEFT){
//		MoveLeft();
//	}
//	else {
//		exit(1);
//	}
//}
//
