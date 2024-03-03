#include<stdlib.h>
#include<stdio.h>
#define rows 6
#define columns 6

char checkDone(int grid[rows][columns]){
	int countred;
	int countblue;
	//check number of colours in rows
	for(int i = 0; i < rows; i++){
		countred = 0;
		countblue = 0;
		for(int j = 0; j < columns; j++){
			if(grid[j][i] == 1){
				countred++;
			} else {
				countblue++;
			}
		}
		if(abs(countred - countblue) > 1){
			return 0;
		}
	}

	//check number of colours in columns
	for(int i = 0; i < columns; i++){
		countred = 0;
		countblue = 0;
		for(int j = 0; j < rows; j++){
			if(grid[i][j] == 1){
				countred++;
			} else {
				countblue++;
			}
		}
		if(abs(countred - countblue) > 1){
			return 0;
		}
	}

	
	
	//check for conescutive colours in rows
	int current;
	int count;
	for(int i = 0; i < rows; i++){
		current = grid[0][i];
		count = 1;
		for(int j = 1; j < columns; j++){
			if(grid[j][i] == current){
				count++;
			} else {
				current = grid[j][i];
				count = 1;
			}
			if(count > 2){
				return 0;
			}
		}
	}

	//check for consecutive colours in columns
	for(int i = 0; i < columns; i++){
		current = grid[i][0];
		count = 1;
		for(int j = 1; j < rows; j++){
			if(grid[i][j] == current){
				count++;
			} else {
				current = grid[i][j];
				count = 1;
			}
			if(count > 2){
				return 0;
			}
		}
	}
	
	//check uniqueness of columns	
	for(int i = 0; i < rows - 1; i++){
		for(int j = i + 1; j < rows; j++){
			for(int k = 0; k < columns; k++){
				if(grid[i][k] != grid[j][k]){
					break;
				}
				if(k == columns - 1){
					return 0;
				}
			}
		}
	}
	
	//check uniqueness of rows
	for(int i = 0; i < columns - 1; i++){
		for(int j = i + 1; j < columns; j++){
			for(int k = 0; k < rows; k++){
				if(grid[k][i] != grid[k][j]){
					break;
				}
				if(k == columns - 1){
					return 0;
				}
			}
		}
	}
	

	return 1;
}

void printGrid(int grid[rows][columns]){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}

}
