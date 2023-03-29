#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

int sizeNode(listStudent students) {
	int count = 0;
	while(students.head != NULL) {
		count++;
		students.head = students.head->next;
	}
	return count;
}

nodeStudent *makeNode(student x) {
	nodeStudent *newNode = malloc(sizeof(nodeStudent));
	newNode->data = x;
	newNode->data.scoreList = x.scoreList;
	newNode->next = NULL;
	return newNode;
}

void pushBack(listStudent *students, student x) {
	nodeStudent *newNode = makeNode(x);
	if(students->head == NULL) {
		students->head = newNode;
		return;
	}
	
	nodeStudent *temp = students->head;
	while(temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newNode;
}

void eraseStudent(listStudent *students, int k) {
	nodeStudent *temp = students->head;
	if(k == 1) {
		if(students->head == NULL) return;
		students->head = students->head->next;
		free(temp);
		return;
	}
	
	for(int i = 0; i < k - 2; i++) {
		temp = temp->next;
	}
	// temp = node (k-1)
	
	//nodeK = node (k)
	nodeStudent *nodeK = temp->next;
	
	//nodeK save address of node (k+1)
	temp->next = nodeK->next;
	
	//free node k;
	free(nodeK);
}

char *lastWord(char *str) {
	char* ptr = strrchr(str, ' '); // Find last space character
    if (ptr != NULL) { // If space found
	    char *last_word = malloc(strlen(ptr + 1) + 1); // Create new string with size of last word
	    strcpy(last_word, ptr + 1); // Copy last word to new string
	    return last_word;
    } else {
    	return NULL;
	}
}

listStudent findStudent(listStudent students, char findString[]) {
	//temp list student
	listStudent matchingStudents;
	matchingStudents.head = NULL;
	
	for(nodeStudent *k = students.head; k != NULL; k = k->next) {
		if(strncasecmp(findString, lastWord(k->data.name), strlen(findString)) == 0) {
			pushBack(&matchingStudents, k->data);
		}
	}
	return matchingStudents;
}

listStudent findScopeScore(listStudent students, int option) {  //0 good, 1 normal, remaining
	//temp list student
	listStudent goodStudents, normalStudents, remaining;
	goodStudents.head = NULL;
	normalStudents.head = NULL;
	remaining.head = NULL;
	
	for(nodeStudent *k = students.head; k != NULL; k = k->next) {
		if(k->data.gpa >= 3.6)
			pushBack(&goodStudents, k->data);
		else if(k->data.gpa >= 3.2)
			pushBack(&normalStudents, k->data);
		else
			pushBack(&remaining, k->data);
	}
	
	if(option == 0)
		return goodStudents;
	else if(option == 1)
		return normalStudents;
	else if(option == 2)
		return remaining;
	else 
		printf("Erorr option!!");
}

void printNode(listStudent students, int yPosition) {
	while(students.head != NULL) {
		int i = 0;
		
		gotoXY(i+=8, yPosition);
		printf("%d ", students.head->data.id);
		
		gotoXY(i+=14, yPosition);
		printf("%s ", students.head->data.studentCode);
		
		gotoXY(i+=14, yPosition);
		checkName(students.head->data.name);
		
		gotoXY(i+=30, yPosition);
		printf("%s ", students.head->data.major);
		
		gotoXY(i+=14, yPosition);
		printDate(students.head->data.date);
		
		gotoXY(i+=14, yPosition);
		printf("%.2f ", students.head->data.gpa);
		
		yPosition++;
		//printf("%.2f ", head->data.scoreList.subject1);
		students.head = students.head->next;	
	}
}

void printNodeScore(listStudent students, int id) {
	nodeStudent *temp = students.head;
	while(temp->data.id != id) {
		temp = temp->next;
	}
	
	int i = 0, j = 6;
	
	gotoXY(i+=8, j);
	printf("%d ", id);
	
	gotoXY(i+=14, j);
	printf("%s ", temp->data.studentCode);
	
	gotoXY(i+=14, j);
	checkName(temp->data.name);
	
	gotoXY(i+=30, j);
	printf("%.2f ", temp->data.scoreList.subject1);
	
	gotoXY(i+=14, j);
	printf("%.2f ", temp->data.scoreList.subject2);
	
	gotoXY(i+=14, j);
	printf("%.2f ", temp->data.scoreList.subject3);
}


void printOneNode(listStudent students, int id) {
	nodeStudent *temp = students.head;
	while(temp->data.id != id) {
		temp = temp->next;
	}
	
	int i = 0, j = 6;
	
	gotoXY(i+=8, j);
	printf("%d ", id);
	
	gotoXY(i+=14, j);
	printf("%s ", temp->data.studentCode);
	
	gotoXY(i+=14, j);
	checkName(temp->data.name);
	
	gotoXY(i+=30, j);
	printf("%s ", temp->data.major);
	
	gotoXY(i+=14, j);
	printDate(temp->data.date);
	
	gotoXY(i+=14, j);
	printf("%.2f ", temp->data.gpa);
}

void printScore(listStudent students, int yPosition) {
	while(students.head != NULL) {
		int i = 0;
		
		gotoXY(i+=8, yPosition);
		printf("%d ", students.head->data.id);
		
		gotoXY(i+=14, yPosition);
		printf("%s ", students.head->data.studentCode);
		
		gotoXY(i+=14, yPosition);
		printf("%s ", students.head->data.name);
		
		gotoXY(i+=30, yPosition);
		printf("%.2f ", students.head->data.scoreList.subject1);
		
		gotoXY(i+=14, yPosition);
		printf("%.2f ", students.head->data.scoreList.subject2);
		
		gotoXY(i+=14, yPosition);
		printf("%.2f ", students.head->data.scoreList.subject3);
		
		yPosition++;
		//printf("%.2f ", head->data.scoreList.subject1);
		students.head = students.head->next;	
	}
}

void sortScoreIncrease(listStudent students) {
	for(nodeStudent *k = students.head; k->next != NULL; k = k->next) { //next last
		for(nodeStudent *h = k->next; h != NULL; h = h->next) { //last
			float maxScore = k->data.gpa;
			if(h->data.gpa > maxScore) maxScore = h->data.gpa;
			if(maxScore != k->data.gpa) {
				student temp = k->data;
				k->data = h->data;
				h->data = temp;
			}	
		}
	}
}

void sortAlphabet(listStudent students) {
	for(nodeStudent *k = students.head; k->next != NULL; k = k->next) {
		for(nodeStudent *h = k->next; h != NULL; h = h->next) {
			char *name1 = lastWord(k->data.name);
			char *name2 = lastWord(h->data.name);
			if(stricmp(name1, name2) > 0) {
				student temp = k->data;
				k->data = h->data;
				h->data = temp;
			}
		}
	}
}

