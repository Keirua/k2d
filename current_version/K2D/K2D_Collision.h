#ifndef _K2D_COLLISION_H_
#define _K2D_COLLISION_H_

#include "K2D_Vector2.h"


#include <cmath>
#include "K2D_Vector2.h"

struct K2D_BBox
{
	K2D_Vector2	m_Pos,	// position du coin en haut à gauche
				m_Size;	// taille de la boite
	
};

struct K2D_BSphere
{
	K2D_Vector2	m_Pos;	// position du centre
	float m_Radius;
};

class K2D_Collision
{
public:
	// Specifique aux structures
	static bool Intersect ( K2D_BSphere bs1, K2D_Vector2 pt ){
		return isInSphere (bs1.m_Pos, bs1.m_Radius , pt);
	}
	static bool Intersect ( K2D_BSphere bs1, K2D_BSphere bs2 ){
		return isSphereCollision (bs1.m_Pos, bs1.m_Radius, 
								  bs2.m_Pos, bs2.m_Radius );
	}
	static bool Intersect ( K2D_BBox b1, K2D_Vector2 pt ){
		return isInBox (b1.m_Pos, b1.m_Size, pt);
	}
	static bool Intersect ( K2D_BBox b1, K2D_BBox b2 ){
		return isBBoxCollision (b1.m_Pos, b1.m_Size, 
								b2.m_Pos, b2.m_Size);
	}

public:
	// Methodes generiques
	static bool isInSphere ( K2D_Vector2 pos, float radius, K2D_Vector2 pt );
	static bool isSphereCollision (	K2D_Vector2 pos1, float radius1,
									K2D_Vector2 pos2, float radius2 );
	static bool isInBox ( K2D_Vector2 pos, K2D_Vector2 size, K2D_Vector2 pt );
	static bool isBBoxCollision ( K2D_Vector2 pos1, K2D_Vector2 size1,
								  K2D_Vector2 pos2, K2D_Vector2 size2 );
};


#endif