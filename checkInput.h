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

void printDate(char date[]) { //1 nhap; 0 print
	//printf("%s", date);
	char *day = strtok(date, "/"); 
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
		scanf("%s", studentCode);
		for(nodeStudent *k = students.head; k != NULL; k = k->next) {
			if(strcmp(studentCode, k->data.studentCode) == 0) flag = 0;	
		}
		if(flag) 
			break;
		else
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

        printf("\t(!) Khong nhap chuoi!!\n");
        printf("\t(?) Nhap lai: ");
    }
}

void checkInputScore(float *x) {
    char input[100];
    while (1) {	
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error reading input\n");
            exit(1);
        }
        if (sscanf(input, "%f", x) == 1) {
        	if(*x > 4 || *x < 0) {
				printf("\t(!) Diem chi thuoc [0; 4]!\n");
				printf("\t(?) Xin nhap lai: ");
			} else break;
        } else {
        	printf("\t(!) Khong nhap chuoi!!\n");
        	printf("\t(?) Xin nhap lai: ");
		} 
    }
}




