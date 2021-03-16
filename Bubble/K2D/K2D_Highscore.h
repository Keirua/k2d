#ifndef _K2D_HIGHSCORE_H_
#define _K2D_HIGHSCORE_H_

#include <string.h>
#include <vector>

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
				strncpy(&Name[0], &(b_.Name)[0], 64);
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
		char Name[64];
		int m_Score;
	};
	
	int Size ()							{	return size;					}
	K2D_ScoreEntry GetScore(int index)	{	return m_Scores[index%size];	}

	private:
	// m_Scores[0] = meilleur score
	std::vector<K2D_ScoreEntry> m_Scores;
	int size;
};

#endif