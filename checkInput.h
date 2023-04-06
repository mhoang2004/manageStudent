enum months {
	JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, 
	OCT, NOV, DEC
};

enum months month;

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

void checkStudentCode(listStudent students, char studentCode[]) {	
	while(1) {
		int flag = 1;
		checkEmpty(studentCode);
		
		for(nodeStudent *k = students.head; k != NULL; k = k->next) {
			if(strcmp(studentCode, k->data.studentCode) == 0) flag = 0;	
		}
		if(flag) 
			break;
		else
			SetColor(4);
			printf("\t(!) Da co MSSV nay, xin nhap lai: ");
	}
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




