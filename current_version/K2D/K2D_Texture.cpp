//*****************************************************************************//
//										 
//		- "Talk to me like I'm a 3 year old!" Programming Lessons -		 
//                                                                       
//		$Author:				Frank Puig	fpuig2003@yahoo.com
//											 
//		$Program:				Quake BSP 5
//														
//		$Description:			Collision between a ray and a BSP		 
//														
//		$Date:					18/5/03								
//											
//		$Original Code:			DigiBen		DigiBen@GameTutorials.com			 
//
//****************************************************************************//

#include "K2D_Texture.h"
#include "K2D_Log.h"

bool K2D_Texture :: Load (char* strFileName, K2D_Filtering iType)
{
	m_szFile = new char [strlen (strFileName)+1];
	strcpy (m_szFile, strFileName);

 	ILuint texture;
	ilGenImages(1, &texture);
	ilBindImage(texture);

	if(ilLoadImage(strFileName)==false)
	{
		K2D_Log::GetInstance ()->Log (K2D_ERROR, "Unable to load %s", strFileName);
		return false;
	}

    m_Width=ilGetInteger(IL_IMAGE_WIDTH);
	m_Height=ilGetInteger(IL_IMAGE_HEIGHT);

  	switch(iType)
	{
		case K2D_NO_FILTER:	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
							glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST); 
						break;


		case K2D_LINEAR:	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
							glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);							
						break;

		case K2D_BILINEAR:	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
							glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
						break;

		case K2D_TRILINEAR:	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
							glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
						break;
	}	

	glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE) ;

	id = ilutGLBindMipmaps();	
//	id = ilutGLBuildMipmaps


	ilDeleteImages(1, &texture); 

	return true;
}


