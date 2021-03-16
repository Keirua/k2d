// K2D_Socket.h - classe repr�sentant une K2D_Socket.
// 2005 par Funto. Si vous utilisez cette classe dans un de vos projets, un mail
// de remerciement � funto66@gmail.com serait le bienvenu ;).
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

// Enum�ration des �tats o� peut �tre une K2D_Socket.
enum SockState
{
	SOCK_FREE=0,
	SOCK_CONNECTED,
	SOCK_LISTENING,
	SOCK_ACCEPTED
};

// Enum�ration des protocoles : pour l'instant on en reste � TCP/IP ^^
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

	// Op�rateur d'affectation
	K2D_Socket& operator=(const K2D_Socket& ref);

	// Fonctions correspondant aux constructeur/destructeur : toutes les autres m�thodes
	// doivent �tre plac�es entre les appels � ces 2 m�thodes.
	bool Create(SockProtocol protocol=SOCK_TCP);
	void Destroy();

	// M�thodes statiques pour la compatibilit� avec les WinSockets : � appeler au
	// d�but et � la fin du programme.
	static bool Init();
	static void CleanUp();

	// Accesseurs
	int GetFD() {return m_fd;}
	bool IsCreated() {return m_fd > 0;}
	SockState GetState() {return m_state;}
	SockProtocol GetProtocol() {return m_protocol;}

	// Connexion � un serveur :
	// -server_ip : IP du serveur auquel on se connecte
	// -port : num�ro du port utilis�
	bool Connect(const char* server_ip, int port);
	
	// Envoi de donn�es (d'un client vers un serveur) :
	// -data : pointeur vers les donn�es
	// -nb_bytes : taille des donn�es � envoyer, en octets
	int Send(const void* data, int nb_bytes);
	
	// Envoi de donn�es (d'un serveur vers un client) :
	// -client_socket : pointeur vers la K2D_Socket correspondant au client � qui envoyer
	// les donn�es (obtenu via Accept())
	// -data : pointeur vers les donn�es
	// -nb_bytes : taille des donn�es � envoyer, en octets
	int Send(K2D_Socket* client_socket, const void* data, int nb_bytes);
	
	// R�ception de donn�es (donn�es allant d'un serveur vers un client) :
	// -buffer : pointeur vers l'endroit o� l'on doit stocker les donn�es
	// -max_bytes : taille du buffer en octets, nombre maximal de donn�es pouvant
	// �tre retourn�es
	int Receive(void* buffer, int max_bytes);
	
	// R�ception de donn�es (donn�es allant d'un client vers un serveur) :
	// -client_socket : K2D_Socket du client qui nous envoie les donn�es
	// -buffer : pointeur vers l'endroit o� l'on doit stocker les donn�es
	// -max_bytes : taille du buffer en octets, nombre maximal de donn�es pouvant
	// �tre retourn�es
	int Receive(K2D_Socket* client_socket, void* buffer, int max_bytes);

	// Pour un client : renvoie true si le serveur nous a envoy� un message, qui
	// est dans la file d'attente, sinon renvoie false.
	bool WaitsForAMessage();
	
	// Pour un serveur : renvoie true si le client sp�cifi� nous a envoy� un message,
	// qui est donc dans la file d'attente, sinon renvoie false.
	// -client_socket : client susceptible de nous avoir envoy� un message.
	bool WaitsForAMessageFrom(K2D_Socket* client_socket);
	
	// Mise sur �coute (pour un serveur) :
	// -port : num�ro du port � �couter
	// -max_queue : nombre maximum de clients pouvant attendre dans une file
	bool Listen(int port, int max_queue=10);

	// Acceptation d'un nouveau client (pour un serveur)
	// -sock_client : pointeur vers la K2D_Socket correspondant au nouveau client accept�
	bool Accept(K2D_Socket* sock_client);
	
	// Ferme la connexion
	void ShutDown();
};

#endif // SOCKET_H

