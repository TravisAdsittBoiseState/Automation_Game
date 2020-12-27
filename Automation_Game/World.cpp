#include "World.h"


World::World() {}


void World::print_ui() {
    system("CLS");

    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            std::cout << get_loc_char(x, y);
        }
        std::cout << '\n';
    }

    std::cout << "---------------------------\n";
    std::cout << "------- COMMANDABLE -------\n";
    std::cout << "---------------------------\n";
    print_commandable();
    std::cout << "===========================\n";
}


void World::add_obj(Game_Object* new_obj) {
    game_objects.push_front(new_obj);

    switch (new_obj->getType()) {
    case commandable:
        com_obj.push_front((Commandable_Object*)new_obj);
        break;
    case consumable:
        con_obj.push_front((Consumable_Object*)new_obj);
        break;
    }
}


void World::print_commandable() {
    int i = 0;
    for (Commandable_Object* curr = com_obj.front(); curr != com_obj.back(); curr++, i++) {
        std::cout << i << " - " << curr->getName() << "(w:" << curr->getStorage().water_val << " f:" << curr->getStorage().fiber_val << " m:" << curr->getStorage().mineral_val << ")\n";
    }

    if (com_obj.front() == com_obj.back()) {
        Commandable_Object* curr = com_obj.back();

        std::cout << "0 - " << curr->getName() << "(w:" << curr->getStorage().water_val << " f:" << curr->getStorage().fiber_val << " m:" << curr->getStorage().mineral_val << ")\n";
    }
        
}


void World::send_commands(int object_to_move, std::string new_commands) {

    if (object_to_move < 0 || object_to_move > com_obj.size()) {
        return;
    }

    std::list<Commandable_Object*>::iterator it = com_obj.begin();
    std::advance(it, object_to_move);

    (*it)->set_commands(new_commands);
}


std::list <Game_Object*> World::get_nearby_objects(Game_Object* observer) {
    std::list <Game_Object*> nearby_objects;
    int x = observer->getX();
    int y = observer->getY();

    int wx = x - 1;
    int ex = x + 1;
    int ny = y - 1;
    int sy = y + 1;

    for (Game_Object* g_obj : game_objects) {
        int curr_x = g_obj->getX();
        int curr_y = g_obj->getY();

        if (curr_x == x) {
            if (curr_y == ny || curr_y == sy) {
                nearby_objects.push_front(g_obj);
            }
        }
        else if (curr_y == y) {
            if (curr_x == wx || curr_x == ex) {
                nearby_objects.push_front(g_obj);
            }
        }
        else if (curr_x == wx) {
            if (curr_y == ny || curr_y == sy) {
                nearby_objects.push_front(g_obj);
            }
        }
        else if (curr_x == ex) {
            if (curr_y == ny || curr_y == sy) {
                nearby_objects.push_front(g_obj);
            }
        }
    }

    return nearby_objects;
}


int World::time_step_world() {
    int num_commands = 0;
    for (Commandable_Object* obj = com_obj.front(); obj != com_obj.back(); obj++) {
        num_commands += obj->execute_command(get_nearby_objects(obj));
    }

    if (com_obj.front() == com_obj.back()) {
        num_commands += com_obj.front()->execute_command(get_nearby_objects(com_obj.front()));
    }

    return num_commands;
}
char World::get_loc_char(int x, int y) {
    for (Game_Object* go : game_objects) {
        if (go->getX() == x && go->getY() == y) {
            return go->getChar();
        }
    }
    return BASE_CHAR;
}