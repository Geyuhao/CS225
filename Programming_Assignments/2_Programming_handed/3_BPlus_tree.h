#ifndef BPLUS_TREE_H
#define BPLUS_TREE_H
 
#include "3_BPlus_node.cpp"
#include <vector>
using namespace std;
 
enum COMPARE_OPERATOR{LT, LE, EQ, BE, BT, BETWEEN}; // 比较操作符：<、<=、=、>=、>、<>
const int INVALID_INDEX = -1;
 
struct SelectResult
{
	int keyIndex;
	CLeafNode* targetNode;
};
 
class CBPlusTree{
public:
	CBPlusTree(RELATION_TYPE t);
	~CBPlusTree();
	bool insert(KeyType key, const DataType& data);
	bool remove(KeyType key);
	bool update(KeyType oldKey, KeyType newKey);
	KeyType max_key(){return m_MaxKey;}
	// 定值查询，compareOperator可以是LT(<)、LE(<=)、EQ(=)、BE(>=)、BT(>)
	vector<DataType> select_value(KeyType compareKey, COMPARE_OPERATOR compareOpeartor);
	// 范围查询，BETWEEN
	vector<DataType> select_range(KeyType smallKey, KeyType largeKey);
	bool search(KeyType key); // 查找是否存在
	void clear();             // 清空
	void print()const;        // 打印树关键字
	void printData()const;    // 打印数据

	// added functions for bptree
	void update_status(KeyType key, STATUS_TYPE status);
	DataType get_block(KeyType key);
	CLeafNode* get_head(){return m_DataHead;}
private:
	void recursive_insert(CNode* parentNode, KeyType key, const DataType& data);
	void recursive_remove(CNode* parentNode, KeyType key);
	void printInConcavo(CNode *pNode, int count)const;
	bool recursive_search(CNode *pNode, KeyType key)const;
	void changeKey(CNode *pNode, KeyType oldKey, KeyType newKey);
	void search(KeyType key, SelectResult& result);
	void recursive_search(CNode* pNode, KeyType key, SelectResult& result);
	void remove(KeyType key, DataType& dataValue);
	void recursive_remove(CNode* parentNode, KeyType key, DataType& dataValue);
private:
	RELATION_TYPE type;
	CNode* m_Root;
	CLeafNode* m_DataHead;
	KeyType m_MaxKey;  // B+树中的最大键
};

/* 
 * Person_into_BP
 * Input: bptree, local queue
 * Output: None
 * 
 * This Function will store all the people with basic information at registration
 * into the bptree
 */
void Person_into_BP(CBPlusTree* &bptree, queue<People*> &local_queue);



void Regist_into_BP(CBPlusTree* &bptree, queue<People*> &local_queue);
 
#endif

