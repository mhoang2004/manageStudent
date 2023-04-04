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

		char userAccount[30], userPassword[30];
		
		gotoXY(x-8, y);
		printf("Nhap tai khoan:");
		onlyBox(x-8, y+1, 40, 2);
		fgets(userAccount, sizeof(userAccount), stdin);
		userAccount[strlen(userAccount) - 1] = '\0';
					
		gotoXY(x-8, y+5);
		printf("Nhap mat khau:");
		onlyBox(x-8, y+6, 40, 2);
		fgets(userPassword, sizeof(userPassword), stdin);
		userPassword[strlen(userPassword) - 1] = '\0';
		
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





