// Tenebra Macabre
// Churrera 3.99.2 modificada con overlay.h
// Compilada con splib2t.lib, versi�n especial modificada por m�.
// Esta versi�n de splib2 pinta o no los atributos dependiendo de
// que haya un 0 o un 1 en 24999.

// churromain.c
// Esqueleto de juegos de la churrera
// Copyleft 2010-2013 The Mojon Twins

// version FORK 3.99b

#include <spritepack.h>

#pragma output STACKPTR=61952
#define AD_FREE			60655

// MAX BINARY SIZE = 35655 (make @ 25000) or 36155 (make @ 24500)

// Optimal place to compile if using COMPRESSED_LEVELS:
// 23296 + MAP_W * MAP_H * (108) + MAX_CERROJOS * 4 + 49

// MODIFIED
#include "overlay.h"

#include "config.h"

// Codigo para joystick virtual Android compatible con Spectranet (comienzo)
#include <sys/socket.h>
#include <sockpoll.h>
#include <sys/compiler.h>
// Codigo para joystick virtual Android compatible con Spectranet (final)

// Cosas del juego:

#include "definitions.h"
#ifdef ACTIVATE_SCRIPTING
#include "msc-config.h"
#endif
#include "aplib.h"
#include "pantallas.h"
#ifdef COMPRESSED_LEVELS
#include "levels.h"
#else
#include "mapa.h"
#endif
#include "tileset.h"
#include "sprites.h"
#include "extrasprites.h"
#ifndef COMPRESSED_LEVELS
#include "enems.h"
#endif
#include "beeper.h"
#include "simpleay.h"
#include "printer.h"
#ifdef ACTIVATE_SCRIPTING
#ifdef ENABLE_EXTERN_CODE
#include "extern.h"
#endif
#include "msc.h"
#endif
#include "engine.h"
#include "mainloop.h"

// Y el main

void main (void) {
	
	// Para uso exclusivo con Spectranet, configura puerto 8081 TCP/IP con Joystick Android virtual
	// El juego no cargara hasta que detecte conexion de joystick o se pulse una tecla
	#asm
		CALL 0DAFh;
		
		; Data
		line: 
			defb 'T','e','n','e','b','r','a',' ','M','a','c','a','b','r','e','.',' ','A','n','d','r','o','i','d',' ','V','i','r','t','u','a','l',' ','J','o','y','s','t','i','c','k',' ','c','o','m','p','a','t','i','b','l','e',' ','v','e','r','s','i','o','n','.','W','a','i','t','i','n','g',' ','f','o','r',' ','a','n',' ','A','n','d','r','o','i','d',' ','J','o','y','s','t','i','c','k','.',13,'$'
			
		start:
			ld      a, 2                  ; channel 2 = "S" for screen
			call    $1601                 ; Select print channel using ROM

			ld hl,line                    ; Print line
			call printline
			ret                        

		printline:                     	  ; Routine to print out a line
			ld a,(hl)                     ; Get character to print
			cp '$'                        ; See if it '$' terminator
			jp z,printend                 ; 
			rst 16                        ; Spectrum: Print the character in 'A'
			inc hl                        ; Move onto the next character
			jp printline                  ; Loop round
		
		printend:
		
	#endasm
	
	if (init_tcpip () == -1){
		return;
	};
	
	do_game ();
}

// From beepola. Phaser engine by Shiru.
#include "music.h"
