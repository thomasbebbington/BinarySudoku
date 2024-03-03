#include<string.h>
#include<stdio.h>
#include"binar.h"

void writegrid(FILE* seeds, int grid[6][6]){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			fprintf(seeds, "%c", (char) grid[i][j]);
		}
	}

}

void main(){
	int validrows[14][6] = {{0,0,1,0,1,1},
				{0,0,1,1,0,1},
				{0,1,0,0,1,1},
				{0,1,0,1,0,1},
				{0,1,0,1,1,0},
				{0,1,1,0,1,0},
				{0,1,1,0,0,1},
				{1,1,0,1,0,0},
				{1,1,0,0,1,0},
				{1,0,1,1,0,0},
				{1,0,1,0,1,0},
				{1,0,1,0,0,1},
				{1,0,0,1,0,1},
				{1,0,0,1,1,0}};

	int countvalid = 0;

	int grid[6][6] = {0};
	
	FILE* seeds = fopen("seeds", "w");

	for(int q = 0; q < 14; q++){
		memcpy(&grid[0][0], &validrows[q], sizeof(int)*6);
		for(int w = 0; w < 14; w++){
			memcpy(&grid[1][0], &validrows[w], sizeof(int)*6);
			for(int e = 0; e < 14; e++){
				memcpy(&grid[2][0], &validrows[e], sizeof(int)*6);
				for(int r = 0; r < 14; r++){
					memcpy(&grid[3][0], &validrows[r], sizeof(int)*6);
					for(int t = 0; t < 14; t++){
						memcpy(&grid[4][0], &validrows[t], sizeof(int)*6);
						for(int y = 0; y < 14; y++){
							memcpy(&grid[5][0], &validrows[y], sizeof(int)*6);
							//printGrid(grid);
							char valid = checkDone(grid);
							
							countvalid += valid;
							if(valid){
								printGrid(grid);
								printf("%d\n", countvalid);
								writegrid(seeds, grid);
							}
						}
					}
				}
			}
		}
	}
	printf("%d\n", countvalid);
	fclose(seeds);
}
