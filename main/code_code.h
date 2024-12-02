#ifndef CODE_CODE_H
#define CODE_CODE_H

#include "keypad.h"
#include "servo.h"


#define CODE_LENGTH 4
#define NUM_CODES 25

extern bool code_correct;

extern const char* accepted_codes[NUM_CODES];
extern char input_code[CODE_LENGTH+1]; // +1 for null terminator


void add_to_code(char key, int *index);

bool use_code(const char* code);

void reset_input_code();





#endif // EXTRA_H

