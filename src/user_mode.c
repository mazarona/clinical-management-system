#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "PATIENT_INFO.h"
#include "ERROR_STATE.h"
#include "linked_list.h"
#include "ADMIN_API.h"

extern int slots[5];
extern char reservations[5][20];
extern List data_base;


Error_state view_rec()
{
    if( data_base.size > 0)
    {
        u32 index;
        u32 ID;
        printf("ID: ");
        scanf("%d", &ID);
        getchar();
        if(check_ID(ID, &index) == ID_NOT_FOUND)
            return ID_NOT_FOUND;

        else
        {
            List_elmt *target;
            list_get_element_at_index(&data_base, &target, index);
            printf("Name: ");
            printf("%s\n", (((Patient *)(target->data))->name));
            printf("Age: ");
            printf("%d\n", (((Patient *)(target->data))->age));
            printf("Gender: ");
            printf("%c\n", (((Patient *)(target->data))->gender));
            printf("reservation: ");
            printf("%d\n", (((Patient *)(target->data))->slot_reservation));
        }
    }
    else
        return NOT_OK;
    return OK;
}

Error_state view_today_res()
{
    u8 flag = 0;
    List_elmt *temp = data_base.head;
    for(u32 i = 0; i < data_base.size; i++)
    {
        if(((Patient *)temp->data)->slot_reservation != 0)
        {
            flag = 1;
            printf("Patient ID: %d -> %s\n", ((Patient *)temp->data)->ID, reservations[(((Patient *)temp->data)->slot_reservation)-1]);
        }
        temp = temp->next;
    }
    if(flag)
        return OK;
    else
        return SLOT_INVALID;
}

