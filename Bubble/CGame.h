#ifndef _CGAME_H_
#define _CGAME_H_

#include "K2D\K2D_Engine.h"
#include "CBubble.h"

/*
	Le jeu en lui meme
*/
class CGame: public K2D_Engine
{
public:
	CGame(){};
	void Init ();
	void Update (float dt);
	void Draw ();
	void OnExit ();
	void OnPress (int key);
private:
	CBubbleGame m_Bubble;
};

#endif