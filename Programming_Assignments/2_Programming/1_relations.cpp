#include "1_relations.h"


bool Block::search_record(RELATION_TYPE r, KeyType key)
{
    if (r != type)  return false;
    if (r == PERSON) {  // search all person records
        Person_BP* temp = Person_;
        for (int i = 0; i < Records_num; i++, temp = temp->next_person) {
            if (temp->id == key)    return true;
        }
    } else if (r == EDGE) { // search all edge records, might not be used
        Edges* temp = Edges_;
        for (int i = 0; i < Records_num; i++, temp = temp->next_edge) {
            if (temp->length == key)    return true;
        }
    }
    return false;
}


bool Block::insert_record(RELATION_TYPE r, Person_BP* &p, Edges* &e)
{
    if (r != type)  return false;
}