/*******************************************************************************
 * List header files 
 *******************************************************************************/
#include<stdio.h>/*printf,scanf*/
#include<string.h>

/*******************************************************************************
 * List preprocessing directives - you may define your own.
 *******************************************************************************/
#define MAX_NUM_EVENTS 10
#define MAX_COMMENT_LEN 400
#define DB_EVENT "database"

/*******************************************************************************
 * List structs
 *******************************************************************************/
struct date_time
{
	int year;/*integer 4 numbers*/
    int month;/*integer between 1 and 12 (inclusive)*/
    int day;/*integer between 1 and 31 (inclusive)*/
    int hour;/*integer between 1 and 23(inclusive)*/
};
typedef struct date_time date_time_t;

struct event
{
	date_time_t remind_time;
	char comment[MAX_COMMENT_LEN];
	struct event *next;
};
typedef struct event event_t;

/*******************************************************************************
 * Function prototypes 
 *******************************************************************************/
void print_menu (void);
void addEvent(event_t *events, int *EVENT_NUM);
void deleteEvent(event_t *events, int *EVENT_NUM);
void exportEvent(event_t *events, int EVENT_NUM);
void readEvent(event_t *events, int *EVENT_NUM);
void exit();

int DT_is_valid(const int year, const int month, 
	const int day, const int hour);

/*******************************************************************************
 * Main
 *******************************************************************************/
int main(void)
{
	event_t events [MAX_NUM_EVENTS];
    int EVENT_NUM=0;/*Cerent event number in the program*/
    
    do{
        print_menu();
        int choice;
        scanf("%d", &choice);
        while(getchar()!='\n');
        switch(choice)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                exit(0);
            default:printf("Invalid choice\n");
        }
    }while(1);
	return 0;
}

void print_menu (void)
{
    printf("\n"
           "1. \n"
           "2. \n"
           "3. \n"
           "4. \n"
           "5. \n"
           "..."
           "Enter choice (number between 1-.)>\n");
}

void addEvent(event_t *events, int *EVENT_NUM)
{
	if(*EVENT_NUM<MAX_NUM_EVENTS)
    {
        int year, month, day, hour;
        while(1)
        {
        	printf("Enter year, month, day and hour seperated by spaces>\n");
        	scanf("%d %d %d %d", &year, &month, &day, &hour);
        	while(getchar()!='\n');
        	if(DT_is_valid(year, month, day, hour))
        	{
        		break;
        	}
        	else
        	{
        		printf("Invalid Inputs\n");
        	}
        }
        date_time_t date = {year, month, day, hour};
        events[*EVENT_NUM].remind_time = date;

        (*EVENT_NUM)++;
    }
    else
    {
        printf("Cannot add more events - memory full\n");
        return;
    }
}

int DT_is_valid(const int year, const int month, 
	const int day, const int hour)
	{
		 if((year % 4 == 0 && year % 100 != 0)||(year % 400 == 0))/*leap year*/
		 {
		 	if(month >= 1 && month <= 12)
		 	{
		 		if(month == 1 || month == 3 || month == 5 ||
		 			month == 7 || month == 8 || month == 10
		 			|| month == 12)
		 		{
		 			if(day >= 1 && day <= 31)
		 			{
		 				if(hour >= 1 && hour <= 23)
		 				{
		 					return 1;
		 				}
		 			}
		 		}
		 		else if(month == 4 || month == 6 || month == 9
		 			|| month == 11)
		 		{
		 			if(day >= 1 && day <= 30)
		 			{
		 				if(hour >= 1 && hour <= 23)
		 				{
		 					return 1;
		 				}
		 			}
		 		}
		 		else
		 		{
		 			if(day >= 1 && day <= 29)
		 			{
		 				if(hour >= 1 && hour <= 23)
		 				{
		 					return 1;
		 				}
		 			}
		 		}
		 	}
		 }
		 else
		 {
		 	if(month >= 1 && month <= 12)
		 	{
		 		if(month == 1 || month == 3 || month == 5 ||
		 			month == 7 || month == 8 || month == 10
		 			|| month == 12)
		 		{
		 			if(day >= 1 && day <= 31)
		 			{
		 				if(hour >= 1 && hour <= 23)
		 				{
		 					return 1;
		 				}
		 			}
		 		}
		 		else if(month == 4 || month == 6 || month == 9
		 			|| month == 11)
		 		{
		 			if(day >= 1 && day <= 30)
		 			{
		 				if(hour >= 1 && hour <= 23)
		 				{
		 					return 1;
		 				}
		 			}
		 		}
		 		else
		 		{
		 			if(day >= 1 && day <= 28)
		 			{
		 				if(hour >= 1 && hour <= 23)
		 				{
		 					return 1;
		 				}
		 			}
		 		}
		 	}
		 }

		 return 0;
	}

void deleteEvent(event_t *events, int *EVENT_NUM)
{

}

/*******************************************************************************
 * The program saves the event in the hard disk as a text file named database.
 * inputs:
 * - 
 * outputs:
 * - database file
 *******************************************************************************/
void exportEvent(event_t *events, int EVENT_NUM)
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
void readEvent(event_t *events, int *EVENT_NUM)
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
	
	exit(0);
}