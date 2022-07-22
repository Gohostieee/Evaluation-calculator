//
// Created by Stt on 7/21/2022.
//
#define max 200
#ifndef C_VALCAPT_H
#define C_VALCAPT_H
#define Black "\033[0;30m"
#define Red "\033[0;31m"
#define Green "\033[0;32m"
#define Yellow "\033[0;33m"
#define White "\033[0;37m"
#endif //C_VALCAPT_H

#include <conio.h>


#include <stdlib.h>

int checkNumString(char string[max], char letter, char mode) {

    if (mode) {

        for (int x = 0; string[x]; x++) {
            if (!(string[x] >= 48 && string[x] <= 57)) {
                return 0;
            }

        }
    } else {
        if (!(letter >= 48 && letter <= 57)) {
            return 0;
        }
    }
    return 1;
}

void printString(char string[max], int mode, int size) {
    if (mode) {
        for (int x = 0; string[x]; x++) {
            printf("%c", string[x]);
        }
        return;
    }
    for (int x = 0; x < size; x++) {
        printf("%c", string[x]);
    }
    return;
}

void remDecNum(char *str, int num) {
    int count = 1, seenPeriod = 0, numAft = 0;
    for (int x = 0; str[x]; x++) {
        count++;
        if (seenPeriod) {
            numAft++;
            if (numAft > num) {
                str[x] = '\0';
                printf("\n pain\n");
            }
        }
        else if (str[x] == '.') { seenPeriod = 1; }
    }
}

float getNum(char string[max], int decNum, int size) {
    int count = 0, periodCount = 0;
    fflush(0);
    char resp[max], charResp;
    system("cls");

    printf("\n%s", string);

    do {
        charResp = getch();
        system("cls");


        if (charResp == 8 && count != 0) {

            count--;
            if (resp[count] == 46) { periodCount--; }
            resp[count] = '\0';
        }
        if (resp[0] == 48) {
            count--;
            resp[count] = '\0';
        }
        printf("\n%s", string);

        if (count >= size && charResp != 13) {
            printf("\nMax number of characters reached!\n");
            printString(resp, 0, count);
            continue;
        }
        if (!checkNumString(resp, charResp, 0)) {
            //why is this if here? idk but it works so imma not touch it xoxo
        } else if (charResp != 13 && charResp != 127) {
            resp[count] = charResp;
            count++;
        }
        if (!periodCount && charResp == 46) {
            resp[count] = charResp;
            count++;
            periodCount++;
        }
        printString(resp, 0, count);
    } while (charResp != 13 | count == 0);
    remDecNum(resp, decNum);
    return atof(resp);
}


void getString(char *string, char *resp,int size){

    char charResp;int pass = 0,count=0;
    printf("\n%s",string);
    printString(resp,0,count-1);

    do{
        charResp=getch();
        system("cls");

        if(charResp==13 && count>0){
            return;
        }
        if(charResp==8 && count!=0){
            count--;
            resp[count]='\0';
        }
        printf("\n%s\n",string);

        if(count>=size){printf("\nMax number of characters reached!\n");} else if(charResp>=32 && charResp<=126){
            resp[count]=charResp;
            count++;

        }


        fflush(0);
        printString(resp,0,count);
    }while(!pass);
    system("cls");
}
