#ifndef NTREE_H_INCLUDED
#define NTREE_H_INCLUDED



using namespace std;

template <class Type, class Position_Type>
class NTree {

public:

	typedef Type 		        value_type;           //Tipo elementi nel NTree
	typedef Position_Type 		position_type;           //Tipo posizioni nel NTree



	// operatori

	//virtual void create() = 0;

	virtual bool empty()  = 0;

	virtual position_type root() = 0;

	virtual void insert_root(value_type) = 0;

	virtual position_type father (position_type)  = 0;

    virtual bool isLeaf(position_type) = 0;

    virtual position_type first_son (position_type)  = 0;

    virtual bool last_brother (position_type)  = 0;

    virtual position_type next_brother(position_type)  = 0;

    //virtual void insert_firt_subtree(position_type, arbero, arbero) = 0;

    //virtual void insert_subtree(position_type, arbero, arbero) = 0;

	virtual void erase_sub_tree (position_type) = 0;

};





#endif // NTREE_H_INCLUDED
