/*
 *    Robbie Perlstein
 *    101130094
 *    Advanced Programming
 *    Spring 2013
 *    Forward Linked List and Node Iterator
 *    
 *    Unit testing to validate the list and iterator work as expected.
 */

#include "stdafx.h"
#include "CppUnitTest.h"

#include <cassert>
#include <sstream>
#include <ostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "FwLinkedList.h"

namespace list_test
{		
    TEST_CLASS(UnitTest1)
    {
    public:
        
        TEST_METHOD(ListCtor){
            fw_list<int> l;
        }

        TEST_METHOD(ListDtor){
            if( true ){
                fw_list<int> l;
                l.push_front(1);
                l.push_front(2);
            }
        }

        
        TEST_METHOD(ListCtorCopy){
            fw_list<int> l1;
            l1.push_front(1);
            fw_list<int> l2(l1);
            Assert::AreEqual( l2.front(), l1.front() );
            Assert::AreEqual( unsigned(1), l2.size() );
            l2.push_front(2);
            l2.push_front(3);
            
            fw_list<int> l3(l2);
            Assert::AreEqual( unsigned(3), l3.size() );

            fw_list<int> l4;
            fw_list<int> l5(l4);
            Assert::AreEqual( unsigned(0), l5.size() );
        }
        
        TEST_METHOD(ListCtorItIt){
            fw_list<int> l1;
            l1.push_front(1);
            l1.push_front(2);
            l1.push_front(3);
            fw_list<int> l2( l1.begin(), l1.end() );
            Assert::AreEqual( l1.front(), l2.front() );
            Assert::AreEqual( l1.size(), l2.size() );
            
            fw_list<int>::iterator it( l1.begin() );
            ++ it;
            ++ it;
            fw_list<int> l3( l1.begin(), it );
            Assert::AreEqual( l1.front(), l3.front() );

            it = l3.begin();
            ++ it;
            ++ it;
            Assert::AreEqual( int(1), it->data );
            Assert::AreEqual( l1.size(), l3.size() );
        }
        
        TEST_METHOD(ListCtorTT){
            int i = 5;
            int j = 8;
            fw_list<int> l1( &i, &j );
            Assert::AreEqual( i, (*l1.begin())  );
            fw_node_iterator<int> it( l1.begin() );
            ++ it;
            Assert::AreEqual( j, (*it) );
        }
        

        TEST_METHOD(ListPushPop){
            fw_list<int> l;
            l.push_front(1);
            l.pop_front();
            Assert::AreEqual( l.size(), unsigned(0) );
        }

        TEST_METHOD(ListBegin){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_node_iterator<int> it( l.begin() );
            Assert::AreEqual( int(2), (*it) );
        }

        TEST_METHOD(ListEnd){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_list<int> m;
            Assert::IsTrue( m.end() == l.end() );
        }
        
        TEST_METHOD(ListIterate){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            l.push_front(3);
            fw_node_iterator<int> it( l.begin() );
            Assert::AreEqual( int(3), (*it) );
            ++ it;
            Assert::AreEqual( int(2), (*it) );
            ++ it;
            Assert::AreEqual( int(1), (*it) );
            ++ it;
            Assert::IsTrue( l.end() == it );
        }
        

        TEST_METHOD(ListErase){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            l.push_front(2);
            l.push_front(3);
            Assert::AreEqual( l.size(), unsigned(4) );
            // Test erase
            Assert::AreEqual( l.erase(2), unsigned(2) );
            Assert::AreEqual( l.size(), unsigned(2) );
            fw_node_iterator<int> it = l.begin();
            Assert::AreEqual( (*it), int(3) );
            ++ it;
            Assert::AreEqual(  (*it), int(1) );
            // Test erase nothing
            Assert::AreEqual( l.erase(2), unsigned(0) );
        }

        TEST_METHOD(ListEraseOne){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            l.push_front(2);
            l.push_front(3);
            Assert::AreEqual( l.size(), unsigned(4) );
            // test erase_one
            Assert::IsTrue( l.erase_one(2) );
            Assert::AreEqual( l.size(), unsigned(3) );
            fw_node_iterator<int> it = l.begin();
            Assert::AreEqual( (*it), int(3) );
            ++ it;
            Assert::AreEqual(  (*it), int(2) );
            ++ it;
            Assert::AreEqual(  (*it), int(1) );
            // test erase_one for nothing
            Assert::IsFalse( l.erase_one(0) );
        }

        TEST_METHOD(ListFind){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            l.push_front(3);
            l.push_front(4);
            Assert::AreEqual( int(1), (*l.find(1)) );
            fw_list<int>::iterator it = l.begin();
            Assert::AreEqual( (*it), (*l.find(4)) );
            Assert::IsTrue( it == l.find(4) );
            ++ it;
            Assert::AreEqual( (*it), (*l.find(3)) );
        }

        TEST_METHOD(ListFront){
            fw_list<int> l;
            l.push_front(1);
            Assert::AreEqual( int(1), l.front() );
            l.push_front(2);
            Assert::AreEqual( int(2), l.front() );
        }

        TEST_METHOD(ListInsert){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            l.push_front(2);
            l.push_front(3);

            // Normal insert
            l.insert( 4, 1 );
            Assert::AreEqual( int(3), l.front() );
            fw_list<int>::iterator it = l.begin();
            ++ it;
            Assert::AreEqual( int(4), (*it) );

            // Same Insert
            l.insert( 5, 1 );
            it = l.begin();
            ++ it;
            Assert::AreEqual( int(5), (*it) );

            // Head insert
            l.insert( 6, 0 );
            Assert::AreEqual( int(6), (*l.begin()) );

            // Tail insert
            l.insert( 7 , l.size() );
            it = l.begin();
            for( int i = 1; i < l.size(); ++ i ){
                ++ it;
            }
            Assert::AreEqual( int(7), (*it) );
        }

        TEST_METHOD(ListInsertAfter){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            l.push_front(2);
            l.push_front(3);

            l.insert_after( l.begin(), 4 );
            fw_list<int>::iterator it = l.begin();
            ++ it;
            Assert::AreEqual( int(4), (*it) );
        }

        TEST_METHOD(ListSize){
            fw_list<int> l;
            Assert::AreEqual( l.size(), unsigned(0) );
            l.push_front(1);
            Assert::AreEqual( l.size(), unsigned(1) );
            l.push_front(2);
            Assert::AreEqual( l.size(), unsigned(2) );
        }

        TEST_METHOD(ListPlusEqualOp){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(1);
            fw_list<int> m;
            m.push_front(2);
            m.push_front(2);
            l += m;
            Assert::AreEqual( unsigned(4), l.size() );
            Assert::AreEqual( int(1), l.front() );
            fw_list<int>::iterator it = l.begin();
            for( int i = 1; i < l.size(); i ++ ){
                ++ it;
            }
            Assert::AreEqual( int(2), (*it) );
        }

        TEST_METHOD(ListAssignmentOp){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(1);
            fw_list<int> m;
            m.push_front(2);
            m.push_front(2);
            l = m;
            Assert::AreEqual( unsigned(2), l.size() );
            Assert::AreEqual( int(2), l.front() );
            fw_list<int>::iterator it = l.begin();
            for( int i = 1; i < l.size(); i ++ ){
                ++ it;
            }
            Assert::AreEqual( int(2), (*it) );
        }

        TEST_METHOD(ListOstream){
            fw_list<int> l;
            l.push_front(3);
            l.push_front(2);
            l.push_front(1);
            std::stringstream ss;
            ss << l;
            Assert::AreEqual( std::string("{ 1, 2, 3 }"), ss.str() );
        }

        TEST_METHOD(ListCopyNode){
            // TODO figure out where to use copy...
        }

        TEST_METHOD(IterCtor){
            fw_node_iterator<int> it;
        }

        TEST_METHOD(IterCtorCopy){
            fw_list<int> l;
            l.push_front(1);
            fw_node_iterator<int> it( l.begin() );
            Assert::IsTrue( it == l.begin() );

            l.push_front(2);
            Assert::IsTrue( it != l.begin() );
            fw_list<int> m;
            m.push_front(1);
            Assert::IsTrue( it != m.begin() );

            fw_node_iterator<int> it1;
            fw_node_iterator<int> it2(it1);
            Assert::IsTrue( it1 == it2 );
        }

        TEST_METHOD(IterCtorNode){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_node_iterator<int> it1( l.begin() );
            fw_node_iterator<int> it2( it1->link );
            Assert::AreEqual( int(1), it2->data );
        }

        TEST_METHOD(IterAssignmentOp){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_node_iterator<int> it = l.begin();
            Assert::AreEqual( int(2), (*it) );
        }

        TEST_METHOD(IterEqualityOp){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_node_iterator<int> it = l.begin();
            Assert::IsTrue( it == l.begin() );

            fw_list<int> m;
            m.push_front(1);
            m.push_front(2);
            Assert::IsFalse( it == m.begin() );
        }

        TEST_METHOD(IterInequalityOP){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_node_iterator<int> it = l.begin();
            Assert::IsFalse( it != l.begin() );

            fw_list<int> m;
            m.push_front(1);
            m.push_front(2);
            Assert::IsTrue( it != m.begin() );
        }

        TEST_METHOD(IterStarOp){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_node_iterator<int> it = l.begin();
            Assert::AreEqual( int(2), *it );
        }

        TEST_METHOD(IterArrowOp){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_node_iterator<int> it = l.begin();
            Assert::AreEqual( int(2), it->data );
            ++ it;
            Assert::IsTrue( it->link == 0 );
        }

        TEST_METHOD(IterPlusPlusOps){
            fw_list<int> l;
            l.push_front(1);
            l.push_front(2);
            fw_node_iterator<int> it = l.begin();
            Assert::AreEqual( int(2), it->data );
            ++ it;
            Assert::AreEqual( int(1), (*it) );
            it = l.begin();
            Assert::AreEqual( int(2), it->data );
            it ++;
            Assert::AreEqual( int(1), (*it) );
        }
    };
}