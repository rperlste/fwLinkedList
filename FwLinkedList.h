/*
 *    Robbie Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    Forward Linked List
 *    
 *    Class declaration for a single-ended, singly-linked list with iterator
 *    support. Compatible with C++ STL
 */

#ifndef _FwLinkedList_H
#define _FwLinkedList_H

#include <iostream>
#include <exception>

// Forward declarations for overloading operator <<
template <typename T> class fw_list;
template <typename T> std::ostream& 
                    operator << ( std::ostream&, const fw_list<T>& );

#include "FLLNodeIterator.h"


// Class definition
template <typename T>
class fw_list {
public:
    typedef fw_node_iterator<T> iterator;

    // Constructors
    fw_list();
    fw_list(        const fw_list<T>& );
    fw_list(        iterator, iterator );
    fw_list(        T*, T* );

    ~fw_list();

    // Constant members
    unsigned        size() const { return used; }
    bool            empty() const { return used==0; }
    const T&        front() const;
    const iterator  find( const T& ) const;

    // Modification members
    void            push_front( const T& );
    void            pop_front();
    iterator        find( const T& );
    void            insert( const T&, unsigned );
    void            insert_after( iterator, const T& );
    bool            erase_one( const T& );
    unsigned        erase( const T& );
    void            clear();

    // Operators
    fw_list<T>&     operator =  ( const fw_list<T>& );
    void            operator += ( const fw_list<T>& );

    // Friends
    template<T> friend std::ostream& 
                    operator << ( std::ostream&, const fw_list<T>& );
    friend class    fw_node_iterator<T>;

    // Forward iterator support
    iterator        begin() const;
    iterator        end() const;

private:
    // Nest our linked-fw_list node
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
fw_list<T>::fw_list(){
    used = 0;
    head = 0;
}

template <typename T>
fw_list<T>::~fw_list() {
    node* temp = head;
    while( used > 0 ) {
        head = head->link;
        delete temp;
        temp = head;
        -- used;
    }
}


template <typename T>
fw_list<T>::fw_list( const fw_list<T>& rList ){
    used = 0;
    head = 0;
    *this = rList;
}

template <typename T>
fw_list<T>::fw_list( iterator insIt, iterator last ){
    used = 0;
    head = 0;
    if( insIt != end() ){
        head = new node( insIt->data );
        node* currNode = head;
        ++ insIt;
        ++ used;
        while(    insIt != last
               && insIt != end() ){
            currNode->link = new node( insIt->data );
            currNode = currNode->link;
            ++ insIt;
            ++ used;
        }
        if( insIt != end() ){
            currNode->link = new node( insIt->data, currNode->link );
            ++ used;
        }
    }
}

template <typename T>
fw_list<T>::fw_list( T* begin, T* end ){
    used = 0;
    head = 0;
    push_front( *end );
    push_front( *begin );
}

template <typename T>
const T& fw_list<T>::front() const {
    if( used == 0 )
        throw std::exception(
            std::string("No elements exist in the fw_list.").c_str());
    return head->data;
}

template <typename T>
const typename fw_list<T>::iterator fw_list<T>::find( const T& data ) const {
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
void fw_list<T>::push_front( const T& data) {
    node* temp = new node(data, head);
    head = temp;
    ++ used;
}

template <typename T>
void fw_list<T>::pop_front(){
    if ( used == 0 ) return;
    typename fw_list<T>::node* toDel = head;
    head = head->link;
    delete toDel;
    -- used;
}


template <typename T>
typename fw_list<T>::iterator fw_list<T>::find( const T& data ){
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
void fw_list<T>::insert( const T& data, unsigned insPos ){
    
    // Special case: Insert at head
    if( insPos == 0 || used == 0 ){
        head = new node( data, head );
    }

    // Insert in middle or end
    else {
        unsigned currPos = 1;
        node* currNode = head;
        while(     currNode->link != 0
                && currPos < insPos ){
            currNode = currNode->link;
            ++ currPos;
        }
        currNode->link = new node( data, currNode->link );
    }
    ++ used;
    return;

}

template <typename T>
void fw_list<T>::insert_after( iterator it, const T& data ){
    // End insert
    if( it->link == 0 ) {
         it->link = new node( data );
    } else {
        it->link = new node( data, it->link );
    }
    ++ used;
}

template <typename T>
bool fw_list<T>::erase_one( const T& toErase ){
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
unsigned fw_list<T>::erase( const T& toErase ){
    unsigned count = 0;
    node* curr = head;
    node* toDel = head;

    // Special case: head deletion
    while(     curr != 0
            && curr->data == toErase ){
        toDel = curr;
        curr = curr->link;
        delete toDel;
        ++ count;
        -- used;
    }

    while( curr != 0 ){
        toDel = curr->link;
        if( toDel != 0 ){
            if( toDel->data == toErase ){
                curr->link = toDel->link;
                delete toDel;
                toDel = curr->link;
                ++ count;
                -- used;
            } else {
                curr  = curr->link;
                toDel = curr->link;
            }
        } else {
            break;
        }
    }
    return count;
}

template <typename T>
void fw_list<T>::clear() {
    while( used > 0 ){
        pop_front();
    }
}

template <typename T>
typename fw_list<T>& fw_list<T>::operator = ( const fw_list<T>& rList ){
    this->clear();
    // avoid unnecessary traversal
    if( rList.size() > 0 ){
        node* insNode = rList.head;
        head = new node( insNode->data );
        node* currNode = head;
        insNode = insNode->link;
        while( insNode != 0 ){
            currNode->link = new node( insNode->data );
            currNode = currNode->link;
            insNode = insNode->link;
        }
    }
    used = rList.size();
    return *this;
}

// Warning... not cheap to use!
template <typename T>
void fw_list<T>::operator += ( const fw_list<T>& rList ){
    // avoid unnecessary traversal
    if( rList.size() > 0 ){
        if( head != 0 ){
            node* currNode = head;
            node* insNode = rList.head;
            while( currNode->link != 0 ){
                currNode = currNode->link;
            }
            while( insNode != 0 ){
                currNode->link = new node(insNode->data);
                currNode = currNode->link;
                insNode = insNode->link;
                ++ used;
            }
        }
    }
}

template <typename T>
std::ostream& operator << ( std::ostream& out, const fw_list<T>& rList ){
    out << "{";
    if( rList.size() > 0 ){
        unsigned pos = 0;
        fw_list<int>::iterator it = rList.begin();

        // Write head without comma
        if( it != rList.end() ){
            out << " " << it->data;
            ++ it;
        }
        while( it != rList.end() ){
            out << ", " << it->data;
            ++ it;
        }
    }
    out << " }";
    return out;
}

template <typename T>
typename fw_list<T>::iterator fw_list<T>::begin() const {
    return iterator( head );
}

template <typename T>
typename fw_list<T>::iterator fw_list<T>::end() const {
    return iterator();
}

template <typename T>
typename fw_list<T>::node* fw_list<T>::copy( node* toCopy ) {
    return new node( toCopy->data, toCopy->link );
}

#endif