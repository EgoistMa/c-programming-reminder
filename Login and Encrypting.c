#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    login();
    return 0;
}

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
