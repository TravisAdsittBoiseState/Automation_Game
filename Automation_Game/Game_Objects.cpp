#include "Game_Objects.h"

void Game_Object::setX(int x_new) {
    x = x_new;
}
int Game_Object::getX() {
    return x;
}
void Game_Object::setY(int y_new) {
    y = y_new;
}
int Game_Object::getY() {
    return y;
}
char Game_Object::getChar() {
    return obj_char;
}
int Game_Object::getType() {
    return type;
}


Commandable_Object::Commandable_Object(std::string new_name) {
    name = new_name;
    type = commandable;
}
std::string Commandable_Object::getName() {
    return name;
}
void Commandable_Object::set_commands(std::string command_str) {
    commands = command_str;
}

Consumable_Object::Consumable_Object(int water, int fiber, int mineral) {
    prop.water_val = water;
    prop.fiber_val = fiber;
    prop.mineral_val = mineral;
    type = consumable;
}

Consumable_Properties Consumable_Object::consume() {
    Consumable_Properties ret;

    ret.water_val = prop.water_val;
    ret.fiber_val = prop.fiber_val;
    ret.mineral_val = prop.mineral_val;

    prop.water_val = 0;
    prop.fiber_val = 0;
    prop.mineral_val = 0;

    obj_char = BASE_CHAR;

    return ret;
}


Grass::Grass() : Consumable_Object(2, 10, 0) {
    obj_char = 'W';
}

Rock::Rock() : Consumable_Object(0, 0, 5) {
    obj_char = 'O';
}

Rover::Rover(std::string new_name) : Commandable_Object(new_name) {
    obj_char = '#';
}


Consumable_Properties Rover::getStorage() {
    return storage;
}

int Rover::execute_command(std::list <Game_Object*> nearby_objects) {

    if (commands.length() == 0) {
        return 0;
    }

    char direction = commands[0];

    //TODO add collision detection
    switch (direction) {
    case 'w':
        if (getY() - 1 < 0) {
            setY(0);
        }
        else {
            setY(getY() - 1);
        }
        break;
    case 'a':
        if (getX() - 1 < 0) {
            setX(0);
        }
        else {
            setX(getX() - 1);
        }
        break;
    case 's':
        if (getY() + 1 >= MAP_SIZE) {
            setY(MAP_SIZE - 1);
        }
        else {
            setY(getY() + 1);
        }
        break;
    case 'd':
        if (getX() + 1 >= MAP_SIZE) {
            setX(MAP_SIZE - 1);
        }
        else {
            setX(getX() + 1);
        }
        break;
    case 'c':
        for (Game_Object* g_obj : nearby_objects) {
            if (g_obj->getType() == consumable) {
                Consumable_Properties collected = ((Consumable_Object*)g_obj)->consume();

                storage.water_val += collected.water_val;
                storage.fiber_val += collected.fiber_val;
                storage.mineral_val += collected.mineral_val;

            }
        }
        break;
    };
    commands.erase(commands.begin());
    return 1;

}
