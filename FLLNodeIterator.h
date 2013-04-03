/*
 *    Robbie Perlstein
 *    Node Iterator
 *    
 *    Forward iterator for fw_list. Complies with C++ STL.
 */

#ifndef _FLLNodeIterator_H
#define _FLLNodeIterator_H

#include <iterator>

template <typename T>
class fw_node_iterator : public std::iterator 
    <std::forward_iterator_tag, T, std::ptrdiff_t, T*, T&> {

public:
    typedef typename		fw_list<T>::node node;

    fw_node_iterator();
    fw_node_iterator( node* nPtr );
    fw_node_iterator( const fw_node_iterator& );
    ~fw_node_iterator() {}

    // Equality operations
    bool                    operator == ( const fw_node_iterator<T>& it ) const;
    bool                    operator != ( const fw_node_iterator<T>& it ) const;

    // Dereference operations
    T&                      operator * ()  const;
    node*                   operator -> () const;

    // Assign/Change iterator's cursor
    void                    operator ++ ();
    void                    operator ++ ( int );
    void                    operator =  ( const fw_node_iterator<T>& it );

    friend class fw_list<T>;

private:
    node*                   cursor;
};

template <typename T>
fw_node_iterator<T>::fw_node_iterator(){
    cursor = 0;
}

template <typename T>
fw_node_iterator<T>::fw_node_iterator( node* nPtr ){
    cursor = nPtr;
}

template <typename T>
fw_node_iterator<T>::fw_node_iterator( const fw_node_iterator<T>& it ){
    this->cursor = it.cursor;
}

template <typename T>
void fw_node_iterator<T>::operator = ( const fw_node_iterator<T>& it ){
    this->cursor = it.cursor;
}

template <typename T>
bool fw_node_iterator<T>::operator == ( const fw_node_iterator<T>& it ) const {
    return ( this->cursor == it.cursor );
}

template <typename T>
bool fw_node_iterator<T>::operator != ( const fw_node_iterator<T>& it ) const {
    return ( this->cursor != it.cursor );
}

template <typename T>
T& fw_node_iterator<T>::operator * () const {
    return cursor->data;
}

template <typename T>
typename fw_node_iterator<T>::node* fw_node_iterator<T>::operator -> () const {
    return cursor;
}

template <typename T>
void fw_node_iterator<T>::operator ++ () {
    if ( cursor != 0 ){
        cursor = cursor->link;
    }
}

template <typename T>
void fw_node_iterator<T>::operator ++ ( int ) {
    if ( cursor != 0 ){
        cursor = cursor->link;
    }
}

#endif