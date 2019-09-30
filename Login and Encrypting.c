#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERS 10

struct user {
    char username[15];
    char password[15];
};
typedef struct user user_t;

void Rencrypting(char* word, int stringsize);
void Encrypting(char* word, int stringsize);
int VerifCombi(char username[], char password[]);
void login(void);
void LoadUsers(user_t user_list[]);


int main(void){
    user_t user_list[MAX_USERS];
    LoadUsers(user_list);
    //login();
    return 0;
}

void LoadUsers(user_t user_list[]) {
    FILE* fichier = NULL;
    fichier = fopen("login.txt", "r");
    int NumberLogin = 0;
    int i = 0, j = 0;
    if (fichier != NULL){
        char line[30];
        char username[15];
        char password[15];
        while(fgets(line,30, fichier)){  //Reading the file line by line
            i = 0;
            fscanf(fichier,"%s", &line);
            while(line[i] != '|') {  //Reading the first 15 characters of the line and saving them in username[], stopping when there is a space.
                username[i] = line[i];
                i++;
            }
            i++;
            while (line[i] != '|') {  //Reading the next 15 characters of the line and saving them in password[], stopping when there is a space.
                password[i] = line[i];
                i++;
                printf("a");
            }
            strcpy(user_list[NumberLogin].username, username);
            strcpy(user_list[NumberLogin].password, password);
            NumberLogin++;
        }
    } else {
        printf("Opening error.");
    }
    for (i = 0; i<NumberLogin; i++) {
        printf("Username: %s Password: %s\n", &user_list[i].username, &user_list[i].password);
    }
}

//void UsersNumber()
//ASK a login and a password, say if they match in our login file                   Matthieu COLIN
void login(void) {
    printf("\nEnter your user name: ");
    char username[15];
    scanf("%s", username);
    printf("\nEnter your password: ");
    char password[15];
    scanf("%s", password);
    int combi = VerifCombi(username, password);
    if(combi == 1){
        printf("username and password verified.");
    } else printf("wrong combinaison.");

}

//Return 0 if the user and password don't match and 1 if they do                Matthieu COLIN
int VerifCombi(char username[], char password[]) {
    FILE* fichier = NULL;
    fichier = fopen("login.txt", "r");
    int i, j, k;
    int same = 1;
    char line[30];
    if(fichier != NULL) {
        char userreading[15];
        char pwreading[15];
        while(fgets(line,sizeof(line), fichier)){
            j = 0, k = 0;
            fscanf(fichier,"%s", &line);
            same = 1;
            //Getting username from the file & keeping the length with j
            for(i=0; i<15; i++) {
                if(line[i] != ' '){
                    userreading[i] = line[i];
                    printf("I got %c but you entered %c\n", userreading[i], username[i]);
                } else {
                    userreading[i] = '\0';
                    i = 15;
                }
                j++;
            }
            //Getting password from the file & keeping the length with k
            for(i = 0; i<15; i++) {
                pwreading[i] = line[i+15];
                printf("and I got %c but you entered %c\n", pwreading[i], password[i]);
                if(line[i+15] == ' ') {
                    pwreading[i] = '\0';
                    i = 15;
                }
                k++;
            }
            for (i=0; i<j; i++){
                //Encrypting
                //printf("je recup %c alors que tu as rentre %c\n", userreading[i], username[i]);
                if(username[i] == userreading[i]){
                    printf("This user character is good.\n");
                } else {
                    printf("This user character is false.\n");
                    same = 0;
                }
            }
            for (i=0; i<k;i++){
                //Encrypting
                //printf("et ici je recup %c alors que tu as rentre %c\n", pwreading[i], password[i],);
                if(password[i] == pwreading[i]){
                    printf("This pw character is good.\n");
                } else {
                    printf("This pw character is false.\n");
                    same = 0;
                }
            }
            //if (same = 1) {
              //  return same;
            //}
        }
        fclose(fichier);
    }
    else{
        printf("Opening error.");
        return 0;
    }
    return same;
}

//Encrypting, receive a string and his size and return an encrypted one             Matthieu COLIN
void Encrypting(char* word, int stringsize) {
    int i;
    for (i = 0; i < sizeof(word); i++){
        word[i] = word[i] + 12;
    }
    word[stringsize - 1] = '\0';
}

//Receive an encrypted string and his size and return a normal string               Matthieu COLIN
void Rencrypting(char* word, int stringsize){
    int i;
    for (i = 0; i < sizeof(word); i++){
        word[i] = word[i] - 12;
    }
    word[stringsize - 1] = '\0';
}
