#ifndef _K2D_SPRITE_H_
#define _K2D_SPRITE_H_

#include "K2D_Vector2.h"
#include "K2D_Texture.h"


class K2D_BaseSprite
{
public:
	void Load (char* szFileName, K2D_Filtering iType=K2D_BILINEAR)
	{
		m_pTexture.Load ( szFileName, iType );
		SetSize (K2D_Vector2(m_pTexture.GetWidth( ), m_pTexture.GetHeight( )));
	}
	void SetTexture (K2D_Texture pTex)
	{
		m_pTexture = pTex;
	}
	void SetSize (K2D_Vector2 size)	{	m_Size = size;		}
	void SetPos	 (K2D_Vector2 pos)	{	m_Pos = pos;		}
	void SetDepth ( int depth)		{	m_Depth = depth;	}

	// Get
	K2D_Vector2 GetPosition ()	{	return m_Pos;	};
	K2D_Vector2 GetSize ()		{	return m_Size;	};
	float	GetWidth ()			{	return m_Size.x;};
	float	GetHeight ()		{	return m_Size.y;};
	K2D_Texture GetTexture ()	{	return m_pTexture;};
	inline int GetDepth ()		{	return m_Depth;	}

	virtual void Draw () {};
	virtual void Draw (K2D_Vector2 pos) {}
	
	
protected:
	K2D_Texture m_pTexture;
	K2D_Vector2 m_Pos,
				m_Size;
	int m_Depth;

};

class K2D_Sprite:public K2D_BaseSprite
{
public:
	K2D_Sprite ()
	{
	}

	void Draw ();
	// ptit raccourci bien pratique
	void Draw (K2D_Vector2 pos)
	{
		SetPos (pos);
		Draw ();
	}
	void Draw (int x, int y, int w, int h)
	{
		m_Pos.x  = x;	m_Pos.y  = y;
		m_Size.x = w;	m_Size.y = h;
		Draw ();

	}
	static void Blit(int x, int y, int w, int h);
	// Set

	float SquarePoints[4][2], SquareTexCoords[4][2];
};

// Comme les sprites, mais en animé
class K2D_AnimatedSprite: public K2D_BaseSprite
{
public:
	K2D_AnimatedSprite ()
	{
		m_nb_Anims = m_nb_Frames = 4;
		m_Delay = 250;	// millisecondes
		curr_delay = curr_anim = curr_frame = 0;
		m_bAnimate = true;
	}
	void Load (char* szFileName, K2D_Filtering iType=K2D_BILINEAR)
	{
		m_pTexture.Load ( szFileName, iType );
		m_Size.Set (m_pTexture.GetWidth( ), m_pTexture.GetHeight( ));
	}
	/* Parametre l animation : 
		nombre d animations, nombre d images par animations, delai entre chaque animations
	*/
	void Init (int nb_anims, int nb_frames, int delay)
	{
		m_nb_Anims	= nb_anims;
		m_nb_Frames = nb_frames;
		m_Delay = delay;
	}
	
	// definit l animation en cours
	void SetAnimation (int anim)	{	curr_anim	= anim;		}
	void SetFrame (int frame)		{	curr_frame	= frame;	}
	void SetSize (K2D_Vector2 size);

	// renvoie l index de l animation en cours
	int GetAnimation ()				{	return curr_anim;		}
	void Animate (bool bAnimate)	{	m_bAnimate = bAnimate;	}

	void Update (float dt);
	void Draw(K2D_Vector2 pos);

private:
	K2D_Texture m_pTexture;
	K2D_Vector2 m_Size;	// taille du sprite
	// "constantes"
	int m_nb_Anims,		// nb d anim
		m_nb_Frames,	// nb d images/anim
		m_Delay;		// duree entre chaque anim, en millisecondes
	
	// variable pour gerer l anim
	int curr_delay, 
		curr_anim, 
		curr_frame;
	bool m_bAnimate;	// doit on ou non animer l image ?
};

#endif
