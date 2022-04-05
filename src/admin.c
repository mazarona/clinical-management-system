#include <stdio.h>
#include <string.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "ADMIN_API.h"


void admin(void)
{
    u8 c;
    u32 input;
    u8 password[] = "123";
    u8 password_input[20];

    //prompting the user
    printf("Enter password: \n");
    for(u32 i = 0; i < 3; i++)
    {
        scanf("%s", password_input);
        getchar();
        if(strcmp(password, password_input) == 0)
            goto admin_main_menu;
        else 
            printf("Incorrect password. Try again!\n");
    }
    printf("you have finished your three trys\n");

    return;
admin_main_menu:
    printf("|=============================================|\n");
    printf("|                 |ADMIN MENU|                |\n");            
    printf("|                 ------------                |\n");             
    printf("|       1 -> Add a new patient record         |\n");
    printf("|       2 -> Edit patient record.             |\n");
    printf("|       3 -> Reserve a slot with the doctor.  |\n");
    printf("|       4 -> Cancel reservation.              |\n");
    printf("|       5 -> Exit admin mode.                 |\n");
    printf("|=============================================|\n");
    c = getchar();
    input = c - '0';
    clear_input_buffer();
    switch(input)
    {
        Error_state es;
        case 1: 
            es = add_patient_rec();
            if(es == ID_INVALID)
                printf("ID is already taken!\n");
            else if(es == GENDER_INVALID)
                printf("Invalid gender! (m / f)\n");
            else if(es == AGE_INVALID)
                printf("Invalid age!\n");
            goto admin_main_menu;
            break;
        case 2:
            es = edit_patient_rec();
            if(es == ID_NOT_FOUND)
                printf("No patient exists with this ID!\n");
            else if(es == ID_INVALID)
                printf("ID is already taken!\n");
            goto admin_main_menu;
            break;
        case 3:
            es = reserve_slot();
            if(es == ID_NOT_FOUND)
                printf("No patient exists with this ID!\n");
            else if(es == MORE_THAN_ONE_RES)
                printf("Patient has already reserved a slot\n");
            else if (es == SLOT_INVALID)
                printf("Invalid slot\n");
            goto admin_main_menu;
            break;
        case 4:
            es = cancel_reservation();
            if(es == ID_NOT_FOUND)
                printf("No patient exists with this ID!\n");
            goto admin_main_menu;
            break;
        case 5:
            return;
        default:
            printf("Invalid input\n");
            goto admin_main_menu;
    }

}
