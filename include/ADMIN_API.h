#ifndef _ADMIN_API_H_
#define _ADMIN_API_H_
#include "ERROR_STATE.h"
#include "STD_TYPES.h"
void admin(void);
void user(void);
void clear_input_buffer(void);

Error_state check_ID(u32 IDa, u32 *index);
Error_state add_patient_rec(void);
Error_state edit_patient_rec(void);
Error_state reserve_slot(void);
Error_state cancel_reservation(void);
#endif
