#include "K2D_HighScore.h"
#include <stdio.h>
#include <sdl/sdl.h>

#define K2D_HIGHSCORE_HASH "K2D\0"

/*
	Sauvegarde les score en faisant un cryptage xor de l'heure de sauvegarde
	sur les score, les infos pour le decryptage etant stockées dans le fichier
*/
void K2D_HighScoreTable:: SaveScore (char* szFile)
{
	FILE* fp = fopen(szFile, "wb");
	if (!fp)
		return;

	fwrite ( K2D_HIGHSCORE_HASH, strlen (K2D_HIGHSCORE_HASH), sizeof(char), fp ); 
	fwrite ( &size, 1,sizeof(int), fp ); 
	
	int key = SDL_GetTicks ();		// clee de cryptage des fichiers
	fwrite ( &key, 1, sizeof(int), fp ); 
	for (int i = 0; i < size; i++)
	{
		K2D_ScoreEntry crypted = m_Scores[i];
		for (int j = 0; j < K2D_SCORE_NAME_SIZE; j++)
			crypted.Name [j] ^= key;
		crypted.m_Score ^= key;
		fwrite (&crypted, 1, sizeof(K2D_ScoreEntry), fp ); 
	}
	fclose(fp);
}

int K2D_HighScoreTable:: LoadScore (char* szFile)
{
	FILE* fp = fopen(szFile, "rb");
	char hash [sizeof(K2D_HIGHSCORE_HASH)];
	int key;
	K2D_ScoreEntry crypted;
	if (!fp)
		return 0;
	
	// Verifie qu'on a bien un fichier de highscores
	fread ( &hash, strlen (K2D_HIGHSCORE_HASH), sizeof(char), fp ); 
	if (strncmp(hash, K2D_HIGHSCORE_HASH, strlen(K2D_HIGHSCORE_HASH)) != 0)
		return 0;

	// Recupere les infos
	fread ( &size, 1, sizeof(int), fp ); 
	fread ( &key, 1, sizeof(int), fp ); 
	// et puis s'en sert pour decrypter les scores
	for (int i = 0; i < size; i++){
		fread (&crypted, 1, sizeof(K2D_ScoreEntry), fp ); 
		for (int j = 0; j < K2D_SCORE_NAME_SIZE; j++)
			crypted.Name [j] ^= key;
		crypted.m_Score ^= key;
		m_Scores[i] = crypted; 
	}
	
	fclose(fp);

	return 1;
}

void K2D_HighScoreTable::Insert (char* Name, int score)
{
	K2D_ScoreEntry entry(Name, score);

	for (int i = 0; i < size; i++)
	{
		if (m_Scores[i].m_Score < score)
		{
			m_Scores.insert(m_Scores.begin()+i, entry);
			break;
		}
	}
}
