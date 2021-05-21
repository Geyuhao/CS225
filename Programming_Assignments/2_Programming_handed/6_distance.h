#include "5_hash.cpp"

class Cluster
{
public:
    Cluster(int treat_type, int num);
    Person_BP** p;
    int num;
    int size;
    int type;

    bool search_people(int ID);
    bool insert_people(Person_BP* a);
    int search_treatment(int treat_type);
};

Cluster::Cluster(int treat_type, int num)
{

    size = num;
    Person_BP** temp = new Person_BP*[size];
    p = temp;
    type = treat_type;
}


void Edges_into_BP(queue<People*> local_q, CBPlusTree* &bptree);

void Creat_Clusters();