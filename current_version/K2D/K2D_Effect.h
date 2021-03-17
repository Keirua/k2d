#ifndef _K2D_EFFECT_H_
#define _K2D_EFFECT_H_

#include <SDL/sdl.h>

/*
	Simplifier l utilisation des couleurs
*/
class K2D_Color
{
public:
	K2D_Color ()
	{
		r = g = b = 0.0f;
	}
	K2D_Color (float _r, float _g, float _b):r (_r), b(_b), g(_g){}
	K2D_Color (K2D_Color& col)
	{
		r = col.r;
		g = col.g;
		b = col.b;
	}

	float r, g, b;
};

/*
	Effets speciaux a l ecran 
	(a consommer avec moderation)
*/
class K2D_Effect
{
public:
	K2D_Effect (){ m_State = Done; m_Elapsed = 0;};
	virtual ~K2D_Effect ()
	{	
		m_Duration = 1000; // ms
		m_Start = SDL_GetTicks()*.001;
		m_Elapsed = 0;
	};
	virtual void Init ()	
	{
		m_State = Playing;
		/*m_Start = SDL_GetTicks()*.001;*/
		m_Elapsed = 0;
	};
	virtual void Update (float dt)	
	{
		m_Elapsed = SDL_GetTicks()*.001 - m_Start;
	};
	virtual void Draw ()	{};

	void Start ()
	{
		m_State = Playing;
		m_Elapsed = 0;
		Init ();
	}

	bool isDone ()
	{
		return ( m_State == Done );
	}
	int GetPaused ()
	{
		return (m_State & Paused ? 1 : 0);
	}
	void SetPaused (bool bState)
	{
		m_State = (bState == true ? Paused : Playing);
	}
	enum
	{
		Done	= (1 << 1),
		Playing	= (1 << 2),
		Paused	= (1 << 3)
	};

protected:
	int m_Duration,	// Duree
		 m_Start,	// Moment ou l on a commence	
		 m_Elapsed;	// temps ecoule depuis;

	int m_State;	// Etat de l effet
};

/*
	Effet de fondu enchainé
*/
class K2D_FadeIn: public K2D_Effect
{
public:
	K2D_FadeIn (K2D_Vector2 from, K2D_Vector2 to, int duration, K2D_Color col)
	{
		m_Duration = duration;
		m_From = from;
		m_To = to;
		m_Color.r = col.r;
		m_Color.g = col.g;
		m_Color.b = col.b;
		Init ();

	}
	void Init ()
	{
		f_alpha = 0.0f;
		m_Elapsed = 0;
	}
	void Update (float dt)
	{
		Draw ();

		// Met a jour les valeurs
		ui_old_time = ui_curr_time ;
		ui_curr_time += dt;//SDL_GetTicks () ;
		
		if (m_State == Paused)
			return;

		f_alpha  += ((float) (ui_curr_time - ui_old_time) / m_Duration);
		if (f_alpha >= 1.0f)
			m_State = Done;
	}

private:
	void Draw ()
	{
		// Affiche
		glDisable (GL_TEXTURE_2D);
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		glColor4f (m_Color.r, m_Color.g, m_Color.b, f_alpha);
		glBegin (GL_QUADS);	   
			glVertex2f((float)m_From.x, (float)m_From.y ); 
			glVertex2f((float)m_From.x, (float)m_To.y ); 
			glVertex2f((float)m_To.x,	(float)m_To.y ); 
			glVertex2f((float)m_To.x,	(float)m_From.y );  	
		glEnd ();

		glDisable( GL_BLEND );
		glEnable (GL_TEXTURE_2D);
	}

	K2D_Color m_Color;
	float f_alpha;				// valeur alpha
	K2D_Vector2 m_From, m_To;	// coordonnées de l effets
	Uint32 ui_old_time, ui_curr_time, ui_time_ms;
};


/*
	Effet de fondu enchainé
*/
class K2D_FadeOut: public K2D_Effect
{
public:
	K2D_FadeOut (K2D_Vector2 from, K2D_Vector2 to, int duration, K2D_Color col)
	{
		m_Duration = duration;
		m_From = from;
		m_To = to;
		m_Color.r = col.r;
		m_Color.g = col.g;
		m_Color.b = col.b;
		Init ();

	}
	void Init ()
	{
		f_alpha = 1.0f;
		m_Elapsed = 0;
	}
	void Update (float dt)
	{
		Draw ();

		// Met a jour les valeurs
		ui_old_time = ui_curr_time ;
		ui_curr_time += dt;//SDL_GetTicks () ;
		
		if (m_State == Paused)
			return;

		f_alpha  -= ((float) (ui_curr_time - ui_old_time) / m_Duration);
		if (f_alpha <= 0.0f)
			m_State = Done;
	}

private:
	void Draw ()
	{
		// Affiche
		glDisable (GL_TEXTURE_2D);
		glEnable( GL_BLEND );
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

		glColor4f (m_Color.r, m_Color.g, m_Color.b, f_alpha);
		glBegin (GL_QUADS);	   
			glVertex2f((float)m_From.x, (float)m_From.y ); 
			glVertex2f((float)m_From.x, (float)m_To.y ); 
			glVertex2f((float)m_To.x,	(float)m_To.y ); 
			glVertex2f((float)m_To.x,	(float)m_From.y );  	
		glEnd ();

		glDisable( GL_BLEND );
		glEnable (GL_TEXTURE_2D);
	}

	K2D_Color m_Color;
	float f_alpha;				// valeur alpha
	K2D_Vector2 m_From, m_To;	// coordonnées de l effets
	Uint32 ui_old_time, ui_curr_time, ui_time_ms;
};

#endif