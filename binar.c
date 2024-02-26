#include "raylib.h"
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
				printf("Row %d has too many consecutive colours\n", i);
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
				printf("Column %d has too many consecutive colours\n", i);
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
					printf("Column %d = Column %d\n", i, j);
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
					printf("Row %d = Row %d\n", i, j);
					return 0;
				}
			}
		}
	}
	

	return 1;
}

void main(){
	const int width = 100*rows;
	const int height = 100*columns;

	int grid[rows][columns] = {{0}};
	
	int filledSquares = 0;

	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}

	InitWindow(width, height, "Binary Sudoku");
	SetTargetFPS(60);

	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);
		drawGameGrid((int*) &grid);
		DrawFPS(10,10);

		if(filledSquares == rows * columns){
			DrawText("FINISHED???", 400, 400, 30, DARKBLUE);

			printf("%d\n", checkDone(grid));
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

			char xb[5];
			char yb[5];

			sprintf(xb, "%d", x);
			sprintf(yb, "%d", y);

			DrawText(xb, 100, 100, 20, DARKGREEN);
			DrawText(yb, 200, 100, 20, DARKGREEN);
		}

		EndDrawing();
	}

	CloseWindow();
}
