#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <stdio.h>

template <typename T> 
class singleton 
{ 
protected: 
    // Constructeur/Destructeur 
    singleton( ) 
	{ 
		m_pInstance = NULL;
	} 
    ~singleton( ) 
	{
        if( m_pInstance != NULL ) 
        { 
            delete m_pInstance; 
            m_pInstance = 0; 
        }
	}

public: 
    // renvoie une instance de la classe, la crée si elle n existe pas
    static T* GetInstance(  ) 
    { 
		if (m_pInstance == NULL)
			m_pInstance = new T;

        return ((T*) m_pInstance);
    }
protected:
	static T* m_pInstance;
}; 

template <typename T> T *singleton<T>::m_pInstance = NULL;

#endif