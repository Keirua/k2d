/*******************
	Fonction Main
*******************/

#include "CGame.h"

CGame* g_pGame = new CGame;

int main(int argc, char *argv[])
{
	g_pGame->Run ();	

	delete g_pGame;
	return 0;
}