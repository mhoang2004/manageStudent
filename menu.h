#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int x = 64, y = 5;

int xPosition = -7; //where is x when draw table
int yPosition = 1; //where is y when draw table
int tableWidth = 100; //14*5 + 30
char menuShowTitle[][MAX] = {"STT", "MSSV", "Ten",
"Lop", "Ngay sinh", "Diem TB"};

void instruction() {
	textcolor(7);
	gotoXY(58, 20);
	printf("Dung %c va %c de di chuyen", 24, 25);
	gotoXY(102, 20);
	printf("Enter: Lua chon");
	gotoXY(58, 21);
	printf("M: Menu");
	gotoXY(102, 21);
	printf("Esc: Thoat");
}

void active(int x, int y, int w, int h, int bg_color, char content[]) {
	textcolor(bg_color);	
	for(int iy = y + 1; iy <= y + h-1; iy++) {
		for(int ix = x + 1; ix <= x + w-1; ix++) {
			gotoXY(ix, iy);
			printf(" ");
		}
	}
	
	SetColor(7); //white character
  	gotoXY(x + 1, y + 1); printf("%s", content); //write content

	textcolor(2);
}

void onlyBox(int x, int y, int w, int h) {
	textcolor(2);
	SetColor(7);
	
	if(h <= 1 || w <= 1) return; //can't handle too small box
	
	for(int ix = x; ix <= x + w; ix++) {
		gotoXY(ix, y);
		printf("%c", 196); //char(196) is ascii
		gotoXY(ix, y + h);
		printf("%c",196);
	}
	
	for(int iy = y; iy <= y + h; iy++) {
		gotoXY(x, iy);
		printf("%c", 179);
		gotoXY(x + w, iy);
		printf("%c", 179);
	}
	
	//border-radius 4 corner;
	gotoXY(x, y); printf("%c", 218);
	gotoXY(x + w, y); printf("%c", 191);
	gotoXY(x + w, y + h); printf("%c", 217);
	gotoXY(x, y + h); printf("%c", 192);
	
	gotoXY(x+2, y+1);
}

void box(int x, int y, int w, int h, int bg_color, char content[]) {
	ShowCur(0);
	active(x, y, w, h, bg_color, content);
 	
	//========draw border============= 
	textcolor(2); //after draw this one will overwiter
	SetColor(7);
	
	if(h <= 1 || w <= 1) return; //can't handle too small box
	
	for(int ix = x; ix <= x + w; ix++) {
		gotoXY(ix, y);
		printf("%c", 196); //char(196) is ascii
		gotoXY(ix, y + h);
		printf("%c",196);
	}
	
	for(int iy = y; iy <= y + h; iy++) {
		gotoXY(x, iy);
		printf("%c", 179);
		gotoXY(x + w, iy);
		printf("%c", 179);
	}
	
	//border-radius 4 corner;
	gotoXY(x, y); printf("%c", 218);
	gotoXY(x + w, y); printf("%c", 191);
	gotoXY(x + w, y + h); printf("%c", 217);
	gotoXY(x, y + h); printf("%c", 192);
}

void n_box(int x, int y, int w, int h, int bg_color, char content[][MAX], int n) {
	for(int i = 0; i < n*3; i+=3) {
		if(i == 0) box(x, y + i, w, h, bg_color, content[i]);
		else box(x, y + i, w, h, bg_color, content[i/3]);
	}
}


#include "table.h"

//handle UI logic
int handleLogic(int n, int x, int y, int w, char content[][MAX]) {
	//========setting===========
	int h = 2;
	
	n_box(x, y, w, h, bg_color, content, n);
	
	int px = x, py = y; //copy 
	int contentIndex = 0;
	int previousX = px, previousY = py;
	int prev_contentIndex = contentIndex;
	
	//check if user press any button, if not it will print active infinity
	bool anyPress = true;
	while(1) {
		if(anyPress) {
			//backspace (reset previous active )
			gotoXY(previousX, previousY);
			active(previousX, previousY, w, h, bg_color, content[prev_contentIndex]);
			previousY = py; 
			previousX = px; //update previous value
			prev_contentIndex = contentIndex;
			
			//set color for next selection
			active(px, py, w, h, active_bg_color, content[contentIndex]);
			anyPress = false;
		}
		
		//======control========
		if(kbhit()) {
			char c = getch();
			anyPress = true;
			if(c == -32) {
				c =  getch();
				if(c == 72) { //up
					if(py != y) {
						contentIndex--;
						py -= 3;
					} else {
						py =  y + 3*(n - 1);
						contentIndex = n-1;	
					}
				} else if(c == 80) { // down
					if(py != y + 3*(n - 1)) {
						contentIndex++;
						py += 3;
					} 
					else {
						contentIndex = 0;
						py = y;
					}
				} 	
			}
			if(c == 13) { //Enter
				//textcolor(2);
				system("cls");
				int selected = (py - y) / 3;
				anyPress = false;
				return selected;	
			}
			if(c == 27) { //Esc
				system("cls");
				exit(0);
			}
			if(c == 109) { //M
				system("cls");
				return -1;
			}
		}
	}
}

//sub menu
void menu1(int selected, listStudent *students) {
	switch(selected) {
		textcolor(7);
		case 0: { //print
			int tableHeight = sizeNode(*students) + 3; //3 more space at the bottom
			
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printNode(*students, 4);
			
			getchar();
			system("cls");
			break;
		}
		case 1: { //add
			textcolor(7);
			//edit here
			student b; //temp
			printf("\nThem sinh vien:\n\n");
			
			printf("\t====================\n");
			printf("\t(?) Nhap ten: ");
			checkEmpty(b.name);
			
			printf("\t====================\n");
			printf("\t(?) Nhap MSSV: ");
			checkStudentCode(*students, b.studentCode);
			printf("\t====================\n");
			
			printf("\t(?) Nhap nganh: ");
			checkEmpty(b.major);
			printf("\t====================\n\n");
			
			printf("\t(!) Nhap dung dinh dang! VD: 1/1/2004\n\n");
			printf("\t(?) Nhap ngay thang nam sinh ngay/thang/nam: ");
			int isError;
			char *day, *month, *year;
			int intDay, intMonth, intYear;
			do {
				isError = 0;
				checkEmpty(b.date);
				
				char temp[14];
				strcpy(temp, b.date);
				
				day = strtok(temp, "/"); 
				month = strtok(NULL, "/");
				year = strtok(NULL, "/");
			
				intDay = atoi(day);
				intMonth = atoi(month);
				intYear = atoi(year);
				
				if(!intDay || !intMonth || !intYear) 
					isError = 1;
				
				if(intDay <= 0|| intMonth <= 0 || intYear <= 1923)
					isError = 1;
				if(intMonth > DEC) {
					isError = 1;
				} else {
					if(intDay > dayOfMonth(intMonth, intYear)) 
						isError = 1;
					if(intYear > 2023) 
						isError = 1;
				}	
				if(isError) {
					SetColor(4);
					printf("\n\t(!) Nhap sai!\n");
					SetColor(7);
					printf("\t(?) Xin nhap lai: ");
				}
					
			} while(isError);
			printf("\n\t====================\n");
			
			printf("\t(?) Nhap diem mon 1: ");
			checkInputScore(&b.scoreList.subject1);
			printf("\t====================\n");
			
			
			printf("\t(?) Nhap diem mon 2: ");
			checkInputScore(&b.scoreList.subject2);
			printf("\t====================\n");
			
			printf("\t(?) Nhap diem mon 3: ");
			checkInputScore(&b.scoreList.subject3);
			printf("\t====================\n");
			
			b.gpa = (b.scoreList.subject1 + b.scoreList.subject2 
			+ b.scoreList.subject3) / 3;
			
			pushBack(students, b);
			writeData(students);
			
			SetColor(2);
			printf("\n\n\t(!) SUCESSFULLY!!!");
			
			getchar();
			system("cls");
			break;
		}
		case 2: { //remove
			textcolor(7);
			printf("Xoa sinh vien\n");
			
			//earase
		    int eraseID = 0;
		    printf("\n\t(?) Nhap id muon xoa: ");
		    checkInputInt(&eraseID);
			
			if(eraseID > sizeNode(*students) || eraseID <= 0) {
				SetColor(4);
				printf("\n\t(!) Khong co sinh vien can xoa!!!");
				
				getchar(); //consume enter
				getchar(); //stop programme to see result
				system("cls");
				break;
			}
			
			nodeStudent *temp = students->head;
			while(temp->data.id != eraseID) {
				temp = temp->next;
			}
			
			//each student have 2 height
			int tableHeight = 4; //3 more space at the bottom
			int yPosition = 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printOneNode(*students, eraseID);
			
			printf("\n\n\n");
			printf("\t(?) Ban co that su muon xoa sinh vien nay?\n");
			
			char confirmTitle[][MAX] = {"YES", "NO"};
			int selected = handleLogic(2, 10, 10, 10, confirmTitle);
			if(selected == 0) {
				eraseStudent(students, eraseID);
				writeData(students);
				printf("\n\n\t(!) SUCESSFULLY!!!");
			} else printf("\n\n\t(!) UNSUCESSFULLY!!!");

			getchar();
			getchar();
			system("cls");
			break;
		}
		case 3: { //edit
			textcolor(7);
			
			printf("Sua sinh vien: \n\n");
			
		    int editID = 0, isTrue = 1;
		    printf("\t(?) Nhap id muon sua: ");
		    scanf("%d", &editID);
			
			if(editID > sizeNode(*students) || editID <= 0) {
				SetColor(4);
				printf("\n\t(!) Khong co sinh vien de sua!!!");
				
				getchar(); //consume enter
				getchar(); //stop programme to see result
				system("cls");
				break;
			}
			
			nodeStudent *temp = students->head;
			while(temp->data.id != editID) {
				temp = temp->next;
			}
			
			//each student have 1 height
			int tableHeight = 4; //3 more space at the bottom
			int yPosition = 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printOneNode(*students, editID);
			
			getchar();
			printf("\n\n");
			
			//edit here
			printf("\n\t(!) Dang sua sinh vien co id %d... \n", editID);
			printf("\t(!) Nhan Enter de bo qua truong khong can sua!\n\n");
			
			char c[MAX]; //check if press enter
			
			printf("\t====================\n");
			printf("\t(?) Nhap lai ten: ");
			fgets(c, sizeof(c), stdin); //press enter
			if(c[0] != '\n') {
				c[strlen(c) - 1] = '\0'; //remove Enter at the end
			    strcpy(temp->data.name, c); 
			}
			printf("\t====================\n");
			
			printf("\t(?) Nhap lai MSSV: ");
			checkEditStudentCode(*students, c, temp->data.studentCode);
			
			printf("\t====================\n");
			
			printf("\t(?) Nhap lai nganh: ");
			fgets(c, sizeof(c), stdin);
			if(c[0] != '\n') {
				c[strlen(c) - 1] = '\0';
			    strcpy(temp->data.major, c);
			}
			
			printf("\t====================\n\n");
			printf("\t(!) Nhap dung dinh dang! VD: 1/1/2004\n\n");
			printf("\t(?) Nhap ngay thang nam sinh ngay/thang/nam: ");
			checkEditDate(c, temp->data.date);
			printf("\n\t====================\n");
			
			printf("\t(?) Nhap lai diem mon 1: ");
			checkScore(c, &temp->data.scoreList.subject1);
			
			printf("\t====================\n");
			
			printf("\t(?) Nhap lai diem mon 2: ");
			checkScore(c, &temp->data.scoreList.subject2);
			printf("\t====================\n");
			
			printf("\t(?) Nhap lai diem mon 3: ");
			checkScore(c, &temp->data.scoreList.subject3);
			printf("\t====================\n");
			
			temp->data.gpa = (temp->data.scoreList.subject1 + temp->data.scoreList.subject2
			+ temp->data.scoreList.subject3) / 3;
			
			SetColor(2);
			printf("\n\t(!) SUCESSFULLY!!!");
			SetColor(7);
			writeData(students);
			printOneNode(*students, editID);
		
			getchar();
			
			system("cls");
			break;
		}
	}
}

void menu2(int selected, listStudent *students) {	
	switch(selected) {
		case 0: { //find
			textcolor(7);
			printf("Tim sinh vien: \n");
			char findString[MAX]; //id / name
		    int findID;
			printf("\n\t(?) Nhap id/ten sinh vien muon tim: ");
			scanf("%s", findString);
		      
		    //how to processing with int and string
		    if (sscanf(findString, "%d", &findID) == 1) {
		    	//int
		    	int tableHeight = 4;
		    	int yPosition = 3;
	    		if(findID < 1 || findID > sizeNode(*students)) {
					printf("(!) Khong co sinh vien can tim!!!\n");
				} else {
					drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
					printOneNode(*students, findID);	
				}
			} else {
				//string
				listStudent result; 
				result = findStudent2(*students, findString);
				
				if(result.head == NULL) {
					printf("\n\t(!) Khong co sinh vien can tim!!!\n");
				} else {
					int yPosition = 3;
					int tableHeight = sizeNode(result) + 3;
					drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
					printNode(result, 6);
				}
			} 

			getch();
			system("cls");
			break;
		}
		case 1: { //sort
			textcolor(7);
			printf("Sap xep sinh vien:\n");
			printf("\n\t(?) Chon cach sap xep: \n");
			char sortTitle[][MAX] = {"Sap xep theo ten ABC", 
			"Sap xep theo diem giam dan"};
			int selected = handleLogic(2, 10, 4, 35, sortTitle);
			
			switch(selected) {
				case 0: {
					sortAlphabet(*students);
					break;
				}
				case 1: {
					sortScoreIncrease(*students);
					break;
				}	
			}
			int tableHeight = sizeNode(*students) + 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printNode(*students, 4);
			getch();
			system("cls");
			break;
		}
		case 2: { //statistical
			textcolor(7);
			
			float numberOfStudent = sizeNode(*students);
			float sum;
			int good = 0, normal = 0, bad = 0;
			float maxScore = 0;
			for(nodeStudent *k = students->head; k != NULL; k = k->next) {
				sum += k->data.gpa;
				
				if(k->data.gpa >= 3.6) 
					good++;
				else if(k->data.gpa >= 3.2)
					normal++;
				else 
					bad++;
				
				if(k->data.gpa > maxScore) {
					maxScore = k->data.gpa;
				}
			}
			
			printf("Thong ke:\n");
			printf("\n\t===========================\n");
			printf("\n\t(!) Diem trung binh ca lop: %.2f\n", sum / numberOfStudent);
			printf("\n\t===========================\n");
			printf("\n\t(!) Ti le sinh vien gioi: %.2f%%\n", (good / numberOfStudent) * 100);
			printf("\n\t===========================\n");
			printf("\n\t(!) Ti le sinh vien kha: %.2f%%\n", (normal / numberOfStudent) * 100);
			printf("\n\t===========================\n");
			printf("\n\t(!) Ti le sinh vien trung binh & yeu: %.2f%%\n", (bad / numberOfStudent) * 100);
			
			printf("\n\t===========================\n");
			printf("\n\t(!) Sinh vien diem cao nhat la: ");
			for(nodeStudent *h = students->head; h != NULL; h = h->next) {
				if(h->data.gpa == maxScore) {
					printf("%s - %.2f; ", h->data.name, h->data.gpa);
				}
			}
			getch();
			system("cls");
			break;
		}
		case 3: { //filter
			textcolor(7);
			
			char filterTitle[3][MAX] = {"Loc sinh vien gioi", 
			"Loc sinh vien kha", "Loc sinh vien trung binh & yeu"};
			
			int selected = handleLogic(3, x, y, 40, filterTitle);
			
			listStudent result; 
			result = findScopeScore(*students, selected);
			
			int tableHeight = sizeNode(result) + 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printNode(result, 4);
			
			getch();
			system("cls");
			break;
		}
	}
}

void menu3(int selected, listStudent *students) {	
	switch(selected) {
		case 0: {
			char menuShowTitle[][MAX] = {"STT", "MSSV", "Ten",
			"Diem mon 1", "Diem mon 2", "Diem mon 3"};
			int tableHeight = sizeNode(*students) + 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printScore(*students, 4);
			
			getchar();
			system("cls");
			break;
		}
		case 1: {
			textcolor(7);
			char menuShowTitle[][MAX] = {"STT", "MSSV", "Ten",
			"Diem mon 1", "Diem mon 2", "Diem mon 3"};
		    int editID = 0;
		    printf("\n\n\t(?) Nhap id muon sua diem: ");
		    scanf("%d", &editID);
			
			if(editID > sizeNode(*students) || editID <= 0) {
				SetColor(4);
				printf("\n\t(!) Khong co sinh vien de sua!!!");
				
				getchar(); //consume enter
				getchar(); //stop programme to see result
				system("cls");
				break;
			}
			
			nodeStudent *temp = students->head;
			while(temp->data.id != editID) {
				temp = temp->next;
			}
			
			//each student have 1 height
			int tableHeight = 4; //3 more space at the bottom
			int yPosition = 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printNodeScore(*students, editID);
			
			getchar();
			
			//edit here
			printf("\n\n\t(!) Dang sua diem sinh vien co id %d... \n", editID);
			printf("\t(!) Nhan Enter de bo qua truong khong can sua!\n\n");
			
			char c[MAX];
			
			printf("\n\t===========================\n");
			printf("\t(?) Nhap lai diem mon 1: ");
			checkScore(c, &temp->data.scoreList.subject1);
			
			printf("\n\t===========================\n");
			printf("\t(?) Nhap lai diem mon 2: ");
			checkScore(c, &temp->data.scoreList.subject2);
			
			printf("\n\t===========================\n");
			printf("\t(?) Nhap lai diem mon 3: ");
			checkScore(c, &temp->data.scoreList.subject3);
			
			temp->data.gpa = (temp->data.scoreList.subject1 + temp->data.scoreList.subject2
			+ temp->data.scoreList.subject3) / 3;
			
			SetColor(2);
			printf("\n\n\t(!) SUCESSFULLY!!!");
			SetColor(7);
			
			writeData(students);
			printNodeScore(*students, editID);
		

			getchar();
			system("cls");
			break;
		}
	}
}

void menuStudent(int selected, listStudent *students) {
	switch(selected) {
		case 0: { //print
			int tableHeight = sizeNode(*students) + 3; //3 more space at the bottom
			
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printNode(*students, 4);
			
			getchar();
			system("cls");
			break;
		}
		case 1: {
			char menuShowTitle[][MAX] = {"STT", "MSSV", "Ten",
			"Diem mon 1", "Diem mon 2", "Diem mon 3"};
			int tableHeight = sizeNode(*students) + 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printScore(*students, 4);
			
			getchar();
			system("cls");
			break;
		}
		case 2: {
			system("cls");
			gotoXY(60, 10);
			printf("(?) Ban co that su muon dang xuat?\n");
			
			char confirmTitle[][MAX] = {"YES", "NO"};
			int selected = handleLogic(2, 70, 12, 10, confirmTitle);
				if(selected == 0) main();
			break;
		}
		case 3: {
			exit(0);
		}
	}
}

void menuTeacher(int selected, listStudent *students) {
	switch(selected) {
		case 0: { //print
			int tableHeight = sizeNode(*students) + 3; //3 more space at the bottom
			
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printNode(*students, 4);
			
			getchar();
			system("cls");
			break;
		}
		case 1: {
			char menuShowTitle[][MAX] = {"STT", "MSSV", "Ten",
			"Diem mon 1", "Diem mon 2", "Diem mon 3"};
			int tableHeight = sizeNode(*students) + 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printScore(*students, 4);
			
			getchar();
			system("cls");
			break;
		}
		case 2: {
			textcolor(7);
			char menuShowTitle[][MAX] = {"STT", "MSSV", "Ten",
			"Diem mon 1", "Diem mon 2", "Diem mon 3"};
		    int editID = 0;
		    printf("\n\n\t(?) Nhap id muon sua diem: ");
		    scanf("%d", &editID);
			
			if(editID > sizeNode(*students) || editID <= 0) {
				SetColor(4);
				printf("\n\t(!) Khong co sinh vien de sua!!!");
				
				getchar(); //consume enter
				getchar(); //stop programme to see result
				system("cls");
				break;
			}
			
			nodeStudent *temp = students->head;
			while(temp->data.id != editID) {
				temp = temp->next;
			}
			
			//each student have 1 height
			int tableHeight = 4; //3 more space at the bottom
			int yPosition = 3;
			drawTable(xPosition, yPosition, tableWidth, tableHeight, menuShowTitle);
			printNodeScore(*students, editID);
			
			getchar();
			
			//edit here
			printf("\n\n\t(!) Dang sua diem sinh vien co id %d... \n", editID);
			printf("\t(!) Nhan Enter de bo qua truong khong can sua!\n\n");
			
			char c[MAX]; //check if press enter
			
			printf("\n\t===========================\n");
			printf("\t(?) Nhap lai diem mon 1: ");
			checkScore(c, &temp->data.scoreList.subject1);
			
			printf("\n\t===========================\n");
			printf("\t(?) Nhap lai diem mon 2: ");
			checkScore(c, &temp->data.scoreList.subject2);
			
			printf("\n\t===========================\n");
			printf("\t(?) Nhap lai diem mon 3: ");
			checkScore(c, &temp->data.scoreList.subject3);
			
			temp->data.gpa = (temp->data.scoreList.subject1 + temp->data.scoreList.subject2
			+ temp->data.scoreList.subject3) / 3;
			
			SetColor(2);
			printf("\n\n\t(!) SUCESSFULLY!!!");
			SetColor(7);
			
			writeData(students);
			printNodeScore(*students, editID);
			
			getchar();
			system("cls");
			break;
		}
		case 3: {
			system("cls");
			gotoXY(60, 10);
			printf("(?) Ban co that su muon dang xuat?\n");
			
			char confirmTitle[][MAX] = {"YES", "NO"};
			int selected = handleLogic(2, 70, 12, 10, confirmTitle);
			if(selected == 0) main();
			break;
		}
	}
}

//main menu
void menu(int selected, int user) {
	listStudent students;
	students.head = NULL;
	loadData(&students);
	
	textcolor(7);
	gotoXY(x + 9, y - 3); //title
	printf("===QUAN LI SINH VIEN===");
	
	//how to control
	instruction();
	if(user == 2) {
		system("cls");
		menuStudent(selected, &students);
	} else if(user == 1) {
		system("cls");
		menuTeacher(selected, &students);
	} else if(user == 0) {
		switch(selected) {
			case 0: {
				char basicFunc[5][MAX] = {"Hien thi sinh vien", "Them sinh vien", 
				"Xoa sinh vien", "Sua sinh vien", "Quay lai"};
				int selected2 = handleLogic(5, x, y, 40, basicFunc);
				menu1(selected2, &students);
				break;
			}
			case 1: {
				char advanceFunc[5][MAX] = {"Tim kiem", "Sap xep", 
				"Thong ke", "Loc diem", "Quay lai"};
				int selected3 = handleLogic(5, x, y, 40, advanceFunc);
				menu2(selected3, &students);
				break;
			}
			case 2: {
				char scoreManip[3][MAX] = {"Xem diem", "Sua diem", "Quay lai"};
				int selected4 = handleLogic(3, x, y, 40, scoreManip);
				menu3(selected4, &students);
				break;
			}
			case 3: {
				system("cls");
				exit(0);
				break;
			}
		}
	}
}
