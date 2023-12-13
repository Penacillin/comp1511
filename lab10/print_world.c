#include "trader_bot.h"
#include <stdio.h>

void print_world(struct bot *b)
{
    struct location* end = b->location;
    int first = 1;
    for(struct location* iter = b->location ; iter != end || first; first = 0, iter = iter->next)
    {
        switch(iter->type)
        {
        case LOCATION_START:
            printf("%s: start\n", iter->name);
            break;
        case LOCATION_SELLER:
            printf("%s: will sell %d units of %s for $%d\n", iter->name, iter->quantity, iter->commodity->name, iter->price);
            break;
        case LOCATION_DUMP:
            printf("%s: dump\n", iter->name);
            break;
        case LOCATION_OTHER:
            printf("%s: other\n", iter->name);
            break;
        case LOCATION_BUYER:
            printf("%s: will buy %d units of %s for $%d\n", iter->name, iter->quantity, iter->commodity->name, iter->price);
            break;
        case LOCATION_PETROL_STATION:
            printf("%s: Petrol station %d units of available fuel for $%d\n", iter->name, iter->quantity, iter->price);
            break;
        }
    }
}
