#include "3_BPlus_tree.cpp"

class cluster
{
public:
    cluster();
    Person_BP* p;
    int size;

    bool search_people(int ID);
    bool insert_people(Person_BP* a);
    int search_treatment(int treat_type);
};

cluster::cluster()
{
    size = 0;
    p = NULL;
}