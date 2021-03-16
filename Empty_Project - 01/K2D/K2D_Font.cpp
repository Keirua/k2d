#include "K2D_Font.h"

/*
	La font et toutes ses caracteristiques
*/

int K2D_Font::SetSize(float x, float y)       // Set the size of the font
{
	sizex=x;
	sizey=y;

	return 1;
}

bool K2D_Font::Load(char *strFile)          // Build Our Font Display List
{
	int loop1;
	float cx, cy;


	if(!font.Load(strFile))
	{
		return false;// erreur de chargement
	}

	base=glGenLists(256);                          // Creating 256 Display Lists

	glBindTexture(GL_TEXTURE_2D, font.id);

	for (loop1=0; loop1<256; loop1++)              // Loop Through All 256 Lists
	{
	cx=(float)(loop1%16)/16.0f;                  // X Position Of Current Character
	cy=(float)(loop1/16)/16.0f;                  // Y Position Of Current Character

	glNewList(base+loop1,GL_COMPILE);            // Start Building A List
	glBegin(GL_QUADS);                           // Use A Quad For Each Character
	  glTexCoord2f(cx,1.0f-cy-0.0625f);          // Texture Coord (Bottom Left)
	  glVertex2d(0,16);                          // Vertex Coord (Bottom Left)
	  glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);  // Texture Coord (Bottom Right)
	  glVertex2i(16,16);                         // Vertex Coord (Bottom Right)
	  glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);   // Texture Coord (Top Right)
	  glVertex2i(16,0);                          // Vertex Coord (Top Right)
	  glTexCoord2f(cx,1.0f-cy-0.001f);           // Texture Coord (Top Left)
	  glVertex2i(0,0);                           // Vertex Coord (Top Left)
	glEnd();                                     // Done Building Our Quad (Character)
	glTranslated(12,0,0);                        // Move To The Right Of The Character
	glEndList();                                 // Done Building The Display List
	}                                              // Loop Until All 256 Are Built
	return true;
}

int K2D_Font::KillFont(GLvoid)                     // Delete The Font From Memory
{
	glDeleteLists(base,256);                       // Delete All 256 Display Lists
	return 1;
}

int K2D_Font::DrawText(GLint x, GLint y, char type, char *fmt,...)// Where The Printing Happens
{
	static char text[1024];                            // Holds Our String
	int blendOn,scissorOn,textureOn;  // Holds the previous GL settings
	int depthOn,matrixMode,screenStats[4],blendSrc,blendDst;
	char typ=type;

	va_list ap;                                    // Pointer To List Of Arguments

	if (fmt == NULL)                               // If There's No Text
	return 0;                                      // Do Nothing

	va_start(ap, fmt);                             // Parses The String For Variables
#ifdef _WIN32
   vsprintf(text, fmt, ap);
#else
   // linux
   vsnprintf(text, 4096, fmt, ap);	
#endif
	va_end(ap);                                    // Results Are Stored In Text

	if (type>3)                                     // Did User Choose An Invalid Character Set?
	type=3;                                       // If So, Select Set 2 (Italic)

	textureOn = glIsEnabled(GL_TEXTURE_2D); // Were textures enabled?
	depthOn = glIsEnabled(GL_DEPTH_TEST);  // Was GL_DEPTH_TEST enabled?

	scissorOn = glIsEnabled(GL_SCISSOR_TEST);  // etc.
	glGetIntegerv(GL_MATRIX_MODE, &matrixMode);

	blendOn= glIsEnabled(GL_BLEND);
	glGetIntegerv(GL_BLEND_SRC, &blendSrc);
	glGetIntegerv(GL_BLEND_DST, &blendDst);
	glGetIntegerv(GL_VIEWPORT, screenStats);

	if (depthOn) 
	  glDisable(GL_DEPTH_TEST);  // If they were enabled/disabled
	if (!textureOn) 
	  glEnable(GL_TEXTURE_2D); // then enable/disable them
	if (!blendOn) 
	  glEnable(GL_BLEND);
	if (!scissorOn) 
	  glEnable(GL_SCISSOR_TEST);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set the correct blending mode

	//glActiveTextureARB(GL_TEXTURE0_ARB);

	glMatrixMode(GL_PROJECTION); // and initalize Ortho mode
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0.0f,screenStats[2],screenStats[3],0.0f,-1.0f,1.0f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	 
	glBindTexture(GL_TEXTURE_2D, font.id);

	if(type>1) typ=typ-2;
	glLoadIdentity();
	glTranslated(x,y,-10);
	glListBase(base-32+(128*typ));
	glScalef(sizex,sizey,1.0f);
	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);

	if(type>1)
	{
	glLoadIdentity();
	glTranslated(x+1,y,0);
	glListBase(base-32+(128*(type-2)));
	glScalef(sizex,sizey,1.0f);
	glCallLists(strlen(text),GL_UNSIGNED_BYTE, text);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	if (depthOn) glEnable(GL_DEPTH_TEST);
	if (!textureOn) glDisable(GL_TEXTURE_2D);
	if (!blendOn) glDisable(GL_BLEND);
	if (!scissorOn) glDisable(GL_SCISSOR_TEST);

	glBlendFunc(blendSrc, blendDst);
	glMatrixMode(matrixMode);
	return 1;
}

