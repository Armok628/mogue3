#include "actions.h"
static char *actions[]={
	"Do nothing",
	"Build a boat",
	"Pick up a rock",
	"Make an axe"
};
static int n_actions=sizeof(actions)/sizeof(char *);
static char *boats[]={
	"Build a raft",
	"Build a canoe"
};
static int n_boats=sizeof(boats)/sizeof(char *);
void boat_menu()
{
	if (has_raft||has_canoe) {
		announce("s","You already have a boat");
		return;
	}
	int choice=menu(boats,n_boats);
	switch (choice) {
	case 0: // Raft
		if (logs>=8) {
			has_raft=true;
			logs-=8;
			announce("s","You build a raft");
		} else
			announce("s sds","Not enough logs",
					"(",logs,"/8)");
		return;
	case 1: // Canoe
		if (!equipped(player,&axe)) {
			announce("s","You need an axe");
			return;
		}
		if (logs>=24) {
			//has_canoe=true;
			logs-=24;
			world[map_coords].landing=true;
			announce("s","You build a canoe");
		} else
			announce("s sds","Not enough logs",
					"(",logs,"/24)");
		return;
	}
}
void action_menu()
{
	tile_t *t;
	int choice=menu(actions,n_actions);
	switch (choice) {
	case 0: // Do nothing
		return;
	case 1: // Build a boat
		boat_menu();
		return;
	case 2: // Pick up a rock
		t=&local_area[player->coords];
		if (t->bg!='.'&&t->bg!=',') {
			announce("s","You are not near any rocks");
		} else if (t->bg_c!=DGRAY&&t->bg_c!=LGRAY) {
			rocks+=!(rand()%10);
			announce("s","You have trouble finding one here");
		} else if (rand()%3) {
			announce("s","You fail to find a useful rock");
		} else {
			announce("s","You pick up a good-sized rock");
			rocks++;
		}
		announce("s d s","You now have",rocks,"rocks");
		return;
	case 3: // Make an axe
		if (logs>0&&rocks>1) {
			logs--;
			rocks-=2;
			add_item(player->inventory,spawn_item(&axe));
			announce("s","You make an axe");
		} else {
			announce("s","You don't have the materials");
		}
		return;
	}
}
