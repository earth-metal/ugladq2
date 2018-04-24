# uGladQ2
MrElusive's Gladiator Bot is the most advanced non-human deathmatch opponent ("bot") available for Quake 2.  (The Quake 3: Arena bot is the direct successor of the Gladiator Bot.)  The source code for the Quake 2 version of the bot was never released, however the source for the deathmatch games they can play was made available.

This is an unofficial effort to clean up the rough edges in the game source for the original Gladiator Bot, making the available Deathmatch types (particularly Capture the Flag and Rocket Arena) more polished.

Gladiator Bot Downloads & Documentation
---------------
As of 2018, the original downloads for 32-bit Windows and Linux are available at http://mrelusive.com/oldprojects/gladiator/download.shtml.htm
 
###Building
- For Windows users, a compiled gamex86.dll is downloadable from this repository.
- Windows users wishing to compile their own uGladQ2 library will need to install Mingw-w64 (https://mingw-w64.org).  In a Mingw-w64 terminal, navigate to the directory containing the uGladQ2 Makefile and run "mingw32-make" to create the "gamex86.dll" file.
- Linux users, navigate to the Makefile's parent directory in a terminal and run the "make" command.  Rename the generated "game.so" file to be suitable for your Q2 engine.

Installation
---------------
Place the uGladQ2 library into the "gladiator" folder in your Q2 directory.  Make a backup of the original file if desired.

Compatibility
---------------
While this game source will probably build on virtually any architecture type, compiled versions of the proprietary Gladiator Bot library are only available for 32-bit Windows and Linux systems.  Compatibility has been verified running Quake 2 v3.24 ("The Unofficial Patch") in Windows XP.

As of Windows 10, full compatibility for Win32 applications is still maintained, so Windows users should be able to run the uGladQ2 DLL and play against bots using a 32-bit Quake 2 engine (such as v3.20 or v3.24).  Linux users will either need to run a 32-bit OS variant or install a 32-bit compatibility layer applicable for the Quake 2 engine and the Gladiator SO they wish to use.

###Copyright and distribution permissions 
No warranties are made--expressed or implied--regarding the usage, functionality, or implied operability of this source code. All elements are available solely on an "as-is" basis. Usage is subject to the user's own risk.

The Gladiator Bot game source code may NOT be sold or used in commercial products in ANY form.

Should you decide to release a modified version of the Gladiator Bot game source code or parts of it, in source code or compiled form, you MUST add the following text to the documentation included with your product.

    This product incorporates source code from the Gladiator bot.
    The Gladiator bot is available at the Gladiator Bot page
    http://www.botepidemic.com/gladiator.

    This program is in NO way supported by MrElusive.

    This program may NOT be sold in ANY form whatsoever. If you have paid
    for this product, you should contact MrElusive immidiately via the
    Gladiator bot page or at MrElusive@botepidemic.com

Origination
---------------
The code bases for this project were publicly released by id Sotware, Xatrix Entertainment, Rogue Entertainment, David Wright, and MrElusive during the years 1998 and 1999.  Interested parties should contact the respective creators or their successors for licensing information.

