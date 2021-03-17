#ifndef _K2D_TOOL_H_
#define _K2D_TOOL_H_

#pragma warning (disable:4786)

#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>

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
	// Attention taille limite de 2048 caracteres
	static inline std::string Format(const char *format, ...)
	{
		static const int MAX_BUFF_SIZE = 2048;
		static char buffer[MAX_BUFF_SIZE];
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
		static std::string days[]={"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
		static std::string months[]={"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", 
							"Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

		char buffer[32];	// conversions via itoa

		// todo: commented out until it builds
		// for (int i = 0; i < format.size();i++)
		// {
		// 	switch (format[i])
		// 	{
		// 	// Heure
		// 	case 'h':
		// 		itoa(timeinfo->tm_hour, &buffer[0], 10);
		// 		szDate += buffer;
		// 		break;
		// 	// minute
		// 	case 'i':
		// 		itoa(timeinfo->tm_min, &buffer[0], 10);
		// 		szDate += buffer;
		// 		break;
		// 	// secondes
		// 	case 's':
		// 		itoa(timeinfo->tm_sec, &buffer[0], 10);
		// 		szDate += buffer;
		// 		break;
		// 	// jour (chiffre)
		// 	case 'd':
		// 		itoa(timeinfo->tm_mday, &buffer[0], 10);
		// 		szDate += buffer;
		// 		break;
		// 	// jour (lettres)
		// 	case 'D':
		// 		szDate += days[timeinfo->tm_wday];
		// 		break;
		// 	// mois (chiffre)
		// 	case 'm':
		// 		itoa(timeinfo->tm_mon, &buffer[0], 10);
		// 		szDate += buffer;
		// 		break;
		// 	// mois (lettres)
		// 	case 'M':
		// 		szDate += months[timeinfo->tm_mon];
		// 		break;
		// 	// annee (chiffre)
		// 	case 'y':
		// 		itoa(timeinfo->tm_year+1900, &buffer[0], 10);
		// 		szDate += buffer;
		// 		break;
		// 	// Si on trouve un caractere autre, on l ajoute au résultat
		// 	default:
		// 		szDate += format[i];
		// 		break;
		// 	}
		// }

		return szDate;
	}
};


/*
	Fonctions utiles sur les chaines de caractères
*/
class string_func
{
public:
	// todo: commented out until it builds
	// todo: unused
	// met a la suite tous les elements du tableau,  et les sépare par le caractere delim
	// static std::string implode ( std::vector <std::string> v, char delim = ' ' )
	// {
	// 	std::string res = "";
	// 	for (int i =0; i < v.size()-1;i++)
	// 	{
	// 		res += v [i];
	// 		res += delim;
	// 	}
	// 	res += v[i];
	// 	return res;
	// }

	// sépare une chaine suivant le caractere delim et met le tout dans un tableau
	static std::vector <std::string> explode ( std::string in, char delim = ' ')
	{
		std::vector <std::string> v;
		std::string curr = "";
		for (int i = 0; i < in.length();i++)
		{
			if (in [i] == delim && curr != "")
			{
				v.push_back ( curr );
				curr = "";
			}
			else
				curr += in [i];
		}

		if (curr != "")
			v.push_back ( curr );

		return v;
	}

	// Fonction date comme en php
	//static std::string string_func date (std::string format);



};

/*
// Exemple d'utilisation de ces fonctions
	std::vector<std::string> v;
	v.push_back ("abc");
	v.push_back ("def");
	v.push_back ("ghi");
	v.push_back ("klm");
	
	// -> on met tout dans la mm chaine
	std::string res = string_func::implode (v, '/');
	printf ("%s\n", res.c_str());
	v.clear ();

	// -> On sépare suivant un caractère donné
	v = string_func::explode (res, '/');
	for (int i = 0; i < v.size(); i++)
		printf ("%s\n", v[i].c_str());
*/

/*
	string conversion class from string to anything or the contrary
*/
template<typename T>
class str
{
public:
	
	static T string_to(std::string s)
	{
		T t;
		std::istringstream ss(s);
		ss >> t;
		return t;
	}

	static std::string string_from(T t)
	{
		std::ostringstream ss;
		ss << t;
		return ss.str();	
	}

};

#endif