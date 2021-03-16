// K2D_Socket.cpp - classe représentant une K2D_Socket.
// 2005 par Funto. Si vous utilisez cette classe dans un de vos projets, un mail
// de remerciement à funto66@gmail.com serait le bienvenu ;).
// Version 1.0

#include "K2D_Socket.h"

#include <stdio.h>
#include <string.h>

K2D_Socket::K2D_Socket() :
m_fd(0), m_state(SOCK_FREE), m_protocol(SOCK_TCP), m_addr()
{
}

K2D_Socket::K2D_Socket(const K2D_Socket& ref)
: m_fd(ref.m_fd), m_state(ref.m_state), m_protocol(ref.m_protocol),
  m_addr(ref.m_addr)
{
}

K2D_Socket::~K2D_Socket()
{
	Destroy();
}

K2D_Socket& K2D_Socket::operator=(const K2D_Socket& ref)
{
	m_fd = ref.m_fd;
	m_state = ref.m_state;
	m_protocol = ref.m_protocol;
	memcpy((void*)&m_addr, (const void*)&ref.m_addr, sizeof(struct sockaddr_in));

	return *this;
}

bool K2D_Socket::Create(SockProtocol protocol)
{
	Destroy();	// Si la K2D_Socket était déjà créée, on la détruit avant.

	if(protocol != SOCK_TCP)
	{
		fprintf(stderr, "Erreur : protocole non implemente\n");
		return false;
	}
	
	m_fd = socket(AF_INET, SOCK_STREAM, 0);	// AF_INET : internet; SOCK_STREAM : par flux; 0 : protocol (TCP)

	if(m_fd < 0)
	{
		fprintf(stderr, "Erreur lors de la creation de la K2D_Socket\n");
		return false;
	}

	return true;
}

void K2D_Socket::Destroy()
{
	if(m_fd <= 0) return;
	
	ShutDown();
#ifdef WIN32
	closesocket(m_fd);
#else
	close(m_fd);
#endif

	m_fd = 0;
	m_state = SOCK_FREE;
	m_protocol = SOCK_TCP;
}

bool K2D_Socket::Init()
{
#ifdef WIN32
	WSAData data;
	int err = WSAStartup(MAKEWORD(1, 1), &data);
	if( err != 0 )
	{
		fprintf(stderr, "Erreur lors de l'initialisation des"
			" Windows Sockets : %d\n", err);
		return false;
	}
#endif
	return true;
}

void K2D_Socket::CleanUp()
{
#ifdef WIN32
	WSACleanup();
#endif
}

// Connexion au serveur
bool K2D_Socket::Connect(const char* server_ip, int port)
{
	if(m_fd <= 0) return false;

	// On remplit la structure m_addr
	m_addr.sin_family = AF_INET;	// Adresse de type internet : on doit toujours mettre ça
	m_addr.sin_port = htons(port);			// Port
	m_addr.sin_addr.s_addr = inet_addr(server_ip);	// Adresse IP du serveur
	memset(&(m_addr.sin_zero), 0, 8);	// On met le reste (8 octets) à 0

	if(connect(m_fd, (struct sockaddr*)&m_addr, sizeof(struct sockaddr)) < 0)
	{
		fprintf(stderr, "Erreur lors de la connexion au serveur\n");
		m_state = SOCK_FREE;
	}
	else
		m_state = SOCK_CONNECTED;
	
	return m_state == SOCK_CONNECTED;
}
	
// Envoi de données (d'un client vers un serveur) :
int K2D_Socket::Send(const void* data, int nb_bytes)
{
	if(m_state != SOCK_CONNECTED) return -1;

#ifdef WIN32
	return send(m_fd, (const char*)data, nb_bytes, 0);
#else
	return send(m_fd, data, nb_bytes, 0);
#endif
}

// Envoi de données (d'un serveur vers un client) :
int K2D_Socket::Send(K2D_Socket* client_socket, const void* data, int nb_bytes)
{
	if(m_state != SOCK_LISTENING) return -1;
	
#ifdef WIN32
	return send(client_socket->GetFD(), (const char*)data, nb_bytes, 0);
#else
	return send(client_socket->GetFD(), data, nb_bytes, 0);
#endif
}

// Réception de données (données allant d'un serveur vers un client) :
int K2D_Socket::Receive(void* buffer, int max_bytes)
{
	if(m_state != SOCK_CONNECTED) return -1;

#ifdef WIN32
	return recv(m_fd, (char*)buffer, max_bytes, 0);
#else
	return recv(m_fd, buffer, max_bytes, 0);
#endif
}

// Pour un client : renvoie true si le serveur nous a envoyé un message, qui
// est dans la file d'attente, sinon renvoie false.
bool K2D_Socket::WaitsForAMessage()
{
	// On crée un fd_set, c'est à dire une liste des FDs à tester. On ne met en fait
	// dans cette liste que notre FD.
	fd_set set;
	
	FD_ZERO(&set);
	FD_SET(m_fd, &set);
	
	// Le timeout du fd_set que l'on a créé est de 0s et 0µs, ce qui signifie que
	// select() rendra la main immédiatement.
	struct timeval timeout = {0, 0};
	
	// On fait un select(), qui permet de savoir si les FDs du fd_set ont un message
	// da la file d'attente.
	if(select(m_fd+1, &set, NULL, NULL, &timeout) < 0)
	{
		fprintf(stderr, "Erreur : select() renvoie -1\n");
		return false;
	}

	return FD_ISSET(m_fd, &set) != 0;
}

// Pour un serveur : renvoie true si le client spécifié nous a envoyé un message,
// qui est donc dans la file d'attente, sinon renvoie false.
bool K2D_Socket::WaitsForAMessageFrom(K2D_Socket* client_socket)
{
	// Pour les explications, Cf au-dessus
	fd_set set;
	
	FD_ZERO(&set);
	FD_SET(client_socket->m_fd, &set);
	
	struct timeval timeout = {0, 0};
	
	if(select(client_socket->m_fd+1, &set, NULL, NULL, &timeout) < 0)
	{
		fprintf(stderr, "Erreur : select() renvoie -1\n");
		return false;
	}
	
	return FD_ISSET(client_socket->m_fd, &set) != 0;
}

// Réception de données (données allant d'un client vers un serveur) :
int K2D_Socket::Receive(K2D_Socket* client_socket, void* buffer, int max_bytes)
{
	if(m_state != SOCK_LISTENING) return -1;

#ifdef WIN32
	return recv(client_socket->m_fd, (char*)buffer, max_bytes, 0);
#else
	return recv(client_socket->m_fd, buffer, max_bytes, 0);
#endif
}

// Mise sur écoute (pour un serveur) :
bool K2D_Socket::Listen(int port, int max_queue)
{
	// On remplit la structure m_addr, qui correspond à l'adresse du serveur (nous)
	m_addr.sin_family = AF_INET;			// Adresse de type internet : on doit toujours mettre ça
	m_addr.sin_port = htons(port);			// Port
	m_addr.sin_addr.s_addr = htons(INADDR_ANY);	// On écoute tout le monde, quelle que soit son adresse IP
	memset(&(m_addr.sin_zero), 0, 8);		// On met le reste (8 octets) à 0
	
	// On associe la K2D_Socket à un port et à une adresse, définis dans server_addr :
	if(bind(m_fd, (struct sockaddr*)&m_addr, sizeof(struct sockaddr)) < 0)
	{
		fprintf(stderr, "Erreur lors de l'association de la K2D_Socket avec l'adresse\n");
		m_state = SOCK_FREE;
	}
	else
	{
		// On se met sur écoute
		if(listen(m_fd, max_queue) < 0)
		{
			fprintf(stderr, "Erreur lors de la mise sur ecoute\n");
			m_state = SOCK_FREE;
		}
		else
			m_state = SOCK_LISTENING;
	}
	
	return m_state == SOCK_LISTENING;
}

// Acceptation d'un nouveau client (pour un serveur)
bool K2D_Socket::Accept(K2D_Socket* sock_client)
{
	// On remplit la structure m_addr, qui correspond à l'adresse du serveur (nous)
	sock_client->m_addr.sin_family = AF_INET;	// Adresse de type internet : on doit toujours mettre ça
	sock_client->m_addr.sin_port = 0;			// Port
	sock_client->m_addr.sin_addr.s_addr = htons(INADDR_ANY);	// On écoute tout le monde, quelle que soit son adresse IP
	memset(&(sock_client->m_addr.sin_zero), 0, 8);		// On met le reste (8 octets) à 0

#ifdef WIN32
	int sin_size = sizeof(struct sockaddr);
	sock_client->m_fd = accept(m_fd, (struct sockaddr*)&(sock_client->m_addr), &sin_size);
#else
	socklen_t sin_size = sizeof(struct sockaddr);
	sock_client->m_fd = accept(m_fd, (struct sockaddr*)&(sock_client->m_addr), &sin_size);
#endif

	if(sock_client->m_fd > 0)
	{
		sock_client->m_state = SOCK_ACCEPTED;
		return true;
	}
	else
	{
		fprintf(stderr, "Erreur lors de l'acceptation d'un nouveau client\n");
		return false;
	}
}

// Ferme la connexion
void K2D_Socket::ShutDown()
{
	if(m_state != SOCK_FREE)
	{
		shutdown(m_fd, 2);
		m_state = SOCK_FREE;
	}
}
