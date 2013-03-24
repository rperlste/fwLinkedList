// Author: Will Trobaugh
// Course:  CSCI 3320, Spring 2013
// File: list.h
// Class definition of an adt that represents a single-ended, singly-linked list with iterator support
// for compatibility with the C++ standard template library

#ifndef _FwLinkedList_H
#define _FwLinkedList_H

#include <iostream>
#include <exception>

// Forward declarations for overloading operator <<
template <typename T> class list;
template <typename T> std::ostream& 
					operator << (std::ostream&, const list<T>&);

#include "FLLNodeIterator.h"


// Class definition
template <typename T>
class list {
public:
	typedef FLLNodeIterator<T> iterator;

	// Constructors
	list();
	list(const list<T>&);
	list(iterator, iterator);
	list(T*, T*);

	~list();

	// Constant members
	unsigned        size() const { return used; }
	bool            empty() const { return used==0; }
	const T&        front() const;
	const iterator  find(const T&) const;

	// Modification members
	void            push_front(const T&);
	void            pop_front();
	iterator        find(const T&);
	void            insert(const T&, unsigned);
	void            insert_after(iterator, const T&);
	bool            erase_one(const T&);
	unsigned        erase(const T&);
	void            clear();

	// Operators
	list<T>&        operator = (const list<T>&);
	void            operator += (const list<T>&);

	// Friends
	friend std::ostream& operator << (std::ostream&, const list<T>&);
	friend class    FLLNodeIterator<T>;

	// Forward iterator support
	iterator        begin() const;
	iterator        end() const;

private:
	// Nest our linked-list node
	struct node
	{
		node(const T& val=T(), node* n=0):data(val),link(n) { }
		T           data;
		node*       link;
	};
	node*           head;
	unsigned        used;
	node*           copy(node*);
};

template <typename T>
list<T>::list(){
	used = 0;
	head = 0;
}

template <typename T>
list<T>::~list() {
	node* temp = head;
	while( used > 0 ) {
		head = head->link;
		delete temp;
		temp = head;
		-- used;
	}
}


template <typename T>
list<T>::list( const list<T>& l ){
	node* insNode = l.head;
	while( insNode != 0 ){
		push_front(insNode->data);
	}
}

template <typename T>
list<T>::list( iterator begin, iterator end ){
	used = 0;
	head = 0;
	iterator it = begin;
	while( it != end ){
		this->push_front( *it );
		++ it;
		++ used;
	}
	this->push_front(*it);
}

template <typename T>
list<T>::list( T* begin, T* end ){
	used = 0;
	head = 0;
	push_front( *end );
	push_front( *begin );
}

template <typename T>
const T& list<T>::front() const {
	if( used == 0 )
		throw std::exception(
			std::string("No elements exist in the list.").c_str());
	return head->data;
}

template <typename T>
const typename list<T>::iterator list<T>::find( const T& data ) const {
	iterator it(0);
	for( it = begin();
			it != end();
			++ it ){
		if( (*it) == data )
			return it;
	}
	return it;
}


template <typename T>
void list<T>::push_front( const T& data) {
	typename list<T>::node* temp = new node(data, head);
	head = temp;
	++ used;
}

template <typename T>
void list<T>::pop_front(){
	if ( used == 0 ) return;
	typename list<T>::node* toDel = head;
	head = head->link;
	delete toDel;
	-- used;
}


template <typename T>
typename list<T>::iterator list<T>::find( const T& data ){
	unsigned i = 0;
	node* n = head;
	while( i < used ){
		if( n->data == data )
			break;
		n = n->link;
		++i;
	}
	return iterator( n );
}


template <typename T>
void list<T>::insert(const T& data, unsigned insPos) {
	unsigned currPos = 0;
	node* currNode = head;

	// Special case: Insert at head
	if( insPos == 0 ){
		push_front( data );
		
	// Special case: Insert at end
	} else if ( insPos >= used ){
		while( currNode->link != 0 ){
			currNode = currNode->link;
		}
		currNode->link = new node(data);

	// Normal case: Insert at pos
	} else {
		++ currPos;
		while( currPos < insPos ){
			currNode->link;
			++ currPos;
		}
		currNode->link = new node( data, currNode->link );
	}
	return;

}

template <typename T>
void list<T>::insert_after( iterator it, const T& data ){
	it._node->link = new node( data, it._node->link );
}

template <typename T>
bool list<T>::erase_one( const T& toErase ){
	unsigned pos = 0;
	node* curr = head;
	node* toDel = head;

	// Delete head, special case
	if( curr != 0 && curr->data == toErase ){
		if( curr->link != 0 ){
			curr = curr->link;
		}
		delete toDel;
		-- used;
		return true;
	}
	++ pos;
	toDel = curr->link;
	while( pos < used ){
		if( toDel->data == toErase ){
			curr->link = toDel->link;
			-- used;
			return true;
		}
		++ pos;
		curr = toDel;
		toDel = toDel->link;
	}
	return false;
}

template <typename T>
unsigned list<T>::erase( const T& toErase ){
	unsigned pos = 0;
	unsigned count = 0;
	node* curr = head;
	node* toDel = head;

	// Delete head, special case
	if( curr != 0 && curr->data == toErase ){
		if( curr->link != 0 ){
			curr = curr->link;
		}
		delete toDel;
		-- used;
		++ count;
	}

	++ pos;
	toDel = curr->link;
	while( pos < used ){
		if( toDel->data == toErase ){
			curr->link = toDel->link;
			delete toDel;
			toDel = curr->link;
			-- used;
			++ count;
		} else {
			curr = toDel;
			toDel = toDel->link;
		}
		++ pos;
	}
	return count;
}

template <typename T>
void list<T>::clear() {
	while( used > 0 ){
		pop_front();
	}
}

template <typename T>
typename list<T>& list<T>::operator = (const list<T>& l){
	this->clear();
	iterator it(0);
	for( it = l.begin() ;
			it != l.end();
			++ it ){
				this->push_front(*it);
	}
	push_front(*it);
	used = l.size();
	return *this;
}


template <typename T>
void list<T>::operator += (const list<T>& l){
	//todo
}

template <typename T>
std::ostream& operator << ( std::ostream& out, const list<T>& l ){
	//todo
	return out;
}

template <typename T>
typename list<T>::iterator list<T>::begin() const {
	return iterator( head );
}

template <typename T>
typename list<T>::iterator list<T>::end() const {
	node* temp = head;

	if( temp == 0 )
		return iterator( temp );

	while( temp->link != 0 )
		temp = temp->link;
	return iterator( temp );
}

template <typename T>
typename list<T>::node* list<T>::copy( node* toCopy ) {
	return new node( (*toCopy) );
}

#endif