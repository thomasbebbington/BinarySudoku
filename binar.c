#include "raylib.h"
#include "binar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define rows 6
#define columns 6

void drawGameGrid(int* grid, char* locks){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			if(grid[(columns*i) + j] == 0){
				DrawRectangle(5 + (i * 100),5 + (j * 100), 90, 90, RAYWHITE);
			} else if (grid[(columns*i) + j] == 1){
				DrawRectangle(5 + (i * 100),5 + (j * 100), 90, 90, RED);
			} else {
				DrawRectangle(5 + (i * 100),5 + (j * 100), 90, 90, BLUE);
			}
			if(locks[(columns*i) + j] == 1){
				DrawRectangle(45 + (i * 100),45 + (j*100), 10, 10, BLACK);
			}
		}
	}
}

void getGrid(int* grid){
	srand(time(NULL));
	int id = rand() % 4140;

	FILE* seeds = fopen("seeds", "r");
	
	fseek(seeds, id * 6, SEEK_SET);

	char readbytes[36];

	fread(&readbytes, 1, 36, seeds);
	fclose(seeds);

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			grid[(columns*i) + j] = (readbytes[(columns*i) + j] + 1);
		}
	}
}

void main(){
	const int width = 100*rows;
	const int height = 100*columns;
	
	int donegrid[rows][columns] = {{0}};
	int grid[rows][columns] = {{0}};
	
	int filledSquares;
	
	getGrid((int*) &donegrid);

	int squarestofill = (rand() % 5) + 10;

	char lockedsquares[rows][columns] = {{0}};

	int r = rand() % 6;
	int c = rand() % 6;
	
	grid[r][c] = donegrid[r][c];
	lockedsquares[r][c] = 1;

	for(int k = 0; k < squarestofill - 1; k++){
		while(grid[r][c] != 0){
			r = rand() % 6;
			c = rand() % 6;
		}
		grid[r][c] = donegrid[r][c];
		lockedsquares[r][c] = 1;
	}

	filledSquares = squarestofill;

	InitWindow(width, height, "Binary Sudoku");
	SetTargetFPS(60);

	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		drawGameGrid((int*) &grid, (char*) &lockedsquares);
		//DrawFPS(10,10);

		char timebuff[10];
		snprintf(timebuff, sizeof(char)*6, "%f", GetTime());
		DrawText(timebuff, 10, 10, 20, DARKGREEN);
		

		if(filledSquares == rows * columns){
			if(checkDone(grid)){
				DrawText("VALID", width/2, height/2, 30, RAYWHITE);

			} else {
				DrawText("INVALID", width/2, height/2, 30, RAYWHITE);
			}		
		}

		if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
			Vector2 mpos = GetMousePosition();

			float xpos = mpos.x;
			float ypos = mpos.y;

			xpos = xpos/100;
			ypos = ypos/100;

			xpos = floor(xpos);
			ypos = floor(ypos);

			int x = (int) xpos;
			int y = (int) ypos;

			if(lockedsquares[x][y] == 0){
				if(grid[x][y] == 0){
					grid[x][y] = 1;
					filledSquares++;
				} else if (grid[x][y] == 1){
					grid[x][y] = 2;
				} else {
					grid[x][y] = 0;
					filledSquares--;
				}
			}
		}

		EndDrawing();
	}

	CloseWindow();
}
