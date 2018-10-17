

//Rocket Arena 2 Bot Support Routines
// Copyright 1998, David Wright
// For non-commercial use only

#include "g_local.h"

#ifdef ROCKETARENA //#endif at the end of the file
#include "bl_spawn.h"

extern gitem_armor_t bodyarmor_info;
extern int weapon_vals[];

int idmap;
int num_arenas;
							//	  0  2  3  4  5   6    9   8   7
int weapon_vals_x[] = { 256, 1, 2, 4, 8, 16, 128, 64, 32 };

// from q_dev15.zip
// Use this function to send a command string to a CLIENT.
// E.g. stuffcmd(player, "alias ready \"cmd ready\"\n");
/*void stuffcmd(edict_t *e, char *s)
{
	gi.WriteByte (11);
	gi.WriteString (s);
	gi.unicast (e, true);
}*/

void RA2JoinArena(edict_t *ent, int arena)
{
	PMenu_Close(ent);
	RA2_MoveToArena(ent, arena, true);
}

void RA2JoinArena1(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 1);
}

void RA2JoinArena2(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 2);
}

void RA2JoinArena3(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 3);
}

void RA2JoinArena4(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 4);
}

void RA2JoinArena5(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 5);
}

void RA2JoinArena6(edict_t *ent, pmenu_t *p)

{
	RA2JoinArena(ent, 6);
}

void RA2JoinArena7(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 7);
}

void RA2JoinArena8(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 8);
}

void RA2JoinArena9(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 9);
}

void RA2JoinArena10(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 10);
}

void RA2JoinArena11(edict_t *ent, pmenu_t *p)
{
	RA2JoinArena(ent, 11);
}

void *join_menu_functions[] = {
	RA2JoinArena1,
	RA2JoinArena2,
	RA2JoinArena3,
	RA2JoinArena4,
	RA2JoinArena5,
	RA2JoinArena6,
	RA2JoinArena7,
	RA2JoinArena8,
	RA2JoinArena9,
	RA2JoinArena10,
	RA2JoinArena11
};

pmenu_t arena_menu[] = {
	{ "*Quake 2 - Gladiator Bot",		PMENU_ALIGN_CENTER, NULL, NULL },
	{ "*Rocket Arena 2 - Arena List",	PMENU_ALIGN_CENTER, NULL, NULL },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, NULL },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena1 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena2 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena3 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena4 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena5 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena6 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena7 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena8 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena9 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena10 },
	{ NULL,					PMENU_ALIGN_LEFT, NULL, RA2JoinArena11 },
	{ "Use [ and ] to move cursor",	PMENU_ALIGN_LEFT, NULL, NULL },
	{ "ENTER to select",	PMENU_ALIGN_LEFT, NULL, NULL },
	{ "ESC to Exit Menu",	PMENU_ALIGN_LEFT, NULL, NULL },
	{ "(TAB to Return)   v" UGLADQ2_VERSION,	PMENU_ALIGN_LEFT, NULL, NULL }
};

void RA2OpenArenaMenu(edict_t *ent)
{
	PMenu_Open(ent, arena_menu, -1, sizeof(arena_menu) / sizeof(pmenu_t));
}

//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
int RA2_NumArenas(void)
{
	return num_arenas;
} //end of the function RA2_NumArenas
//===========================================================================
// RA2_GetArenaName - looks for the name from the bsp
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
char *RA2_GetArenaName(int arena)
{
	edict_t *spot = NULL;
	static char newname[35];

	while ((spot = G_Find(spot, FOFS(classname), "info_player_intermission")) != NULL)
	{
		if (spot->arena == arena) return spot->message;
	} //end while
	sprintf(newname, "Arena Number %d", arena);
	return newname;
} //end of the function RA2_GetArenaName
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_ArenaSound(char *soundname, int context)
{
	int i;
	edict_t *e;

	for (i = 0; i < maxclients->value; i++)
	{
		e = g_edicts + 1 + i;
		if(!e->inuse) continue;
		if (!e->client) continue;
		if (e->client->resp.context != context) continue;
		if (e->flags & FL_BOT) continue;
		//
		gi.WriteByte(11);
		gi.WriteString(va("play %s\n", soundname));
		gi.unicast(e, true);
		//stuffcmd(e, va("play %s\n",soundname));
	} //end for
} //end of the function RA2_ArenaSound
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_ArenaCenterPrint(char *s, int context)
{
	int i;
	edict_t *e;

	for (i = 0; i < maxclients->value; i++)
	{
		e = g_edicts + 1 + i;
		if(e->inuse && e->client && e->client->resp.context == context)
		{
			gi.centerprintf(e, s);
		} //end if
	} //end for
} //end of the function RA2_ArenaCenterPrint
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_ArenaCPrint(int priority, char *s, int context)
{
	int i;
	edict_t *e;

	for (i = 0; i < maxclients->value; i++)
	{
		e = g_edicts + 1 + i;
		if(e->inuse && e->client && e->client->resp.context == context)
		{
			gi.cprintf(e,priority, s);
		} //end if
	} //end for
} //end of the function RA2_ArenaCPrint
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void SetObserverMode(edict_t *ent, observer_mode_t omode)
{
	switch(omode) 
	{
		case NORMAL:
		{
			ent->movetype = MOVETYPE_WALK;
			ent->solid = SOLID_BBOX;
			ent->clipmask = MASK_PLAYERSOLID;
			ent->svflags &= ~SVF_NOCLIENT;
			ent->s.modelindex = 255;
			ent->client->ps.pmove.pm_flags &= ~PMF_NO_PREDICTION;
			break;
		} //end case
		case FREEFLYING:
		{
			ent->movetype = MOVETYPE_NOCLIP;
			ent->solid = SOLID_NOT;
			ent->clipmask = 0;
			ent->svflags |= SVF_NOCLIENT;
			ent->client->ps.pmove.pm_time = 0;
			ent->client->ps.pmove.pm_flags &= ~PMF_NO_PREDICTION;
			ent->client->ps.pmove.pm_flags &= ~PMF_TIME_TELEPORT;
			break;
		} //end case
	} //end switch
} //end of the function SetObserverMode

float ArenaPlayersRangeFromSpot (edict_t *spot, int arena, qboolean observer)
{
	edict_t	*player;
	float	bestplayerdistance;
	vec3_t	v;
	int		n;
	float	playerdistance;


	bestplayerdistance = 9999999;

	for (n = 1; n <= maxclients->value; n++)
	{
		player = &g_edicts[n];

		if (!player->inuse)
			continue;

		if (player->health <= 0)
			continue;

		if (!player->client)
			continue;

		if (player->client->resp.context != arena)
			continue;

		if (!observer)
		{
			if (player->flags & FL_NOTARGET)
				continue;
		}
		else
		{
			if (!(player->flags & FL_NOTARGET))
				continue;
		}

		if (player->solid == SOLID_NOT)
			continue;

		VectorSubtract (spot->s.origin, player->s.origin, v);
		playerdistance = VectorLength (v);

		if (playerdistance < bestplayerdistance)
			bestplayerdistance = playerdistance;
	}

	return bestplayerdistance;
}

int CountSpawnPoints(char *classn, int arena)
{
	edict_t	*spot;
	int		count = 0;
	
	spot = NULL;
	while ((spot = G_Find (spot, FOFS(classname), classn)) != NULL)
	{
		if (spot->arena != arena && idmap==false) continue;
		count++;
	}
	
	return count;
} //end of the function CountSpawnPoints

//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
edict_t *SelectRandomArenaSpawnPoint (char *classn, int arena)
{
	edict_t	*spot;
	int		count;
	int		selection;
	
	count = CountSpawnPoints(classn, arena);
	
	if (count < 1)
		return NULL;
	
	selection = rand() % count;
	
	//gi.dprintf("%d spots, %d selected\n",count,selection);
	
	spot = NULL;
	do
	{
		spot = G_Find (spot, FOFS(classname),classn);
		if (spot->arena != arena && idmap==false) 
			selection++;
	} while(selection--);
	
	return spot;
} //end of the function SelectRandomArenaSpawnPoint
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
edict_t *SelectFarthestArenaSpawnPoint(int arena, qboolean observer)
{
	edict_t	*bestspot;
	float	bestdistance, bestplayerdistance;
	edict_t	*spot;
	char *classn;
	
	spot = NULL;
	bestspot = NULL;
	bestdistance = 50;
	if (observer)
		classn = "misc_teleporter_dest";
	else
		classn = "info_player_deathmatch";
	while ((spot = G_Find (spot, FOFS(classname), classn)) != NULL)
	{
		//gi.bprintf (PRINT_HIGH,"arena %d spot %d\n", arena, spot->arena);
		if (spot->arena != arena && idmap==false) continue;
		bestplayerdistance = ArenaPlayersRangeFromSpot (spot, arena, observer);
		
		if (bestplayerdistance > bestdistance)
		{
			bestspot = spot;
			bestdistance = bestplayerdistance;
		}
	}
	
	return bestspot;
} //end of the function SelectFarthestArenaSpawnPoint

edict_t *GetNextObserverSpawnPoint(int arena)
{
	edict_t *dest = NULL;

	if (!(dest = SelectFarthestArenaSpawnPoint (arena, true)))
	{
		dest = SelectRandomArenaSpawnPoint ("info_player_deathmatch", arena);
	} //end if
	
	return dest;
} //end of the function GetNextObserverSpawnPoint

//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_MoveToArena(edict_t *ent, int arena, qboolean observer)
{
	vec3_t mins = {-16, -16, -24};
	vec3_t maxs = {16, 16, 32};
	edict_t *dest;
	int i;
	
	if(!arena)
	{
		if (num_arenas == 1)
			arena = 1;
		else if (ent->flags & FL_BOT)
		{
			arena = (int) atof(Info_ValueForKey(ent->client->pers.userinfo, "arena"));
			if (arena > num_arenas)
				arena = (rand() % num_arenas) + 1;
		}
	}

	if (observer)
	{
		dest = GetNextObserverSpawnPoint(arena);
		if (!dest)
		{
			gi.cprintf(ent, PRINT_HIGH, "arena not found\n");
			return;
		} //end if
		//if the player is changing arenas
		if (ent->client->resp.context != arena)
		{
			//put the client in the desired arena
			ent->client->resp.context = arena;
			//put the client at the end of the waiting list
			ent->client->ra_time = level.time;
			ent->client->ra_winner = false;
		}
		if (arena)
		{
			gi.dprintf("%s moved to arena %d as observer\n", ent->client->pers.netname, arena);
			gi.centerprintf(ent, "moved to arena %d\n", arena);
		} //end if
		else
		{
			RA2OpenArenaMenu(ent);
		} //end else
	} //end if
	else
	{
		dest = SelectFarthestArenaSpawnPoint (arena, false);

		if (!dest)
		{
			RA2_MoveToArena(ent, arena, true);
			return;
		} //end if

		ent->client->resp.context = arena;
		gi.dprintf("%s entered arena %d\n", ent->client->pers.netname, arena);
	} //end else

	gi.unlinkentity(ent);
	//
	ent->health = 100;
	ent->deadflag = DEAD_NO;
	ent->client->latched_buttons = 0;
	//
	if (ent->client->pers.weapon)
	{
		ent->client->ps.gunindex = gi.modelindex(ent->client->pers.weapon->view_model);
	} //end if
	//remove the observer flag
	if (ent->client->resp.spectator)
	{
		ent->client->resp.spectator = false;
		ent->client->pers.spectator = false;
		// reset his spectator var
		gi.WriteByte (svc_stufftext);
		gi.WriteString ("spectator 0\n");
		gi.unicast(ent, true);
	}
	ent->solid = SOLID_BBOX;
	ent->movetype = MOVETYPE_WALK;
	// clear entity state values
	ent->s.effects = 0;
	if (!observer)
	{
		ent->s.modelindex = 255;		// will use the skin specified model
		ent->s.modelindex2 = 255;		// custom gun model
	} //end if
	// sknum is player num and weapon number
	// weapon number will be added in changeweapon
	ent->s.skinnum = ent - g_edicts - 1;
	ent->s.frame = 0;
	//
	VectorCopy(dest->s.origin, ent->s.origin);
	VectorCopy(dest->s.origin, ent->s.old_origin);
	ent->s.origin[2] += 10;

	//clear the velocity and hold them in place briefly
	VectorClear (ent->velocity);
	//
	if (!observer)
	{
		// hold in place briefly
		ent->client->ps.pmove.pm_flags = PMF_TIME_TELEPORT;
		ent->client->ps.pmove.pm_time = 14;
		//draw the teleport splash at source and on the player
		ent->s.event = EV_PLAYER_TELEPORT;
	} //end if
	//set angles
	for (i = 0; i < 3; i++)
	{
		ent->client->ps.pmove.delta_angles[i] = ANGLE2SHORT(dest->s.angles[i] - ent->client->resp.cmd_angles[i]);
	} //end for
	
	VectorClear(ent->s.angles);
	VectorClear(ent->client->ps.viewangles);
	VectorClear(ent->client->v_angle);
	if (observer)
	{
		ent->flags |= FL_NOTARGET;
		ent->takedamage = DAMAGE_NO; //always start with no damage
		if (strcmp(dest->classname, "misc_teleporter_dest") != 0
#ifdef BOT
			//bots always go into free flying mode.
			//first off all we don't want them to waiste CPU
			//second the bots can be in an invalid AAS area because
			//of the one invisible walls
			|| (ent->flags & FL_BOT)
#endif //BOT
			)
		{
			SetObserverMode(ent, FREEFLYING);
		} //end if
		else
		{
			KillBox(ent);
			SetObserverMode(ent, NORMAL);
		} //end else
	} //end if
	else
	{
		KillBox(ent);
		ent->takedamage = DAMAGE_YES;
		SetObserverMode(ent, NORMAL);
	} //end else
	gi.linkentity(ent);
} //end of the function RA2_MoveToArena
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_Init(edict_t *wsent)
{
	if(!wsent) return;

	//we have to precache all items, after all we can't just use
	//the items without precaching them!!!!!!!!!!
	//now why would I hate to support mods
	PrecacheItem(FindItemByClassname("item_armor_body"));
	PrecacheItem(FindItemByClassname("item_armor_combat"));
	PrecacheItem(FindItemByClassname("item_armor_jacket"));
	PrecacheItem(FindItemByClassname("item_armor_shard"));
	PrecacheItem(FindItemByClassname("item_power_screen"));
	PrecacheItem(FindItemByClassname("item_power_shield"));
	PrecacheItem(FindItemByClassname("weapon_blaster"));
	PrecacheItem(FindItemByClassname("weapon_shotgun"));
	PrecacheItem(FindItemByClassname("weapon_supershotgun"));
	PrecacheItem(FindItemByClassname("weapon_machinegun"));
	PrecacheItem(FindItemByClassname("weapon_chaingun"));
	PrecacheItem(FindItemByClassname("ammo_grenades"));
	PrecacheItem(FindItemByClassname("weapon_grenadelauncher"));
	PrecacheItem(FindItemByClassname("weapon_rocketlauncher"));
	PrecacheItem(FindItemByClassname("weapon_hyperblaster"));
	PrecacheItem(FindItemByClassname("weapon_railgun"));
	PrecacheItem(FindItemByClassname("weapon_bfg"));
	PrecacheItem(FindItemByClassname("ammo_shells"));
	PrecacheItem(FindItemByClassname("ammo_bullets"));
	PrecacheItem(FindItemByClassname("ammo_cells"));
	PrecacheItem(FindItemByClassname("ammo_rockets"));
	PrecacheItem(FindItemByClassname("ammo_slugs"));
	PrecacheItem(FindItemByClassname("item_quad"));
	PrecacheItem(FindItemByClassname("item_invulnerability"));
	PrecacheItem(FindItemByClassname("item_silencer"));
	PrecacheItem(FindItemByClassname("item_breather"));
	PrecacheItem(FindItemByClassname("item_enviro"));
	PrecacheItem(FindItemByClassname("item_ancient_head"));
	PrecacheItem(FindItemByClassname("item_adrenaline"));
	PrecacheItem(FindItemByClassname("item_bandolier"));
	PrecacheItem(FindItemByClassname("item_pack"));
	PrecacheItem(FindItemByClassname("item_health"));
	PrecacheItem(FindItemByClassname("item_health_small"));
	PrecacheItem(FindItemByClassname("item_health_large"));
	PrecacheItem(FindItemByClassname("item_health_mega"));

	num_arenas = wsent->arena; //worldspawn arena flag is # of arenas
	if (!num_arenas)
	{
		num_arenas = 1;
		idmap = true;
	} //end if
	else
	{
		idmap = false;
	} //end else

	int i, j;
	for (i=1, j=3; i<=11; i++)
	{
		if (i <= num_arenas)
		{
			arena_menu[j].text = RA2_GetArenaName(i);
			arena_menu[j].SelectFunc = join_menu_functions[i-1];
		}
		else
		{
			arena_menu[j].text = NULL;
			arena_menu[j].SelectFunc = NULL;
		}

		j++;
	}
} //end of the function RA2_Init
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_GetSettings(arena_settings_t *settings)
{
	cvar_t *shotgun;
	cvar_t *supershotgun;
	cvar_t *machinegun;
	cvar_t *chaingun;
	cvar_t *grenadelauncher;
	cvar_t *rocketlauncher;
	cvar_t *hyperblaster;
	cvar_t *railgun;
	cvar_t *bfg;
	cvar_t *armor;
	cvar_t *health;
	cvar_t *shells;
	cvar_t *bullets;
	cvar_t *slugs;
	cvar_t *grenades;
	cvar_t *rockets;
	cvar_t *cells;
	
	shotgun =			gi.cvar("shotgun", "1", 0);
	supershotgun =		gi.cvar("supershotgun", "1", 0);
	machinegun =		gi.cvar("machinegun", "1", 0);
	chaingun =			gi.cvar("chaingun", "1", 0);
	grenadelauncher =	gi.cvar("grenadelauncher", "1", 0);
	rocketlauncher =	gi.cvar("rocketlauncher", "1", 0);
	hyperblaster =		gi.cvar("hyperblaster", "1", 0);
	railgun =			gi.cvar("railgun", "0", 0);
	bfg =					gi.cvar("bfg", "0", 0);
	//
	armor =				gi.cvar("armor", "200", CVAR_SERVERINFO);
	health =				gi.cvar("health", "100", CVAR_SERVERINFO);
	shells =				gi.cvar("shells", "100", CVAR_SERVERINFO);
	bullets =			gi.cvar("bullets", "200" ,CVAR_SERVERINFO);
	slugs =				gi.cvar("slugs", "50", CVAR_SERVERINFO);
	grenades =			gi.cvar("grenades", "50", CVAR_SERVERINFO);
	rockets =			gi.cvar("rockets", "50", CVAR_SERVERINFO);
	cells =				gi.cvar("cells", "150", CVAR_SERVERINFO);
	
	settings->weapons = 0;
	if (shotgun->value) settings->weapons += weapon_vals_x[1];
	if (supershotgun->value) settings->weapons += weapon_vals_x[2];
	if (machinegun->value) settings->weapons += weapon_vals_x[3];
	if (chaingun->value) settings->weapons += weapon_vals_x[4];
	if (grenadelauncher->value) settings->weapons += weapon_vals_x[5];
	if (railgun->value) settings->weapons += weapon_vals_x[6];
	if (hyperblaster->value) settings->weapons += weapon_vals_x[7];
	if (rocketlauncher->value) settings->weapons += weapon_vals_x[8];
	if (bfg->value) settings->weapons += weapon_vals_x[0];
	//
	settings->armor = armor->value;
	settings->health = health->value;
	settings->shells = shells->value;
	settings->bullets = bullets->value;
	settings->slugs = slugs->value;
	settings->grenades = grenades->value;
	settings->rockets = rockets->value;
	settings->cells = cells->value;
} //end of the function RA2_GetSettings
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_GiveAmmo(edict_t *e)
{
	arena_settings_t settings;
	gitem_t *w[9];
	gitem_t *it;
	int i;
	
	RA2_GetSettings(&settings);
	
	// give health
	e->health = settings.health;
	
	// give weapons
	memset(w, 0, sizeof(w));
	w[0] = FindItemByClassname("weapon_bfg");
	w[1] = FindItemByClassname("weapon_shotgun");
	w[2] = FindItemByClassname("weapon_supershotgun");
	w[3] = FindItemByClassname("weapon_machinegun");
	w[4] = FindItemByClassname("weapon_chaingun");
	w[5] = FindItemByClassname("weapon_grenadelauncher");
	w[6] = FindItemByClassname("weapon_railgun");
	w[7] = FindItemByClassname("weapon_hyperblaster");
	w[8] = FindItemByClassname("weapon_rocketlauncher");
	for(i = 0; i <= 8; i++)
	{
		if (settings.weapons & weapon_vals_x[i])
		{
			e->client->newweapon = w[i];
			e->client->pers.lastweapon = w[i];
			e->client->pers.selected_item = e->client->ps.stats[STAT_SELECTED_ITEM] = ITEM_INDEX(w[i]);
			e->client->pers.inventory[ITEM_INDEX(w[i])] = 1;
		} //end if
		else
		{
			e->client->pers.inventory[ITEM_INDEX(w[i])] = 0;
		} //end else
	} //end for
	// give ammo
	if(it = FindItemByClassname("ammo_shells")) e->client->pers.inventory[ITEM_INDEX(it)] = settings.shells;	//shells	100
	if(it = FindItemByClassname("ammo_bullets")) e->client->pers.inventory[ITEM_INDEX(it)] = settings.bullets;	//bullets       200
	if(it = FindItemByClassname("ammo_slugs")) e->client->pers.inventory[ITEM_INDEX(it)] = settings.slugs;	//slugs	 50
	if(it = FindItemByClassname("ammo_grenades")) e->client->pers.inventory[ITEM_INDEX(it)] = settings.grenades;	//grenades      50
	if(it = FindItemByClassname("ammo_rockets")) e->client->pers.inventory[ITEM_INDEX(it)] = settings.rockets;	//rockets       50
	if(it = FindItemByClassname("ammo_cells")) e->client->pers.inventory[ITEM_INDEX(it)] = settings.cells;	//cells	 200
	// give body armor
	if(it = FindItemByClassname("item_armor_body"))
	{
		e->client->pers.inventory[ITEM_INDEX(it)] = settings.armor;
	} //end if
	//set max
	e->client->pers.health			= 100;
	e->client->pers.max_health		= 100;
	e->client->pers.max_bullets	= settings.bullets;
	e->client->pers.max_shells		= settings.shells;
	e->client->pers.max_rockets	= settings.cells;
	e->client->pers.max_grenades	= settings.grenades;
	e->client->pers.max_cells		= settings.rockets;
	e->client->pers.max_slugs		= settings.slugs;
} //end of the function RA2_GiveAmmo
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void Cmd_toarena_f(edict_t *ent, int context)
{
	if (!ra->value)
	{
		if (ent) gi.cprintf(ent, PRINT_HIGH, "Rocket Arena should be enabled to use this command\n");
		else gi.dprintf("Rocket Arena should be enabled to use this command\n");
		return;
	} //end if
	if (context < 0 || context > num_arenas)
	{
		if (ent) gi.cprintf(ent, PRINT_HIGH, "arena number not in the range [0, %d]\n", num_arenas);
		else gi.dprintf("arena number not in the range [0, %d]\n", num_arenas);
		return;
	} //end if
	//move to the arena
	RA2_MoveToArena(ent, context, true);
} //end of the function Cmd_toarena_f
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
edict_t *RA2_GetArenaWinner(int arena)
{
	int i;
	edict_t *e;

	for (i = 0; i < maxclients->value; i++)
	{
		e = g_edicts + 1 + i;
		if(!e->inuse) continue;
		if (!e->client) continue;
		if (e->client->resp.context != arena) continue;
		if (e->client->ra_winner) return e;
	} //end for
	return NULL;
} //end of the function RA2_GetArenaWinner
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
#ifdef BOT
edict_t *RA2_GetLongestWaitingHuman(int arena)
{
	int i;
	float besttime;
	edict_t *e, *bestent;

	besttime = 0;
	bestent = NULL;
	for (i = 0; i < maxclients->value; i++)
	{
		e = g_edicts + 1 + i;
		if(!e->inuse) continue;
		if (!e->client) continue;
		if (e->flags & FL_BOT) continue;
		if (e->client->resp.context != arena) continue;
		//invalid time, client is already in the match
		if (e->client->ra_time < 0) continue;
		//if no time set then just set the current time
		if (!e->client->ra_time) e->client->ra_time = level.time;
		//get the client that is waiting longest
		if (!besttime || e->client->ra_time < besttime)
		{
			besttime = e->client->ra_time;
			bestent = e;
		} //end if
	} //end for
	return bestent;
} //end of the function RA2_GetLongestWaitingHuman
#endif //BOT
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
edict_t *RA2_GetLongestWaiting(int arena)
{
	int i;
	float besttime;
	edict_t *e, *bestent;

	besttime = 0;
	bestent = NULL;
	for (i = 0; i < maxclients->value; i++)
	{
		e = g_edicts + 1 + i;
		if(!e->inuse) continue;
		if (!e->client) continue;
		if (e->client->resp.context != arena) continue;
		//invalid time, client is already in the match
		if (e->client->ra_time < 0) continue;
		//if no time set then just set the current time
		if (!e->client->ra_time) e->client->ra_time = level.time;
		//get the client that is waiting longest
		if (!besttime || e->client->ra_time < besttime)
		{
			besttime = e->client->ra_time;
			bestent = e;
		} //end if
	} //end for
	return bestent;
} //end of the function RA2_GetLongestWaiting
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
qboolean RA2_AddPlayersOnSameTeamToMatch(int arena, edict_t *ent)
{
	int i;
	edict_t *e;
	int same_team_already_in_arena = 0;
	int arena_capacity = CountSpawnPoints("info_player_deathmatch", arena);
	qboolean team_includes_human = false;

	for (i = 0; i < maxclients->value; i++)
	{
		e = g_edicts + 1 + i;
		if(!e->inuse) continue;
		if (!e->client) continue;
		if (e->client->resp.context != arena) continue;
		if (ent == e || OnSameTeam(ent, e))
		{
			//invalidate the time
			e->client->ra_time = -1;
			//check if the arena can hold the player
			if (same_team_already_in_arena < arena_capacity/2)
			{
				e->flags &= ~FL_NOTARGET;
				RA2_GiveAmmo(e);
				same_team_already_in_arena++;
				RA2_MoveToArena(e, e->client->resp.context, false);
				if (!(e->flags & FL_BOT))
					team_includes_human = true;
			}
			else
			{
				gi.centerprintf(e, "Your team is too large\n");
				//move player to observer room if not already there
				if (!(e->flags & FL_NOTARGET))
					RA2_MoveToArena(e, e->client->resp.context, true);
			}
		} //end if
	} //end for
	return team_includes_human;
} //end of the function RA2_AddPlayersOnSameTeamToMatch
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_StartMatch_think(edict_t *ent)
{
	char buf[256];
	int i;
	edict_t *e;

	if (ent->count <= 0)
	{
		RA2_ArenaCenterPrint("FIGHT!", ent->style);
		RA2_ArenaSound("ra/sffight.wav", ent->style);
		//find players in the arena...
		for (i = 0; i < maxclients->value; i++)
		{
			e = g_edicts + 1 + i;
			if (!e->inuse) continue;
			if (!e->client) continue;
			if (e->client->resp.context != ent->style) continue;
			if (e->flags & FL_NOTARGET) continue;
			//...and enable their weapons
			e->takedamage = DAMAGE_AIM;
		} //end for
		//mark the match as active
		ent->nextthink = 0;
		return;
	} //end if

	sprintf(buf, "%d", ent->count);
	RA2_ArenaCenterPrint(buf, ent->style);
	if (ent->count <= 3)
	{
		sprintf(buf, "ra/sf%d.wav", ent->count);
		RA2_ArenaSound(buf, ent->style);
	}
	ent->count--;
	ent->nextthink = level.time + 1;
} //end of the function RA2_StartMatch_think
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_StartMatch(int context)
{
	int i;
	edict_t *e;
	qboolean first_team_includes_human;

	//check for an active match in this arena
	e = G_Find(NULL, FOFS(classname), "arenacountdown");
	while(e)
	{
		if (e->style == context) return;
		e = G_Find(e, FOFS(classname), "arenacountdown");
	} //end while
	//check for an intermission in this arena
	e = G_Find(NULL, FOFS(classname), "stopmatch");
	while(e)
	{
		if (e->style == context)
		{
			if(e->nextthink) return;
			else
			{
				G_FreeEdict(e);
				break;
			}
		}
		e = G_Find(e, FOFS(classname), "stopmatch");
	} //end while
	//respawn any dead players
	for (i = 0; i < maxclients->value; i++)
	{
		e = g_edicts + 1 + i;
		if (!e->inuse) continue;
		if (!e->client) continue;
		if (e->client->resp.context != context) continue;
		if (e->health <= 0 || e->deadflag == DEAD_DEAD)
		{
			respawn(e);
		} //endif
	} //end for
	//
	gi.dprintf("Starting match in %s\n", RA2_GetArenaName(context));
	//get any winner(s) from the previous match
	e = RA2_GetArenaWinner(context);
	//there are no winners so get the longest waiting player/team
	if (!e) e = RA2_GetLongestWaiting(context);
	//no teams to add... how did we get here?
	if (!e)
		return;
	//add the first player/team
	else
		first_team_includes_human = RA2_AddPlayersOnSameTeamToMatch(context, e);
	//if bot-cycling is on and the first team didn't include a human
	if (ra_botcycle->value && !first_team_includes_human)
		e = RA2_GetLongestWaitingHuman(context);
	else
		e = RA2_GetLongestWaiting(context);
	//add the second player/team
	if (e) RA2_AddPlayersOnSameTeamToMatch(context, e);

	//start countdown
	e = G_Spawn();
	e->classname = "arenacountdown";
	e->style = context;
	e->count = 5;
	e->think = RA2_StartMatch_think;
	e->nextthink = level.time + 1;
} //end of the function RA2_StartMatch
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void Cmd_start_match_f(edict_t *ent, int context)
{
	if (!ra->value)
	{
		if (ent) gi.cprintf(ent, PRINT_HIGH, "Rocket Arena should be enabled to use this command\n");
		else gi.dprintf("Rocket Arena should be enabled to use this command\n");
		return;
	} //end if
	if (context <= 0 || context > num_arenas)
	{
		if (ent) gi.centerprintf(ent, "first enter an arena in the range [1, %d]", num_arenas);
		else gi.dprintf("the arena number must be in the range [1, %d]\n", num_arenas);
		return;
	} //end if

	RA2_StartMatch(context);
} //end of the function Cmd_start_match_f
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_StopMatch_think(edict_t *ent)
{
	if (ent->count <= 0)
	{
		int i;
		edict_t *e;

		//mark the match as completed
		e = G_Find(NULL, FOFS(classname), "arenacountdown");
		while(e)
		{
			if (e->style == ent->style)
			{
				G_FreeEdict(e);
				break;
			}
			e = G_Find(e, FOFS(classname), "arenacountdown");
		} //end while

		//mark the arena at intermission
		ent->nextthink = 0;
		return;
	} //end if
	ent->count--;
	ent->nextthink = level.time + 1;
} //end of the function RA2_StopMatch_think
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_StopMatch(int context, int delay)
{
	edict_t *e;

	e = G_Find(NULL, FOFS(classname), "stopmatch");
	while(e)
	{
		if (e->style == context) return;
		e = G_Find(e, FOFS(classname), "stopmatch");
	} //end while
	e = G_Spawn();
	e->classname = "stopmatch";
	e->style = context;
	e->count = delay;
	e->think = RA2_StopMatch_think;
	e->nextthink = level.time + 1;
} //end of the function RA2_StopMatch
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void Cmd_stop_match_f(edict_t *ent, int context, int delay)
{
	if (!ra->value)
	{
		if (ent) gi.cprintf(ent, PRINT_HIGH, "Rocket Arena should be enabled to use this command\n");
		else gi.dprintf("Rocket Arena should be enabled to use this command\n");
		return;
	} //end if
	if (context <= 0 || context > num_arenas)
	{
		if (ent) gi.centerprintf(ent, "first enter an arena in the range [1, %d]", num_arenas);
		else gi.dprintf("the arena number must be in the range [1, %d]\n", num_arenas);
		return;
	} //end if

	RA2_StopMatch(context, delay);
} //end of the function Cmd_stop_match_f
//===========================================================================
//
// Parameter:				-
// Returns:					-
// Changes Globals:		-
//===========================================================================
void RA2_CheckRules(void)
{
	int i, context, numarenateams;
	edict_t *lastclient, *e;
	char buf[1024], arena_team_list[MAX_STRING_CHARS];

	//check for automatically stopping matches
	for (context = 1; context <= num_arenas; context++)
	{
		numarenateams = 0;
		lastclient = NULL;
		strcpy(arena_team_list, "");
		//find out if there are still people playing in the arena
		for (i = 0; i < maxclients->value; i++)
		{
			e = g_edicts + 1 + i;
			if (!e->inuse) continue;
			if (!e->client) continue;
			if (e->client->resp.context != context) continue;
			//another player in this arena
			if ((int)(dmflags->value) & (DF_MODELTEAMS | DF_SKINTEAMS))
			{
				//if we haven't already counted this team
				if (!strstr(arena_team_list, ClientTeam(e)))
				{
					strcat(arena_team_list, ClientTeam(e));
					numarenateams++;
				}
			}
			else
			{
				numarenateams++;
			}
			//if the player is observing
			if (e->flags & FL_NOTARGET) continue;
			//if the player is dead
			if (e->health <= 0 || e->deadflag == DEAD_DEAD) continue;
			//this player is still living in the arena
			if ((int)(dmflags->value) & (DF_MODELTEAMS | DF_SKINTEAMS))
			{
				//if there are other players in the arena
				if (lastclient)
				{
					//if one of the other players is not on the same team
					if (!OnSameTeam(lastclient, e)) break;
				} //end if
				lastclient = e;
			} //end if
			else
			{
				//if there's more than one client in the arena
				if (lastclient) break;
				lastclient = e;
			} //end else
		} //end for
		//if there are still people playing in the arena
		if (i < maxclients->value) continue;
		//if there aren't anough teams in the arena anyway
		if (numarenateams <= 1) continue;
		//if the match is already being stopped
		e = G_Find(NULL, FOFS(classname), "stopmatch");
		while(e)
		{
			if (e->style == context) break;
			e = G_Find(e, FOFS(classname), "stopmatch");
		} //end while
		if (e)
		{
			//if the arena is at intermission and auto starting is on
			if(!e->nextthink && gi.cvar("mstart_auto", "0", 0)->value)
			{
				RA2_StartMatch(context);
			}
			continue;
		}
		//if the match is already being started
		e = G_Find(NULL, FOFS(classname), "arenacountdown");
		while(e)
		{
			if (e->style == context && e->nextthink) break;
			e = G_Find(e, FOFS(classname), "arenacountdown");
		} //end while
		if (e) continue;
		//for player cycling reset the waiting time and winner flags
		for (i = 0; i < maxclients->value; i++)
		{
			e = g_edicts + 1 + i;
			if (!e->inuse) continue;
			if (!e->client) continue;
			if (e->client->resp.context != context) continue;
			//if this player was in the match
			if (e->client->ra_time < 0) e->client->ra_time = level.time;
			//assume player is not a winner
			e->client->ra_winner = false;
		} //end for
		//if there was at least one last client
		if (lastclient)
		{
			//print the winner(s) on the screen
			if ((int)(dmflags->value) & (DF_MODELTEAMS | DF_SKINTEAMS))
			{
				strcpy(buf, "the team with the players:\n");
				for (i = 0; i < maxclients->value; i++)
				{
					e = g_edicts + 1 + i;
					if (!e->inuse) continue;
					if (!e->client) continue;
					if (e->client->resp.context != context) continue;
					//if this player was in the match
					if (e->client->ra_time < 0) e->client->ra_time = level.time;
					//assume player is not a winner
					e->client->ra_winner = false;
					//if the player is on the same team
					if (OnSameTeam(lastclient, e))
					{
						//for player cycling keep track of the winners
						e->client->ra_winner = true;
						//
						strcat(buf, e->client->pers.netname);
						strcat(buf, "\n");
					} //end if
				} //end for
				strcat(buf, "WON!");
			} //end if
			else
			{
				sprintf(buf, "%s WON!\n", lastclient->client->pers.netname);
				//for player cycling keep track of the winners
				lastclient->client->ra_winner = true;
			} //end else
			RA2_ArenaCenterPrint(buf, context);
		} //end if
		//stop the match after three seconds
		RA2_StopMatch(context, 3);
	} //end for
} //end of the function RA2_CheckRules
#endif //ROCKETARENA #ifdef at start of file
