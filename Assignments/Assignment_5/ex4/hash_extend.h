

template<class T> class HashSet_LCFS{
    /* Refer to the given code to design the new hashset */
public:
    HashSet_LCFS(int size = 20);
    T &operator[](int index);

    void insert(T item);
    int member(T item);
    void remove(T item);
    void display();

private:
    void rehash(int newsize);
    int numitems;
    int maxsize;
    T** reprarray;
    T* place_hld;

};

template<class T> class HashSet_RH{
    /* Refer to the given code to design the new hashset */
public:
    HashSet_RH(int size = 20);
    T &operator[](int index);


    void insert(T item);
    int member(T item);
    void remove(T item);
    void display();



private:
    void rehash(int newsize);
    int numitems;
    int maxsize;
    T** reprarray;
    T* place_hld;
};