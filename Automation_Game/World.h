#include <list>
#include <string>
#include <iostream>
#include <cstdlib>
#include "Game_Objects.h"

/*
This class is meant to be used for printing and interacting with the world.
*/
class World {

public:
    World();

    //Print the world
    void print_ui();

    //Add an object to the world
    void add_obj(Game_Object* new_obj);

    //TODO Don't do it this way
    void print_commandable();

    //TODO Don't do it this way
    void send_commands(int object_to_move, std::string new_commands);

    std::list <Game_Object*> get_nearby_objects(Game_Object* observer);

    //TODO eventually we will need a free running world, for now we halt 
    //movement when all commands have been executed by the rovers
    int time_step_world();
private:
    std::list <Game_Object*> game_objects;
    std::list < Commandable_Object*> com_obj;
    std::list < Consumable_Object*> con_obj;

    char get_loc_char(int x, int y);
};