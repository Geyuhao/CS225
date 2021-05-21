#ifndef BPLUS_NODE
#define BPLUS_NODE
 
//#define NULL 0
#include "1_relations.cpp" 


enum NODE_TYPE{INTERNAL, LEAF};        // 结点类型：内结点、叶子结点
enum SIBLING_DIRECTION{LEFT, RIGHT};   // 兄弟结点方向：左兄弟结点、右兄弟结点


// With overflow block added, following modifications are needed:
	// Search: when recursive to leaf node, linear search is needed in overflow block
	// Insert: when leaf node is not full, added into the overflow block first
	//		   when leaf is full after adding the data, sort the elements into the main block
	// Remove: when no merge needed, sort the targeted leaf node and remove
	//		   when merge needed after remove, sort both targeted leaf and siblings then remove
	// 


// 结点基类
class CNode{
public:
	CNode();
	virtual ~CNode();
 
	NODE_TYPE getType() const {return m_Type;}
	void setType(NODE_TYPE type){m_Type = type;}
	int getKeyNum() const {return m_KeyNum;}
	void setKeyNum(int n){m_KeyNum = n;}
	KeyType getKeyValue(int i) const {return m_KeyValues[i];}
	void setKeyValue(int i, KeyType key){m_KeyValues[i] = key;}
	int getKeyIndex(KeyType key)const;  // 找到键值在结点中存储的下标
	// 纯虚函数，定义接口
	virtual void removeKey(int keyIndex, int childIndex)=0;  // 从结点中移除键值
	virtual void split(CNode* parentNode, int childIndex)=0; // 分裂结点
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex)=0;  // 合并结点
	virtual void clear()=0; // 清空结点，同时会清空结点所包含的子树结点
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d)=0; // 从兄弟结点中借一个键值
	virtual int getChildIndex(KeyType key, int keyIndex)const=0;  // 根据键值获取孩子结点指针下标
protected:
	NODE_TYPE m_Type;		// denote whether it is internal node or leaf node
	int m_KeyNum;			// keys in the block
	KeyType m_KeyValues[MAXNUM_KEY];	// Key_Values for the B+ node will be the ID of the person
};
 
// 内结点
class CInternalNode : public CNode{
public:
	CInternalNode();
	virtual ~CInternalNode();
 
	CNode* getChild(int i) const {return m_Childs[i];}
	void setChild(int i, CNode* child){m_Childs[i] = child;}
	void insert(int keyIndex, int childIndex, KeyType key, CNode* childNode);
	virtual void split(CNode* parentNode, int childIndex);
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex);
	virtual void removeKey(int keyIndex, int childIndex);
	virtual void clear();
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d);
	virtual int getChildIndex(KeyType key, int keyIndex)const;
private:
	CNode* m_Childs[MAXNUM_CHILD];
};
 
// 叶子结点
class CLeafNode : public CNode{
public:
	CLeafNode();
	virtual ~CLeafNode();
  
	CLeafNode* getLeftSibling() const {return m_LeftSibling;}
	void setLeftSibling(CLeafNode* node){m_LeftSibling = node;}
	CLeafNode* getRightSibling() const {return m_RightSibling;}
	void setRightSibling(CLeafNode* node){m_RightSibling = node;}
	DataType getData(int i) const {return m_Datas[i];}
	void setData(int i, const DataType& data){m_Datas[i] = data;}
	void insert(KeyType key, const DataType& data);
	virtual void split(CNode* parentNode, int childIndex);
	virtual void mergeChild(CNode* parentNode, CNode* childNode, int keyIndex);
	virtual void removeKey(int keyIndex, int childIndex);
	virtual void clear();
	virtual void borrowFrom(CNode* destNode, CNode* parentNode, int keyIndex, SIBLING_DIRECTION d);
	virtual int getChildIndex(KeyType key, int keyIndex)const;
	// added function for the required overflow block
	bool check_merge(int keyindex1, int keyindex2);
	DataType merge_blocks(int keyindex1, int keyindex2);

private:
	CLeafNode* m_LeftSibling;
	CLeafNode* m_RightSibling;
	DataType m_Datas[MAXNUM_LEAF];		// the data for each leaf node should be pointers pointing out to blocks
};
#endif

