#
# Makefile for the Gladiator Bot game source: gamex86.dll
# Intended for mingw32-make (gcc for Win32)
#

# Detect the OS
ifdef SystemRoot
OSTYPE := Windows
else
OSTYPE := $(shell uname -s)
endif
 
# Special case for MinGW
ifneq (,$(findstring MINGW,$(OSTYPE)))
OSTYPE := Windows
endif

# Compiler options
CC=gcc
#CC=i686-w64-mingw32-gcc
BASE_CFLAGS=-Dstricmp=strcasecmp -DC_ONLY -m32

#use these cflags to optimize it
CFLAGS=$(BASE_CFLAGS) -O6 -ffast-math -funroll-loops \
	-fomit-frame-pointer -fexpensive-optimizations -falign-loops=2 \
	-falign-jumps=2 -falign-functions=2
#use these when debugging 
#CFLAGS=$(BASE_CFLAGS) -g

LDFLAGS=-ldl -lm
ifeq ($(OSTYPE), Windows)
 SHLIBEXT=x86.dll
else
 ifeq ($(CC), i686-w64-mingw32-gcc)
  SHLIBEXT=x86.dll
 else
  SHLIBEXT=i386.so
 endif
endif
SHLIBCFLAGS=-fPIC
SHLIBLDFLAGS=-shared

DO_CC=$(CC) $(CFLAGS) $(SHLIBCFLAGS) -o $@ -c $<

#############################################################################
# SETUP AND BUILD
# GLADIATOR BOT GAME SOURCE
#############################################################################

.c.o:
	$(DO_CC)

GAME_OBJS = \
	src/bl_cmd.o\
	src/bl_botcfg.o src/bl_debug.o src/bl_main.o src/bl_redirgi.o src/bl_spawn.o src/dm_ball_rogue.o\
	src/dm_tag_rogue.o src/g_ai.o src/g_arena.o src/g_ch.o src/g_chase.o src/g_cmds.o src/g_combat.o\
	src/g_ctf.o src/g_func.o src/g_items.o src/g_log.o src/g_main.o src/g_misc.o src/g_monster.o\
	src/g_newai_rogue.o src/g_newdm_rogue.o src/g_newfnc_rogue.o src/g_newtarg_rogue.o\
	src/g_newtrig_rogue.o src/g_newweap_rogue.o src/g_phys.o src/g_save.o src/g_spawn.o\
	src/g_sphere_rogue.o src/g_svcmds.o src/g_target.o src/g_trigger.o src/g_turret.o\
	src/g_utils.o src/g_weapon.o src/m_actor.o src/m_berserk.o src/m_boss2.o src/m_boss3.o\
	src/m_boss31.o src/m_boss32.o src/m_boss5_xatrix.o src/m_brain.o src/m_carrier_rogue.o\
	src/m_chick.o src/m_fixbot_xatrix.o src/m_flash.o src/m_flipper.o src/m_float.o src/m_flyer.o\
	src/m_gekk_xatrix.o src/m_gladb_xatrix.o src/m_gladiator.o src/m_gunner.o src/m_hover.o\
	src/m_infantry.o src/m_insane.o src/m_medic.o src/m_move.o src/m_move2_rogue.o src/m_mutant.o\
	src/m_parasite.o src/m_soldier.o src/m_stalker_rogue.o src/m_supertank.o src/m_tank.o\
	src/m_turret_rogue.o src/m_widow2_rogue.o src/m_widow_rogue.o src/p_botmenu.o\
	src/p_client.o src/p_hud.o src/p_lag.o src/p_menu.o src/p_menulib.o src/p_trail.o\
	src/p_view.o src/p_weapon.o src/q_shared.o

game$(SHLIBEXT) : $(GAME_OBJS)
	$(CC) $(CFLAGS) $(SHLIBLDFLAGS) -o $@ $(GAME_OBJS)


#############################################################################
# MISC
#############################################################################

clean:
	-rm -f $(GAME_OBJS)

depend:
	gcc -MM $(GAME_OBJS:.o=.c)


install:
	cp game$(SHLIBEXT) ..

#
# From "make depend"
#

