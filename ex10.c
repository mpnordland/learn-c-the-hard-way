#include <stdio.h>

int main(int argc, char *argv[]){
    int i = 0;
    // go through eah string in argv
    // why am I skipping argv[0]?
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas",
        argv[0]
    };

    for(i = 0; i < argc; i++){
        printf("arg %d: %s\n", i, argv[i]);
        if (i >= 2){
            break;
        }
    }

    // let's make our own array of strings
    int num_states = 5;
    
    for(i = 0; i<num_states;i++){
        printf("state %d: %s\n", i, states[i]);
        if (i >= 2){
            break;
        }
    }
    return 0;
}
