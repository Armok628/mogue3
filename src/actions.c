#include "actions.h"
static char *actions[]={
	"Do nothing",
	"Build a boat",
	"Search for a rock",
	"Make an axe"
};
static int n_actions=sizeof(actions)/sizeof(char *);
static char *boats[]={
	"Build a raft",
	"Build a canoe",
};
static int n_boats=sizeof(boats)/sizeof(char *);
void boat_menu()
{
	if (item_count(player->inventory,&raft)||world[map_coords].landing) {
		announce("s","You already have a boat here");
		return;
	}
	int choice=menu(boats,n_boats);
	switch (choice) {
	case 0: // Raft
		if (remove_item(player->inventory,&lumber,8)) {
			add_item(player->inventory,&raft,1);
			announce("s","You build a raft");
		} else {
			int c=item_count(player->inventory,&lumber);
			announce("sds","Not enough lumber (",c,"/8)");
		}
		return;
	case 1: // Canoe
		if (!item_count(player->inventory,&axe)) {
			announce("s","You must have an axe");
			return;
		}
		if (remove_item(player->inventory,&lumber,24)) {
			world[map_coords].landing=true;
			announce("s","You build a canoe");
		} else {
			int c=item_count(player->inventory,&lumber);
			announce("sds","Not enough lumber (",c,"/24)");
		}
		return;
	}
}
void action_menu()
{
	tile_t *t;
	int logs=0,rocks=0;
	switch (menu(actions,n_actions)) {
	case 0: // Do nothing
		return;
	case 1: // Build a boat
		boat_menu();
		return;
	case 2: // Search for a rock
		t=&local_area[player->coords];
		if (t->bg!='.'&&t->bg!=',')
			announce("s","You are not on any rocks");
		else if (t->bg_c!=D_GRAY&&t->bg_c!=L_GRAY) {
			announce("s","You have trouble finding rocks here");
			rocks=!(rand()%10);
		} else
			rocks=rand()%4;
		if (rocks>1)
			announce("s","You find some suitable rocks on the ground");
		else if (rocks)
			announce("s","You find a good-sized rock on the ground");
		else
			announce("s","You fail to find any useful rocks");
		add_item(t->pile,&rock,rocks);
		return;
	case 3: // Make an axe
		logs=item_count(player->inventory,&lumber);
		rocks=item_count(player->inventory,&rock);
		if (logs>=1&&rocks>=2) {
			remove_item(player->inventory,&lumber,1);
			remove_item(player->inventory,&rock,2);
			add_item(player->inventory,&axe,1);
			announce("s","You make an axe");
		} else {
			announce("s","You don't have the materials");
		}
		return;
	}
}
