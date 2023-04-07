int login() {
	acc users[3];
			
	strcpy(users[0].username, "admin");
	strcpy(users[0].password, "admin");
	
	strcpy(users[1].username, "tranthidung");
	strcpy(users[1].password, "123456");
	
	strcpy(users[2].username, "hocsinh");
	strcpy(users[2].password, "hocsinh");
	
	int nonUser = 1;
	int user;
	while(nonUser) {
		gotoXY(x + 4, y - 3); //title
		textcolor(7);
		printf("===DANG NHAP===");

		char userAccount[MAX], userPassword[MAX];
		
		gotoXY(x-8, y);
		printf("Nhap tai khoan:");
		onlyBox(x-8, y+1, 40, 2);
		checkLoginEnter(userAccount);
		userAccount[strlen(userAccount) - 1] = '\0';			
		gotoXY(x-8, y+5);
		printf("Nhap mat khau:");
		onlyBox(x-8, y+6, 40, 2);
		int inputKeyBoard = 0, i = 0, n = x-6;
		while(inputKeyBoard != 13) {
			inputKeyBoard = getch();
			if(inputKeyBoard == 8) {
				if(i > 0) 
					i--;
				userPassword[i] = '\0';
				if(n > x - 6)
					n--;
	
				//clear old data
				gotoXY(n, y+7);
				printf(" ");
				gotoXY(n, y+7);
			} else 
				n++;
			if(inputKeyBoard != 13 && inputKeyBoard != 8){
				userPassword[i++] = (char)inputKeyBoard;
				printf("*");
			}
		}
		
		for(int i = 0; i < 3; i++) {
			if(!strcmp(userAccount, users[i].username) &&
			!strcmp(userPassword, users[i].password)) {
				nonUser = 0;
				user = i;
			}
		}
		
		if(nonUser) {
			gotoXY(x-8, y+10);
			SetColor(4);
			printf("(!) Sai ten dang nhap hoac mat khau");
			Sleep(1000);
			system("cls");
			SetColor(7);	
		} else {
			gotoXY(x-8, y+10);
			SetColor(2);
			printf("(!) Chao mung ban");
			Sleep(1000);
			system("cls");
			SetColor(7);
		}				
	}
	
	return user;
}







