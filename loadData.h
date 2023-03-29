#include <stdio.h>
#include <stdlib.h>

void loadData(listStudent *students) {
		student *a = malloc(sizeof(student));
		
		//declare variable to manip file
		FILE *filein;
		FILE *filescore;
			
		//open file
		filein = fopen("data.txt", "r");
		filescore = fopen("scores.txt", "r");
		
		//check
		if(filein == NULL || filescore == NULL) {
			printf("Error file!");
			exit(0);
		}
		
		while(fscanf(filein, "%d, %[^,], %[^,], %[^,], %[^,], %f", &a->id,
		a->studentCode, a->name, a->major, a->date, &a->gpa) == 6) {	
			fscanf(filescore, "%f %f %f", &a->scoreList.subject1,
			&a->scoreList.subject2, &a->scoreList.subject3);
			pushBack(students, *a);
		}
		
		//close file
		fclose(filein);	
		fclose(filescore);
}

