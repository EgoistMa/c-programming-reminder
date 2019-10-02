#include <stdio.h>


struct record{
    int;
    char;
    float;
    double;
    
};


int main()
{
    
    printf("Welcome to calendar reminder.\n");
    
    return 0;
    
};

typedef struct record record_list;

void display_menu(void){
    
    printf("\n"
           "1.Log in\n"
           "2.Add event\n"
           "3.Delete event\n"
           "4.display\n"
           "5.Search by date\n"
           "6.Enter database\n"
           "7.Read database\n"
           "8.Exit\n"
           "Enter choice (number between 1-8)>\n"
           
           );
    
    
}

int main {
         switch(choice){
             case 1:
                 /*statement*/
                 break;
             case 2:
                 addEvent(*events,*EVENT_NUM);
                 break;
             case 3:
                 deleteEvent(*events,*EVENT_NUM);
                 break;
             case 4:
                 /*statement*/
                 break;
             case 5:
                 /*statement*/
                 break;
             case 6:
                 exportEvent(*events,*EVENT_NUM);
                 break;
             case 7:
                 readEvent(*events,*EVENT_NUM);
                 break;
             case 8:
                 /*statement*/
                 break;
             default:printf("Invalid choice\n");
                 
         }
         
}
