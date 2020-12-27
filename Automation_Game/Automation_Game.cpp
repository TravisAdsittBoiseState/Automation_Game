/*
This is a simple game, The objective is to 
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "World.h"


//Entry point to the game
int main()
{
    bool quit = false;

    World* new_game = new World();

    //Compile the basic game in, possibly create a 
    //configuration file load function.
#if BASIC_GAME
    Rover* rov = new Rover("Travis");
    Grass* grass = new Grass();
    Rock* rock = new Rock();

    rov->setX(MAP_SIZE / 2);
    rov->setY(MAP_SIZE / 2);

    grass->setX(1);
    grass->setY(1);

    rock->setX(MAP_SIZE - 2);
    rock->setY(MAP_SIZE - 2);

    new_game->add_obj(rov);
    new_game->add_obj(grass);
    new_game->add_obj(rock);
#endif

    while (!quit) {
        int object_to_move;
        int action_choice;

        new_game->print_ui();

        std::cout << "0: Quit -- 1: Send Commands -- 2: Execute Commands\n";
        std::cin >> action_choice;

        //Quit the game
        if (action_choice == 0) {
        QUIT:
            quit = true;
            continue;
        }

        //Send commands to the rovers
        if (action_choice == 1) {
            std::string new_commands;
            int ship;
            int i = 0;

            //Print the objects commandable
            std::cout << "Which vehicle would you like to command?\n";
               
            //Get the users choice
            std::cin >> object_to_move;

            if(std::cin.fail()) {
                continue;
            }

            //Ask for the command sequence
            std::cout << "Please input command sequence (q to exit)\n";
            std::cin >> new_commands;

            if (new_commands[0] == 'q') {
                goto QUIT;
            }

            //Tell our world of the changes
            new_game->send_commands(object_to_move, new_commands);

        }

        //Allow rovers to execute the commands
        if (action_choice == 2) {
            int num_com_ex = new_game->time_step_world();
            while (num_com_ex > 0) {
                new_game->print_ui();
                std::cout << "...Executing sequence(s)...\n";
                GAME_TICK
                num_com_ex = new_game->time_step_world();
            }
        }


            
    }
    return 0;
    }
    

