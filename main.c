#include <stdio.h>

#include "dohoa.h"
#include "structure.h"
#include "checkInput.h"
#include "ctdl.h"	
#include "loadData.h"
#include "writeData.h"  
#include "menu.h"
#include "login.h"

int main() {
	//textcolor(9);
	int user = login(); //0 admin; 1 teacher; 2 students
	
	//===setting menu=======
	char mainMenu[MAX][MAX];
	if(user == 2) {
		strcpy(mainMenu[0], "Hien thi sinh vien");
		strcpy(mainMenu[1], "Xem diem");
		strcpy(mainMenu[2], "Dang xuat");
		strcpy(mainMenu[3], "Thoat");
	} else if(user == 1) {
		strcpy(mainMenu[0], "Hien thi sinh vien");
		strcpy(mainMenu[1], "Xem diem");
		strcpy(mainMenu[2], "Sua diem");
		strcpy(mainMenu[3], "Dang xuat");
	} else if(user == 0) {
		strcpy(mainMenu[0], "Tinh nang co ban");
		strcpy(mainMenu[1], "Tinh nang nang cao");
		strcpy(mainMenu[2], "Quan ly diem");
		strcpy(mainMenu[3], "Thoat");
	}
	while(1) {		
		gotoXY(x + 9, y - 3); //title
		textcolor(7);
		printf("===QUAN LI SINH VIEN===");
		
		instruction();
		int selected = handleLogic(4, x, y, 40, mainMenu);	
		menu(selected, user);
	}
	return 0;
}
