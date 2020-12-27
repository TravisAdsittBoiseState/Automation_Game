//Used to define the type of Game_Object
enum Object_Type {
    unknown,
    commandable,
    consumable
};

//Used to keep track of or define a consumables properties
typedef struct Consumable_Properties {
    int water_val;
    int fiber_val;
    int mineral_val;
};