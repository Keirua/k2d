#ifndef _K2D_HIGHSCORE_H_
#define _K2D_HIGHSCORE_H_

#include <string.h>
#include <vector>

#define K2D_SCORE_NAME_SIZE 64

/*
	Classe de gestion des meilleures scores
	Les scores sont crypés pour eviter la triche


	Exemple d'utilisation: 

if (score.LoadScore ("save.txt")==0)
{
	printf ("pas de score, on cree\n");
	for ( i = 0; i < score.Size();i++)
	{
		strcpy(score[i].Name, "JohN");
		score[i].m_Score = 1000*(rand()%10+1);
	}	
}
else
	printf ("Les scores sont charges\n");

for ( i = 0; i < score.Size();i++)
{
	printf ("%s :: %d\n", score[i].Name, score[i].m_Score);
}
score.SaveScore ("save.txt");
*/

class K2D_HighScoreTable
{
public:
	K2D_HighScoreTable(int tableSize = 10)
	{
		m_Scores.resize (tableSize+1);
		size = tableSize;
	}
	int LoadScore (char* szFile);
	void SaveScore (char* szFile);

	void Insert (char* Name, int score);

	struct K2D_ScoreEntry
	{
		K2D_ScoreEntry ()
		{
			m_Score = 0;
			strcpy(&Name[0], "");
		}
		K2D_ScoreEntry (char* name, int score)
		{
			strcpy(&Name[0], name);
			m_Score = score;
		}
		inline K2D_ScoreEntry operator=(const K2D_ScoreEntry &b_)
		{
			if(&b_ != this)
			{
				strncpy(&Name[0], &(b_.Name)[0], K2D_SCORE_NAME_SIZE);
				m_Score = b_.m_Score;
			}
			return *this;
		}
		inline bool operator==(const K2D_ScoreEntry &b_)
		{
			if(&b_ != this)
			{
				return (b_.m_Score == m_Score) && (strcmp (b_.Name, Name)==0);
			}
		}
		char Name[K2D_SCORE_NAME_SIZE];
		int m_Score;
	};
	
	int Size ()							{	return size;					}
	K2D_ScoreEntry GetScore(int id)		{	return m_Scores[id%size];		}
	K2D_ScoreEntry& operator [] (int id){	return m_Scores[id%size];		}

private:
	// m_Scores[0] = meilleur score
	std::vector<K2D_ScoreEntry> m_Scores;
	int size;
};

#endif