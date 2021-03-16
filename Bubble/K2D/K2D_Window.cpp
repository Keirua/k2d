#include "K2D_Window.h"

#include <il\il.h>
#include <il\ilu.h>
#include <il\ilut.h>
#include <vector>
#include <windows.h>
#include <gl\gl.h>

extern K2D_Window	g_Gfx;
extern K2D_Timer	g_Timer;

#define iter(i,p)		for(i = p.begin(); i != p.end(); i++)

/*
	Initialise la fenetre de taille w*h
*/
bool K2D_Window :: Init( int w, int h, int bpp, bool fullscreen )
{
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) 
	{
        printf("Couldn't Loadialize SDL: %s\n", SDL_GetError());
        return false;
    }

    // Nettoyer en quittant
    atexit( SDL_Quit );
    
	ilInit();
	ilutRenderer(ILUT_OPENGL); 

	m_iWinX = w;
	m_iWinY = h		;
	m_iBpp  = bpp;

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    int Flags = SDL_OPENGL;

	if (fullscreen )
		Flags |= SDL_FULLSCREEN;

	if(SDL_SetVideoMode(m_iWinX, m_iWinY, m_iBpp, Flags) == NULL)
	{
		printf("\n SDL_SetVideoMode(): %s \n", SDL_GetError());
		return 0;
	}

	//Couleur d arrière plan
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);

	SDL_ShowCursor ( false );

	// Repetition des touches
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,SDL_DEFAULT_REPEAT_INTERVAL+50);

	Resize (m_iWinX, m_iWinY);

	return true;
}

void K2D_Window :: Resize (int w, int h)
{
	m_iWinX = w;
	m_iWinY = h;

	glViewport(0, 0, m_iWinX, m_iWinY);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, m_iWinX, 0, m_iWinY, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*
	Swap le back buffer avec le front buffer
*/
void K2D_Window :: Flip ( )
{
	//double buffering -> echange le back buffer
	SDL_GL_SwapBuffers();
	glClear(GL_COLOR_BUFFER_BIT);
}

