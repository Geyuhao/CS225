/* Put your decleration here */
template<class T> class item_node;
template<class T> class ch_node;


template<class T> class MultiSet{
    public:
        MultiSet(int size = 20);
        /* You should add other functions to make the structure work  */
        /* The following is required for this assignment */
        /* It is not complete, you should design the APIs by yourself */
        void insertion(T item);
        void deletion(T item);
        item_node<T>* retrieval(T item);
        void rehash(int newsize);

        void setunion(MultiSet<T> sets);
        void intersection(MultiSet<T> sets);
        MultiSet<T> difference(MultiSet<T> sets);
        void display(void);

    //private:
        int numitems;
        item_node<T> **reprarray;
        item_node<T> *pt_nil;              // used as placeholder
        int maxsize;            // defines the size of the hashtable

};

template<class T> class item_node{
    public:
        item_node(T item);
        int multiplicity;
        T value;
};

template<class T> class ch_node{
    public:
        ch_node(T item);
        T value;
        ch_node<T> *pointer_next;
};





template<class T> class MultiSet_Chaining{
    public:
        MultiSet_Chaining(int size = 20);
        /* You should add other functions to make the structure work  */
        /* The following is required for this assignment */
        /* It is not complete, you should design the APIs by yourself */
        void insertion(T item);
        void deletion(T item);
        T retrieval(T item);

        void setunion(MultiSet_Chaining<T> sets);
        void intersection(MultiSet_Chaining<T> sets);
        void difference(MultiSet_Chaining<T> sets);
        void display_chaining(void);

    private:
        int maxsize;
        int numitems;
        ch_node<T> **reprarray;

};
