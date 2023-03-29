#include <stdio.h>

#define MAX 100

int active_bg_color = 39;
int bg_color = 1;

void drawTable(int xPosition, int yPosition, int tableWidth, int tableHeight, char menuShowTitle[][MAX]) {
	//draw table
	for(int i = 0; i < 6; i++) {
		xPosition += 14;
		
		//draw 
		if(i == 2) { //box "name" need more space
			box(35, yPosition, 30, tableHeight, bg_color, "");
			
			//border between columns
			gotoXY(35, yPosition);
			printf("%c", 194);	
			gotoXY(35, tableHeight + yPosition);
			printf("%c", 193);
	
			
			gotoXY(8 + 2*14, yPosition + 1);
			printf(menuShowTitle[i]);
			
			xPosition = 51;
		} else {
			box(xPosition, yPosition, 14, tableHeight, bg_color, ""); //draw column
			
			if(i != 0) {
				gotoXY(xPosition, yPosition); 
				printf("%c", 194); //border column
				
				gotoXY(xPosition, tableHeight + yPosition);
				printf("%c", 193);
			}
			
			//print content title
			if(i > 2) {
				gotoXY(24 + i*14, yPosition + 1); 
				printf(menuShowTitle[i]);
			} else {
				gotoXY(8 + i*14, yPosition + 1); 
				printf(menuShowTitle[i]);	
			}	
		} 	
	}
	
	//draw a line
	for(int i = 0; i <= tableWidth; i++) {
		if(i == 0) {
			gotoXY(i+7, yPosition + 2);
			printf("%c", 195);
		} else if(i == tableWidth) {
			gotoXY(i+7, yPosition + 2);
			printf("%c", 180);
		} else {
			gotoXY(i+7, yPosition + 2);
			printf("%c", 196);
		}
	}
	
	//intersection between column and row
	for(int i = 0; i < 5; i++) {
		if(i < 2) {
			gotoXY(21 + i*14, yPosition + 2);
			printf("%c", 197);
		} else {
			gotoXY(37 + i*14, yPosition + 2);
			printf("%c", 197);
		}
	}

}
