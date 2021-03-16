#include "K2D_Collision.h"

// Collision rectangle/rectangle
bool K2D_Collision :: isBBoxCollision (K2D_Vector2 pos1, K2D_Vector2 size1, 
							 K2D_Vector2 pos2, K2D_Vector2 size2  )
{
	// adapté de http://www.gamedev.net/reference/articles/article735.asp
	static float left1, left2;
	static float right1, right2;
	static float top1, top2;
	static float bottom1, bottom2;

	left1 = pos1.x;
	left2 = pos2.x;
	right1 = left1 + size1.x;
	right2 = left2 + size2.x;
	top1 = pos1.y;
	top2 = pos2.y;
	bottom1 = top1 + size1.y;
	bottom2 = top2 + size2.y;

	if (bottom1 < top2) return(0);
	if (top1 > bottom2) return(0);

	if (right1 < left2) return(0);
	if (left1 > right2) return(0);

	return(1);

}

// Teste si un point pt est dans la boite
bool K2D_Collision :: isInBox (K2D_Vector2 pos, K2D_Vector2 size, K2D_Vector2 pt)
{
	return (pt.x > pos.x && pt.x < (pos.x+size.x)
		 && pt.y > pos.y && pt.y < (pos.y+size.y) );
}

// Collision sphere/sphere (abus de langage, c' est des cercles)
bool K2D_Collision :: isSphereCollision (K2D_Vector2 pos1, float radius1, 
							   K2D_Vector2 pos2, float radius2  )
{
	K2D_Vector2 relPos = pos1 - pos2;

	float rel_dist = relPos.x * relPos.x + relPos.y * relPos.y;
	float rad_dist = radius1 + radius2;

	return (rel_dist <= (rad_dist * rad_dist));
}



// Teste si pt est dans le cercle ce centre center et de rayon radius
bool K2D_Collision :: isInSphere (K2D_Vector2 center, float radius, K2D_Vector2 pt)
{
	// renvoie vrai si la distance carrée centre/point est inférieure au rayon au carré
	K2D_Vector2 rel (center - pt);
	return (rel.x*rel.x + rel.y*rel.y) < (radius*radius);
}