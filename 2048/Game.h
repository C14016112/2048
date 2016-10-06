#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "assert.h"
#include "Record_4tile_Outside.h"
#include "Record_4tile_Inside.h"
//#include "Record.h"

#define LEARNING_RATE 0.0025

double Evaluate(Board board, int action);
int FindBestAction(Board b);
void Learn_Evaluation(Board b1, int action, int score, Board b1_moved, Board b2);
void Write_Record();
//void Learn_Evaluation(stack<State>, Record &, Game game);
void Read_Record();
void MakeMoveTable();
void GetDataFromMoveTable(int i, int j, int k, int l, int index[5]);
void MoveLeft(Board & CurrentBoard, int & award);
void MoveUp(Board & CurrentBoard_AfterMove, int & award);
void MoveDown(Board & CurrentBoard_AfterMove, int & award);
void MoveRight(Board & CurrentBoard_AfterMove, int & award);
void Move(int, Board & CurrentBoard_AfterMove, int & award);
#endif