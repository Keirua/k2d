#ifndef _ARRAY2D_H______
#define _ARRAY2D_H______

#include <vector>
#include <algorithm>
#include <memory>

typedef unsigned int uint;
/*
	Classe de tableaux à 2 dimensions
	Utilisée pour stocker les maps par exemple ...
*/
template <class Type> 
class Array2D
{
    Type *values;  // données
    
    uint _size;  // nombre de valeurs
    uint _nbRow; // nombre de lignes
    uint _nbCol; // nombre de colonnes
    
public:

	// constructeur par defaut
    Array2D();
	// destructeur
    ~Array2D();
    
	// constructeur par copie
    Array2D(const Array2D &v);
    
	// constructeurs
    Array2D(const std::vector< std::vector< Type > > &v);
	Array2D(const std::vector< Type > &v, int nbCol);
    Array2D(const Type *v, uint nbRow, uint nbCol);
    Array2D(uint nbRow, uint nbCol);
	Array2D(uint nbRow, uint nbCol, const Type &init_value);
    
	// operateurs d'affection
    Array2D& operator = (const Array2D &v);
    
    Array2D& operator = (const std::vector< std::vector< Type > > &v);
    
	// accesseurs
	//
	// remarque : l'opérateur () (opérateur fonctionnel) permet d'accéder
	//  à un élément du tableau 2D en spécifiant l'indice de sa ligne et
	//  de sa colonne.
    uint size() const;
    uint row() const;
    uint col() const;
    
	// renvoie l'element correspondant
    Type operator [] (uint ind) const;
    Type operator () (uint indR, uint indC) const;
    Type at (uint ind) const;
    Type at (uint indR, uint indC) const;
    
    Type& operator [] (uint  ind);
    Type& operator () (uint indR, uint indC);
    Type& at(uint ind);
    Type& at(uint indR, uint indC);

	// retourne c-style array 
	const Type* c_array() const;
    
	// redimensionne
	void resize(uint nbRow, uint nbCol);
    void resize(uint nbRow, uint nbCol, const Type &init_value);

	// operateurs de comparaison
	bool operator == (const  Array2D &v) const;
	bool operator != (const  Array2D &v) const;
};

template<class Type>
Array2D<Type>::Array2D() : values(0), _size(0), _nbRow(0), _nbCol(0)
{
}

template<class Type>
Array2D<Type>::~Array2D()
{
    delete[] values;
}

template<class Type>
Array2D<Type>::Array2D(const Array2D<Type> &v) : _size(v._size), _nbRow(v._nbRow), _nbCol(v._nbCol)
{
    values=new Type[_size];
	memcpy(values, v.values, _size * sizeof(Type) );
}

template<class Type>
Array2D<Type>::Array2D(const std::vector< std::vector< Type > > &v) : _nbRow(v.size()), _nbCol(v[0].size())
{
    _size=_nbRow * _nbCol;
    values=new Type[_size];
    
    for(uint i=0;i<v.size();i++)
        for(uint j=0;j<v[0].size();j++)
            values[ i*_nbCol + j ]=v[i][j];
 
}

template<class Type>
Array2D<Type>::Array2D(const std::vector< Type > &v, int nbCol) : _size(v.size()), _nbCol(nbCol)
{
	_nbRow= _size / _nbCol;
	values=new Type[_size];

	for(uint i=0; i<_size; i++)
		values[i]=v[i];
}

template<class Type>
Array2D<Type>::Array2D(const Type *v, uint nbRow, uint nbCol) : _nbRow(nbRow), _nbCol(nbCol)
{
    _size=_nbRow * _nbCol;
    values=new Type[_size];
    
    memcpy( values, v, _size * sizeof(Type) );
}

template<class Type>
Array2D<Type>::Array2D(uint nbRow, uint nbCol) : _nbRow(nbRow), _nbCol(nbCol)
{
    _size=_nbRow * _nbCol;
    values=new Type[_size];
}

template<class Type>
Array2D<Type>::Array2D(uint nbRow, uint nbCol, const Type &init_value) : _nbRow(nbRow), _nbCol(nbCol)
{
    _size=_nbRow * _nbCol;
    values=new Type[_size];
	for(uint i=0; i<_size; i++)
		values[i]=init_value;
}

template<class Type>
Array2D<Type>& Array2D<Type>::operator = (const Array2D<Type> &v)
{
    if( this == &v  )
        return *this;
        
    _size=v._size;
    _nbRow=v._nbRow;
    _nbCol=v._nbCol;
    
    if( values  ) 
        delete[] values;
        
    values=new Type[_size];   
	memcpy(values, v.values, _size * sizeof(Type) );

    return *this;
}

template<class Type>
Array2D<Type>& Array2D<Type>::operator = (const std::vector< std::vector< Type > > &v)
{
    _nbRow=v.size();
    _nbCol=v[0].size();
    _size=_nbRow *  _nbCol;
    
    if( values  ) 
        delete[] values;
        
    values=new Type[_size];
    
    for(uint i=0;i<v.size();i++)
        for(uint j=0;j<v[0].size();j++)
            values[ i*_nbCol + j ]=v[i][j];
}

template<class Type>
inline uint Array2D<Type>::size() const
{
    return _size;
}

template<class Type>
inline uint Array2D<Type>::row() const
{
    return _nbRow;
}

template<class Type>
inline uint Array2D<Type>::col() const
{
    return _nbCol;
}

template<class Type>
inline Type Array2D<Type>::operator [] (uint ind) const
{
    return values[ind];
}

template<class Type>
inline Type Array2D<Type>::operator () (uint indR, uint indC) const
{
    return values[ ( indR * _nbCol ) + indC ];
}

template<class Type>
inline Type Array2D<Type>::at (uint ind) const
{
    if( ind >= _size )
        return values[_size-1];
    return values[ind];
}

template<class Type>
inline Type Array2D<Type>::at (uint x, uint y) const
{
    if( y >= _nbRow || x >= _nbCol )
        return values[_size-1];
    return values[ ( y * _nbCol ) + x ];
}

template<class Type>
inline Type& Array2D<Type>::operator [] (uint  ind)
{
    return values[ind];
}

template<class Type>
inline Type& Array2D<Type>::operator () (uint x, uint y)
{
    return values[ ( y * _nbCol ) + x ];
}

template<class Type>
inline Type& Array2D<Type>::at(uint ind)
{
    if( ind >= _size )
        return values[_size-1];
    return values[ind];
}

template<class Type>
inline Type& Array2D<Type>::at(uint x, uint y)
{
    if( y >= _nbRow || x >= _nbCol )
        return values[_size-1];
    return values[ ( y * _nbCol ) + x ];
}

template<class Type>
const Type* Array2D<Type>::c_array() const
{
	return values;
}

template<class Type>
void Array2D<Type>::resize(uint nbRow, uint nbCol)
{
    if( _nbRow==nbRow && _nbCol==nbCol )
        return;
       
    _size=nbRow * nbCol;

    Type *v_tmp=new Type[_size];
	
	uint minR = (_nbRow < nbRow ) ? _nbRow : nbRow;
    uint minC = (_nbCol < nbCol ) ? _nbCol : nbCol;
    
    for(uint i=0; i<minR; i++)
        for(uint j=0; j<minC; j++)
            v_tmp[ i*nbCol + j ]=values[ i*_nbCol + j ];      

	_nbRow=nbRow;
    _nbCol=nbCol;

    delete[] values;
    values=v_tmp;
}

template<class Type>
void Array2D<Type>::resize(uint nbRow, uint nbCol, const Type &init_value)
{
    if( _nbRow==nbRow && _nbCol==nbCol )
        return;
	uint i      ;
    _size=nbRow * nbCol;

    Type *v_tmp=new Type[_size];
	for( i = 0; i < _size; i++) 
		v_tmp[i]=init_value;
	
	uint minR = (_nbRow < nbRow ) ? _nbRow : nbRow;
    uint minC = (_nbCol < nbCol ) ? _nbCol : nbCol;
    
    for( i = 0; i < minR; i++)
        for(uint j = 0; j<minC; j++)
            v_tmp[ i*nbCol + j ]=values[ i*_nbCol + j ];      

	_nbRow=nbRow;
    _nbCol=nbCol;

    delete[] values;
    values=v_tmp;
}

template<class Type>
bool Array2D<Type>::operator == (const  Array2D<Type> &v) const
{
	if( this == &v  )
		return true;

	if( _nbRow != v._nbRow || _nbCol != v._nbCol )
		return false;

	for(uint i=0; i<_nbRow; i++)
		for(uint j=0; j<_nbCol; j++)
		{
			uint ind=i*_nbCol +j;
			if( values[ind]!=v.values[ind] )
				return false;
		}

	return true;
}

template<class Type>
bool Array2D<Type>::operator != (const  Array2D<Type> &v) const
{
	return !( (*this)==v );
}


#endif // _ARRAY2D_H______
