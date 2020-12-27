#include <list>
#include <string>
#include "Misc.h"
#include "Settings.h"

/*
The ultimate base class for all objects in the world to inherit from
*/
class Game_Object {
public:
    /*
    Set the x coordinate for the object
    */
    void setX(int x_new);
    /*
    Get the x coordinate for the object
    */
    int getX();
    /*
    Set the y coordinate for the object
    */
    void setY(int y_new);
    /*
    Get the y coordinate for the object
    */
    int getY();
    /*
    Get the character used to represent the object
    */
    char getChar();
    /*
    Get the object type (commandable, consumable...)
    */
    int getType();

protected:
    int x = 0; //Current x coordinate
    int y = 0; //Current y coordinate
    int type = unknown; //Object type
    bool collidable; //TODO for object collision
    char obj_char = BASE_CHAR; //Objects character representation
};

/*
An object that can accept commands (like a rover)
*/
class Commandable_Object : public Game_Object {
public:
    /*
    Constructor for a Commandable object
    */
    Commandable_Object(std::string new_name);
    /*
    Get the objects name
    */
    std::string getName();
    /*
    Set the commands the object needs to execute
    */
    void set_commands(std::string command_str);
    /*
    Instruct the object to execute a command in it's list, requires nearby objects for 
    interaction
    */
    virtual int execute_command(std::list <Game_Object*> nearby_objects) = 0;
    /*
    Get the objects current storage values
    */
    virtual Consumable_Properties getStorage() = 0;

protected:
    std::string name; //Object name
    std::string commands; //The command list
    Consumable_Properties storage = {0,0,0}; //Storage
};

/*
An object that can be consumed for properties
*/
class Consumable_Object : public Game_Object {
public:
    /*
    Constructor, giving the object its consumable properties
    */
    Consumable_Object(int water, int fiber, int mineral);

    /*
    Consume the consumable setting it's properties to 0 and giving them to the 
    consumer. Will also set the character to the BASE_CHAR
    */
    Consumable_Properties consume();

protected:
    Consumable_Properties prop; //Consumable properties
};

/*
A consumable for minerals
*/
class Rock : public Consumable_Object {
public:
    Rock();
};

/*
A consumable for water, and fiber
*/
class Grass : public Consumable_Object {
public:
    Grass();
};

/*
A commandable object to collect and build(TODO)
*/
class Rover : public Commandable_Object {
public:
    /*
    Constructor
    */
    Rover(std::string new_name);
    /*
    Execute a step in command list
    */
    int execute_command(std::list <Game_Object*> nearby_objects);
    /*
    Get the current storage values of the rover
    */
    Consumable_Properties getStorage();
};