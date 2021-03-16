#ifndef _K2D_STATE_H
#define _K2D_STATE_H

#include <windows.h>
#include <gl\gl.h>

enum K2D_States
{
	K2D_TEXTURE		= (1 << 1),
	K2D_COLOR_KEY	= (1 << 2),
	K2D_BLENDING	= (1 << 3)
};

/*
	Classe utilisee pour effectivement les traitements graphiques à l'ecran
*/
class K2D_Gfx
{
public:
	static void Enable (int state)
	{
		/* Active les texture
		Indispenable si on utilise des sprite
		*/
		if (state & K2D_TEXTURE)
			glEnable (GL_TEXTURE_2D);
		/*
		Active la color keying via la couche alpha de la texture
		Sert pour ignorer certaines parties d une texture
		Pour editer la couche alpha -> Tga alpha edit
		*/
		if (state & K2D_COLOR_KEY)
		{
			glEnable( GL_ALPHA_TEST );
			glAlphaFunc( GL_GREATER, 0.0f );
		}
		/*
		Autorise la transparence
		On définit la facteur de transparence via le 4eme parametre de glColor4f
		1.0f = pas de transparence; 0.0f = on ne voit plus la texture
		*/
		if (state & K2D_BLENDING)
		{
			glEnable (GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		}
	}
	/* La meme chose, mais annule les effets
	Il est important de faire appel a cette fonction regulierement pour annuler
	les effets qui ne sont pas utilisés mais qui necessitent des ressources (le blending par ex)
	*/
	static void Disable (int state)
	{
		if (state & K2D_TEXTURE)
			glDisable (GL_TEXTURE_2D);
		if (state & K2D_COLOR_KEY)
		{
			glDisable( GL_ALPHA_TEST );
			glAlphaFunc( GL_GREATER, 0.0f );
		}
		if (state & K2D_BLENDING)
		{
			glDisable (GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
		}
	}
		
};

#endif