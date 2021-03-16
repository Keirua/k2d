#ifndef _CBUBBLE_H_
#define _CBUBBLE_H_

#include "K2D\K2D_Engine.h"

// La fenetre
#define WIDTH 640
#define HEIGHT 480

#define BALL_SPEED 20	// vitesse de la balle

/*
	La balle (que le joueur gere)
	Pas tres propre mais bon... ( tout est public )
*/
class CBalle
{
public:
	void Init ();
	void Draw ();
	void Update ( float dt );

	int size;			// rayon de la balle;
	K2D_Vector2		m_Pos, 
					m_Speed;
	K2D_Animation	m_Spr;
};

// les differents types d objets
enum	 OBJ_TYPE
{
	OBJ_BUBBLE = 0,	// bulle (augmente la taille du joueur)
	OBJ_BOMB,
	OBJ_BONUS
};

#define BONUS_DURATION 5000	// les effets durent 5 secondes

// Differents types de bonus (possibilite de cumul ?)
enum OBJ_BONUS
{
	OBJ_SPEED = ( 1 << 1 ),	// accelere le jeu
	OBJ_SLOW  = ( 1 << 2 ),	// ralentit le jeu
	OBJ_JUNKY = ( 1 << 3 ),	// mode junky
	OBJ_GOD   = ( 1 << 4 ),	// invincible
	OBJ_INVERT= ( 1 << 5 )	// ionverse le sens de jeu
};

#define MAX_OBJECTS 256 // nombre d objets differents présents sur la carte au maximum

// Particules presents dans la carte: bonus, bulle, bombe...
struct CObject
{
	K2D_Vector2 m_Pos, 
				m_Dir;
	int type;	// type d objet
	int info;	// type de bonus, ou taille de la bulle
};

enum Playing_State
{
	Menu = 0,
	Game,
	HighScores,
	Exit_Game
};

/*
	gestion du jeu
*/
class CBubbleGame
{
public:
	void Init ( );
	void Update ( float dt );
	void Draw ( );
	void DrawObjects ( );
	int GetState()	{return state;};
	void SetState (int s){state = s;}
private:
	void Spawn ( int id );
	void UpdateObjects ( float dt );
	void UpdateBall (float dt);
	bool Collide (K2D_Vector2 player_pos, float pl_radius, int obj_id);
	void DrawBackGround ();
	void DrawBonus ();
	void HandleMenu ();
	void HandleHighScore();

	K2D_Font m_Font;
	CBalle m_Ball;
	CObject m_Object[MAX_OBJECTS];
	
	K2D_Sprite m_Sprites[8];
	K2D_Animation m_BombAnim;
	int m_Alive;			// nombre de particules actives;
	int m_Caught;			// nombre de balles attrapées
	int nb_BubbleToCatch;	// nombre de bulles a attraper pour passer au niveau suivant
	int m_CurrEffect;		// effet actuel
	int m_EffectElapsed;	// temps ecoulé depuis le debut de l effet
	int m_Score;			// score
	int ColorElapsed;
	K2D_Color m_Bg;			// couleur d arriere plan
	K2D_Effect* m_pEffect;

	K2D_Sound Snd_Intro, Snd_GameOver;

	int state;
	K2D_Sprite m_MouseSpr;
	K2D_Sprite m_MenuEntry[3];

	K2D_HighScoreTable m_HighScore;
};

#endif