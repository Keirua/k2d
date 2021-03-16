#ifndef _K2D_PARTICLE_MANAGER_H_
#define _K2D_PARTICLE_MANAGER_H_

#include <vector>
#include "K2D_Vector2.h"
#include "Singleton.h" 

#include "K2D_State.h"
#include "K2D_Sprite.h"

/* 
	Structure representant 1 particule (ultra simple)
*/
struct K2D_Particle
{
	K2D_Vector2 m_Pos, m_Dir;	// Position / direction
	int m_Life;				// etat de santé de la particule ( 0 = mort)
	int m_Info;				// stocke diverses infos, un peu le bazar mais tres pratique
};

/*
	Classe abstraite representant un systeme de particules
*/
class K2D_ParticleSystem
{
public:
	virtual void Init () = 0;
	virtual void Update ( float dt ) = 0;
	virtual void Draw () = 0;

protected:
	std::vector < K2D_Particle > m_ParticleList;
};

/*
	On cree une classe dérivée, qui sera un systeme de nuages (sans blague ?)
*/
class K2D_CloudSystem: public K2D_ParticleSystem
{
public:
	// Le constructeur définit les parametres
	K2D_CloudSystem (int nb_clouds, int ratio, int ScreenX, int ScreenY);

	// Les fonctions heritees travaillent avec ces parametres.
	void Init ();
	void Update ( float dt );
	void Draw ();
private:
	K2D_Sprite m_Sprite [2];	// 2 sprite, 1 pour les gros nuages, un pr les petits
	int 	m_Width, m_Height;
	int nb_cloud, m_ratio;
};

/*
	Gestionnaire de particules
	S occupe de la mise a jour des particules
*/
class K2D_ParticleManager: public singleton <K2D_ParticleManager>
{
	friend class singleton <K2D_ParticleManager>;
public:
	void AddSystem ( K2D_ParticleSystem* pSystem );
	void Update ( float dt );
	void Draw ();

private:
	std::vector < K2D_ParticleSystem* >  m_SystemList;
};
#endif