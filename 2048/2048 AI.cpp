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
	
	errno_t err;
	
	if ((err = fopen_s(&result, "result.txt", "w+")) != 0)
		printf("The file 'result.txt' was not opened\n");
	else
		printf("The file 'result.txt' was opened\n");
	
	double start;
	double end;
	int best_result = 0 ;
	unsigned long long int best_state = 0;
	double averagescore = 0 ;
	start = clock();
	//Record record;
	
	//Read_Record(record);
	

	const int Round = 500;
	for (int i = 0; i < Round; i++){
		
		/*if(i % (Round / 10) == 0 )
			printf("%d \n", i);*/
		
		Board board;
		
		int score = 0 ;

		bool isEnd = false;
		while (isEnd == false){

			Board Current_Board;
			Board Current_Board_Moved;
			Board Next_Board;

			Current_Board.setState(board);
			int Action = FindBestAction(Current_Board);
			system("pause");
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
		
			// the following is the random game, using to test the time and effect of AI
			/*if(board.isFull() == true){
				isEnd = true;
			}
			else{
				board.addRandomNumber();
				int award = 0;
				Move(rand() % 4 + 1, board, award);
				score += award;

			}*/
			Current_Board.Print();
			printf("Action = %d \n", Action);
			Current_Board_Moved.Print();
		}
		
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
	printf("the time is %f \n And the best result is %d \n", finish, best_result);
	printf("the average score is %f \n", averagescore);
	printf("the best state is: \n");
	Board best_board;
	best_board.setState(best_state);
	best_board.Print();
	system("pause");
	return 0;
}

