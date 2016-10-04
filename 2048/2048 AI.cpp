// 2048 AI.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "Board.h"
#include "Game.h"
#include<iostream>
#include<iomanip>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	MakeMoveTable();

	srand(time(NULL));
	FILE * result;
	
	errno_t err;
	
	if ((err = fopen_s(&result, "result.txt", "w+")) != 0)
		printf("The file 'result.txt' was not opened\n");
	else
		printf("The file 'result.txt' was opened\n");
	
	double start;
	double end;
	int best_result = 0 ;
	unsigned long long int best_state = 0;
	start = clock();
	Record record;
	
	Read_Record(record);
	
	const int Round = 5000;
	for (int i = 0; i < Round; i++){
		
		if(i % (Round / 10) == 0 )
			printf("%d \n", i);
		
		Board board;
		int times_count[4] = { 0, 0, 0, 0 };
		int score = 0 ;

		while (board.isFull() == false){

			Board Current_Board;
			Board Current_Board_Moved;
			Board Next_Board;

			Current_Board.setState(board);
			int Action = FindBestAction(Current_Board, record);
			int award = 0;
			Current_Board_Moved.setState(Current_Board);
			Move(Action, Current_Board_Moved, award);
			Next_Board.setState(Current_Board_Moved);
			Next_Board.addRandomNumber();
			Learn_Evaluation(Current_Board, Action, award, Current_Board_Moved, Next_Board, record);
			score += award;
			board.setState(Next_Board);

			times_count[Action - 1]++;
		}
		
		fprintf(result, " %d \n", score);
		//system("pause");
		/*for (int l = 0; l < 4; l++)printf(" %d ", times_count[l]);
		printf("\n");*/
		if(best_result < score){
			best_result = score;
			best_state = board.getState();
		}
	}
	

	if (result)	{
		if (fclose(result))	{
			printf("The file 'result.txt' was not closed\n");
		}
	}

	Write_Record(record);
	end = clock();
	double finish;
	finish = ( end - start ) / CLOCKS_PER_SEC;
	printf("the time is %f \n And the best result is %d \n", finish, best_result);
	printf("the best state is: \n");
	Board best_board;
	best_board.setState(best_state);
	best_board.Print();
	system("pause");
	return 0;
}

