#include "K2D_HighScore.h"
#include <stdio.h>

void K2D_HighScoreTable:: SaveScore (char* szFile)
{
	FILE* fp = fopen(szFile, "wb");
	if (!fp)
		return;

	fwrite ( &size, 1, sizeof(int), fp ); 

	for (int i = 0; i < size; i++)
		fwrite (&m_Scores[i], 1, sizeof(K2D_ScoreEntry), fp ); 
	fclose(fp);
}

int K2D_HighScoreTable:: LoadScore (char* szFile)
{
	FILE* fp = fopen(szFile, "rb");
	if (!fp)
		return 0;

	fread ( &size, 1, sizeof(int), fp ); 

	for (int i = 0; i < size; i++)
		fread (&m_Scores[i], 1, sizeof(K2D_ScoreEntry), fp ); 
	
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
