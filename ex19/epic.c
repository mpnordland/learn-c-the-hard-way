#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "game.h"



int Map_init(void *self){
    assert(self != NULL);
    Map *map = self;

    // make some rooms for a small map
    Room *hall = NEW(Room, "The great Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *tower = NEW(Room, "The tower, overlooking the moat, a griffin looks in the window");
    Room *stores= NEW(Room, "The stores room, filled with supplies, you hear a noise");
    Room *kitchen = NEW(Room, "The kitchen, you have the knife now");

    // put the bad guy in the arena
    arena->bad_guy = NEW(Monster, "The evil minotaur");

    stores->bad_guy = NEW(Monster, "A giant rat!");

    tower->bad_guy = NEW(Monster, "The sinister griffin");

    //setup the map rooms
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->north = tower;
    arena->east = throne;

    kitchen->west = throne;
    kitchen->south = stores;
    
    tower->south = arena;

    stores->north = kitchen;

    //start the map and the character off in the hall
    map->start = hall;
    map->location = hall;
    return 1;
}



int main(int argc, char *argv[]) {
    //simple way to setup the randomness
    srand(time(NULL));

    // make our map to work with
    Map *game = NEW(Map, "The Castle.");
    printf("You have been summoned to rid the castle of terrible beasts\n");
    printf("You enter the ");
    game->location->_(describe)(game->location);
    printf("Everything is eerily quiet.\n");

    while(process_input(game)){
    }
    return 0;
}
