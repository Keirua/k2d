// K2D_Socket.h - classe représentant une K2D_Socket.
// 2005 par Funto. Si vous utilisez cette classe dans un de vos projets, un mail
// de remerciement à funto66@gmail.com serait le bienvenu ;).
// Version 1.0

#ifndef _K2D_SOCKET_H_
#define _K2D_SOCKET_H_

#ifdef WIN32
	#include <windows.h>
#pragma comment (lib, "ws2_32.lib")
	#ifndef FD_SET
		#include <winsock2.h>
	#endif
#else
	#include <sys/types.h>
	#include <sys/K2D_Socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <unistd.h>
#endif

// Enumération des états où peut être une K2D_Socket.
enum SockState
{
	SOCK_FREE=0,
	SOCK_CONNECTED,
	SOCK_LISTENING,
	SOCK_ACCEPTED
};

// Enumération des protocoles : pour l'instant on en reste à TCP/IP ^^
enum SockProtocol
{
	SOCK_TCP=0
};

class K2D_Socket
{
private:
	int m_fd;
	SockState m_state;
	SockProtocol m_protocol;
	sockaddr_in m_addr;
	
public:
	K2D_Socket();
	K2D_Socket(const K2D_Socket& ref);
	~K2D_Socket();

	// Opérateur d'affectation
	K2D_Socket& operator=(const K2D_Socket& ref);

	// Fonctions correspondant aux constructeur/destructeur : toutes les autres méthodes
	// doivent être placées entre les appels à ces 2 méthodes.
	bool Create(SockProtocol protocol=SOCK_TCP);
	void Destroy();

	// Méthodes statiques pour la compatibilité avec les WinSockets : à appeler au
	// début et à la fin du programme.
	static bool Init();
	static void CleanUp();

	// Accesseurs
	int GetFD() {return m_fd;}
	bool IsCreated() {return m_fd > 0;}
	SockState GetState() {return m_state;}
	SockProtocol GetProtocol() {return m_protocol;}

	// Connexion à un serveur :
	// -server_ip : IP du serveur auquel on se connecte
	// -port : numéro du port utilisé
	bool Connect(const char* server_ip, int port);
	
	// Envoi de données (d'un client vers un serveur) :
	// -data : pointeur vers les données
	// -nb_bytes : taille des données à envoyer, en octets
	int Send(const void* data, int nb_bytes);
	
	// Envoi de données (d'un serveur vers un client) :
	// -client_socket : pointeur vers la K2D_Socket correspondant au client à qui envoyer
	// les données (obtenu via Accept())
	// -data : pointeur vers les données
	// -nb_bytes : taille des données à envoyer, en octets
	int Send(K2D_Socket* client_socket, const void* data, int nb_bytes);
	
	// Réception de données (données allant d'un serveur vers un client) :
	// -buffer : pointeur vers l'endroit où l'on doit stocker les données
	// -max_bytes : taille du buffer en octets, nombre maximal de données pouvant
	// être retournées
	int Receive(void* buffer, int max_bytes);
	
	// Réception de données (données allant d'un client vers un serveur) :
	// -client_socket : K2D_Socket du client qui nous envoie les données
	// -buffer : pointeur vers l'endroit où l'on doit stocker les données
	// -max_bytes : taille du buffer en octets, nombre maximal de données pouvant
	// être retournées
	int Receive(K2D_Socket* client_socket, void* buffer, int max_bytes);

	// Pour un client : renvoie true si le serveur nous a envoyé un message, qui
	// est dans la file d'attente, sinon renvoie false.
	bool WaitsForAMessage();
	
	// Pour un serveur : renvoie true si le client spécifié nous a envoyé un message,
	// qui est donc dans la file d'attente, sinon renvoie false.
	// -client_socket : client susceptible de nous avoir envoyé un message.
	bool WaitsForAMessageFrom(K2D_Socket* client_socket);
	
	// Mise sur écoute (pour un serveur) :
	// -port : numéro du port à écouter
	// -max_queue : nombre maximum de clients pouvant attendre dans une file
	bool Listen(int port, int max_queue=10);

	// Acceptation d'un nouveau client (pour un serveur)
	// -sock_client : pointeur vers la K2D_Socket correspondant au nouveau client accepté
	bool Accept(K2D_Socket* sock_client);
	
	// Ferme la connexion
	void ShutDown();
};

#endif // SOCKET_H

