#include <stdio.h>

void array_like_print_loop(char **names, int *ages, int len){
    int i = 0;
    for(i = len-1; i>=0; i--){
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }
}
void array_like_while_loop(char **names, int *ages, int len){
    int i = 0;
    while (i < len){
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
        i++;
    }
}

void pointer_plus_i_loop(char **names, int *ages, int len) {
    int i = 0;
    for (i = 0; i < len; i++){
        printf("%s is %d years old.\n",
                *(names+i), *(ages+i));
    }
}

void pointer_plus_i_while(char **names, int *ages, int len) {
    int i = 0;
    while(i<len){
        printf("%s is %d years old.\n",
                *(names+i), *(ages+i));
        i++;
    }
}
void pointer_increment_loop(char **names, int *ages, int len){
    int *cur_age;
    char **cur_name;
    for(cur_name = names, cur_age = ages; 
        (cur_age - ages) < len; cur_name++, cur_age++){
        printf("%s lived %d years so far.\n",
            *cur_name, *cur_age);
    }
}

void pointer_increment_while(char **names, int *ages, int len){
    int *cur_age;
    char **cur_name;
    while((cur_age - ages) < len){
        printf("%s lived %d years so far.\n",
            *cur_name, *cur_age);
        
        cur_age++; cur_name++;
    }
}
int main(int argc, char *argv[]){
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };



    //safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    //pointer through that argv array:
    for(i = 0; i < argc; i++){
        printf("ARG %d: %s\n", i, *(argv+i));
    }

    //first way using indexing
    array_like_print_loop(names, ages, count);

    array_like_while_loop(names, ages, count);
    printf("---\n");

    //setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    pointer_plus_i_loop(cur_name, cur_age, count);

    pointer_plus_i_while(cur_name, cur_age, count);

    printf("---\n");

    //third way, pointers are just arrays
    array_like_print_loop(cur_name, cur_age, count);
    array_like_while_loop(cur_name, cur_age, count);

    printf("---\n");

    //fourth way with pointers in a stupid complex way

    pointer_increment_loop(names, ages, count);
    pointer_increment_while(names, ages, count);
    printf("---\n");

    for(cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++){
        printf("%p -> %s, %p -> %d\n",
            cur_name, *cur_name, cur_age, *cur_age);

        printf("loop cond: %p %p\n", cur_age, ages);
    }

    return 0;
}
