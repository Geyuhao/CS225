#include "1_relations.h"


bool Block::search_record(RELATION_TYPE r, KeyType key)
{
    if (r != type)  return false;
    if (r == PERSON) {  // search all person records
        for (int i = 0; i < Records_num; i++) {
            if (Person_[i]->id == key)    return true;
        }
    } return false;
}


void Block::sort_block()
{
    if (type == PERSON)   return;
    for (int i = 0; i < Overflow_num; i++) {
        Edges_[i+Main_num] = Overflow[i];
    } Main_num += Overflow_num; Overflow_num = 0; Records_num = Main_num + Overflow_num;    // update the counter

    // insertion sort for the main block
    for (int i = 1, j; i < Main_num; i++) {
        int temp = Edges_[i]->length;
		Edges* temp_node = Edges_[i];
        for (j = i; j > 0 && temp < Edges_[j-1]->length; j--){
            Edges_[j] = Edges_[j-1];
        } Edges_[j] = temp_node;
    }
}

// insert function for Person
bool Block::insert_record(Person_BP* &p)
{
    if (PERSON != type)  return false;
    if (search_record(PERSON, p->id))   return false;
    if (Records_num + 1 > size)     return false;

    Person_[Records_num] = p;
    Records_num++;  // update the number
    if (p->id > label)  label = p->id;      // update the label of the block as maximum id
    return true;
}

// insert function for Edge
bool Block::insert_record(Edges* &e)
{
    if (e == NULL)  return false;
    if (EDGE != type)   return false;
    if (Records_num + 1 > size)     return false;
    if (Records_num > 0 && e->Edge_ID != label) return false;

    if (Overflow_num < size/2) {
        Overflow[Overflow_num] = e;
        Overflow_num++;
        Records_num = Main_num + Overflow_num;
        if (e->length > label)  label = e->Edge_ID;
    } else if (Overflow_num >= size/2) {
        sort_block();       // sort all records in overflow into the main block
        Overflow[Overflow_num] = e;     // insert into empty overflow space
        Overflow_num++;
        Records_num = Main_num + Overflow_num;
        if (e->length > label)  label = e->Edge_ID;
    } return true;
}


/*bool Block::remove_record(RELATION_TYPE r, KeyType key)
{
    if (r != type)      return false;
    if (!search_record(r, key))     return false;
    if (Records_num == 0)   return false;

    if (r == PERSON) {
        int index;
        for (int i = 0; i < Records_num; i++) {
            if (Person_[i]->id == key) {
                index = i;
                for (int j = index; j < Records_num; j++) {
                    Person_[j] = Person_[j+1];
                }
                Records_num--;
                return true;
            }
        }
    } else if (r == EDGE) {
        Edges* temp = Edges_;
        for (int i = 0; i < Records_num; i++, temp = temp->next_edge) {
            if (temp->length == key) {
                temp->prev_edge->next_edge = temp->next_edge;
                temp->next_edge->prev_edge = temp->prev_edge;
                temp->next_edge = temp->prev_edge = temp;
                Records_num--;
                return true;
            }
        }
    } return false;
}*/


Block* Block::merge_block(Block* &m_block)
{
    if (Records_num + m_block->record_num() > size) {
        cout << "Space Overflow\n";
        return NULL;
    }
    if (m_block->type != type || type == PERSON) {
        cout << "Type Different\n";
        return NULL;
    }
    if (type == EDGE) {
        m_block->sort_block();      // sort all records in overflow into the main
        for (int i = 0; i < m_block->record_num(); i++) {
            Edges* temp = m_block->Edges_[i];
            insert_record(temp);
        }
        m_block = NULL;
    } return this;
}


Block* Block::split_block()
{
    if (Records_num != size) {
        cout << "Space Remains\n"; return NULL;
    }
    if (type == PERSON) return NULL;

    sort_block();   
    Block* new_block = new Block(EDGE, size);
    for (int i = Records_num/2; i < Records_num; i++) {
        new_block->insert_record(Edges_[i]);
    } 
    Records_num = Records_num - new_block->record_num();
    Main_num = Records_num;
    return new_block;
}


void Block::display_block()
{
    cout << "Size:         " << size << endl;
    cout << "Records:      " << Records_num << endl;
    cout << "Main_num:     " << Main_num << endl;
    cout << "Overflow_num: " << Overflow_num << endl;
    cout << "Label:        " << label << "\n" << endl;
}