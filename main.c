/*******************************************************************************
 * List header files
 *******************************************************************************/
#include<stdio.h>/*printf,scanf*/
#include<stdlib.h>
#include<string.h>
#include "zip.h"
#include "Login and Encryption.h"

/*******************************************************************************
 * List preprocessing directives - you may define your own.
 *******************************************************************************/
#define MAX_NUM_EVENTS 10
#define MAX_COMMENT_LEN 400
#define DB_EVENT "database.txt"

#define MAX_USERS 100

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
};
typedef struct event event_t;

int debug = 0;

/*******************************************************************************
 * Function prototypes
 *******************************************************************************/
void print_welcome(void);
void print_menu (void);
void addEvent(event_t *events, int *EVENT_NUM);
void deleteEvent(event_t *events, int *EVENT_NUM);
void display_events(event_t *events, int EVENT_NUM);
int sort_by_data (event_t *events , int EVENT_NUM);
void exportEvent(event_t *events, int EVENT_NUM);
void readEvent(event_t *events, int *EVENT_NUM);
void exitProgram(event_t* events,int EVENT_NUM);
int display_all(event_t* events,int EVENT_NUM);

int DT_is_valid(const int year, const int month, const int day);
int need_swap(event_t e1,event_t e2);

/*******************************************************************************
 * Main
 *******************************************************************************/
int main(void)
{
    event_t events [MAX_NUM_EVENTS] = {{{0,0,0},0}};
    int EVENT_NUM=0;/*Cerent event number in the program*/
    char pause;
    print_welcome();
    printf("Welcome to ReminderX!\n");
    printf("Do you have an account? (Y/N)>\n");
    char flag;
    scanf("%c",&flag);
    if (flag == 'Y' || flag == 'y')
    {
        User_login(debug);
    }
    else
    {
        User_registration(debug);
    }
    readEvent(events, &EVENT_NUM);
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
            case 3:display_events(events, EVENT_NUM);
                break;
            case 4:display_all(events, EVENT_NUM);
                break;
            case 5:exportEvent(events, EVENT_NUM);
                break;
            case 6:readEvent(events, &EVENT_NUM);
                break;
            case 7:zip(debug);
                printf("press any key to continue ...\n");
                scanf("%c", &pause);
                break;
            case 8:unzip(debug);
                printf("press any key to continue ...\n");
                scanf("%c", &pause);
                break;
            case 9:exitProgram(events,EVENT_NUM);
                exit(0);
            case 999:
                debug = 1;
                printf("Debug Enabled.\n");
                break;
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
    printf("                                                                 auther: Tianyu Ma\n");
    printf("                                                                         Matthieu Colin\n");
    printf("                                                                         Nuo Chen\n");
    printf("                                                                         Abhinav Ganguly\n");
    printf("                                                                         Suet Yi Chui\n");
    printf("\n\n");
}

void print_menu (void)
{
    printf("\n"
           "1. add an event\n"
           "2. delete an event\n"
           "3. search events by date and display\n"
           "4. display all the events and sort events by date\n"
           "5. save the events to the database file\n"
           "6. load the events from the database file\n"
           "7. zip the program\n"
           "8. unzip the program\n"
           "9. exit\n"
           "Enter choice (number between 1-9)>\n");
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
                        return 1;                         }
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

int display_all(event_t *events,int EVENT_NUM)
{
    if (EVENT_NUM == 0)
    {
        printf("There is no events.\n");
    }
    else
    {
        sort_by_data(events, EVENT_NUM);
        int i;
        for(i=0;i<EVENT_NUM;i++)
        {
            printf("reminder #%d :%d-%d-%d \n notes: %s\n",i+1,events[i].remind_time.year,events[i].remind_time.month,events[i].remind_time.day,events[i].comment);
        }
    }
    return 0;
}

void deleteEvent(event_t *events, int *EVENT_NUM)
{
    display_all(events,*EVENT_NUM);
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

void display_events(event_t *events, int EVENT_NUM)
{
    int i,j,k;
    event_t e1;
    printf("Enter datetime (year)>\n");
    scanf("%d", &e1.remind_time.year);
    while(getchar()!='\n');
    if(EVENT_NUM==0)
    {
        printf("No events\n");
    }
    else
    {
        int flag1=0;
        for(i=0; i<EVENT_NUM; i++)
        {
            if(e1.remind_time.year==events[i].remind_time.year)
            {
                printf("Enter datetime (month)>\n");
                scanf("%d",&e1.remind_time.month);
                while(getchar()!='\n');
                for(j=0; j<EVENT_NUM; j++)
                {
                    if(e1.remind_time.month==events[i].remind_time.month)
                    {
                        printf("Enter datetime (day)>\n");
                        scanf("%d",&e1.remind_time.day);
                        while(getchar()!='\n');
                        for (k=0; k<EVENT_NUM; k++)
                        {
                            if (e1.remind_time.day==events[i].remind_time.day)
                            {
                                printf("%04d %02d %02d\n", events[i].remind_time.year,
                                       events[i].remind_time.month,events[i].remind_time.day);
                                printf("%s\n", events[i].comment);
                                flag1=1;
                            }
                        }
                    }
                }
            }
        }
        if(flag1==0)
        {
            printf("No events\n");
        }
    }
}

int need_swap(event_t e1,event_t e2)
{
    /* All cases when true should be returned*/
    if (e1.remind_time.year > e2.remind_time.year)
    {
        return 1;
    }
    if (e1.remind_time.year == e2.remind_time.year && e1.remind_time.month > e2.remind_time.month)
    {
        return 1;
    }
    if (e1.remind_time.year == e2.remind_time.year && e1.remind_time.month == e2.remind_time.month &&
        e1.remind_time.day > e2.remind_time.day)
    {
        return 1;
    }
    return 0;
    /*when need swap return 1*/
}

int sort_by_data (event_t *events , int EVENT_NUM)
{
    int i=0;
    int j=0;
    event_t temp;
    for(j=0;j<EVENT_NUM-1;j++)
    {
        for(i=0;i<EVENT_NUM-1;i++)
        {
            if(need_swap(events[i],events[i+1]))
            {
                temp = events[i];
                events[i] = events[i+1];
                events[i+1] = temp;
            }
        }
    }
    return 0;
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
    if((fp = fopen(DB_EVENT, "r")) == NULL)
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
void exitProgram(event_t* events,int EVENT_NUM)
{
    printf("Do you want to save your Calendar? Y/N\n");
    char flag;
    scanf("%c",&flag);
    if (flag == 'Y' || flag == 'y') {
        exportEvent(events,EVENT_NUM);
    }
    exit(0);
}
