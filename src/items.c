#include "items.h"
bool has_axe=false;
bool has_raft=false;
bool has_canoe=false;
int logs=0;
int rocks=0;
itype_t sword={
	.name="Sword",
	.category=OFFENSE,
	.effect=10,
	.value=100
};
itype_t gold={
	.name="Gold",
	.category=UTILITY,
	.effect=0,
	.value=1
};

item_t *spawn_item(itype_t *type)
{
	item_t *i=malloc(sizeof(item_t));
	i->type=type;
	i->count=1;
	return i;
}
// Very incomplete
