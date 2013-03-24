#include "stdafx.h"
#include "CppUnitTest.h"
#include <cassert>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "FwLinkedList.h"

namespace list_test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ListCtor){
			list<int> l;
		}

		TEST_METHOD(ListDtor){
			if( true ){
				list<int> l;
				l.push_front(1);
				l.push_front(2);
			}
		}

		
		TEST_METHOD(ListCopyCtor){
			list<int> l1;
			l1.push_front(1);
			list<int> l2(l1);
			Assert::AreEqual( l2.front(), l1.front() );
			Assert::AreEqual( unsigned(1), l2.size() );
			l2.push_front(2);
			l2.push_front(3);
			
			list<int> l3(l2);
			Assert::AreEqual( unsigned(3), l3.size() );

			list<int> l4;
			list<int> l5(l4);
			Assert::AreEqual( unsigned(0), l5.size() );
		}
		
		/*
		TEST_METHOD(ListItItCtor){
			list<int> l1;
			l1.push_front(1);
			l1.push_front(2);
			l1.push_front(3);
			list<int> l2( l1.begin(), l1.end() );
			Assert::AreEqual( l2.front(), l1.front() );
		}
		*/
		
		TEST_METHOD(ListTTCtor){
			int i = 5;
			int j = 8;
			list<int> l1( &i, &j );
			Assert::AreEqual( i, (*l1.begin())  );
			Assert::AreEqual( j, (*l1.end()) );
		}
		

		TEST_METHOD(ListPushPop){
			list<int> l;
			l.push_front(1);
			l.pop_front();
			Assert::AreEqual( l.size(), unsigned(0) );
		}

		TEST_METHOD(ListBegin){
			list<int> l;
			l.push_front(1);
			l.push_front(2);
			FLLNodeIterator<int> it( l.begin() );
			Assert::AreEqual( int(2), (*it) );
		}

		TEST_METHOD(ListEnd){
			list<int> l;
			l.push_front(1);
			l.push_front(2);
			Assert::AreEqual( int(1), (*l.end()) );
		}
		
		TEST_METHOD(ListIterate){
			list<int> l;
			l.push_front(1);
			l.push_front(2);
			l.push_front(3);
			FLLNodeIterator<int> it( l.begin() );
			Assert::AreEqual( int(3), (*it) );
			++ it;
			Assert::AreEqual( int(2), (*it) );
			++ it;
			Assert::AreEqual( int(1), (*it) );
			assert( l.end() == it );
			++ it;
			assert( l.end() == it );
		}
		

		TEST_METHOD(ListErase){
			list<int> l;
			l.push_front(1);
			l.push_front(2);
			l.push_front(2);
			l.push_front(3);
			Assert::AreEqual( l.size(), unsigned(4) );
			// Test erase
			Assert::AreEqual( l.erase(2), unsigned(2) );
			Assert::AreEqual( l.size(), unsigned(2) );
			FLLNodeIterator<int> it = l.begin();
			Assert::AreEqual( (*it), int(3) );
			++ it;
			Assert::AreEqual(  (*it), int(1) );
			// Test erase nothing
			Assert::AreEqual( l.erase(2), unsigned(0) );
		}

		TEST_METHOD(ListEraseOne){
			list<int> l;
			l.push_front(1);
			l.push_front(2);
			l.push_front(2);
			l.push_front(3);
			Assert::AreEqual( l.size(), unsigned(4) );
			// test erase_one
			Assert::IsTrue( l.erase_one(2) );
			Assert::AreEqual( l.size(), unsigned(3) );
			FLLNodeIterator<int> it = l.begin();
			Assert::AreEqual( (*it), int(3) );
			++ it;
			Assert::AreEqual(  (*it), int(2) );
			++ it;
			Assert::AreEqual(  (*it), int(1) );
			// test erase_one for nothing
			Assert::IsFalse( l.erase_one(0) );
		}

		TEST_METHOD(ListFind){
			list<int> l;
			l.push_front(1);
			l.push_front(2);
			l.push_front(3);
			l.push_front(4);
			Assert::AreEqual( (*l.end()), (*l.find(1)) );
			list<int>::iterator it = l.begin();
			Assert::AreEqual( (*it), (*l.find(4)) );
			assert( it == l.find(4) );
			++ it;
			Assert::AreEqual( (*it), (*l.find(3)) );
		}

		TEST_METHOD(ListFront){
			list<int> l;
			l.push_front(1);
			Assert::AreEqual( int(1), l.front() );
			l.push_front(2);
			Assert::AreEqual( int(2), l.front() );
		}

		TEST_METHOD(ListInsert){
			list<int> l;
			l.push_front(1);
			l.push_front(2);
			l.push_front(2);
			l.push_front(3);

			// Normal insert
			l.insert(4,1);
			Assert::AreEqual( int(3), l.front() );
			list<int>::iterator it = l.begin();
			++ it;
			Assert::AreEqual( int(4), (*it) );

			// Same Insert
			l.insert(5,1);
			it = l.begin();
			++ it;
			Assert::AreEqual( int(5), (*it) );

			// Head insert
			l.insert(6,0);
			Assert::AreEqual( int(6), (*l.begin()) );

			// Tail insert
			l.insert(7,l.size());
			Assert::AreEqual( int(7), (*l.end()) );
		}

		TEST_METHOD(ListInsertAfter){
			list<int> l;
			l.push_front(1);
			l.push_front(2);
			l.push_front(2);
			l.push_front(3);

			l.insert_after(l.begin(),4);
			list<int>::iterator it = l.begin();
			++ it;
			Assert::AreEqual( int(4), (*it) );

			l.insert_after(l.end(),5);
			Assert::AreEqual( int(5), (*l.end()) );
		}

		TEST_METHOD(ListSize){
			list<int> l;
			Assert::AreEqual( l.size(), unsigned(0) );
			l.push_front(1);
			Assert::AreEqual( l.size(), unsigned(1) );
			l.push_front(2);
			Assert::AreEqual( l.size(), unsigned(2) );
		}

		TEST_METHOD(ListPlusEqualOp){
			list<int> l;
			l.push_front(1);
			l.push_front(1);
			list<int> m;
			m.push_front(2);
			m.push_front(2);
			l += m;
			Assert::AreEqual( unsigned(4), l.size() );
			Assert::AreEqual( int(1), l.front() );
			Assert::AreEqual( int(2), (*l.end()) );
		}

		TEST_METHOD(ListAssignmentOp){
			list<int> l;
			l.push_front(1);
			l.push_front(1);
			list<int> m;
			m.push_front(2);
			m.push_front(2);
			l = m;
			Assert::AreEqual( unsigned(2), l.size() );
			Assert::AreEqual( int(2), l.front() );
			Assert::AreEqual( int(2), (*l.end()) );
		}

		TEST_METHOD(ListOstream){
			Assert::IsTrue(false);
		}

		TEST_METHOD(ListCopyNode){

		}
	};
}