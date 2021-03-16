#ifndef _K2D_CONSOLE_H_
#define _K2D_CONSOLE_H_

#include <vector>
#include <string>
#include "K2D_Vector2.h"
#include "K2D_Sprite.h"
#include "K2D_Font.h"
#include "singleton.h"

#define CON_MSG "K2D_Console v1.0"

// Espace reserve par la console.
#define K2D_CONSOLE_NEEDED_MEMORY	1024
// longueur max du buffer
#define K2D_CONSOLE_BUFFER_SIZE		256
// (Comment ca j'aime les #define longs ?)

class K2D_Console//: public singleton<K2D_Console>
{
	//friend class singleton<K2D_Console>;

public:
	K2D_Console (){}
	void Init ();
	void Draw ();							// Affiche
	bool isEnabled ();						// Affichee ?
	void Enable (int bEnable);				// Affiche si bEnable == true
	void Toggle ();							// Invers l etat d affichage

	void SetSize (K2D_Vector2 size)			// definit la taille de la console
	{
		m_WindowSize = size;
	}
	void LoadFont(char* szFont)
	{
		m_Font.Load (szFont);
	}
	void AddChar (char c);
	void Write (const char *format, ...);

	void Register (std::string name, void (*callback) (int argc, std::vector<std::string> argv));
	void Execute (std::string name, int argc, std::vector<std::string> argv);

private:
	bool isChar (char c);
	bool m_bEnabled;						// console affichee ou non ?
	K2D_Vector2 m_WindowSize;				// taille de la fenetre
	std::vector<std::string> m_History;		// historique de la console.
	K2D_Sprite m_BackGround;				// Image d arriere plan
	K2D_Font m_Font;						// Font servant a l affichage

	char m_Buffer[K2D_CONSOLE_BUFFER_SIZE];	// buffer servant a stocker les commandes rentrees
	int m_BufferIndex;						// index indiquant ou on se trouve dans le buffer
	int m_HistoryIndex;						// index indiquant la position dans l historique
	
	// structure interne servant a stocker une fonction (son nom et son callback)
	struct K2D_Function
	{
		K2D_Function (std::string n, void (*c) (int argc, std::vector<std::string> argv))
		{
			Name = n;
			callback = c;
		}

		std::string Name;
		void (*callback) (int argc, std::vector<std::string> argv);
	};

	std::vector <K2D_Function> m_FuncList;
};

#endif