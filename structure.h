typedef struct accounts {
	char username[30];
	char password[30];
} acc;

typedef struct scores {
	float subject1;
	float subject2;
	float subject3;
} scores;

typedef struct student {
	int id;
	char studentCode[11];
	char name[30];
	char major[14];
	char date[14];
	scores scoreList;
	float gpa;
} student;

struct nodeStudent {
	student data;
	struct nodeStudent *next;
};
typedef struct nodeStudent nodeStudent;

typedef struct listStudent {
	nodeStudent *head;
} listStudent;
