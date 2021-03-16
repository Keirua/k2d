#include "CBubble.h"
#include "CGame.h"
#include <cstdlib>

extern CGame* g_pGame;

/*
	La balle
*/
void CBalle::Init ()
{
	m_Spr.Load ("data\\ball.tga");
	m_Spr.Init (1,4, 250);
	size = 20;
	m_Pos.x  = (WIDTH >> 1) - (size >> 1);
	m_Pos.y  = (HEIGHT >> 2);

}

void CBalle::Update ( float dt )
{

	m_Spr.Update ( dt*100 );
	
	if (m_Pos.x < 0)
		m_Pos.x = 0;
	if (m_Pos.x+size > WIDTH)
		m_Pos.x = WIDTH-size;
	if (m_Pos.y < 0)
		m_Pos.y = 0;
	if (m_Pos.y+size > HEIGHT)
		m_Pos.y = HEIGHT-size;

}

// Affiche la balle
void CBalle::Draw ()
{
	//glColor3f (1,1,1);
	K2D_Vector2 vSize (size, size);
	m_Spr.SetSize ( K2D_Vector2 (size, size) );
	m_Spr.Draw ( m_Pos );
}

/*
	Le jeu :: fonctions annexes
*/

// Gestion du clavier pour la balle
void CBubbleGame::UpdateBall(float dt)
{
		// touches inversées
	if (m_CurrEffect & OBJ_INVERT)
	{
		if (g_pGame->GetKeyState (SDLK_UP))
			m_Ball.m_Pos.y -= BALL_SPEED * dt;
		if (g_pGame->GetKeyState (SDLK_DOWN))
			m_Ball.m_Pos.y += BALL_SPEED * dt;
		if (g_pGame->GetKeyState (SDLK_LEFT))
			m_Ball.m_Pos.x += BALL_SPEED * dt;
		if (g_pGame->GetKeyState (SDLK_RIGHT))
			m_Ball.m_Pos.x -= BALL_SPEED * dt;

	}
	else	// touches normales
	{
		if (g_pGame->GetKeyState (SDLK_UP))
			m_Ball.m_Pos.y += BALL_SPEED * dt;
		if (g_pGame->GetKeyState (SDLK_DOWN))
			m_Ball.m_Pos.y -= BALL_SPEED * dt;
		if (g_pGame->GetKeyState (SDLK_LEFT))
			m_Ball.m_Pos.x -= BALL_SPEED * dt;
		if (g_pGame->GetKeyState (SDLK_RIGHT))
			m_Ball.m_Pos.x += BALL_SPEED * dt;
	}

}

void CBubbleGame::Spawn( int id )
{
	int rnd = rand ()%100;
	if (0 <= rnd && rnd < 50)	// 50% de chances d avoir une bulle
	{
		m_Object[id].type = OBJ_BUBBLE;
		m_Object[id].info = K2D_Tool::Random ( 3, 20 );
	}	
	else if (50 <= rnd && rnd < 90)	// 40 % d avoir une bombe
	{
		m_Object[id].type = OBJ_BOMB;
		m_Object[id].info = 3+rand()%17+1;
	}
	else if (90 <= rnd && rnd < 100)	// 10% d avoir un bonus
	{
		m_Object[id].type = OBJ_BONUS;
		m_Object[id].info = (int)pow(2, ((int) (K2D_Tool::Random(1,5)) ));// bonus tiré au hasard
	}
	// en mode inversion, les objets apparaissent en bas
	if (m_CurrEffect & OBJ_INVERT)
		m_Object[id].m_Pos.y = 0;
	else
		m_Object[id].m_Pos.y = HEIGHT + (rand () % 30);

	m_Object[id].m_Pos.x = rand () % WIDTH;
	m_Object[id].m_Dir.x = 0;
	m_Object[id].m_Dir.y = -(3+rand () % 27+1);	// vitesse aleatoire
}

void CBubbleGame::UpdateObjects( float dt )
{
	K2D_Vector2 pl_pos(m_Ball.m_Pos.x+m_Ball.size /2, m_Ball.m_Pos.y+m_Ball.size /2 );

	for (int i = 0; i < m_Alive; i++)
	{
		// ajoute la vitesse. inverse le sens de deplacement si le mode est activé
		m_Object[i].m_Pos += (m_Object[i].m_Dir)* dt * (m_CurrEffect & OBJ_INVERT ? -1 : 1);

		if (Collide (pl_pos, m_Ball.size /2, i))	// si on rentre en collision avec un objet
		{
			// si on collisionne une bulle, on augmente la taille du joueur et augment le score
			if (m_Object[i].type == OBJ_BUBBLE )
			{
				m_Score += (int)m_Object[i].info;
				m_Ball.size += m_Object[i].info / 3;
			}
			// si c est un bonus
			else if (m_Object[i].type == OBJ_BONUS) 
			{
				m_Score += 50;
				if (m_CurrEffect == 0)				// on lance le compeur de durée de l effet
					m_EffectElapsed = 0;
				m_CurrEffect |= m_Object[i].info;	// on ajoute cet effet
			}
			// si c est une bombe est qu on est pas invincible, on meurt
			else if (m_Object[i].type == OBJ_BOMB )
			{
				// si on est invincible, on gagne du score
				if (m_CurrEffect & OBJ_GOD)
					m_Score += 50;
				else
				{
					// cree un fondu au noir sur tout l ecran, pendant 3 secondes
					m_pEffect = new K2D_FadeIn (K2D_Vector2 (0,0), K2D_Vector2(WIDTH, HEIGHT), 3000, K2D_Color (0,0,0));
					// flemme de coder l entree du pseudo 
					m_HighScore.Insert ("Player", m_Score);
					m_HighScore.SaveScore ("highscores.sav");
					Snd_GameOver.Play ();
				}
			}
			Spawn ( i );
			continue;
		}

		if (m_CurrEffect & OBJ_INVERT && m_Object[i].m_Pos.y > HEIGHT)
			Spawn ( i );
		else if (m_Object[i].m_Pos.y < 0)
			Spawn ( i );
	}
}

// Affiche un objet avec le sprite adapté
void CBubbleGame::DrawObjects ( )
{
	for (int i = 0; i < m_Alive; i++)
	{
		if (m_Object[i].type == OBJ_BUBBLE)
			m_Sprites[m_Object[i].type].SetSize (K2D_Vector2(m_Object[i].info,m_Object[i].info));
		if (m_Object[i].type == OBJ_BOMB)
		{
			m_BombAnim.Draw (m_Object[i].m_Pos);
			continue;
		}
		m_Sprites[m_Object[i].type].Draw (m_Object[i].m_Pos);
		// pour les bonus, on affiche une lettre correspondant a ce bonus
		if (m_Object[i].type == OBJ_BONUS)
		{
			char c;
			if (m_Object[i].info & OBJ_SPEED)
				c = 'S';
			if (m_Object[i].info & OBJ_SLOW)
				c = 'B';
			if (m_Object[i].info & OBJ_JUNKY)
				c = 'J';
			if (m_Object[i].info & OBJ_GOD)
				c = 'G';
			if (m_Object[i].info & OBJ_INVERT)
				c = 'I';
			m_Font.DrawText (m_Object[i].m_Pos.x, HEIGHT-m_Object[i].m_Pos.y-15, 2, "%c", c);
		}
	}
}

/*
	Test de collision sphere/sphere 
*/
bool CBubbleGame::Collide(K2D_Vector2 pl, float pl_radius, int id)
{
	// quelques ajustements
	float obj_radius = (m_Object[id].type==OBJ_BUBBLE ? m_Object[id].info/2 : 10);
	K2D_Vector2 obj_pos(m_Object[id].m_Pos.x+obj_radius, m_Object[id].m_Pos.y+obj_radius);
	
	return K2D_Collision::isSphereCollision (pl, pl_radius, obj_pos, obj_radius );
}

void CBubbleGame::DrawBackGround ()
{
	K2D_State::Disable ( K2D_TEXTURE );
	// si l effet unky est activé, on met un fond de couleur ... spéciale
	if ( m_CurrEffect & OBJ_JUNKY)
		glColor3d (m_Bg.r, m_Bg.g, m_Bg.b);
	else
		glColor3f (0,.5, 1);	// sinon fond bleu

	K2D_Sprite::Blit (0,0,WIDTH, HEIGHT);
}


void CBubbleGame::DrawBonus ()
{
	if (m_CurrEffect != 0)
	{
		std::string str = "Bonus : ";
		if (m_CurrEffect & OBJ_SPEED)
			str += "Speed ";
		if (m_CurrEffect & OBJ_SLOW)
			str += "Bullet time ";
		if (m_CurrEffect & OBJ_JUNKY)
			str += "Junky ";
		if (m_CurrEffect & OBJ_GOD)
			str += "God ";
		if (m_CurrEffect & OBJ_INVERT)
			str += "Inversion ";
		str += "!";
		glColor3f (1,.5,.25);
		K2D_Sprite::Blit ( 10, HEIGHT-40-15, BONUS_DURATION/12-m_EffectElapsed/12,15);
		m_Font.DrawText (10, 25, 2, "%s", str.c_str());
	}
}

void CBubbleGame::HandleMenu ()
{
	DrawBackGround();	
	K2D_State::Enable (K2D_TEXTURE | K2D_COLOR_KEY);
	glColor3f (1,1,1);

	K2D_Vector2 tmp = g_pGame->GetMousePos();
	tmp.y = HEIGHT - 32 - tmp.y;
	K2D_Vector2 MouseOGLPos(tmp.x, tmp.y+32);
	int i;
	for ( i = 0; i < 3; i++)
	{
		 m_MenuEntry[i].Draw ();
		 // si on a cliqué sur ce bouton
		 if (K2D_Collision::isInBox (m_MenuEntry[i].GetPosition (), m_MenuEntry[i].GetSize (), MouseOGLPos)
			 && g_pGame->GetMouseState(K2D_BUTTON_LEFT))
		 {
			state = i+1;
		 }
	}
	m_MouseSpr.Draw (tmp);

	K2D_State::Disable (K2D_TEXTURE | K2D_COLOR_KEY);
}

void CBubbleGame::HandleHighScore ()
{
	DrawBackGround();	
	K2D_State::Enable (K2D_TEXTURE | K2D_COLOR_KEY);
	glColor3f (1,1,1);

	K2D_Vector2 tmp = g_pGame->GetMousePos();
	tmp.y = HEIGHT - 32 - tmp.y;
	K2D_Vector2 MouseOGLPos(tmp.x, tmp.y+32);
	int i;

	K2D_HighScoreTable::K2D_ScoreEntry entry;
	glColor3f (1,1,1);
	for ( i = 0; i < m_HighScore.Size(); i++)
	{
		entry = m_HighScore.GetScore (i);
		m_Font.DrawText (50, 100+(20*i),2, "%s %6d", entry.Name, entry.m_Score );
	}

	m_MouseSpr.Draw (tmp);

	K2D_State::Disable (K2D_TEXTURE | K2D_COLOR_KEY);
}


/*
	Le jeu :: code principal du jeu
*/
void CBubbleGame::Init ()
{
	int i=0;

	srand (time(NULL));
	m_Font.Load ("data\\font.tga");
	m_Ball.Init ();
	m_Sprites[OBJ_BUBBLE].Load ("data\\bubble.tga");
	m_Sprites[OBJ_BONUS].Load ("data\\bubble.tga");
	m_Sprites[OBJ_BONUS].SetSize (K2D_Vector2(20,20));
	m_BombAnim.Load ("data\\bomb.tga");
	m_BombAnim.Init(1,4, 250);
	m_BombAnim.SetSize (K2D_Vector2(20,20));

	m_MenuEntry	[0].Load ("data\\play.tga");
	m_MenuEntry	[1].Load ("data\\highscores.tga");
	m_MenuEntry	[2].Load ("data\\exit.tga");
	for ( i = 0; i < 3; i++)
		 m_MenuEntry[i].SetPos(K2D_Vector2(50, 300-80*i));

	m_Alive = 10;
	for ( i = 0; i < m_Alive; i++)
		Spawn ( i );
	m_Score = 0;
	m_EffectElapsed = 0;
	m_CurrEffect = 0;
	ColorElapsed = 0;

	m_pEffect = NULL;

	Snd_Intro.Load ("data\\start.wav");
	Snd_Intro.Play ();
	Snd_GameOver.Load ("data\\death.wav");
	m_MouseSpr.Load ("data\\pointer.tga");
	
	if (!m_HighScore.LoadScore("highscores.sav"))
		for (i = 0; i <= 10; i++)
			m_HighScore.Insert ("Keirua", 100 * i);
}

void CBubbleGame::Update(float dt)
{

	if (state != Game)
		return;
	if (m_pEffect)
	{
		// si on a un effet = on est mort -> on affiche rien d autre
		m_pEffect->Update( dt );
		if (g_pGame->GetKeyState (SDLK_SPACE))
		{
			Snd_GameOver.Stop ();
			Init();
		}

		return;
	}

	if (m_CurrEffect != 0)
	{
		m_EffectElapsed += dt;
		ColorElapsed += dt;
		if (ColorElapsed > 100)
		{
			while (ColorElapsed > 100)
				ColorElapsed -= 100;
			m_Bg.r = (float)rand() / RAND_MAX;
			m_Bg.g = (float)rand() / RAND_MAX;
			m_Bg.b = (float)rand() / RAND_MAX;
		}
	}

	// Une fois qu on a depassé le temps d un effet, cet effet s arrete
	if ( m_EffectElapsed > BONUS_DURATION)
	{
		m_EffectElapsed = 0;
		m_CurrEffect = 0;
	}

	m_BombAnim.Update (dt);
	int factor = 100;
	if (m_CurrEffect & OBJ_SPEED)	// si le mode accéléré est activé -> on va + vite
		factor /= 4;
	if (m_CurrEffect & OBJ_SLOW)	// si le mode ralentit est activé -> on va moins vite
		factor *= 4;
	m_Ball.Update ( dt/factor );
	UpdateBall ( dt/100 );	// la balle va toujours a la meme vitesse
	UpdateObjects ( dt/factor );
}

void CBubbleGame::Draw ( )
{
	if (state == Exit_Game)
		g_pGame->Quit ();
	if (state == Menu)
		HandleMenu ();
	if (state == HighScores)
		HandleHighScore();
	else if (state == Game)
	{
		DrawBackGround ();
		glColor3f (1,1,1);
		// Active les textures et le color keying
		K2D_State::Enable (K2D_TEXTURE | K2D_COLOR_KEY);
		// affiche les objets
		DrawObjects ();
		m_Ball.Draw ();
		m_Font.DrawText (10,10,2, "Score : %d", m_Score);

		// désactive textures et color keying
		K2D_State::Disable(K2D_BLENDING);
		K2D_State::Disable (K2D_TEXTURE | K2D_COLOR_KEY);

		// si un effet est active, on affiche une barre de progression
		if (m_CurrEffect != 0)
			DrawBonus ();
		if (m_pEffect)
		{
			std::string str = "Appuyez sur espace pour recommencer";
			m_pEffect->Draw ();
			glColor3f (1.0f,1.0f,1.0f);
			m_Font.DrawText ((WIDTH/2-15*str.length()/2), (HEIGHT/2-7), 2, "%s", str.c_str());
			m_Font.DrawText (10,10, 2, "Score = %d", m_Score);
		}
	}
}

