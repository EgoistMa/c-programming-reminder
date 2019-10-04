/*******************************************************************************
 * List header files 
 *******************************************************************************/
#include<stdio.h>/*printf,scanf*/
#include<stdlib.h>
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
void print_welcome(void);
void print_menu (void);
void addEvent(event_t *events, int *EVENT_NUM);
void deleteEvent(event_t *events, int *EVENT_NUM);
void exportEvent(event_t *events, int EVENT_NUM);
void readEvent(event_t *events, int *EVENT_NUM);
void exitProgram(void);

int DT_is_valid(const int year, const int month, const int day);
event_t* search_by_date(event_t *root,int year,int month,int day);

/*******************************************************************************
 * Main
 *******************************************************************************/
int main(void)
{
	event_t events [MAX_NUM_EVENTS];
    int EVENT_NUM=0;/*Cerent event number in the program*/
    print_welcome();
    do{
        print_menu();
        int choice;
        scanf("%d", &choice);
        while(getchar()!='\n');
        switch(choice)
        {
            case 1:addEvent(events, &EVENT_NUM);
                break;
            case 2:deleteEvent(events, &EVENT_NUM);
                break;
            case 3:exportEvent(events, EVENT_NUM);
                break;
            case 4:readEvent(events, &EVENT_NUM);
                break;
            case 5:exitProgram();
                exit(0);
            default:printf("Invalid choice\n");
        }
    }while(1);
	return 0;
}

void print_welcome(void)
{
 printf("\n\n\n\n");
 printf("                               _             _              __   __ \n");
 printf("                              (_)           | |             \\ \\ / / \n");
 printf("         _ __  ___  _ __ ___   _  _ __    __| |  ___  _ __   \\ V /  \n");
 printf("        | '__|/ _ \\| '_ ` _ \\ | || '_ \\  / _` | / _ \\| '__|   > <   \n");
 printf("        | |  |  __/| | | | | || || | | || (_| ||  __/| |     / ^ \\  \n");
 printf("        |_|   \\___||_| |_| |_||_||_| |_| \\__,_| \\___||_|    /_/ \\_\\ \n");
 printf("\n");
 printf("                                     _                __      ___   \n");
 printf("                                    (_)              /_ |    / _ \\  \n");
 printf("            __   __ ___  _ __  ___  _   ___   _ __    | |   | | | | \n");
 printf("            \\ \\ / // _ \\| '__|/ __|| | / _ \\ | '_ \\   | |   | | | | \n");
 printf("             \\ V /|  __/| |   \\__ \\| || (_) || | | |  | | _ | |_| | \n");
 printf("              \\_/  \\___||_|   |___/|_| \\___/ |_| |_|  |_|(_) \\___/  \n");
 printf("\n");
 printf("                                                                 auther: a\n");
 printf("                                                                         b\n");
 printf("                                                                         c\n");
 printf("                                                                         d\n");
 printf("                                                                         e\n");
 printf("\n\n");
}

void print_menu (void)
{
    printf("\n"
    	   "Welcome to ReminderX!\n"
           "1. add an event\n"
           "2. delete an event\n"
           "3. save the events to the database file\n"
           "4. load the events from the database file\n"
           "5. exit\n"
           "Enter choice (number between 1-5)>\n");
}

void addEvent(event_t *events, int *EVENT_NUM)
{
	if(*EVENT_NUM<MAX_NUM_EVENTS)
    {
        int year, month, day;
        while(1)
        {
        	printf("Enter year, month and day seperated by spaces>\n");
        	scanf("%d %d %d", &year, &month, &day);
        	while(getchar()!='\n');
        	if(DT_is_valid(year, month, day))
        	{
        		break;
        	}
        	else
        	{
        		printf("Invalid Inputs\n");
        	}
        }
        date_time_t date = {year, month, day};
        events[*EVENT_NUM].remind_time = date;

        char temp[MAX_COMMENT_LEN+1];
       	printf("Enter comments>\n");
       	scanf("%s", temp);
        while(getchar()!='\n');
        strcpy(events[*EVENT_NUM].comment,temp);

        (*EVENT_NUM)++;
    }
    else
    {
        printf("Cannot add more events - memory full\n");
        return;
    }
}

int DT_is_valid(const int year, const int month, const int day)
	{
		if(year>=0 && year<=9999)
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
			 				return 1;
			 			}
			 		}
			 		else if(month == 4 || month == 6 || month == 9
			 			|| month == 11)
			 		{
			 			if(day >= 1 && day <= 30)
			 			{
			 				return 1;			 			}
			 		}
			 		else
			 		{
			 			if(day >= 1 && day <= 29)
			 			{
			 				return 1;
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
			 				return 1;
			 			}
			 		}
			 		else if(month == 4 || month == 6 || month == 9
			 			|| month == 11)
			 		{
			 			if(day >= 1 && day <= 30)
			 			{
			 				return 1;
			 			}
			 		}
			 		else
			 		{
			 			if(day >= 1 && day <= 28)
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
	int position, i;
	printf("Enter the location where you wish to delete element\n");
	scanf("%d", &position);

	if (position > *EVENT_NUM)
	{
    	printf("Deletion not possible.\n");
	}
   	else
   	{
      	for (i = position - 1; i < *EVENT_NUM - 1; i++)
      	{
        	events[i] = events[i+1];
    	}
    	(*EVENT_NUM)--;
    	printf("Deletion succeed!\n");
   	}
}

void display_records(event_t *events, int EVENT_NUM)
{

}

event_t* search_by_date(event_t *root,int year,int month,int day)
{
   
    event_t *current;
    event_t *results = NULL;
    event_t *head = results;

    for (current = root; current !=NULL; current = (*current).next) {
        if((*current).remind_time.year == year && (*current).remind_time.month
         == month && (*current).remind_time.day == day)
        {
            results = current;
            results = (*results).next;
        }
    }
    return head;
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
	FILE *fp =fopen(DB_EVENT, "a");
	int i;
	fprintf(fp, "%d\n", EVENT_NUM);
	for(i=0; i<EVENT_NUM; i++)
	{
		fprintf(fp, "%d %d %d\n", events[i].remind_time.year, 
			events[i].remind_time.month, events[i].remind_time.day);
		fprintf(fp, "%s\n", events[i].comment);
	}
	printf("Save succeed\n");
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
    if((fp = fopen(DB_EVENT, "a+")) == NULL)
    {
        printf("Read error\n");
        return;
    }
    else
    {
    	fscanf(fp, "%d", EVENT_NUM);
        int i;
        for(i=0; i<*EVENT_NUM; i++)
        {
            fscanf(fp, "%d %d %d", &events[i].remind_time.year, 
			&events[i].remind_time.month, &events[i].remind_time.day);
			fscanf(fp, "%s", events[i].comment);
        }
        printf("Read available\n");
        fclose(fp);
    }
}

/*******************************************************************************
 * Exit the interactive program and save the database.
 * inputs:
 * - none
 * outputs:
 * - none
 *******************************************************************************/
void exitProgram(void)
{
	exit(0);
}