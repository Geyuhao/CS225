#include "6_distance.h"

void Edges_into_BP(queue<People*> local_q, CBPlusTree* &bptree)
{
    vector<People*> temp;
    while (!local_q.empty()) {
        temp.push_back(local_q.front());
        local_q.pop();
    }
    for (int i = 0; i < temp.size(); i++) {
        for (int j = i+1; j < temp.size(); j++) {
            Edges* new_edge = new Edges(temp[i], temp[j]);
            Block* new_block = new Block(EDGE, BLOCK_SIZE);
            new_block->insert_record(new_edge);
            bptree->insert(new_block->get_label(), new_block);
        }
    } return;
}




bool Cluster::search_people(int ID)
{
    for (int i = 0; i < num; i++) {
        if (p[i]->id == ID) return true;
    } return false;
}


bool Cluster::insert_people(Person_BP* n)
{
    if (num >= size || n == NULL)    return false;
    p[num] = n;
    num++;
    return true;
}