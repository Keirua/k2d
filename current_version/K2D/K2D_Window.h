#ifndef _K2D_WINDOWS_H_
#define _K2D_WINDOWS_H_

#pragma once

#include <SDL/SDL.h>
#include <stdlib.h>
#include <math.h>

/*
	Les librairies necessaires
*/
#ifdef _MSC_VER
	#pragma comment(lib, "opengl32.lib")
	#pragma comment(lib, "glu32.lib")
	#pragma comment(lib, "glaux.lib")
	#pragma comment(lib, "sdl.lib")
	#pragma comment(lib, "sdlmain.lib")
	#pragma comment	(lib, "fmodvc.lib")
#endif

#include "K2D_Vector2.h"

/*
	Classe simple de timer;
*/
class K2D_Timer 
{
public:
	K2D_Timer()
	{
		m_Elapsed = m_Last = SDL_GetTicks ();
	}
	// actualise le timer
	void Update ()
	{	
		m_Last = m_Elapsed;
		m_Elapsed = SDL_GetTicks ();
		m_Delta = ((float)(m_Elapsed - m_Last))/1000;

		m_Frame++;

		if (m_Elapsed - m_LastStart > 1000 )
		{
			m_LastStart = m_Elapsed;
			m_Fps = m_Frame;
			m_Frame = 0;
		}
	}
	inline float GetTime (){	return (float)m_Elapsed;	}
	inline float GetDelta(){	return (float)m_Delta;		}
	inline unsigned long GetFps  (){	return m_Fps;		}

private:
	int		m_Elapsed,	// temps actuel
			m_Last;		// derniere sauvegarde du temps
	float			m_Delta;	// duree entre 2 frames
	unsigned long	m_LastStart;
	unsigned long	m_Fps, m_Frame;

};

enum K2D_MOUSE_BUTTONS
{
	K2D_BUTTON_LEFT = 0,
	K2D_BUTTON_RIGHT,
	K2D_BUTTON_MIDDLE
};

/*
	La fenetre;
	Sert a dessiner a l ecran
*/
class K2D_Window
{
public:
	bool Init (int w = 640, int h = 480, int bpp = 32, bool fullscreen = false);
	void Flip ();
	void Resize (int w, int h);

	inline int GetWidth()	{ return m_iWinX; };
	inline int GetHeight()	{ return m_iWinY; };
	inline int GetBpp()		{ return m_iBpp;  };

	K2D_Vector2 GetWindowSize ()
	{
		return K2D_Vector2 ((float)m_iWinX, (float)m_iWinY);
	}

private:

	int m_iWinX,
		m_iWinY, 
		m_iBpp;
};


#endif //  _K2D_WINDOWS_H_

