//
//  alist.h
//  
//
//  Created by KD on 14.01.21.
//

#ifndef alist_h
#define alist_h
template<class T> class AList;



/* 
 * SRC class defined for structural recursion
 */
template<class T> class SRC
{
public:
    int e;
    SRC(){e = 0;}
    T strcutural_recursion(AList<T> list);
    T func_f(AList<T> list);
    T func_g(T val1, T val2);
};


template<class T> class AList
{
public:
    AList(int size = 20);
//    virtual ~AList();
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(AList<T> &list);
    bool member(T value);
    bool equal(AList<T> &list);
    bool sublist(AList<T> &list);

    //*************** Member functions declaration for HW1 ***********************
    // HW1 Q1.2
    int delete_last(int value);
    // HW1 Q2.4
    void gen_rand(int size);
    template<typename Q> Q strcutural_recursion(AList<T> list ,Q e, Q *func_f(Q val), Q *func_g(Q val1, Q val2));
                                                /*T (SRC<T>::*func_f)(AList<T> list), 
                                                T (SRC<T>::*func_g)(T val1, T val2));*/
    // HW1 Q3.2
    void pushback (T value);        //four operations
    void pushfront (T value);
    T popback(void);
    T popfront(void);
    void display_q3 (void);

    // HW1 Q4
    void display_q4 (void);
    void gen_rand(void);
    void selectionsort(void);
    void insertionsort(void);
    void bubblesort(void);

private:
    int maxsize, minsize;
    int numitems;
    //head of queue
    int front;
    //tail+1 position of circular queue
    int rear;
    //circular array
    T *reprarray;
    void allocate(void);
    void deallocate(void);
};

template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    front = 0;
    rear = 0;
    reprarray = new T[maxsize];
}

//template<class T> AList<T>::~AList()
//{
//    delete[] reprarray;
//}

#endif /* alist_h */
