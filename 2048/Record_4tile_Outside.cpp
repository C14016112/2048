#include "stdafx.h"
#include "Record_4tile_Outside.h"

Record_4tile_Outside::Record_4tile_Outside()
{
	for (int i = 0 ;i < 4 ; i++){
		index[0][i] = i;
		index[1][i] = 15 - i;
		index[2][i] = 12 - 4 * i;
		index[3][i] = 4 * i + 3;
		index[4][i] = 3 - i;
		index[5][i] = 4 * i;
		index[6][i] = 12 + i;
		index[7][i] = 15 - 4 * i;
	}
	for (int i = 0 ; i< 16 * 16 * 16 * 16; i++){
		Data[i] = 0;
	}
	iUpperBound = 16;
	Read_Record();
}

Record_4tile_Outside::~Record_4tile_Outside()
{
}

void Record_4tile_Outside::setScore(int inputindex[4], double score){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = score;
}

double Record_4tile_Outside::getScore(int inputindex[4]){
	int position = inputindex[0] + inputindex[1]*iUpperBound + inputindex[2] * iUpperBound * iUpperBound + inputindex[3] * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];
}

double Record_4tile_Outside::getScore(Board b){
	double value = 0;
	for (int i = 0 ; i< 8 ; i++){
		int index1 = b.getState(index[i][0]);
		int index2 = b.getState(index[i][1]);
		int index3 = b.getState(index[i][2]);
		int index4 = b.getState(index[i][3]);
		int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
		value = value + Data[position];
	}
	return value;
}


double Record_4tile_Outside::get_OneFeature_Score(Board b, int no)
{
	assert(no >= 0 && no < 8);
	int index1 = b.getState(index[no][0]);
	int index2 = b.getState(index[no][1]);
	int index3 = b.getState(index[no][2]);
	int index4 = b.getState(index[no][3]);
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	return Data[position];
	
}

void Record_4tile_Outside::set_OneFeature_Score(Board b, int no, double value)
{
	assert(no >= 0 && no < 8);
	int index1 = b.getState(index[no][0]);
	int index2 = b.getState(index[no][1]);
	int index3 = b.getState(index[no][2]);
	int index4 = b.getState(index[no][3]);
	int position = index1 + index2*iUpperBound + index3 * iUpperBound * iUpperBound + index4 * iUpperBound * iUpperBound * iUpperBound;
	Data[position] = value;

}

void Record_4tile_Outside::Read_Record()
{
	FILE * score_data;
	errno_t err;
	char name[30] = "data_record2.txt";

	if ((err = fopen_s(&score_data, name, "r")) != 0)
	{
		printf("The file '%s' was not opened\n", name);
	}
	else{
		printf("The file '%s' was opened\n", name);

		for (int i = 0; i < 16; i++){
			for (int j = 0; j < 16; j++){
				for (int k = 0; k < 16; k++){
					for (int l = 0; l < 16; l++){
						double value = 0;
						fscanf_s(score_data, "%lf", &value);
						int position =0;
						position = l + k * 16 + j * 16 *16 + i * 16 * 16 * 16;
						Data[position] = value;
					}
				}
			}
		}
		if (score_data)
		{
			if (fclose(score_data))
			{
				printf("The file '%s' was not closed\n", name);
			}
		}
	}
		
}