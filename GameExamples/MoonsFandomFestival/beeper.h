// Churrera Engine
// ===============
// Copyleft 2010, 2011, 2012, 2013 by The Mojon Twins

// beeper.h
// Cointains Beeper sound effects

// Most effects have been taken off BeepFX's demo project.
// So I guess they should be credited to Shiru again ;)

#asm

.sound_play
   
   ld hl, soundEffectsData   ;address of sound effects data

   ;di
   push iy

   ld b,0
   ld c,a
   add hl,bc
   add hl,bc
   ld a,(hl)
   inc hl
   ld h,(hl)
   ld l,a
   push hl
   pop ix         ;put it into ix

.readData
   ld a,(ix+0)      ;read block type
   or a
   jr nz,readData_sound
   pop iy
   ;ei
   ret
   
.readData_sound
   ld c,(ix+1)      ;read duration 1
   ld b,(ix+2)
   ld e,(ix+3)      ;read duration 2
   ld d,(ix+4)
   push de
   pop iy

   dec a
   jr nz,sfxRoutineNoise



;this routine generate tone with many parameters

.sfxRoutineTone
   ld e,(ix+5)      ;freq
   ld d,(ix+6)
   ld a,(ix+9)      ;duty
   ld (sfxRoutineTone_duty + 1),a
   ld hl,0

.sfxRoutineTone_l0
   push bc
   push iy
   pop bc
.sfxRoutineTone_l1
   add hl,de
   ld a,h
.sfxRoutineTone_duty
   cp 0
   sbc a,a
   and 16
.sfxRoutineTone_border
   or 0
   out ($fe),a

   dec bc
   ld a,b
   or c
   jr nz,sfxRoutineTone_l1

   ld a,(sfxRoutineTone_duty + 1)
   add a,(ix+10)   ;duty change
   ld (sfxRoutineTone_duty + 1),a

   ld c,(ix+7)      ;slide
   ld b,(ix+8)
   ex de,hl
   add hl,bc
   ex de,hl

   pop bc
   dec bc
   ld a,b
   or c
   jr nz,sfxRoutineTone_l0

   ld c,11
.nextData
   add ix,bc      ;skip to the next block
   jr readData

;this routine generate noise with two parameters

.sfxRoutineNoise
   ld e,(ix+5)      ;pitch

   ld d,1
   ld h,d
   ld l,d
.sfxRoutineNoise_l0
   push bc
   push iy
   pop bc
.sfxRoutineNoise_l1
   ld a,(hl)
   and 16
.sfxRoutineNoise_border
   or 0
   out ($fe),a
   dec d
   jr nz,sfxRoutineNoise_l2
   ld d,e
   inc hl
   ld a,h
   and $1f
   ld h,a
.sfxRoutineNoise_l2
   dec bc
   ld a,b
   or c
   jr nz,sfxRoutineNoise_l1

   ld a,e
   add a,(ix+6)   ;slide
   ld e,a

   pop bc
   dec bc
   ld a,b
   or c
   jr nz,sfxRoutineNoise_l0

   ld c,7
   jr nextData
   
.soundEffectsData
   defw soundEffectsData_sfx0
   defw soundEffectsData_sfx1
   defw soundEffectsData_sfx2
   defw soundEffectsData_sfx3
   defw soundEffectsData_sfx4
   defw soundEffectsData_sfx5
   defw soundEffectsData_sfx6
   defw soundEffectsData_sfx7
   defw soundEffectsData_sfx8
   defw soundEffectsData_sfx9
   defw soundEffectsData_sfx10
   defw soundEffectsData_sfx11
   
.soundEffectsData_sfx0
   //defb 0x01
   //defw 0x000a,0x03e8,0x00c8,0x0016,0x1680
   //defb 0x00
.soundEffectsData_sfx1
   defb 1 ;tone
   defw 40,2125,16384,45459,128
   defb 0
.soundEffectsData_sfx2
   //defb 1 ;tone
   //defw 5,1800,1000,1000,65408
   //defb 0
.soundEffectsData_sfx3
   //defb 1 ;tone
   //defw 50,100,200,65531,128
   //defb 0
.soundEffectsData_sfx4
   defb 1 ;tone
   defw 1,1000,2000,0,64
   defb 1 ;pause
   defw 1,1000,0,0,0
   defb 1 ;tone
   defw 1,1000,1500,0,64
   defb 0
.soundEffectsData_sfx5
   //defb 2 ;noise
   //defw 2,2000,32776
   //defb 0
.soundEffectsData_sfx6
   //defb 1 ;tone
   //defw 10,100,2000,100,128
   //defb 0
.soundEffectsData_sfx7
   defb 1 ;tone
   defw 10,1000,200,2,272
   defb 1 ;pause
   defw 1,4000,0,0,0
   defb 1 ;tone
   defw 10,1000,200,65534,272
   defb 0
.soundEffectsData_sfx8
   //defb 1 ;tone
   //defw 1,2000,400,0,128
   //defb 1 ;tone
   //defw 1,2000,600,0,128
   //defb 1 ;tone
   //defw 1,2000,800,0,128
   //defb 1 ;tone
   //defw 1,2000,400,0,16
   //defb 1 ;tone
   //defw 1,2000,600,0,16
   //defb 1 ;tone
   //defw 1,2000,800,0,16
   //defb 0
.soundEffectsData_sfx9
   defb 1 ;tone
   defw 5,2000,200,100,128
   defb 0
.soundEffectsData_sfx10
   defb 1 ;tone
   defw 4,1000,1000,400,128
   defb 0
.soundEffectsData_sfx11
   //defb 0x01
   //defw 0x0014,0x01f4,0x00c8,0x0005,0x0110
   //defb 0x01
   //defw 0x0001,0x03e8,0x0000,0x0000,0x0000
   //defb 0x01
   //defw 0x001e,0x01f4,0x00c8,0x0008,0x0110
   //defb 0x01
   //defw 0x0001,0x07d0,0x0000,0x0000,0x0000
   //defb 0x00
#endasm

/*
   TABLA DE SONIDOS

   n   Sonido
   ----------
   1	Computerized sound
   2	Not in use (removed to save space)
   3	Not in use (removed to save space)
   4	Selector
   5	Not in use (removed to save space)
   6    Not in use (removed to save space)
   7    Oh no!
   8	Not in use (removed to save space)
   9	Reaction
   10	Reaction
   11   Not in use (removed to save space)
   
*/

int peta_el_beeper (unsigned char n) {
   // Cargar en A el valor de n
   asm_int [0] = n+1;
   #asm
      push ix
      push iy
      ld a, (_asm_int)
      call sound_play
      pop ix
      pop iy
   #endasm
}