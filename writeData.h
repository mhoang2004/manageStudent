#include <stdio.h>
#include <stdlib.h>

void writeData(listStudent *students) {
	//khai bao bien file
	FILE *fileout;
	FILE *filescores;
	
	//mo file
	fileout = fopen("data.txt", "w");
	filescores = fopen("scores.txt", "w");
	
	//kiem tra
	if(fileout == NULL || filescores == NULL) {
		printf("Error! File not found!");
		exit(0);
	}
	
	//ghi file
	int i = 0;
	for(nodeStudent *k = students->head; k != NULL; k = k->next) {
		i++;
		fprintf(fileout, "%d, %s, %s, %s, %s, %.2f\n", i, k->data.studentCode, 
		k->data.name, k->data.major, k->data.date, k->data.gpa);
		fprintf(filescores, "%.2f %.2f %.2f\n", k->data.scoreList.subject1,
		k->data.scoreList.subject2, k->data.scoreList.subject3);
	}
	
	//dong file
	fclose(fileout);
	fclose(filescores);
}

