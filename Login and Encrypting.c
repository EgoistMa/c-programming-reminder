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
            if(!strcmp(user_list[i].username,usern) && !strcmp(user_list[i].password,passw)){
                return 1;
            }
        }
        return 0;

    } else {
        printf("Opening error.");
    }
    //Users from the file are now saved, we can ask the user to enter username & password
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
