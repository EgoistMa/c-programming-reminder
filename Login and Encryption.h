/*
//  Login and Encryption.h
//  Group Task
//
//  Created by cn2nick on 8/10/19.
//  Copyright © 2019 nick. All rights reserved.
*/

#ifndef Login_and_Encryption_h
#define Login_and_Encryption_h

struct nickname {
    char username[15];
    char password[15];
};
typedef struct nickname user_t;

#include <stdio.h>

void User_registration(int mode);
void User_login(int mode);
int encrypt_file(int mode);
int decrypt_file(int mode);

#endif /* Login_and_Encryption_h */
