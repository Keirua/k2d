#ifndef _IMAGE_H
#define _IMAGE_H

#include <vector>
#include <string.h>



#ifdef _MSC_VER
	#include <windows.h>					// Include the much need windows.h
#endif

#include <GL/gl.h>						// Header File For The OpenGL32 Library
#include <GL/glu.h>						// Header File For The GLu32 Library
// #include <GL/glaux.h>					// Header File For The GLaux Library

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

#include "K2D_Vector2.h"
#include "K2D_Effect.h"

enum K2D_Filtering
{
	K2D_NO_FILTER=0,
	K2D_LINEAR,
	K2D_BILINEAR,
	K2D_TRILINEAR,
	K2D_ANISOTROPIC_TRILINEAR_FILTERING
};


/*
	Classe de texture
	Utilise la librairie
*/
class K2D_Texture
{
public:
	bool Load (char* strFileName, K2D_Filtering iType=K2D_BILINEAR);
	
	~K2D_Texture()	
	{	
		glDeleteTextures(1, &id);
		delete[] m_szFile;
	}

	inline void Bind (){	glBindTexture(GL_TEXTURE_2D, id);}

	// Get
	int		GetWidth ()		{ return m_Width;	}
	int		GetHeight ()		{ return m_Height;	}
	char*	GetFileName ()	{ return m_szFile;	}

	unsigned int id;
	char *m_szFile;
private:
	unsigned int m_Width, m_Height;
};

#endif

