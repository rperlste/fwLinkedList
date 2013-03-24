#ifndef _FLLNodeIterator_H
#define _FLLNodeIterator_H

#include "FwLinkedList.h"

template <typename T> class FLLNodeIterator;

template <typename T>
class FLLNodeIterator
{
public:

	typedef typename		list<T>::node node;

	FLLNodeIterator( node*  nPtr );
	FLLNodeIterator( const  FLLNodeIterator& );
	~FLLNodeIterator() {}

	bool					operator == ( const FLLNodeIterator<T>& it ) const;
	bool					operator != ( const FLLNodeIterator<T>& it ) const;

	T&						operator * ()  const;
	T&						operator -> () const;

	void					operator ++ ();
	void					operator ++ ( int );

	friend class list<T>;

private:
	node*					_node;
	bool					_end;
};


template <typename T>
FLLNodeIterator<T>::FLLNodeIterator( node* nPtr ){
	_node = nPtr;
	( nPtr == 0 || nPtr->link == 0 ) 
		? _end = true
		: _end = false;
}

template <typename T>
bool FLLNodeIterator<T>::operator == ( const FLLNodeIterator<T>& it ) const {
	return ( this->_node->data == it._node->data )
		&& ( this->_node->link == it._node->link )
		&& ( this->_end == it._end );
}

template <typename T>
bool FLLNodeIterator<T>::operator != ( const FLLNodeIterator<T>& it ) const {
	return ( this->_node->data != it._node->data )
		|| ( this->_node->link != it._node->link )
		|| ( this->_end != it._end );
}

template <typename T>
T& FLLNodeIterator<T>::operator * () const {
	return _node->data;
}

template <typename T>
T& FLLNodeIterator<T>::operator -> () const {
	return _node->data;
}

template <typename T>
void FLLNodeIterator<T>::operator ++ () {
	if ( _node->link != 0 ){
		_node = _node->link;
	} 
	if( _node->link == 0 ){
		_end = true;
	}
}

template <typename T>
void FLLNodeIterator<T>::operator ++ ( int ) {
	++ *this;
}

#endif