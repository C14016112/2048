// 2048 AI.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "Board.h"
#include "Record_4tile_Outside.h"
#include "Record_4tile_Inside.h"
#include "Game.h"
#include<iostream>
#include<iomanip>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	MakeMoveTable();

	srand(time(NULL));
	FILE * result;
	FILE * log;
	
	errno_t err;
	errno_t err2;
	
	if ((err = fopen_s(&result, "result.txt", "w+")) != 0)
		printf("The file 'result.txt' was not opened\n");
	else
		printf("The file 'result.txt' was opened\n");

	if ((err2 = fopen_s(&log, "log.txt", "a+")) != 0)
		printf("The file 'log.txt' was not opened\n");
	else
		printf("The file 'log.txt' was opened\n");
	
	double start;
	double end;
	int best_result = 0 ;
	unsigned long long int best_state = 0;
	double averagescore = 0 ;
	start = clock();
	int movecount = 0;

	const int Round = 1000;
	for (int i = 0; i < Round; i++){
		
		if(i % (Round / 10) == 0 )
			printf("%d \n", i);
		
		Board board;
		board.addRandomNumber();
		board.addRandomNumber();
		int score = 0 ;

		bool isEnd = false;
		while (isEnd == false){

			Board Current_Board;
			Board Current_Board_Moved;
			Board Next_Board;

			Current_Board.setState(board);
			int Action = FindBestAction(Current_Board);
			int award = 0;
			Current_Board_Moved.setState(Current_Board);
			Move(Action, Current_Board_Moved, award);
			score += award;
			Next_Board.setState(Current_Board_Moved);

			if(Next_Board.isFull() == false){
				Next_Board.addRandomNumber();
				Learn_Evaluation(Current_Board, Action, award, Current_Board_Moved, Next_Board);
				board.setState(Next_Board);
			}
			else {	isEnd = true;}
			movecount++;
		
		}
		if( i % (Round / 1000) == 0)
			fprintf(result, " %d \n", score);

		if(best_result < score){
			best_result = score;
			best_state = board.getState();
		}
		averagescore = averagescore + score;
	}
	

	if (result)	{
		if (fclose(result))	{
			printf("The file 'result.txt' was not closed\n");
		}
	}
	averagescore = averagescore / Round;
	Write_Record();

	end = clock();
	double finish;
	finish = ( end - start ) / CLOCKS_PER_SEC;
	fprintf_s(log, "\n");
	fprintf_s(log, "Round =  %d\n", Round);
	fprintf_s(log, "Move count is %d \n", movecount);
	fprintf_s(log, "the time is %f \n And the best result is %d \n", finish, best_result);
	fprintf_s(log, "Move count per sec = %f move/sec \n", movecount / finish );
	fprintf_s(log, "the average score is %f \n", averagescore);
	fprintf_s(log, "the best state is: \n");
	Board best_board;
	best_board.setState(best_state);
	for (int i = 0 ; i< 16 ; i++){
		fprintf_s(log, " %d ", best_board.getState(i));
		if(i % 4 == 3)
			fprintf_s(log, "\n");
	}
	fprintf_s(log, "\n");
	system("pause");
	return 0;
}

