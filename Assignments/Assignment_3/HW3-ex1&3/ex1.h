#ifndef ex1
#define ex1

template<class T> class AList;

template<class T> class AList
{
public:
    AList(int size = 20);
    T &operator[](int index);
    int getlength(void);
    T getitem(int index);
    void append(T value);
    void remove(int index);

    //*************** Member functions declaration for HW1 ***********************
    void display(void);
    void gen_rand(void);
    void find_smallest(void);

private:
    int maxsize, minsize;
    int numitems;
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
    reprarray = new T[maxsize];
}


#endif