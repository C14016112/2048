#include "stdafx.h"
#include "Game.h"

int Move_Table[16*16*16*16*5] = {};
Record_4tile_Inside record1;
Record_4tile_Outside record2;

double Evaluate(Board board, int action)
{
	// evaluate action 
	int award = 0;
	Move(action, board, award);
	return record1.getScore(board) + record2.getScore(board);
	//return record.getScore(board);
}


int FindBestAction(Board b)
{
	double value[4];
	int next_action = 1;
	Board next_board;
	int award = 0;

	for (int i = 1; i <= 4; i++){
		value[i - 1] = Evaluate(b, i);
	}
	if (value[0] == value[1] && value[0] == value[2] && value[0] == value[3] ){
		next_action = rand() % 4 + 1;
	}
	else{
		for (int i = 2; i <= 4; i++){
			if (value[i - 1] > value[next_action - 1]){
				next_action = i;
			}
		}
	}
	
	//check that the state after action is different
	// if not, trying to find anther action
	next_board.setState(b.getState());
	Move(next_action, next_board, award);

	while(next_board.getState() == b.getState() && b.isFull() == false){
		next_action = next_action % 4 + 1;
		next_board.setState(b.getState());
		Move(next_action, next_board, award);
	}
	
	assert(next_action >= 1 && next_action <= 4);

	return next_action;
}

void Learn_Evaluation(Board b1, int action, int score, Board b1_moved, Board b2)
{
	int next_action = 1;
	next_action = FindBestAction(b2);

	/*
	COMPUTE AFTERSTATE( s'', a_next)
	*/
	int tmpaward = 0; // r_next
	Board b2_moved; // s'_next
	b2_moved.setState(b2);
	Move(next_action, b2_moved, tmpaward);
	
	double next_value = 0;
	double now_value = 0;
	double delta = 0;
	now_value = record1.getScore(b1_moved) + record2.getScore(b1_moved);
	if (b2.isFull() == true){
		delta = LEARNING_RATE * now_value * -1;
	}
	else{
		next_value = record1.getScore(b2_moved) + record2.getScore(b2_moved);
		delta = LEARNING_RATE * ((double)tmpaward + next_value - now_value);
	}
		
	for (int i = 0; i < 8; i++){
		double new_value = record1.get_OneFeature_Score(b1_moved, i) + delta ;
		record1.set_OneFeature_Score(b1_moved, i, new_value);
	}
	for (int i = 0; i < 8; i++){
		double new_value = record2.get_OneFeature_Score(b1_moved, i) + delta;
		record2.set_OneFeature_Score(b1_moved, i, new_value);
	}
}

void Write_Record()
{
	int tablenumber = 1;
	for (int m = 1; m <= tablenumber; m++){
		FILE * data;
		errno_t err;
		char name[30] = "data_record";
		char number[20];
		sprintf_s(number, "%d", m);
		strcat_s(name, number);
		char name2[] = ".txt";
		strcat_s(name, name2);

		if ((err = fopen_s(&data, name, "w+")) != 0)
			printf("The file '%s' was not opened\n", name);
		else
			printf("The file '%s' was opened\n", name);

		for (int i = 0; i < 16; i++){
			for (int j = 0; j < 16; j++){
				for (int k = 0; k < 16; k++){
					for (int l = 0; l < 16; l++){
						int index[4] = { i, j, k, l };
						fprintf(data, "%lf \n", record1.getScore(index));
					}
				}
			}
		}
		
		if (data)
		{
			if (fclose(data))
			{
				printf("The file '%s' was not closed\n", name);
			}
		}
	}

}

//void Read_Record(Record & record)
//{
//	int tablenumber = record.get_tablenumber();
//	for (int m = 1; m <= tablenumber; m++){
//		FILE * data;
//		errno_t err;
//		char name[30] = "data_record";
//		char number[20];
//		sprintf_s(number, "%d", m);
//		strcat_s(name, number);
//		char name2[] = ".txt";
//		strcat_s(name, name2);
//
//		if ((err = fopen_s(&data, name, "r")) != 0)
//			printf("The file '%s' was not opened\n", name);
//		else
//			printf("The file '%s' was opened\n", name);
//		if (m <= record.get_four_tile_tablenumber()){
//			for (int i = 0; i < 16; i++){
//				for (int j = 0; j < 16; j++){
//					for (int k = 0; k < 16; k++){
//						for (int l = 0; l < 16; l++){
//							double value = 0;
//							fscanf_s(data, "%lf", &value);
//							int index[4] = { i, j, k, l };
//							record.set_onetable_Data(m, index, value);
//						}
//					}
//				}
//			}
//		}
//		else{
//			for (int i = 0; i < 16; i++){
//				for (int j = 0; j < 16; j++){
//					for (int k = 0; k < 16; k++){
//						for (int l = 0; l < 16; l++){
//							for (int level5 = 0; level5 < 16; level5++){
//								for (int level6 = 0; level6 < 16; level6++){
//									double value = 0;
//									fscanf_s(data, "%lf", &value);
//									int index[6] = { i, j, k, l, level5, level6 };
//									record.set_onetable_Data(m, index, value);
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//		
//		if (data)
//		{
//			if (fclose(data))
//			{
//				printf("The file '%s' was not closed\n", name);
//			}
//		}
//	}
//}

void MakeMoveTable()
{
	// move table for moving to left
	for (int i = 0 ; i< 16 ; i++){
		for (int j = 0 ; j< 16 ; j++){
			for (int k = 0 ; k< 16 ; k++){
				for (int l = 0 ; l < 16 ; l++){
					// the fifth element is award
					
					int index[5] = {i, j, k, l, 0};

					// pull the element to the left side
					int head = 0; 
					int tail = 0;
					while(tail < 4){
						if(index[tail] != 0){
							int tmp = index[head];
							index[head] = index[tail];
							index[tail] = tmp;
							head++;
							tail++;
						}
						else{
							tail++;
						}
					}

					int check_position = 0;
					while(check_position < 3){
						if(index[check_position] != 0 && (index[check_position] == index[check_position + 1])){
							index[check_position] = index[check_position] + 1;
							index[check_position + 1] = 0;
							int tmpaward = 1; 
							for (int s = 0 ; s< index[check_position]; s++){
								tmpaward = tmpaward * 2;
							}
							index[4] = index[4] + tmpaward;
							check_position = check_position + 2;
						}
						else{
							check_position = check_position + 1;
						}
					}

					// pull to left again
					head = 0; 
					tail = 0;
					while(tail < 4){
						if(index[tail] != 0 ){
							int tmp = index[head];
							index[head] = index[tail];
							index[tail] = tmp;
							head++;
							tail++;
						}
						else{
							tail++;
						}
					}
					for (int m = 0 ; m < 5 ; m++){
						Move_Table[5 * i + 5 * j * 16 + 5 * k * 16 * 16 + 5 * l * 16 * 16 * 16 + m] = index[m];
					}
				}
			}
		}
	}
}

void GetDataFromMoveTable(int i, int j, int k, int l, int index[5])
{
	for (int m = 0 ; m< 5 ; m++){
		index[m] = Move_Table[5 * i + 5 * j * 16 + 5 * k * 16 * 16 + 5 * l * 16 * 16 * 16 + m];
	}
}

void MoveLeft(Board & CurrentBoard, int & award)
{
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int index[4] = {i * 4, i * 4 + 1, i * 4 + 2, i * 4 + 3 };
		int boardindex[4] ={};
		for (int j = 0 ; j< 4 ;j ++){
			boardindex[j] = CurrentBoard.getState(index[j]);
		}

		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard.setState(newindex[j], index[j]);
		}
	}
}

void MoveRight(Board & CurrentBoard, int & award)
{
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int index[4] = {i * 4 + 3, i * 4 + 2, i * 4 + 1, i * 4};
		int boardindex[4] ={};
		for (int j = 0 ; j< 4 ;j ++){
			boardindex[j] = CurrentBoard.getState(index[j]);
		}

		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard.setState(newindex[j], index[j]);
		}
	}
}

void MoveUp(Board & CurrentBoard, int & award)
{
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int index[4] = {i, 4 + i, 8 + i, 12 + i};
		int boardindex[4] ={};
		for (int j = 0 ; j< 4 ;j ++){
			boardindex[j] = CurrentBoard.getState(index[j]);
		}

		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard.setState(newindex[j], index[j]);
		}
	}
}

void MoveDown(Board & CurrentBoard, int & award)
{
	for (int i = 0 ; i< 4 ; i++){
		int newindex[5] = {};
		int index[4] = {12 + i, 8 + i, 4 + i, i};
		int boardindex[4] ={};
		for (int j = 0 ; j< 4 ;j ++){
			boardindex[j] = CurrentBoard.getState(index[j]);
		}

		GetDataFromMoveTable(boardindex[0], boardindex[1], boardindex[2], boardindex[3], newindex);
		award += newindex[4];
		for (int j = 0 ; j< 4 ; j++){
			CurrentBoard.setState(newindex[j], index[j]);
		}
	}
}

void Move(int action, Board & CurrentBoard_AfterMove, int & award){
	assert(action >= 1 && action <= 4);
	if (action == MOVEDOWN){
		MoveDown(CurrentBoard_AfterMove, award);
	}
	if (action == MOVEUP){
		MoveUp(CurrentBoard_AfterMove, award);
	}
	if (action == MOVERIGHT){
		MoveRight(CurrentBoard_AfterMove, award);
	}
	if (action == MOVELEFT){
		MoveLeft(CurrentBoard_AfterMove, award);
	}
}