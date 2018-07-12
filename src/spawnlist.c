#include "spawnlist.h"
etype_t *spawnlist[]={
	&player_etype,
	&human_etype,
	&monster_etype,
	&toad_etype,
	&mage_etype,
	&dragon_etype,
};
int spawnlist_size=sizeof(spawnlist)/sizeof(etype_t *);
