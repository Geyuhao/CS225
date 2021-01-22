//
//  alist.h
//  
//
//  Created by KD on 14.01.21.
//

#ifndef alist_h
#define alist_h

template<class T> class AList
{
public:
    AList(int size = 20);
//    virtual ~AList();
    T &operator[](int index);
    void pushback (T value);        //four operations
    void pushfront (T value);
    T popback(void);
    T popfront(void);
    void display(void);
    
private:
    int maxsize, minsize;
    int numitems;       //number of elements in list
    //head of queue
    int front;
    //tail+1 position of circular queue
    int rear;
    //circular array
    T * arr;

    void allocate(void);        //allocate when number of elements reached to max
    void deallocate(void);      //deallocate when few elements
};

template<class T> AList<T>::AList(int size)
{
    
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;       //the initial case
    arr = new T [maxsize];
    front = 0;
    rear = 0;
}

//template<class T> AList<T>::~AList()
//{
//    delete[] reprarray;
//}

#endif /* alist_h */
