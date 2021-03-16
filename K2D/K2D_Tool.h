#ifndef _K2D_TOOL_H_
#define _K2D_TOOL_H_

#include <cmath>
#include <string>

/*
	Classe utilitaire contenant quelques fonctions *utiles*
*/

class K2D_Tool
{
public:
	// renvoie un nombre compris entre 
	static inline float Random (int imin, int imax)
	{
		return ( rand() % (imax - imin) ) + imin;
	}

	// formatte le texte, a la facon de printf
	static inline std::string Format(const char *format, ...)
	{
		static char buffer[2048];
		va_list args;

		va_start(args, format);
			vsprintf(buffer, format, args);
		va_end(args);

		return buffer;
	}

	/*
		Fonction date similaire a celle du Php
		on lui passe en parametre le format de la date que l on veut:
		h = heure
		i = minutes (le m est déja pris par mois)
		s = secondes
		d = le jour du mois, en chiffres
		D = le jour de la semaine, en lettres (ex = Lundi)
		m = le mois en chiffre
		M = le mois en lettres (ex = Janvier)
		y = l année courante (ex = 2004)

		Exemple d appel:
		date ("h:i:s").c_str() donne 23:15:21
	*/
	static std::string Date (std::string format)
	{
		std::string szDate="";
		time_t raw;
		struct tm* timeinfo;
		
		// recupere le temps ecoule de le 1er janvier 1970
		time(&raw);
		// puis obtient une structure tm qui contient toutes les infos dont on a besoin
		timeinfo = localtime(&raw);

		if (!timeinfo)
			return "";

		// Definition de quelques trucs utiles :D
		static char* days[]={"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
		static char* months[]={"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", 
							"Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

		char buffer[32];	// conversions via itoa

		for (int i = 0; i < format.size();i++)
		{
			switch (format[i])
			{
			// Heure
			case 'h':
				itoa(timeinfo->tm_hour, &buffer[0], 10);
				szDate += buffer;
				break;
			// minute
			case 'i':
				itoa(timeinfo->tm_min, &buffer[0], 10);
				szDate += buffer;
				break;
			// secondes
			case 's':
				itoa(timeinfo->tm_sec, &buffer[0], 10);
				szDate += buffer;
				break;
			// jour (chiffre)
			case 'd':
				itoa(timeinfo->tm_mday, &buffer[0], 10);
				szDate += buffer;
				break;
			// jour (lettres)
			case 'D':
				szDate += days[timeinfo->tm_wday];
				break;
			// mois (chiffre)
			case 'm':
				itoa(timeinfo->tm_mon, &buffer[0], 10);
				szDate += buffer;
				break;
			// mois (lettres)
			case 'M':
				szDate += months[timeinfo->tm_mon];
				break;
			// annee (chiffre)
			case 'y':
				itoa(timeinfo->tm_year+1900, &buffer[0], 10);
				szDate += buffer;
				break;
			// Si on trouve un caractere autre, on l ajoute au résultat
			default:
				szDate += format[i];
				break;
			}
		}

		return szDate;
	}
};

#endif