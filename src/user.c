#include <stdio.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
#include "USER_API.h"


void user(void)
{
    u8 c;
    u32 input;
    Error_state es;

user_main_menu:
    printf("|=============================================|\n");
    printf("|                 |USER MENU|                 |\n");
    printf("|                 -----------                 |\n");
    printf("|       1 -> View patient record              |\n");
    printf("|       2 -> View today reservations          |\n");
    printf("|       3 -> Exit user mode                   |\n");
    printf("|=============================================|\n");
    c = getchar();
    input = c - '0';
    clear_input_buffer();
    switch(input)
    {

        case 1:
            es = view_rec();
            if(es == ID_NOT_FOUND)
                printf("No patient exists with this ID!\n");
            else if (es == NOT_OK)
                printf("Patients record is empty!\n");
            goto user_main_menu;
            break;
        case 2:
            es = view_today_res();
            if(es == SLOT_INVALID)
                printf("No reservations were made!\n");
            goto user_main_menu;
            break;
        case 3:
            return;
            break;
        default:
            printf("Invalild input\n");
            goto user_main_menu;
    }



}
