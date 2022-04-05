#ifndef _PATIENT_INFO_H_
#define _PATIENT_INFO_H_
#include "STD_TYPES.h"
#include "ERROR_STATE.h"
typedef struct _Patient
{
    u8 name[100];
    u8 gender;
    u32 age;
    u32 slot_reservation;
    u32 ID;
    
}Patient;
#endif
