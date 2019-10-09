#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INT 15
#define LOGIN "login.txt"
#define ENCRY "login.bin"

struct nickname {
    char username[MAX_INT];
    char password[MAX_INT];
};
typedef struct nickname user_t;
int encrypt_file(int mode)
{
    FILE *fpr = fopen(LOGIN, "r");
    FILE *fpw = fopen(ENCRY, "wb");
    char buffer = 0;
    while((buffer = getc(fpr))!=EOF)
    {
        if(mode)
        {
            printf("reading %c:%d printting %c:%d\n",buffer,buffer,buffer+12,buffer+12);
        }
        fputc(buffer+12, fpw);
    }
    fclose(fpr);
    fclose(fpw);
    return 0;
}
int decrypt_file(int mode)
{
    FILE *fpr = fopen(ENCRY, "rb");
    FILE *fpw = fopen(LOGIN, "w");
    char buffer = 0;
    if(fpr == NULL)
    {
        return 1;
    }
    while((buffer = getc(fpr))!=EOF)
    {
        if(mode)
        {
            printf("reading %c:%d printting %c:%d\n",buffer,buffer,buffer-12,buffer-12);
        }
        fputc(buffer-12, fpw);
    }
    fclose(fpr);
    fclose(fpw);
    return 0;
}

void User_registration(int mode)
{
    char username[MAX_INT];
    char password1[MAX_INT];
    char password2[MAX_INT];
    printf("Please enter your username\n");
    scanf("%s",username);/*查看长度范围*/
    printf("Please enter your password\n");
    scanf("%s",password1);
    printf("Please confirm your password\n");
    scanf("%s",password2);
    if(!strcmp(password1, password2))
    {
        decrypt_file(mode);
        FILE *fpw = fopen(LOGIN,"a+");
        fprintf(fpw, "%s %s\n",username,password1);
        fclose(fpw);
        encrypt_file(mode);
        printf("registration succeed!\n");
    }else
    {
        printf("Password failed! Try again.\n");
        User_registration(mode);
    }
}

void User_login(int mode)
{
    user_t user_list[100];
    char username[MAX_INT];
    char password[MAX_INT];
    printf("Please enter your username\n");
    scanf("%s",username);
    printf("Please enter your password\n");
    scanf("%s",password);
    decrypt_file(mode);
    FILE *fpr = fopen(LOGIN, "r");
    char buffer = 0;
    int user_number = 0;
    int i;
    while ((buffer = fgetc(fpr))!=EOF)
    {
        if(buffer =='\n')
        {
            user_number++;
        }
    }
    fseek(fpr, 0L, 0);
    for(i=0;i<user_number;i++)
    {
        fscanf(fpr,"%s %s",user_list[i].username,user_list[i].password);
    }
    if(mode)
    {
        for(i=0;i<user_number;i++)
        {
            printf("reading...%s %s\n",user_list[i].username,user_list[i].password);
        }
    }
    fclose(fpr);
    remove(LOGIN);
    int flag = 0;
    /*check password*/
    for(i = 0;i<user_number;i++)
    {
        if(!strcmp(user_list[i].username, username) && !strcmp(user_list[i].password, password))
        {
            flag = 1;
        }
    }
    if(!flag)
    {
        printf("invaild username or password, please try again\n");
        User_login(mode);
    }
}


