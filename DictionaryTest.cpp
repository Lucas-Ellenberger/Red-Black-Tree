//-----------------------------------------------------------------------------
// DictionaryTest.cpp
// A test client for Dictionary ADT
// Lucas Ellenberger
// lmellenb
// pa8
//-----------------------------------------------------------------------------

#include<iostream>
#include<fstream>
#include<string>
#include <cstdlib>

#include "Dictionary.h"

using namespace std;

int main(int argc, char** argv) {
    // Tests for constructor
    Dictionary * A = new Dictionary();

    // Trivial tests on empty dictionary
    cout << "Expected: 0" << endl;
    cout << "Actual:   " << A->size() << endl;
    cout << "Expected: false" << endl;
    cout << "Actual:   " << (A->hasCurrent()?"true":"false") << endl;
    cout << "Expected: false" << endl;
    cout << "Actual:   " << (A->contains("big")?"true":"false") << endl;
    
    // Tests for setValue()
    A->setValue("round", 13);
    A->setValue("big", 100);
    A->setValue("super", 50);
    A->setValue("apple", 4);
    A->setValue("car", 88);
    A->setValue("fig", 123);
    A->setValue("sizeable", 20);
    A->setValue("zoo", 98);
    A->setValue("zap", 11);
    A->setValue("zoos", 333);

    // Non-trivial tests
    cout << "Expected: 10" << endl;
    cout << "Actual:   " << A->size() << endl;
    cout << "Expected: false" << endl;
    cout << "Actual:   " << (A->hasCurrent()?"true":"false") << endl;
    cout << "Expected: false" << endl;
    cout << "Actual:   " << (A->contains("ginormous")?"true":"false") << endl;
    cout << "Expected: true" << endl;
    cout << "Actual:   " << (A->contains("big")?"true":"false") << endl;
    // Test for getValue()
    cout << "Expected: 123" << endl;
    cout << "Actual:   " << A->getValue("fig") << endl;

    // Test for contains()

    // Test for begin()
    A->begin();
    cout << "Expected: true" << endl;
    cout << "Actual:   " << (A->hasCurrent()?"true":"false") << endl;
    // Tests for current key and val
    cout << "Expected: apple" << endl;
    cout << "Actual:   " << A->currentKey() << endl;
    cout << "Expected: 4" << endl;
    cout << "Actual:   " << A->currentVal() << endl;

    // Test for next()
    A->next();
    // Tests for current key and val
    cout << "Expected: big" << endl;
    cout << "Actual:   " << A->currentKey() << endl;
    cout << "Expected: 100" << endl;
    cout << "Actual:   " << A->currentVal() << endl;

    A->next();
    // Tests for current key and val
    cout << "Expected: car" << endl;
    cout << "Actual:   " << A->currentKey() << endl;
    cout << "Expected: 88" << endl;
    cout << "Actual:   " << A->currentVal() << endl;

    // Test for end()
    A->end();
    // Tests for current key and val
    cout << "Expected: zoos" << endl;
    cout << "Actual:   " << A->currentKey() << endl;
    cout << "Expected: 333" << endl;
    cout << "Actual:   " << A->currentVal() << endl;

    // Test for prev()
    A->prev();
    // Tests for current key and val
    cout << "Expected: zoo" << endl;
    cout << "Actual:   " << A->currentKey() << endl;
    cout << "Expected: 98" << endl;
    cout << "Actual:   " << A->currentVal() << endl;

    A->prev();
    // Tests for current key and val
    cout << "Expected: zap" << endl;
    cout << "Actual:   " << A->currentKey() << endl;
    cout << "Expected: 11" << endl;
    cout << "Actual:   " << A->currentVal() << endl;

    cout << A->pre_string() << endl;
    cout << (*A) << endl;

    // Test for copy constructor
    Dictionary * B = new Dictionary(*A);
    // cout << "Expected: true" << endl;
    // cout << "Actual:   " << (A==B?"true":"false") << endl;
    cout << (*A) << endl;
    cout << (*B) << endl;

    // Tests for remove()
    B->remove("round");
    cout << "Expected: false" << endl;
    cout << "Actual:   " << (B->contains("round")?"true":"false") << endl;
    // Test to make sure A stays the same
    cout << "Expected: true" << endl;
    cout << "Actual:   " << (A->contains("round")?"true":"false") << endl;
    cout << "Expected: false" << endl;
    cout << "Actual:   " << (A==B?"true":"false") << endl;

    B->remove("zoos");
    cout << "Expected: false" << endl;
    cout << "Actual:   " << (B->contains("zoos")?"true":"false") << endl;
    cout << "Expected: 8" << endl;
    cout << "Actual:   " << B->size() << endl;

    cout << (*B) << endl;
    cout << B->pre_string() << endl;

    // Test for clear
    A->clear();
    cout << "Expected: 0" << endl;
    cout << "Actual:   " << A->size() << endl;
    cout << "Expected: false" << endl;
    cout << "Actual:   " << (A->hasCurrent()?"true":"false") << endl;

    // Test for assignment opperator
    Dictionary C = *B;
    cout << C << endl;
    cout << (*B) << endl;

    // // Tests for equals operator
    // cout << "Expected: true" << endl;
    // cout << "Actual:   " << ((&C) == B?"true":"false") << endl;

    delete A;
    delete B;

    return EXIT_SUCCESS;
}
