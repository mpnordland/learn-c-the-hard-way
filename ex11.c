#include <stdio.h>

int main(int argc, char *argv[]){
    int i = argc-1;
    while(i>=0){
        printf("arg %d: %s\n", i, argv[i]);
        i--;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;
    i = num_states-1;
    while (i >= 0){
        printf("state %d: %s\n", i, states[i]);
        i--;
        if (i < 2){
            break;
        }
    }
    i=0;
    while(i<argc&&i<num_states){
        states[i] = argv[i];    
        i++;
    }
    i = 0;
    while (i < num_states){
        printf("state %d: %s\n", i, states[i]);
        i++;
        if (i < 2){
            break;
        }
    }


    return 0;

}
