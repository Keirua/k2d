#ifndef _CGAME_H_
#define _CGAME_H_

#include "K2D/K2D_Engine.h"


/*
	Le jeu en lui meme
*/
class CGame: public K2D_Engine
{
public:
	CGame(): score (10) {};
	void Init ();
	void Update (float dt);
	void Draw ();
	void OnExit ();
	void OnPress (int key);
private:

	// todo: commented out until it builds
	// K2D_Sound m_BgMusic;
	K2D_AnimatedSprite* m_Spr;
	K2D_Effect* m_pEffect;
	K2D_HighScoreTable score;
};

#endif