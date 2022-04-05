#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "PATIENT_INFO.h"
#include "ERROR_STATE.h"
#include "linked_list.h"


extern int slots[5];
extern char reservations[5][20];
extern List data_base;


void clear_input_buffer(void){u8 c; while(getchar() != '\n');}

Error_state check_ID(u32 IDa, u32 *index)
{
    List_elmt *temp = data_base.head;
    for(u32 i = 0; i < data_base.size; i++)
    {
        if (((Patient*)temp->data)->ID == IDa)
        {
            *index = i;
            return ID_FOUND;
        }
        else
            temp = temp->next;
    }
    return ID_NOT_FOUND;
}
//we use this when we add a new patient for the first time.
void list_patient_element_assign(u8 *name, u32 size, u8 gender, u32 age, u32 ID)
{
    for(u32 i = 0; i < size; i++)
        ((Patient *)data_base.head->data)->name[i] = name[i];
    ((Patient *)data_base.head->data)->gender = gender;
    ((Patient *)data_base.head->data)->age = age;
    ((Patient *)data_base.head->data)->ID = ID;
    ((Patient *)data_base.head->data)->slot_reservation = 0;
}
//we use this for when we edit an existing patient we need to assign the new values to a particular node that corresponds to the right index.
void list_patient_element_assign_at_index(u8 *name, u32 size, u8 gender, u32 age, u32 ID, u32 index)
{
    List_elmt *target = data_base.head;
    //het the target element we want to assign to at the provided index
    for(u32 i = 0; i < index; i++)
        target = target->next;
    for(u32 i = 0; i < size; i++)
        ((Patient *)(target->data))->name[i] = name[i];
    ((Patient *)(target->data))->gender = gender;
    ((Patient *)(target->data))->age = age;
    ((Patient *)(target->data))->ID = ID;

}

Error_state add_patient_rec(void)
{

    void *data;
    data = malloc(sizeof(Patient));
    list_ins_next(&data_base, NULL, (const void *)data);
    ((Patient *)data_base.head->data)->slot_reservation = 0;

//================================================
//----------handling ID input-------------
    u32 index;
    u32 ID;
    printf("ID: ");
    scanf("%d", &ID);
    getchar();
    if(check_ID(ID, &index) == ID_FOUND)
        return ID_INVALID;

//----------handling name input-------------

    u8 name[20];
    u8 c;
    u32 size;
enter_name:
    printf("Name: ");
    u32 i;
    for(i = 0; (c = getchar()) != '\n'; i++)
    {
        if(i < 20)
            name[i] = c;
        else 
        {
            printf("Name exceeds 20 characters, please re-enter your name.\n");
            clear_input_buffer();
            goto enter_name;
        }
    }
    name[i] = '\0';
    size = i;

//----------handling age input-------------
    u32 age;
    printf("Age: ");
    scanf("%d", &age);
    getchar();
    if(age < 0)
        return AGE_INVALID;


//----------handling gender input-------------

    u8 gender;
    printf("Gender: ");
    scanf("%c", &gender);
    getchar();
    if(gender != 'm' && gender != 'M'&& gender != 'f' && gender != 'F')
        return GENDER_INVALID;
//================================================
    list_patient_element_assign(name, size, gender, age, ID);
    return OK;
}




Error_state edit_patient_rec(void)
{
    u32 ID;
    u32 index;
    printf("ID: ");
    scanf("%d", &ID);
    getchar();
    if(check_ID(ID, &index) == ID_NOT_FOUND)
        return ID_NOT_FOUND;
    else 
    {
    //================================================
    //----------handling ID input-------------
        u32 new_ID;
        u32 new_index;
        printf("New ID: ");
        scanf("%d", &new_ID);
        getchar();
        if(check_ID(new_ID, &new_index) == ID_FOUND)
            return ID_INVALID;

    //----------handling name input-------------

        u8 name[20];
        u8 c;
        u32 size;
    enter_name:
        printf("New name: ");
        u32 i;
        for(i = 0; (c = getchar()) != '\n'; i++)
        {
            if(i < 20)
                name[i] = c;
            else 
            {
                printf("Name exceeds 20 characters, please re-enter your name.\n");
                goto enter_name;
            }
        }
        name[i] = '\0';
        size = i;

    //----------handling age input-------------
        u32 age;
        printf("new Age: ");
        scanf("%d", &age);
        getchar();
        if(age < 0)
            return AGE_INVALID;


    //----------handling gender input-------------

        u8 gender;
        printf("New gender: ");
        scanf("%c", &gender);
        getchar();
        if(gender != 'm' && gender != 'M'&& gender != 'f' && gender != 'F')
            return GENDER_INVALID;
        
        list_patient_element_assign_at_index(name, size, gender, age, ID, index);
    }

    return OK;
}

Error_state reserve_slot()
{
    for(u32 i = 0; i < 5; i++)
        if(slots[i] == 0)
            printf("%d -> %s\n", i+1 ,reservations[i]);
    

    u32 ID;
    u32 index;
    printf("Patient ID: ");
    scanf("%d", &ID);
    getchar();
    if(check_ID(ID, &index) == ID_NOT_FOUND)
        return ID_NOT_FOUND;


    List_elmt *target;
    list_get_element_at_index(&data_base, &target, index);
    if(((Patient *)target->data)->slot_reservation != 0)
        return MORE_THAN_ONE_RES;


    u32 slot;
    printf("Desired slot: ");
    scanf("%d", &slot);
    getchar();
    if(slot > 5 || slot < 1)
        return SLOT_INVALID;
    else if(slots[slot-1] == 1)
        return SLOT_INVALID;
    else
    {
        slots[slot-1] = 1;
        ((Patient *)target->data)->slot_reservation = slot;
    }
    return OK;
}




Error_state cancel_reservation()
{
    u32 ID;
    u32 index;
    printf("Patient ID: ");
    scanf("%d", &ID);
    getchar();
    if(check_ID(ID, &index) == ID_FOUND)
    {
        List_elmt *target;
        list_get_element_at_index(&data_base, &target, index);
        slots[((Patient*)target->data)->slot_reservation -1] = 0;
        ((Patient*)target->data)->slot_reservation = 0;
    }
    else
        return ID_NOT_FOUND;
    return OK;

}
