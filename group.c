/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3 Group
 * Name: Nuo Chen
 * Student ID: 12843773
 * Date of submission:25 Sep
 * A brief statement on what you could achieve (less than 50 words):
 * export database
 * read database
 * exit
 *******************************************************************************/
#include<stdio.h>
#define DB_EVENT "database"

struct date_time
{
    int month;/*integer between 1 and 12 (inclusive)*/
    int day;/*integer between 1 and 31 (inclusive)*/
    int hour;/*integer between 0 and 23 (inclusive)*/
    int minute;/*integer between 0 and 59 (inclusive)*/
};
typedef struct date_time date_time_t;

struct event
{
	date_time_t time;
	char comment[];

};
typedef struct event event_t;

void exportEvent();
void readEvent();
void exit();

int main(void)
{

	return 0;
}

/*******************************************************************************
 * The program saves the event in the hard disk as a text file named database.
 * inputs:
 * - 
 * outputs:
 * - database file
 *******************************************************************************/
void exportEvent()
{
	FILE *fp =fopen(DB_EVENT, "w");

	fclose(fp);
}

/*******************************************************************************
 * The program reads the database file and put the data into events.
 * inputs:
 * - 
 * outputs:
 * - database file
 *******************************************************************************/
void readEvent()
{
	FILE *fp;
    if((fp = fopen(DB_EVENT, "r")) == NULL)
    {
        printf("Read error\n");
        return;
    }
    else
    {

    }
}

/*******************************************************************************
 * Exit the interactive program and save the database.
 * inputs:
 * - none
 * outputs:
 * - none
 *******************************************************************************/
void exit()
{
	exportEvent();
	exit(0);
}