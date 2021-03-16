#ifndef _K2D_FONT_H_
#define _K2D_FONT_H_

#include "K2D_Texture.h"

/*
	Font class
	Allow to draw string on the screen
*/
class K2D_Font
{
public:
  K2D_Font() {
	  sizex=1.0f; sizey=1.0f;
	};
	~K2D_Font() {KillFont();};
  bool Load( char *strFile);
  int DrawText( int x, int y, char type, char *fmt, ... );
  int KillFont();
  int SetSize( float x, float y );

  K2D_Texture font;
  char* GetFileName (){	return font.GetFileName ();  }

private:
  int base;
  float sizex,sizey;
};

#endif