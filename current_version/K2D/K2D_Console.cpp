#include "K2d_Console.h"
#include <SDL/sdl.h>


bool K2D_Console :: isEnabled ()
{
	return m_bEnabled;
}

void K2D_Console :: Enable (int bEnable)
{
	m_bEnabled = (bEnable == 1 ? true : false);
	// Pour les touches pressees
	SDL_EnableUNICODE( m_bEnabled ? 1 : 0 );

}

void K2D_Console :: Toggle ()
{
	this->Enable ( 1 - this->isEnabled ());
}

void K2D_Console:: Init()
{
	// 2 * pour eviter un probleme ... etrange
	m_History.push_back (CON_MSG);
	
	m_bEnabled = false;

	m_BufferIndex = 1;
	strcpy (m_Buffer, ">");
	m_HistoryIndex = 0;
	m_History.reserve ( K2D_CONSOLE_NEEDED_MEMORY );

	// A CHANGER 
	m_BackGround.Load ( "data\\console_bg.png" );
	m_BackGround.SetSize (K2D_Vector2(m_WindowSize.x, m_WindowSize.y/2+20));
}

void K2D_Console :: Draw ()
{
	glColor3f (1,1,1);
	glEnable (GL_TEXTURE_2D);

	m_BackGround.Draw (0, m_WindowSize.y, m_WindowSize.x, -m_WindowSize.y/2);

	// Affiche la commande tapee
	glColor3f (0,0,0);
	m_Font.DrawText(10,(m_WindowSize.y*.5 -15), 2, m_Buffer );
	
	int y;

	for (int i = 0;i < m_History.size(); i++)
	{
		y = (m_WindowSize.y*.5)-i*15 -2*15;
		if (y < 0)
			break;
		m_Font.DrawText(10, y, 2, (char*)m_History[i].c_str());
	}
	glColor3f (1,1,1);
	glEnable (GL_TEXTURE_2D);
}

void K2D_Console :: Write (const char *format, ...)
{
	static char buffer[256];
	va_list args;

	va_start(args, format);
		vsprintf(buffer, format, args);
	va_end(args);


	// Insere la commande au debut
	m_History.insert (m_History.begin(), buffer);
	
	if (m_History.size () == m_History.capacity ())
	{
		m_History.reserve (2*m_History.size ());
		printf ("Memory allocation needed");
	}
}

/*
	FIXME
*/
void K2D_Console::AddChar (char c)
{
	// Entree
	if (c == 13)
	{
		Write (&m_Buffer[1]);
		//Execute la fonction
		std::string func_name, curr_argv;
		std::vector<std::string> arg_list;
		int argc = 0;

		char* curr = &m_Buffer[1];

		// recupere le nom de la fonction
		while (*curr && *curr != '(')
		{
			func_name += *curr;
			curr++;
		}

		// saute la (
		if (*curr == '(')
			curr++;
		// liste les parametres
		while (*curr)
		{
			if (*curr == ',')
			{
				arg_list.push_back (curr_argv);
				curr_argv = "";
				argc++;
				curr++;
				continue;
			}
			else if (*curr == ')')
			{
				arg_list.push_back (curr_argv);
				if (curr_argv != "")
					argc++;
				curr_argv = "";
				break;
			}
			else
				curr_argv += *curr;
			curr++;
		}
		Execute (func_name, argc, arg_list);

		for (int i = 0; i < K2D_CONSOLE_BUFFER_SIZE; i++)
			m_Buffer[i] = '\0';

		m_Buffer[0] = '>';
		m_BufferIndex = 1;

	}
	// backspace
	else if (c == SDLK_BACKSPACE && m_BufferIndex > 1)
	{
		m_Buffer[m_BufferIndex]	= '\0';
		m_BufferIndex--;
		m_Buffer[m_BufferIndex]	= ' ';
	}
	else if ( c == SDLK_TAB )
	{
		int matched_total = 0;
		for (int i = 0; i < m_FuncList.size(); i++)
		{
			matched_total = 0;
			int len = m_BufferIndex -1;
			int j;
			for (j = 0; j < len; j++)
			{
				if (m_FuncList[i].Name[j] == m_Buffer[j+1])
					matched_total++;
				else
					break;
			}
			if (matched_total == len)	
			{
				for (j = 0; j < m_FuncList[i].Name.size(); j++)
				{
					m_Buffer[j+1] = m_FuncList[i].Name[j];
				}
				m_BufferIndex = m_FuncList[i].Name.size()+1;
			}
		}

	}
	else if (isChar(c))
	{
		m_Buffer[m_BufferIndex] = c;
		m_BufferIndex ++;
	}
}

/*
	Teste si la lettre passe en parametres est affichage dans la console
*/
bool K2D_Console :: isChar (char c)
{
	return ( c < 0x80 && c > 0);
}

/* Enregistre une fonction
TODO :: organiser par ordre alphabetique
*/
void K2D_Console :: Register (std::string name, void (*callback) (int argc, std::vector<std::string> argv))
{
	m_FuncList.push_back (K2D_Function (name, callback));
}
/* Execute une fonction
TODO :: optimiser (dichotomie)
*/
void K2D_Console :: Execute (std::string name, int argc, std::vector<std::string> argv)
{
	std::vector<K2D_Function>::iterator it;
	for (it = m_FuncList.begin(); it != m_FuncList.end(); it++)
	{
		if ((*it).Name == name)
		{
			(*it).callback (argc, argv);
		}
	}
}