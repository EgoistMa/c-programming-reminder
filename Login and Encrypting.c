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
int LoadUsers(user_t user_list[]);


int main(void){
    user_t user_list[MAX_USERS];
    int verif = LoadUsers(user_list);
    if (verif == 1) {
        printf("Login in successfull.\n");
    } else printf("Login in failed.\n");
    //login();
    return 0;
}

int LoadUsers(user_t user_list[]) {
    FILE* fichier = NULL;
    fichier = fopen("login.txt", "r");
    if (fichier != NULL){
        int nbline = 0, i = 0, j = 0;
        char c;
        do
        {
            c = fgetc(fichier);
            if (c == '\n') {
                nbline++;
            }
        } while (c != EOF);
        nbline++;
        rewind(fichier);
        for(i = 0; i < nbline; i++){  //Reading the file line by line
            fscanf(fichier, "%s %s", user_list[i].username, user_list[i].password);
        }
        for (i = 0; i<nbline; i++) {
            printf("Username: %s Password: %s\n", &user_list[i].username, &user_list[i].password);
        }
        printf("Username: ");
        char usern[15];
        scanf("%s", usern);
        printf("Password: ");
        char passw[15];
        scanf("%s", passw);
        for(i = 0; i<nbline; i++) {
            printf("[username] you entered %s and i'm reading %s\n", usern, user_list[i].username);
            printf("[password] you entered %s and i'm reading %s\n", passw, user_list[i].password);
            printf("\n");
            if(user_list[i].username == usern && user_list[i].password == passw){
                return 1;
            }
        }
        return 0;

    } else {
        printf("Opening error.");
    }
    //Users from the file are now saved, we can ask the user to enter username & password

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
