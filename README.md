# uGladQ2
MrElusive's Gladiator Bot is the most realistic non-human deathmatch opponent ("bot") available for Quake 2.  (The Quake 3: Arena bot is the direct successor of the Gladiator Bot.)  The source code for the Quake 2 version of the bot was never released, however the source for the game-types they can play was made available.

This is an Unofficial effort to clean up the rough edges in the game source for the original Gladiator Bot, making the available Deathmatch types (particularly "Capture the Flag" and "Rocket Arena") more polished.  See the CHANGELOG for a full list of improvements.

Compatibility
---------------
While this game source will probably build with GCC on virtually any architecture type, compiled versions of the proprietary Gladiator Bot library are only available for 32-bit Windows and Linux systems.

Compatibility for Win32 applications is supported in Windows 10, so users should be able to run the uGladQ2 DLL and play against bots using a 32-bit Quake 2 engine such as v3.20 or v3.24.  Modified engines such as KMQ2 and Quake2XP will not work with this DLL!  Compatibility has been verified running Quake 2 v3.24 ("The Unofficial Patch") in Windows XP.

Linux users will either need to run a 32-bit OS variant or install a 32-bit compatibility layer applicable for the official Quake 2 executable they wish to use.

Gladiator Bot Downloads & Documentation
---------------
As of April 2018, the original Gladiator downloads and documentation for 32-bit Windows and Linux are available at http://mrelusive.com/oldprojects/gladiator/download.shtml.htm

An optional "Singleplayer Deathmatch" campaign can be downloaded at http://www.mediafire.com/file/l5zb6rmo9gnso55/gladq2096_to_099u_patch.zip/file
 
Building
---------------
### Windows
- A compiled gamex86.dll is downloadable from this repository.
- Users wishing to compile their own uGladQ2 library will need to install Mingw-w64 (https://mingw-w64.org).  In a Mingw-w64 terminal, navigate to the directory containing the uGladQ2 Makefile and run "mingw32-make" to create the "gamex86.dll" file.
### Linux
- A compiled gamei386.so is downloadable from this repository.  (This was generated using Ubuntu's "gcc-multilib" library.  It may not work for other distributions.)
- Users wishing to compile their own uGladQ2 library, navigate to the Makefile's parent directory in a terminal and run the "make" command to create the "gamei386.so" file.

Installation
---------------
Make a backup of any original .dll (or .so) files if desired.  Place the uGladQ2 library into the "gladiator" folder in your Q2 directory, then start Quake 2 normally.

New Console Variables
--------------
uGladQ2 adds the following console variables.  These are also toggle-able from the in-game menu.  For all other commands see the original documentation for version 0.96 (included in the downloads at the link above).

ctf_hook <0/1>: Default: ON.
- Toggle "offhand hook" availability off/on in CTF matches.  Available from the in-game "CTF" menu.

NOTES
1. Any active bots must be reloaded if changing this setting from the console.
2. Bots don't use the regular grappling hook.

ra_fastswitch <0/1>: Default: OFF.
- Toggle "fast weapon switching" off/on in Rocket Arena matches.  Available from the in-game "RA2" menu.

sp_dm <0/1>: Default: OFF.
- Enables "Singleplayer Deathmatch" mode when deathmatch is also enabled.

NOTES
1. After a new map is loaded the server executes a config at "sp_dm/[mapname].cfg"
2. Disables usage of the "Bots" and "DM/CTF/RA2" in-game menus.
3. Current map is replayed until a human player has the highest score.

Obsolete Variables
--------------
The following console variables are no longer in use.

ra_playercycle <0/1>
- Possibly intended for debugging.  When set to "0" all observers in an arena were spawned into matches as participants regardless of team membership.  Removed from the in-game "RA2" menu.

Legalities
---------------
The license for the Gladiator Bot's game source requires that the following text be included in this file:

    This product incorporates source code from the Gladiator bot.
    The Gladiator bot is available at the Gladiator Bot page
    http://www.botepidemic.com/gladiator.

    This program is in NO way supported by MrElusive.

    This program may NOT be sold in ANY form whatsoever. If you have paid
    for this product, you should contact MrElusive immidiately via the
    Gladiator bot page or at MrElusive@botepidemic.com
