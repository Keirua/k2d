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

	// todo: commented out until it builds
	// m_BgMusic.Load ("data/The World Is Mine.mp3");
	// m_BgMusic.Play ();
	m_pEffect = new K2D_FadeOut (K2D_Vector2(0,0), K2D_Vector2(WIDTH, HEIGHT), 3000, K2D_Color(0,128,255));
	m_Spr = new K2D_AnimatedSprite;
	m_Spr->Load ("data/player.png");
		
	m_Spr->Init (4,5,1000);
	int i;


}

/*
	Code a remplir pour la mise a jour des variables
*/
void CGame :: Update (float dt)
{
	m_Spr->Update (dt);
	K2D_Gfx::Disable (K2D_COLOR_KEY|K2D_TEXTURE);
	m_pEffect->Update (dt);
}

/*
	Code a remplir pour l affichage (Opengl)
*/
void CGame :: Draw ()
{
	glColor3f(1,1,1);
	m_Spr->Draw (K2D_Vector2(10,10));
	if (m_pKeyBoard[SDLK_F2])
		TakeScreenshot((char*)K2D_Tool::Format ("scr/Screen %f.tga", 3.14).c_str());
	m_pEffect->Draw ();
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
	K2D_Log::GetInstance ()->Close ();
	score.SaveScore ("save.txt");
	delete m_Spr;
}
