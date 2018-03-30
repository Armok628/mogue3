#include "actions.h"
static char *actions[]={"Do nothing","Build a raft"};
void action_menu()
{
	int choice=menu(actions,2);
	switch (choice) {
	case 0:
		return;
	case 1:
		if (trees_chopped>=20) {
			has_raft=true;
			trees_chopped-=20;
			announce("s","You build a raft");
		}
		return;
	}
}
