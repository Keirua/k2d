#include "K2D_Sprite.h"

void K2D_Sprite::Draw ()
{
	m_pTexture.Bind ();

	glBegin (GL_QUADS);	   
		glTexCoord2f(0, 0);	glVertex2i( m_Pos.x,			m_Pos.y );
		glTexCoord2f(1, 0);	glVertex2i( m_Pos.x + m_Size.x,	m_Pos.y );
		glTexCoord2f(1, 1);	glVertex2i( m_Pos.x + m_Size.x,	m_Pos.y + m_Size.y );
		glTexCoord2f(0, 1);	glVertex2i( m_Pos.x,			m_Pos.y + m_Size.y );
	glEnd ();
}

void K2D_Sprite :: Blit(int x, int y, int w, int h)
{
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);	glVertex2i(x, y);
		glTexCoord2f(1, 0);	glVertex2i(x+w, y);
		glTexCoord2f(1, 1);	glVertex2i(x+w, y+h);
		glTexCoord2f(0, 1);	glVertex2i(x, y+h);
	glEnd();
}

void K2D_Animation :: Draw(K2D_Vector2 pos)
{
	K2D_Vector2 size (m_Size.x / m_nb_Frames, m_Size.y / m_nb_Anims);
	K2D_Vector2 over (size.x/m_Size.x, size.y/m_Size.y);

	m_pTexture.Bind ();

	glBegin(GL_QUADS);
		glTexCoord2f(curr_frame*over.x, curr_anim*over.y);	glVertex2i(pos.x, pos.y);
		glTexCoord2f(curr_frame*over.x+over.x, curr_anim*over.y);	glVertex2i(pos.x+size.x, pos.y);
		glTexCoord2f(curr_frame*over.x+over.x, curr_anim*over.y+over.y);	glVertex2i(pos.x+size.x, pos.y+size.y);
		glTexCoord2f(curr_frame*over.x, curr_anim*over.y+over.y);	glVertex2i(pos.x, pos.y+size.y);
	glEnd();
}


void K2D_Animation :: Update (float dt)
{	
	// si on ne doit pas animer, on sort
	if (m_bAnimate == false)
		return;
	// met a jour le compteur	
	curr_delay += dt;
	if (curr_delay > m_Delay)
	{
		curr_delay = curr_delay % m_Delay;
		curr_frame ++;
		if (curr_frame >= m_nb_Frames)
			curr_frame = 0;
	}
}

void K2D_Animation::SetSize (K2D_Vector2 size)
{	
	m_Size.Set (size.x * m_nb_Frames, size.y* m_nb_Anims);
}