#include "K2D_Particle.h"

// Ajoute un systeme a la liste des systemes a mettre a jour
void K2D_ParticleManager :: AddSystem ( K2D_ParticleSystem* pSystem )
{
	if (!pSystem)
		return;

	pSystem->Init();
	m_SystemList.push_back ( pSystem );
}

// Met a jour tous les systems
void K2D_ParticleManager :: Update ( float dt )
{
	std::vector < K2D_ParticleSystem* >::iterator it;
	for ( it = m_SystemList.begin(); it != m_SystemList.end (); it++ )
	{
		(*it)->Update (dt);
	}
}

// Affiche tous les systemes
void K2D_ParticleManager :: Draw ()
{
	std::vector < K2D_ParticleSystem* >::iterator it;
	for ( it = m_SystemList.begin(); it != m_SystemList.end (); it++ )
	{
		(*it)->Draw ();
	}	
}

/*
	Systeme de nuages
	nb_cloud = nombre de nuages
	ratio = pourcentage de l ecran a occuper en hauter
	screenx/y = resolution de l ecran
*/
K2D_CloudSystem::K2D_CloudSystem(int nb_clouds, int ratio, int ScreenX, int ScreenY)
{
	m_Width = ScreenX;
	m_Height = ScreenY;
	nb_cloud = nb_clouds;
	m_ratio = ratio;
}

// On initialise le systeme
void K2D_CloudSystem :: Init ()
{
	m_Sprite [0].Load ("cloud1.tga");	
	m_Sprite [1].Load ("cloud2.tga");

	K2D_Particle tmp;
	for (int i = 0; i < nb_cloud; i++)
	{
		// 0 = petit nuage, 1 = gros nuage
		tmp.m_Info = (int)rand() % 2;

		tmp.m_Pos.x = rand () % m_Width;
		tmp.m_Pos.y = m_Height-m_Sprite [tmp.m_Info].GetHeight() - rand () % m_ratio ;

		float x = rand () % 5;
		if (x < .5)		
			x = .5;
		if ((int)rand () % 2 == 0) 
			x *= -1;
		
		tmp.m_Dir.Set( x, 0);
		
		m_ParticleList.push_back ( tmp );
	}


}

// On fait bouger les nuages
void K2D_CloudSystem :: Update (float dt)
{
	std::vector<K2D_Particle>::iterator it;
	for (it = m_ParticleList.begin(); it != m_ParticleList.end(); it++)
	{
		(*it).m_Pos += (*it).m_Dir * dt/100;

		if ((*it).m_Pos.x+m_Sprite[(*it).m_Info].GetWidth () < 0)
			(*it).m_Pos.x = m_Width + m_Sprite[(*it).m_Info].GetWidth ();
		if ((*it).m_Pos.x > m_Width)
			(*it).m_Pos.x = 0- m_Sprite[(*it).m_Info].GetWidth ();
	}
}

// Et les affiche
void K2D_CloudSystem :: Draw ()
{
	K2D_Gfx ::Enable (K2D_TEXTURE | K2D_COLOR_KEY);
	std::vector<K2D_Particle>::iterator it;
	for (it = m_ParticleList.begin(); it != m_ParticleList.end(); it++)
	{
		m_Sprite[(*it).m_Info].Draw ((*it).m_Pos);
	}
	K2D_Gfx ::Disable (K2D_TEXTURE | K2D_COLOR_KEY);
}
