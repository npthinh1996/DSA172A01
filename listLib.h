/*
 * =========================================================================================
 * Name        : listLib.h
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 1 - Data structures and Algorithms - Spring 2018
 * =========================================================================================
 */

#ifndef A01_LISTLIB_H
#define A01_LISTLIB_H

#include <string>
using namespace std;

class DSAException {
    int     _error;
    string  _text;
public:

    DSAException() : _error(0), _text("Success") {}
    DSAException(int err) : _error(err), _text("Unknown Error") {}
    DSAException(int err, const char* text) : _error(err), _text(text) {}

    int getError() { return _error; }
    string& getErrorText() { return _text; }
};

template <class T>
struct L1Item {
    T data;
    L1Item<T> *pNext;
    L1Item() : pNext(NULL) {}
    L1Item(L1Item<T>* p) : pNext(p) {}
    L1Item(T &a) : data(a), pNext(NULL) {}
    L1Item(T &&a) : data(std::move(a)), pNext(NULL) {}
    L1Item(T &a, L1Item<T> *p) : data(a), pNext(p) {}
};

template <class T>
class L1List {
    L1Item<T>   *_pHead;// The head pointer of linked list
    size_t      _size;// number of elements in this list
public:
    L1List() : _pHead(NULL), _size(0) {}
    ~L1List(){clean();};

    void    clean(){  // * Code
        while(_pHead){
            L1Item<T> *p = _pHead;
            _pHead = _pHead->pNext;
            delete p;
            p = NULL;
        }
    }
    bool    isEmpty() {
        return _pHead == NULL;
    }
    size_t  getSize() {
        return _size;
    }

    T&      at(int i){ // * Code
        if(i < 0 || i > _size) throw -1;
        L1Item<T> *p = _pHead;
        while(i > 0){
            p = p->pNext;
            i--;
        }
        return p->data;
    }
    T&      operator[](int i){  // * Code
        if(i < 0 || i > _size) throw -1;
        L1Item<T> *p = _pHead;
        while(i > 0){
            p = p->pNext;
            i--;
        }
        return p->data;
    }

    bool    find(T& a, int& idx){ // * Code
        L1Item<T> *p = _pHead;
        idx = 0;
        while(p){
            if(p->data == a){
                return true;
            }
            idx++;
            p = p->pNext;
        }
        return false;
    }
    int     insert(int i, T& a){ // * Code
        if(i == 0) return insertHead(a);
        L1Item<T> *pPre = _pHead;
        L1Item<T> *pCur = pPre->pNext;
        while(i > 1){
            i--;
            pPre = pCur;
            pCur = pCur->pNext;
        }
        pPre->pNext = new L1Item<T>(a,pCur);
        return 0;
    }
    int     remove(int i){ // * Code
        if(i == 0) return removeHead();
        L1Item<T> *pPre = _pHead;
        L1Item<T> *pCur = pPre->pNext;
        while(i > 1){
            i--;
            pPre = pCur;
            pCur = pCur->pNext;
        }
        pPre->pNext = pCur->pNext;
        delete pCur;
        pCur = NULL;
        _size--;
        return 0;
    }

    int     push_back(T& a);
    int     insertHead(T& a);
    int     insertHead() {
        _pHead = new L1Item<T>(_pHead);
        _size++;
        return 0;
    }

    int     removeHead();
    int     removeLast();

    void    reverse(){ // * Code
        L1Item<T> *pPre = NULL;
        L1Item<T> *pCur = _pHead;
        L1Item<T> *pNex = NULL;
        while(pCur){
            pNex = pCur->pNext;
            pCur->pNext = pPre;
            pPre = pCur;
            pCur = pNex;
        }
        _pHead = pPre;
    }

    void    traverse(void (*op)(T&)) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data);
            p = p->pNext;
        }
    }
    void    traverse(void (*op)(T&, void*), void* pParam) {
        L1Item<T>   *p = _pHead;
        while (p) {
            op(p->data, pParam);
            p = p->pNext;
        }
    }
};

/// Insert item to the end of the list
/// Return 0 if success
template <class T>
int L1List<T>::push_back(T &a) {
    if (_pHead == NULL) {
        _pHead = new L1Item<T>(a);
    }
    else {
        L1Item<T>   *p = _pHead;
        while (p->pNext) p = p->pNext;
        p->pNext = new L1Item<T>(a);
    }

    _size++;
    return 0;
}

/// Insert item to the front of the list
/// Return 0 if success
template <class T>
int L1List<T>::insertHead(T &a) {
    L1Item<T>   *p = new L1Item<T>(a);
    p->pNext = _pHead;
    _pHead = p;
    _size++;
    return 0;
}

/// Remove the first item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeHead() {
    if(_pHead) {
        L1Item<T>* p = _pHead;
        _pHead = p->pNext;
        delete p;
        _size--;
        return 0;
    }
    return -1;
}

/// Remove the last item of the list
/// Return 0 if success
template <class T>
int L1List<T>::removeLast() {
    if(_pHead) {
        if(_pHead->pNext) {
            L1Item<T>* prev = _pHead;
            L1Item<T>* pcur = prev->pNext;
            while(pcur->pNext) {
                prev = pcur;
                pcur = pcur->pNext;
            }
            delete pcur;
            prev->pNext = NULL;
        }
        else {
            delete _pHead;
            _pHead = NULL;
        }
        _size--;
        return 0;
    }
    return -1;
}

#endif //A01_LISTLIB_H
