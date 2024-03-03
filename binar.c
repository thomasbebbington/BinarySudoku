#include "raylib.h"
#include "binar.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define rows 6
#define columns 6

void drawGameGrid(int* grid){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			if(grid[(columns*i) + j] == 0){
				DrawRectangle(5 + (i * 100),5 + (j * 100), 90, 90, RAYWHITE);
			} else if (grid[(columns*i) + j] == 1){
				DrawRectangle(5 + (i * 100),5 + (j * 100), 90, 90, RED);
			} else {
				DrawRectangle(5 + (i * 100),5 + (j * 100), 90, 90, BLUE);
			}
		}
	}
}

	
	


void main(){
	const int width = 100*rows;
	const int height = 100*columns;

	int grid[rows][columns] = {{0}};
	
	int filledSquares = 0;

	InitWindow(width, height, "Binary Sudoku");
	SetTargetFPS(60);

	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		drawGameGrid((int*) &grid);
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

		EndDrawing();
	}

	CloseWindow();
}
