
#include "K2D_Engine.h"


/*
	L abstraction en elle meme, la ou c est sympa
*/
K2D_Engine :: K2D_Engine ()
{
	bDone = false;
	SetApplicationTitle ( "K2D Demo" );
	m_pLog = K2D_Log::GetInstance ();
	m_pLog->Open (K2D_LOG_FILE);
}

K2D_Engine :: ~K2D_Engine ()
{
}

/*
	Quitte l application
*/
void K2D_Engine :: Quit ()
{
	bDone = true;
}

/*
	Prend un screenshot au format tga
	et le stocke dans szFile
	Bout de code pris sur cone3d.gamedev.net
*/
int K2D_Engine :: TakeScreenshot (char* szFile)
{
//création d'une image : 
	ILuint id; 
	ilGenImages(1, &id); 
	ilBindImage(id); 
	printf ("Creation de la capture d'ecran vers %s", szFile);
	int xsize = m_Window.GetWidth(), 
		ysize  = m_Window.GetHeight();
	ilTexImage(xsize, ysize, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, NULL); 
	unsigned char* buffer = new unsigned char[xsize*ysize*4];
//copie du framebuffer d'OpenGL actuellement affiché vers l'image : 

	glReadPixels(0, 0, m_Window.GetWidth(), m_Window.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]); 
	ilSetData ( buffer );
//sauvegarde de l'image dans un fichier : 
	ilSaveImage(szFile);
	
//destruction de l'image : 
	delete[] buffer;
	ilDeleteImages(1, &id); 
	return 1;
};

/*
	Change le titre du programme
*/
void K2D_Engine :: SetApplicationTitle ( char* szName )
{
	strncpy ( m_szAppName, szName, 64 );
	SDL_WM_SetCaption ( szName, NULL );
}

/*
	Initialise le moteur
*/
void K2D_Engine :: Init ()
{
	m_Elapsed = m_Last = SDL_GetTicks ();
	m_MouseState[K2D_BUTTON_LEFT] = false;
	m_MouseState[K2D_BUTTON_MIDDLE] = false;
	m_MouseState[K2D_BUTTON_RIGHT] = false;


}

void K2D_Engine :: HandleMessage ()
{
	// Gestion des messages recus
	while( SDL_PollEvent( &m_Event ) )
	{
		switch( m_Event.type )
		{
			case SDL_QUIT:
				bDone = true;
			break;

			case SDL_MOUSEMOTION:
				//	Recupere la position de la souris
				m_MousePos.x = m_Event.motion.x;
				m_MousePos.y = m_Event.motion.y;

				break;
			// Quand on 'déclique'
			case SDL_MOUSEBUTTONUP:

				switch ( m_Event.button.button )
				{
				case SDL_BUTTON_LEFT:
					m_MouseState[K2D_BUTTON_LEFT] = false;
					break;

				case  SDL_BUTTON_MIDDLE:
					m_MouseState[K2D_BUTTON_MIDDLE] = false;
					break;

				case  SDL_BUTTON_RIGHT:
					m_MouseState[K2D_BUTTON_RIGHT] = false;
					break;

				default:
					break;
				}
				break;
			// Clics de la souris
			case SDL_MOUSEBUTTONDOWN:
				switch ( m_Event.button.button )
				{
					// Boutons
					case  SDL_BUTTON_LEFT:
						m_MouseState[K2D_BUTTON_LEFT] = true;
						OnPress ( m_Event.button.button );			// Pour le moteur
						break;

					case  SDL_BUTTON_MIDDLE:
						m_MouseState[K2D_BUTTON_MIDDLE] = true;
						OnPress ( m_Event.button.button );
						break;

					case  SDL_BUTTON_RIGHT:
						m_MouseState[K2D_BUTTON_RIGHT] = true;
						OnPress ( m_Event.button.button );
						break;

					default:
						break;
				}
				break;
			case SDL_KEYDOWN:
				//	 event.key.keysym.sym  = la touche pressee;
				if (m_Event.key.keysym.sym == SDLK_F1)
				{
					m_Console.Toggle();	
					break;
				}
				OnPress (m_Event.key.keysym.sym);
				m_pKeyBoard[m_Event.key.keysym.sym] = 1;
					
				if ( m_Console.isEnabled() == true )
				{
					// Unicode pour pas avoir le clavier en qwerty
					m_Console.AddChar (m_Event.key.keysym.unicode);
				}

				break;
			case SDL_KEYUP:
				m_pKeyBoard[m_Event.key.keysym.sym] = 0;
				break;

			default:
			break;
		}

	}
}

/*
	Met a jour le timer
*/
void K2D_Engine :: UpdateTimer ()
{
	m_Last = m_Elapsed;
	m_Elapsed = SDL_GetTicks ();
	
	m_Frame++;
	m_Delta = (m_Elapsed - m_Last);
	//printf ("%f\n", m_Delta);

	if (m_Elapsed - m_LastStart > 1000 )
	{
		m_LastStart = m_Elapsed;
		m_Fps = m_Frame;
		m_Frame = 0;
	}
}

void K2D_Engine :: Run ( )
{	
	//srand (time(NULL));
	// Initialise le programme
	K2D_SoundSystem::Init ();
	Init ();
	m_Console.SetSize (m_Window.GetWindowSize());
	m_Console.Init();
	m_pKeyBoard = SDL_GetKeyState (0);

	while ( !bDone )
	{
		HandleMessage ();		// Messages recus
		UpdateTimer();			// Timer

		Draw ( );					// Affiche tout ce qui est necessaire
		if (m_Console.isEnabled ())	// Et aussi la console
			m_Console.Draw ();

		// Met a jour le timer
		Update ( m_Delta );			// Met a jour les variables
		m_Window.Flip ( );		// Echange le BackBuffer
	}

	OnExit ();
}

void K2D_Engine :: OnExit ()
{
	K2D_SoundSystem::Close ();
}