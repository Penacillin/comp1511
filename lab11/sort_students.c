// starting point for COMP1511 lab 11

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_STUDENT_NAME_LENGTH 128
#define MAX_GRADE_STRING_LENGTH 22
#define MAX_LAB_NAME_LENGTH 32
#define MAX_LINE_LENGTH 4096

struct student {
    int              zid;
    char             name[MAX_STUDENT_NAME_LENGTH + 1];
    char             lab_name[MAX_LAB_NAME_LENGTH + 1];
    char             lab_grades[MAX_GRADE_STRING_LENGTH + 1];
    struct student   *next;
};

struct student *read_students_file(char filename[]);
struct student *read_student(FILE *stream);
double grades2labmark(char grades[]);

int studcmp(struct student* first, struct student* second)
{
    int comp = 0;
    int fLastName = 0;
    int sLastName = 0;
    
    int i = 0;
    for( i = 0; i < strlen(first->name) && first->name[i] != ' '; i++)
    { }
    fLastName = i + 1; 
    for(i = 0; i < strlen(second->name) && second->name[i] != ' '; i++)
    { }
    sLastName = i + 1;
    
        
    comp = strcmp(first->name + fLastName, second->name + sLastName);
    if(comp!= 0)
       return comp;
    
    comp = strcmp(first->name, second->name);
    if(comp != 0)
        return comp;
        
    return first->zid - second->zid;
}

struct student* sortStudentList(struct student* list)
{
    return NULL;
}

int main(int argc, char *argv[]) {
    // CHANGE THIS CODE

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <marks-file>\n", argv[0]);
        return 1;
    }

    struct student *student_list = read_students_file(argv[1]);
  
    //printf("Students file read into linked list (pointer=%p)\n", student_list);
    
    
    // Order the list
    // Get the first lowest (reset the head of the list)
    struct student* lowest = student_list;
	int first = 1;
    
	for(struct student* studentIter = student_list;first == 1;)
    {
        struct student* studentIter2 = studentIter;
        //printf("gonna check from studentiter %s\n", studentIter2->name);
        for(;studentIter2->next != NULL; studentIter2 = studentIter2->next)
        {
            if(studcmp(studentIter2->next, lowest->next) < 0)
                lowest = studentIter2;
        }
        //printf("Lowest is now %s\n", lowest->next->name);
        // Swap lowest to head
		struct student* tempLowest = lowest->next;
		struct student* tempLowestNext = lowest->next->next;
		struct student* tempStudentIterNext = studentIter->next;
		struct student* tempStudentIter = studentIter;
		student_list = tempLowest;
		student_list->next = tempStudentIter;
		lowest->next = tempLowestNext;
		first = 0;
    }
	
    for(struct student* studentIter = student_list;studentIter != NULL && studentIter->next != NULL; )
    {
        struct student* studentIter2 = studentIter->next;
		lowest = studentIter;
        //printf("gonna check from studentiter %s\n", studentIter2->name);
        for(;studentIter2->next != NULL && lowest->next != NULL; studentIter2 = studentIter2->next)
        {
            if(studcmp(studentIter2->next, lowest->next) < 0)
                lowest = studentIter2;
        }
        //printf("Lowest is now %s\n", lowest->next->name);
        // Swap lowest to current pos
        if(studentIter->next != lowest->next) 
		{
            struct student* tempLowest = lowest->next;
            struct student* tempLowestNext = NULL;
			if(lowest->next != NULL)
				tempLowestNext = lowest->next->next;
			
            struct student* tempStudentIterNext = studentIter->next;
            struct student* tempStudentIter = studentIter;
            // Put lowest into studentIters place            
            studentIter->next = tempLowest;
			if(studentIter->next != NULL)
				studentIter->next->next = tempStudentIterNext;
					
			lowest->next = tempLowestNext;
		
           //printf("lowest next is now %s\n", lowest->next->name);
        }
        //printf("new student iter %s\n", studentIter->name);
		if(studentIter != NULL)
			(studentIter = studentIter->next);
    }
    
    //printf("lowest %s\n", lowest->name);
    
   // return 0;
    
    // Print order list
    for(struct student* studentIter = student_list;studentIter != NULL; studentIter = studentIter->next)
    {
       
            printf("%d %-30s %-12s %-22s %4.1lf\n", studentIter->zid, studentIter->name, studentIter->lab_name,
                                           studentIter->lab_grades, grades2labmark(studentIter->lab_grades));
        
    }
    
    return 0;
}

double grades2labmark(char grades[])
{
    int len = strlen(grades);
    double score = 0;
    for(int i = 0; i < len; i++)
    {
        if(grades[i] == '.')
        {
            score += 0;
        }
        else if(grades[i] == 'C')
        {
            score += 0.5;
        }
        else if(grades[i] == 'B')
        {
            score += 0.8;
        }
        else if(grades[i] == 'A')
        {
            if(grades[i+1] == '+')
            {
                score += 1.2;
                i++;
            }
            else
                score += 1.0;
        }
    }
    
    return score > 10 ? 10 : score;;
}


// DO NOT CHANGE THE CODE BELOW HERE - DO NOT CHANGE read_students_file

// read_students_file reads a file where line contains information for 1 student
// it creates a linked of student structs containing the information
// it returns a pointer to the head of the list

struct student *read_students_file(char filename[]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr,"warning file %s could not  be opened for reading\n", filename);
        return NULL;
    }

    struct student *first_student = NULL;
    struct student *last_student = NULL;
    struct student *s;
    while ((s = read_student(fp)) != NULL) {
        if (last_student == NULL) {
            first_student = s;
            last_student = s;
        } else {
            last_student->next = s;
            last_student = s;
        }
    }

    fclose(fp);
    return first_student;
}

// DO NOT CHANGE read_student

// read_student mallocs a student struct
// and reads a line in this format:
//
// 5099703 Tsun Bordignon thu13-sitar A+A+CABAB..A.
//
// stores the values in the struct field
// and returns a pointer to the struct

struct student *read_student(FILE *stream) {
    char line[MAX_LINE_LENGTH];

    struct student *s = malloc(sizeof (struct student));
    assert(s);

    if (fgets(line, MAX_LINE_LENGTH, stream) == NULL) {
        free(s);
        return NULL;
    }

    char *newline_ptr = strchr(line, '\n');
    assert(newline_ptr);
    *newline_ptr = '\0';

    char *space_ptr = strrchr(line, ' ');
    assert(space_ptr);
    strncpy(s->lab_grades, space_ptr + 1, MAX_GRADE_STRING_LENGTH);
    s->lab_grades[MAX_GRADE_STRING_LENGTH] = '\0';
    *space_ptr = '\0';

    space_ptr = strrchr(line, ' ');
    assert(space_ptr);
    strncpy(s->lab_name, space_ptr + 1, MAX_LAB_NAME_LENGTH);
    s->lab_name[MAX_LAB_NAME_LENGTH] = '\0';
    *space_ptr = '\0';

    space_ptr = strchr(line, ' ');
    assert(space_ptr);
    strncpy(s->name, space_ptr + 1, MAX_STUDENT_NAME_LENGTH);
    s->name[MAX_STUDENT_NAME_LENGTH] = '\0';
    *space_ptr = '\0';

    s->zid = atoi(line);
    s->next = NULL;
    return s;
}
