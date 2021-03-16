
#ifndef _K2D_VECTOR2_H_
#define _K2D_VECTOR2_H_

#include <cmath>
#define PI 3.141592654

struct K2D_Vector2
{
public:
	float x, y;
	// Constructuers
	K2D_Vector2(): x(0), y(0){	}
	K2D_Vector2(float x_, float y_): x(x_), y(y_){	}
	K2D_Vector2(const K2D_Vector2 &b_): x(b_.x), y(b_.y){	}

	void Set (float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	// Operateurs
	inline K2D_Vector2 operator=(const K2D_Vector2 &b_)
	{
		if(&b_ != this)
		{
			x = b_.x;
			y = b_.y;
		}
		return *this;
	}

	inline K2D_Vector2 operator+(const K2D_Vector2 &b_)
	{
		K2D_Vector2 c;
		c.x = x + b_.x;
		c.y = y + b_.y;

		return c;
	}

	inline K2D_Vector2 operator-(const K2D_Vector2 &b_)
	{
		K2D_Vector2 c;
		c.x = x - b_.x;
		c.y = y - b_.y;

		return c;
	}

	inline K2D_Vector2 operator*(const float &n_)
	{
		K2D_Vector2 c;
		c.x = x * n_;
		c.y = y * n_;

		return c;
	}

	inline K2D_Vector2 operator/(const float &n_)
	{
		K2D_Vector2 c;
		c.x = x / n_;
		c.y = y / n_;

		return c;
	}

	inline K2D_Vector2 operator+=(const K2D_Vector2 &b_)
	{
		x += b_.x;
		y += b_.y;

		return *this;
	}

	inline K2D_Vector2 operator-=(const K2D_Vector2 &b_)
	{
		x -= b_.x;
		y -= b_.y;

		return *this;
	}

	inline K2D_Vector2 operator*=(const float &n_)
	{
		x *= n_;
		y *= n_;

		return *this;
	}

	inline K2D_Vector2 operator/=(const float &n_)
	{
		x /= n_;
		y /= n_;

		return *this;
	}

	inline bool operator==(const K2D_Vector2 &b_)
	{
		if(&b_ != this)
		{
			return (b_.x == x) && (b_.y == y);
		}
	}

	inline bool operator!=(const K2D_Vector2 &b_)
	{
		if(&b_ != this)
		{
			return (b_.x != x) || (b_.y != y);
		}
	}

	// Methodes
	float Magnitude()
	{
		return sqrtf(x*x + y*y);
	}

	inline void Normalize()
	{
		float length = sqrtf(x*x + y*y);
		if(length != 0)
		{
			x /= length;
			y /= length;
		}
	}

	inline float dot(K2D_Vector2 b)
	{
		return x*b.x + y*b.y;
	}

	K2D_Vector2 GetClosestPointOnSegment(K2D_Vector2 S0, K2D_Vector2 S1)
	{   
		K2D_Vector2 E = S1-S0;      // edge direction    
									// E = S1 - S0    
		K2D_Vector2 D = (*this) - S0;     // relative position of point to the edge    
								// D = P - S0        

		float de = D.x*E.x + D.y*E.y;// project point on edge (dot product)    
		float e2 = E.x*E.x + E.y*E.y;// length of the edge, squared    

		if (de < 0.0f) // if projection is before the edge start point        
			return S0; // return edge start point      

		if (de > e2)   // if projection after edge end point        
			return S1; // return edge end point        

		float t;       // percentage on how far the point projects on the edge    
		t = de / e2;   // t = projection / edge length^2    

		K2D_Vector2 Q = S0 + E * t;             // K2D_Vector2 projection of point on edge    
		return Q;
	}
//	bool PointInCircle(Vector C, float r, Vector P){	Vector D; // relative position of point to circle centre	D.x = P.x - C.x; // D = P - C	D.y = P.y - C.y; //	float d2; // distance squared of the point to the circle centre	d2 = D.x*D.x + D.y*D.y; // d^2 = D dot D	float r2; // radius squared of the circle	r2 = r*r; // r^2 = r * r	if (d2 > r2) // distance squared greater than radius squared		return false; // point not inside the circle		return true; // yes, point is inside}
};

#endif