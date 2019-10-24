/* Compile options needed: none
*/


#include <dos.h>
#include <conio.h>
#include <stdio.h>

#define TRUE  1
#define FALSE 0

#define VIDEO_IO        0x10
#define BIOS_CALL       0x10
#define INTENSITY_TGL   0x03

void toggle_intensity( int );

void main( )

{ 
   long i;
   int row;
   int color;
   char buf[80];

   _settextrows( 43 );
   _clearscreen( _GCLEARSCREEN );
   toggle_intensity( 1 );

/*  Bit 7 = blink; there are 8 background colors and blinking text */

   for (i = 0, row = 1, color = 31; i <= 31; i++, row++, color--)
   {
      _setbkcolor( i );
      _settextcolor( color );
      _settextposition( row, 10 );
      sprintf( buf, "  Background %2ld  Foreground %2d\n", i,color );
      _outtext( buf );
   }

   _setbkcolor( _BLACK );
   _settextcolor( 7 );
   _outtext( "\n\nSetting 8 background colors, blinking text." );
   _outtext( "\n\nStrike any key to continue..." );
   getch( );

   _clearscreen( _GCLEARSCREEN );
   toggle_intensity( 0 );
/*  Bit 7 = intensity; there are 16 background colors */

   for (i = 0, row = 1, color = 31; i <= 31; i++, row++, color--)
   {
      _setbkcolor( i );
      _settextcolor( color );
      _settextposition( row, 10 );
      sprintf( buf, "  Background %2ld  Foreground %2d\n", i,color );
      _outtext (buf);
   }

   _setbkcolor( _BLACK );
   _settextcolor( 7 );
   _outtext( "\n\nSetting 16 background colors, no blinking text." );
   _outtext( "\n\nStrike any key to quit..." );
   getch( );

   _setvideomode( _DEFAULTMODE );
   _clearscreen( _GCLEARSCREEN );

} 

void toggle_intensity( int onoff )

{ 
   union REGS regs;

   regs.h.ah = VIDEO_IO;
   regs.h.al = INTENSITY_TGL;
   if ( !onoff )
      regs.h.bl = 0x0;
   else
      regs.h.bl = 0x1;
   int86( BIOS_CALL, &regs, &regs );

} 