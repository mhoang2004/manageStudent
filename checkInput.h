enum months {
	JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, 
	OCT, NOV, DEC
};

enum months month;

char majors[MAX][MAX] = { "CNTT", "KIENTRUC", "KTVT", "TDHDK", "LOGISTICS" };

void checkNameInput(char name[]) 
{
	for(int i=0; i<strlen(name); i++)
	{
		if (i==0|| (i>0 && name[i-1]==32))
		{
			if(name[i]>=97 && name[i]<=122)
				name[i]=name[i]-32;	
		}else
		{
			if(name[i]>=65 && name[i]<=90)
				name[i]=name[i]+32;	
		}
	}
}

void checkMajor(char string[]) {
	while(1) {
		scanf("%[^\n]s", string);
		getchar();
		int res;	
		for(int i = 0; i < 5; i++) {
			res = findMajor(string, majors[i]);
			if(res) {
				strcpy(string, majors[i]);
				return;
			} 	
		}
		printf("\t(!) Khong co nganh dao tao nay!\n");
		printf("\t(?) Xin nhap lai: ");	
	}	
}

void checkEditMajor(char a[], char string[]) {
	while(1) {
		fgets(a, MAX, stdin);
		
		if(a[0] == '\n') break;
		a[strlen(a)-1] = '\0';
		int res;	
		for(int i = 0; i < 5; i++) {
			res = findMajor(string, majors[i]);
			if(res) {
				strcpy(string, majors[i]);
				return;
			} 	
		}
		printf("\t(!) Khong co nganh dao tao nay!\n");
		printf("\t(?) Xin nhap lai: ");	
	}
}

//Kiem tra MSSV co qua 10 chu so hay khong?
void checkStudentCode(char studentCode[], listStudent students) {
	int checkLength, flag;
	do {
		checkLength = 1, flag = 1;
		checkEmpty(studentCode);
		
		if(strlen(studentCode) <= 10)
			checkLength = 0;
		if(checkLength) {
			SetColor(4);
			printf("\t(!) MSSV da nhap vuot qua chieu dai cho phep!\n");
			SetColor(7);
			printf("\t(?) Xin nhap lai: ");
		} else {
			for(nodeStudent *k = students.head; k != NULL; k = k->next) {
				if(strcmp(studentCode, k->data.studentCode) == 0) flag = 0;	
			}
			if(flag) 
				break;
			else {
				SetColor(4);
				printf("\t(!) Da co MSSV nay!\n");	
				SetColor(7);
				printf("\t(?) Xin nhap lai: ");
			}	
		}
	} while(checkLength || !flag);
}

//in MSSV, neu MSSV it hon 10 chu so tu dong them cac so 0 vao dau
void checkPrintStudentCode(char studentCode[]) {	
	int len = strlen(studentCode);
	if(len < 10) {
		int i, numZeros = 10 - len;
        char temp[11];

        for (i = 0; i < numZeros; i++) {
            temp[i] = '0';
        }
        temp[i] = '\0';

        strcat(temp, studentCode); 

        strcpy(studentCode, temp);
	}
}

int leapYear(int y) {
	return ((y%4 == 0 && y%100 != 0) || y % 400 == 0);
}
	
int dayOfMonth(int m, int y) {
  	switch(m) {
	    case JAN:
		case MAR:
		case MAY:
		case JUL:
		case AUG:
		case OCT:
		case DEC: {
	      return 31;
	      break;
	    }
	    case FEB: {
	      	if(leapYear(y)) 
	        	return 29;
			
			return 28;
	    }
	    case APR:
		case JUN:
		case SEP:
		case NOV: {
	      return 30;
	    }  
  	}
}

void checkLoginEnter(char string[]){
	do {
		gotoXY(58, 7);
		fgets(string, MAX, stdin);
	} while(strlen(string) == 1);	
}

void checkEmpty(char string[]) {
	do {
		scanf("%[^\n]s", string);
		getchar();
		//fgets(b.name, MAX, stdin);
		if(strlen(string) == 0) {
			
			SetColor(4);
			printf("\t(!) Chuoi rong!!\n");
			SetColor(7);
			printf("\t(?) Xin nhap lai: ");
		}
	} while(strlen(string) == 0);
}

void checkEditDate(char a[], char date[]) { //edit function
	int isError;
	char *day, *month, *year;
	int intDay, intMonth, intYear;
	do {
		isError = 0;
		
		fgets(a, MAX, stdin);
		
		if(a[0] == '\n') break;
		a[strlen(a)-1] = '\0';
		
		char temp[14];
		strcpy(temp, a);
		
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
		} else
			strcpy(date, a);
			
	} while(isError);
}

void checkDate(char date[]) {
	int isError;
	char *day, *month, *year;
	int intDay, intMonth, intYear;
	do {
		isError = 0;
		checkEmpty(date);
		
		char temp[14];
		strcpy(temp, date);
		
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
}

void printDate(char date[]) { //1 nhap; 0 print
	
	char temp[14];
	strcpy(temp, date);

	char *day = strtok(temp, "/"); 
	char *month = strtok(NULL, "/");
	char *year = strtok(NULL, "/");

	int intDay = atoi(day);
	int intMonth = atoi(month);
	int intYear = atoi(year);
	
	if(intDay < 10) 
		printf("0%d/", intDay);
	else
		printf("%d/", intDay);	
	
	if(intMonth < 10) 
		printf("0%d/", intMonth);
	else
		printf("%d/", intMonth);
	
	printf("%d", intYear);

}

void checkName(char name[]) {
	if(strlen(name) >= 30) {
		for(int i = 0; i < 29; i++) {
			printf("%c", name[i]);
		}
	} else
		printf("%s ", name);
}

void checkEditStudentCode(listStudent students, char c[], char studentCode[]) {
	int checkLength, flag;
	do {
		checkLength = 1, flag = 1;
		fgets(c, MAX, stdin);
		if(c[0] == '\n') break;
		c[strlen(c)-1] = '\0';
		
		
		if(strlen(c) <= 10)
			checkLength = 0;
		if(checkLength) {
			SetColor(4);
			printf("\t(!) MSSV da nhap vuot qua chieu dai cho phep!\n");
			SetColor(7);
			printf("\t(?) Xin nhap lai: ");
		} else {
			checkPrintStudentCode(c);
			for(nodeStudent *k = students.head; k != NULL; k = k->next) {
				if(strcmp(c, k->data.studentCode) == 0) flag = 0;		
			}
			
			if(flag) {
				strcpy(studentCode, c);
				break;
			} else {
				SetColor(4);
				printf("\t(!) Da co MSSV nay!\n");
				SetColor(7);
				printf("\t(?) Xin nhap lai: ");
			}	
		}
	} while(checkLength && !flag);
}

void checkInputInt(int *x) {
    char input[100];
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input\n");
            exit(1);
        }
        if (sscanf(input, "%d", x) == 1) break;
		
		SetColor(4);
        printf("\t(!) Khong nhap chuoi!!\n");
        SetColor(7);
        printf("\t(?) Nhap lai: ");
    }
}

void checkInputScore(float *x) {
    char input[100];
    while (1) {	
        if (fgets(input, sizeof(input), stdin) == NULL) {
        	SetColor(4);
            printf("Error reading input\n");
            exit(1);
        }
        if (sscanf(input, "%f", x) == 1) {
        	if(*x > 4 || *x < 0) {	
        		SetColor(4);
				printf("\t(!) Diem chi thuoc [0; 4]!\n");
				SetColor(7);
				printf("\t(?) Xin nhap lai: ");
			} else break;
        } else {
        	SetColor(4);
        	printf("\t(!) Khong nhap chuoi!!\n");
        	SetColor(7);
			printf("\t(?) Xin nhap lai: ");
		} 
    }
}

void checkScore(char a[], float *x) { //edit input
    while (1) {	
        if(fgets(a, sizeof(a), stdin) == NULL) {
        	SetColor(4);
            printf("Error reading input\n");
            exit(1);
        }
        if(a[0] == '\n') break;
        float temp;
        if (sscanf(a, "%f", &temp) == 1) {
        	if(temp > 4 || temp < 0) {	
        		SetColor(4);
				printf("\t(!) Diem chi thuoc [0; 4]!\n");
				SetColor(7);
				printf("\t(?) Xin nhap lai: ");
			} else {
				*x = temp;
				break;
			}
        } else {
        	SetColor(4);
        	printf("\t(!) Khong nhap chuoi!!\n");
        	SetColor(7);
			printf("\t(?) Xin nhap lai: ");
		} 
    }
}



