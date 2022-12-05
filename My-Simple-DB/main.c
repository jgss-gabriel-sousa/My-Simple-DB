#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getline.h"

typedef struct{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

InputBuffer* new_inputBuffer(){
    InputBuffer* inputBuffer = malloc(sizeof(InputBuffer));
    inputBuffer->buffer = NULL;
    inputBuffer->buffer_length = 0;
    inputBuffer->input_length = 0;

    return inputBuffer;
}

void close_inputBuffer(InputBuffer* inputBuffer){
    free(inputBuffer->buffer);
    free(inputBuffer);
}

void readInput(InputBuffer* inputBuffer){
    ssize_t bytes = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_length), stdin);

    if(bytes <= 0){
        printf("Error reading input \n");
        exit(EXIT_FAILURE);
    }

    inputBuffer->input_length = bytes - 1;
    inputBuffer->buffer[bytes - 1] = 0;
}

void printPrompt(){
    printf("db > ");
}

int main(int argc, char* argv[]){
    InputBuffer* inputBuffer = new_inputBuffer();

    while(1){
        printPrompt();
        readInput(inputBuffer);

        if(strcmp(inputBuffer->buffer, ".exit") == 0){
            close_inputBuffer(inputBuffer);
            exit(EXIT_SUCCESS);
        }
        else{
            printf("Unrecognized command \"%s\".\n", inputBuffer->buffer);
        }
    }
}
