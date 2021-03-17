
#ifndef _K2D_ENGINE_H_
#define _K2D_ENGINE_H_


#include <SDL/SDL.h>
#ifdef _MSC_VER
	#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <time.h>

/*	Typedef utiles */
typedef unsigned char uchar;
typedef unsigned int uint;

#include "K2D_Window.h"
#include "K2D_Sound.h"
#include "K2D_Vector2.h"
#include "K2D_State.h"
#include "K2D_Console.h"
#include "K2D_Particle.h"
#include "K2D_Collision.h"
#include "K2D_Tool.h"
#include "K2D_HighScore.h"
#include "K2D_Log.h"

/*
	Pour finir, la classe de moteur
	En fait, une abstraction permettant d eviter les phases d initialisation
	et de se concentrer le code
*/

class K2D_Engine
{
public:
	K2D_Engine ();
	virtual ~K2D_Engine ();

	virtual void Init () = 0;
	virtual void Update (float DeltaTime)=0;
	virtual void Draw () = 0;
	virtual void OnExit ();
	virtual void OnPress (int key) = 0;

	void Run ();
	void SetApplicationTitle (char* szName);
	void Quit ();
	virtual int TakeScreenshot (char* szName);

	float GetFps ()						{	return m_Fps;			}
	float GetDelta ()					{	return m_Delta;			}
	int GetKeyState (int key)			{	return m_pKeyBoard[key];}
	K2D_Vector2 GetMousePos ()			{	return m_MousePos;		}
	int GetMouseState ( int id )		{	return m_MouseState[id];}
	//K2D_Console GetConsole ()			{	return m_Console;		}
	K2D_Console			m_Console;
protected:
	// Variable heritables
	unsigned char*	m_pKeyBoard;	// Le clavier
	K2D_Vector2		m_MousePos;		// Position de la souris
	bool			m_MouseState[3];		// Etat des boutons		

	K2D_Window		m_Window;
	K2D_Log*		m_pLog;			// log global de K2D

	/*
		Les managers
	*/
	

private:
	// Géré en interne
	void HandleMessage ();
	void UpdateTimer ();
	
	SDL_Event		m_Event;
	bool bDone;
	char	m_szAppName[64];

	float	m_Elapsed,			// Temps ecoule depuis le debut du prog
			m_Last;				// Temps de la frame precedente
	float	m_LastStart;
	float	m_Fps, m_Frame;
	float	m_Delta;			// temps ecoule entre les 2 dernieres frames
};

#endif