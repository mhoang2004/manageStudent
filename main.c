#include <stdio.h>

#include "dohoa.h"
#include "structure.h"
#include "checkInput.h"
#include "ctdl.h"
#include "loadData.h"
#include "writeData.h"  
#include "menu.h"

int main() {
	
	//===setting menu=======
	char mainMenu[4][MAX] = {"Tinh nang co ban",  
	"Tinh nang nang cao", "Quan ly diem", "Thoat"};
	
	while(1) {
		gotoXY(x + 9, y - 3); //title
		textcolor(7);
		printf("===QUAN LI SINH VIEN===");	
		instruction();	
		int selected = handleLogic(4, x, y, 40, mainMenu);	
		
		menu(selected);
	}
	
	return 0;
}
