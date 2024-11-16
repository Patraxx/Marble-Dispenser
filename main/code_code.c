#include "code_code.h"

bool used_codes[NUM_CODES] = {false};
char input_code[CODE_LENGTH+1];

void add_to_code(char key, int *index)
{
    
    if (*index < CODE_LENGTH)
    {
        input_code[*index] = key;
        (*index)++;
    }
    else
    {
        printf("Code is full\n");
    }
}




// Function to check and mark a code as used
bool use_code(const char *code) {
    
    // Check if the code is valid and has not been used yet
    for (int i = 0; i < NUM_CODES; i++) {
        if (strcmp(accepted_codes[i], code) == 0) {
            if (!used_codes[i]) {
                used_codes[i] = true;  // Mark the code as used
                
                return true;  // Successfully used the code
            } else {
                printf("Code %s has already been used.\n", code);
                return false;  // Code already used
            }
        }
    }
    printf("Code %s not found.\n", code);
    return false;  // Code not found in the list
}

void reset_input_code()
{
    for (int i = 0; i < CODE_LENGTH; i++)
    {
        input_code[i] = '\0';
    }
}

const char* accepted_codes[NUM_CODES] = {
    "1034", "1689", "1788", "2520", "2544", "2616", "3117", "3182", "3275", "3810",
    "3845", "4270", "5051", "5103", "5908", "5971", "5982", "6046", "6617", "6646",
    "6674", "8144", "8207", "9312", "9821"
};