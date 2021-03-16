#ifndef _K2D_SOUND_H_
#define _K2D_SOUND_H_

#include <fmod/fmod.h>
#include <fmod/fmod_errors.h>

/*
	Ici tout ce qui est relatif au son
*/

/*
	Classe qui permet de gérer le son
	ne pas oublier d initialiser FMod ni de le fermer, et egalement de
	faire appel a la methode Close (); a la fin du programme pour chaque K2D_Sound;
*/
class K2D_Sound
{
public:
	K2D_Sound (char* strFileName){
		m_Stream = NULL;
		m_iChan = -1;	
		this->Load(strFileName);
	}
	K2D_Sound()	{	
		m_Stream = NULL;
		m_iChan = -1;
	}
	
	~K2D_Sound (){
		Stop ();
		m_Stream = NULL;
	}
	//	Charge un fichier en memoire
	int Load (char* strFileName)
	{
		m_Stream = FSOUND_Stream_Open(strFileName, FSOUND_HW2D | FSOUND_NORMAL | FSOUND_LOOP_OFF,0,0);
		return (m_Stream != NULL) ;
	}
	//	Ferme le stream
	void Close()
	{
		Stop ();
		FSOUND_Stream_Close(m_Stream);
	}
				////////////////////////////////////////////
				// Changements d etats du stream
				////////////////////////////////////////////
	// Joue le stream
	void Play (){	
		m_iChan = FSOUND_Stream_Play(FSOUND_FREE, m_Stream);
	}
	// Stoppe le stream
	void Stop (){
		FSOUND_Stream_Stop ( m_Stream );
	}
	// Met le stream en pause si bPaused == true 
	void SetPaused (bool bPaused){
		FSOUND_SetPaused(m_iChan, bPaused); 
	}
	// Si bMute == true alors le stream continue d avancer mais on ne l entend plus
	void SetMute (bool bMute){
		FSOUND_SetMute(m_iChan, bMute); 
	}

	// Positionne le stream a iPos (en millisecondes)
	void SetPosition (unsigned int iPos){
		FSOUND_SetCurrentPosition(m_iChan, iPos);
	}
				////////////////////////////////////////////
				// Pour connaitre l' etat de lecture du stream
				////////////////////////////////////////////
	// 	Renvoie  1 si le stream est actuellement en lecture, 0 sinon	
	int isPlaying (){
		return FSOUND_IsPlaying(m_iChan);
	}
	// 	Renvoie  1 si le stream est actuellement en pause, 0 sinon	
	signed char isPaused (){
		return FSOUND_GetPaused(m_iChan); 
	}
	// 	Renvoie  1 si le stream est actuellement en mute, 0 sinon	
	signed char IsMuted (){
		return FSOUND_GetMute(m_iChan);
	}
	//	Renvoie la position dans le stream
	unsigned int GetPosition ()
	{
		return FSOUND_GetCurrentPosition(m_iChan);
	}
				////////////////////////////////////////////
				// Le volume
				////////////////////////////////////////////
	/*	Assigne le volume a iVolume 
		Avec 0 <= iVolume <= 255
	*/
	void SetVolume (int iVolume){
		FSOUND_SetVolume(m_iChan, iVolume); 
	}
	//	Renvoie le volume du stream
	int GetVolume (){
		return FSOUND_GetVolume(m_iChan); 
	}

	// La balance
	int GetBalance (){
		return 	FSOUND_GetPan(m_iChan); 
	}
	void SetBalance(int iBalance){
		FSOUND_SetPan(m_iChan, iBalance); 
	}
		
	// La longueur du Stream (en ms)
	int GetLen (){
		return FSOUND_Stream_GetLengthMs(m_Stream); 
	}
	// Temps ecoule depuis le debut de la lecture
	int GetElapsed ()
	{
		return FSOUND_Stream_GetTime(m_Stream); 
	}
	// repositionner le son a iTime millisecondes.
	int SetTime(int iTime){
		FSOUND_Stream_SetTime(m_Stream, iTime); 
	}
private :
	FSOUND_STREAM* m_Stream;	// le stream qu on modifie = pour les musiques
	int m_iChan;				// le channel ou est joué le son
};

/*
	/!\ Important /!\
	Il est necessaire d appeler K2D_SoundSystem()::Init avant de faire quoi que ce soit avec les K2D_Sound
	et de faire un K2D_SoundSystem ::Close () a la sortie du programme...
  */
class K2D_SoundSystem
{
public:
	/*
		Initialise le son et choisit le driver necessaire en fonction de l OS
	*/
	static int Init ( )
	{
		if ( FSOUND_GetVersion( ) < FMOD_VERSION )
			return 0;

		#ifdef WIN32
			FSOUND_SetOutput( FSOUND_OUTPUT_DSOUND );	
		#else
			FSOUND_SetOutput( FSOUND_OUTPUT_A3D );	
		#endif	

		if ( FSOUND_Init( 44000, 128, 0 ) )
			return 1;
		return 0;
	}
	// Ferme FMod
	static void Close ( )
	{
		FSOUND_Close ( );
	}
	// Renvoie entre 0.0f et 100.0f l utilisation processeur de Fmod
	static float GetCpuUsage ()
	{
		return (FSOUND_GetCPUUsage());
	}
	// Renvoie le numero de l erreur (cf la doc de FMod)
	static int GetError ()
	{
		FSOUND_GetError();
	}
};

#endif