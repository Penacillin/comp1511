#include "trader_bot.h"

char *get_bot_name(void)
{
    return "김설현";
}

int min(int a, int b)
{
    return a > b ? b : a;
}

void get_action(struct bot *b, int *action, int *n)
{
    if(b->location->type != LOCATION_PETROL_STATION)
    {
        *action = ACTION_MOVE;
        *n = min(nearest_fuel(b), b->maximum_move);
        return;
    }
    // if it's at a petrol station and the fuel is not full
    if(b->location-> type == LOCATION_PETROL_STATION && b->fuel != b->fuel_tank_capacity)
    {
        *action = ACTION_BUY;
        *n = b->fuel_tank_capacity - b->fuel;
        return;
    }
    if(b->location-> type == LOCATION_PETROL_STATION && b->fuel == b->fuel_tank_capacity)
    {
        *action = ACTION_MOVE;
        *n = b->maximum_move;
        return;
    }
    
}
