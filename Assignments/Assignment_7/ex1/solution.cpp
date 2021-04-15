#include "avl.cpp"
#include <vector>

using std::vector;

// your implementation

/*
*   Ex.1 (i)
*   return value:   a pointer to a new list containing the selected elements
*
*   notes:          typically, there are three variants of DFS in trees:
*                                       inorder, postorder and preorder.
*                   choose whichever you like the most.
*/
template<class T> AList<T>* AVL<T>::DFS(void){

    //list which store node traversed
    AList<T>* alist = new AList<T>;

    alist->append(root->getdata());     //root node traversed
    _dfs(root,alist);

    return alist;
};

template<class T> void AVL<T>::_dfs(avlnode<T>* start, AList<T>* alist)
{   
    avlnode<T>* left = start->getleft();        
    avlnode<T>* right = start->getright();

    if (left != NULL)
    {
        alist->append(left->getdata());     
        _dfs(left,alist);       //recursive through left path first
    }

    if (right != NULL)
    {
        alist->append(right->getdata());
        _dfs(right,alist);
    }

    return ;        //if left and right pointer is null, stop
};

/*
*   Ex.1 (ii)
*   return value:   a pointer to a new list containing the selected elements
*
*   notes:          BFS is usually implemented with a FIFO queue, you may
*                   want to make use of that. Typically, when pushing the
*                   children of a node, there are two orders:
*                                   left child first or right child first.
*                   choose whichever you like the most.
*/
template<class T> AList<T>* AVL<T>::BFS(void){

    AList<T>* alist = new AList<T>;
    //fifo queue which store node tempararily
    vector< avlnode<T>* > fifo1;
    
    fifo1.insert(fifo1.begin(),root);   //insert element at back of queue

    while (fifo1.size() != 0)
    {
        //node which is first in(at back of queue)
        avlnode<T>* node = fifo1.back();        
        fifo1.pop_back();
        alist->append(node->getdata());     //append to temprary queue

        avlnode<T>* left = node->getleft();
        avlnode<T>* right = node->getright();

        if (left != NULL)
        {
            fifo1.insert(fifo1.begin(),left);       //append to output queue if not null
        }
        if (right != NULL)
        {
            fifo1.insert(fifo1.begin(),right);
        }

    }
    return alist;
};



/*
*   Ex.1 (iii)
*   return value:   a pointer to a new list containing the selected elements
*/
template<class T> AList<T>* AVL<T>::range(T x, T y){

    // Alist which stores all the element in tree
    AList<T>* new_list = BFS();
    int length = new_list->getlength();
    AList<T>* output_list = new AList<T>;

    for (int i = 1; i<length+1 ; i++)       //loop through each element
    {
        T value = new_list->getitem(i);
        if (value >= x && value <= y)
        {
            output_list->append(value);
        }
    }

    return output_list;
};
