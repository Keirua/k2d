#include "CGame.h"

#define WIDTH 800
#define HEIGHT 600

extern CGame* g_pGame;

/*
	Quitte le programme via la console
*/
void Con_Quit (int argc, std::vector<std::string> argv)
{
	g_pGame->Quit ();
}

void Curr_Time(int argc, std::vector<std::string> argv)
{
	g_pGame->m_Console.Write ( K2D_Tool::Date ("h:i:s, D d M y").c_str() );
}


/*
	Initialisation du programme
*/
void CGame :: Init ()
{
	// Parametre differentes choses
	m_Window.Init ( WIDTH,HEIGHT,32, false );
	SetApplicationTitle ("   .:: Bubble Game ::.");
	ShowCursor ( true );
	
	m_Console.LoadFont ("data\\font.tga");
	m_Console.Register ("quit", &Con_Quit);
	m_Console.Register ("currenttime", &Curr_Time);

}

/*
	Code a remplir pour la mise a jour des variables
*/
void CGame :: Update (float dt)
{

}

/*
	Code a remplir pour l affichage (Opengl)
*/
void CGame :: Draw ()
{

	if (m_pKeyBoard[SDLK_F2])
		TakeScreenshot("screen.png");
}

/*
	Execute une action lorsqu une touche est presse
	Plusieurs methodes pour tester l etat des touches.
	La liste des touches est presente dans la doc SDL.
*/
void CGame :: OnPress (int key)
{
	if ( key == SDLK_ESCAPE)
			Quit ();
}

/*
	Desinitialisation : faire les delete de tout ce qui a ete alloue par exemple
*/
void CGame :: OnExit ()
{

}
