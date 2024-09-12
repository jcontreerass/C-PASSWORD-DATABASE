#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#define LENGTH 50


typedef struct {
    char user[LENGTH];
    char password[LENGTH];
    char website[LENGTH];
}USER;



void print_user(USER u) {
    printf("WEB: %s\n", u.website);
    printf("USER: %s\n", u.user);
    printf("PASSWORD: %s\n", u.password);
}

void ask_data(USER *u) {
    printf("Introduce the website:\n");
    gets(u->website);
    fflush(stdin);
    printf("Introduce your USER:\n");
    gets(u->user);
    fflush(stdin);
    printf("Introduce your PASSWORD:\n");
    gets(u->password);
    fflush(stdin);

    print_user(*u);
}

bool search_user(FILE *f1) {
    char web[50], name[50];
    fflush(stdin);
    printf("Introduce the website you want to search: ");
    gets(web);
    fflush(stdin);
    printf("Introduce the user you want to search: ");
    gets(name);
    fflush(stdin);

    bool res = false;
    USER aux;
    f1 = fopen("passwd_database.bat", "rb");
    while(fread(&aux, sizeof(USER), 1, f1) && !res) {
        if(strcmp(aux.website, web) && strcmp(aux.user, name)) {
            res = true;
            printf("USER: %-50s\n", aux.user);
            printf("PASSWORD: %-50s\n", aux.password);
        }
    }
    if(res == 0) {
        printf("\nUser not found");
    }
    fclose(f1);
    return res;
}

bool search_if_repeated(FILE *f1, char name[50], char web[50]) {
    bool res = false;
    USER aux;
    f1 = fopen("passwd_database.bat", "rb");
    while(fread(&aux, sizeof(USER), 1, f1) && !res) {
        if(strcmp(aux.website, web) && strcmp(aux.user, name)) {
            res = true;
        }
    }
    fclose(f1);
    return res;
}

void change_passwd(USER *u) {
    char psswd1[50], psswd2[50];
    do {
        printf("Type the new password:\n");
        gets(psswd1);
        printf("Type it again: \n");
        gets(psswd2);
    }while(!strcmp(psswd1, psswd2));
    *u->password = psswd1;
}

void add_user(USER *u, FILE *f1) {
    char confirm;
    printf("Do you want to add the user '%s' to de database?(y/n)", u->user);
    scanf("%c", &confirm);
    fflush(stdin);
    if(confirm == 'y' && !search_if_repeated(f1, u->user, u->website)) {
        f1 = fopen("passwd_database.bat", "ab");
        fwrite(&u, sizeof(USER), 1, f1);
        fclose(f1);
        printf("Added!\n");
    }else if(confirm == 'y' && search_if_repeated(f1, u->user, u->website)) {
        printf("You already added a user in that website");
    }
}

int main(void) {
    FILE *f1 = NULL;
    USER aux;

    int option;
    printf("---- MAIN MENU ----\n");
    printf("1. Add user.\n");
    printf("2. Search user.\n");
    printf("0. Exit\n");
    printf("Introduce option: ");
    do {
        scanf("%d", &option);
        fflush(stdin);
    }while(option != 0 && option != 1 && option != 2);


    if(option == 1) {
        ask_data(&aux);
        add_user(&aux, f1);
    }else if(option == 2) {
        search_user(f1);
    }

    return 0;
}
