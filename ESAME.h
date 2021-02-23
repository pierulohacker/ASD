#ifndef ESAME_H_INCLUDED
#define ESAME_H_INCLUDED
#include "Dynamic_NTree.h"

template <class _value_type>
class until_n_tree
{
public:

     typedef typename Dynamic_NTree<_value_type>::node node;

     //Numero nodi di T di livello k
    int n_level( Dynamic_NTree< _value_type > &, int );

    //numero foglie albero n-ario
    int n_leaf(   Dynamic_NTree< _value_type > &);




//////////////////////////////////////////////////////////////////////
    //supplementi
    void search_leafs( Dynamic_NTree< _value_type > &, node , int &);

    void search_level(  Dynamic_NTree< _value_type > &, node n, int level, int &count);


    /////////////////////////////////////////////////////////////////////




private:

};

template <class _value_type>
int until_n_tree<_value_type>:: n_leaf( Dynamic_NTree< _value_type > &T)
{
    int n_leafs = 0;

    if(!T.empty())
    {
        search_leafs(T,T.root(),n_leafs);
    }
    return n_leafs;
}

template <class _value_type>
int until_n_tree<_value_type>:: n_level( Dynamic_NTree< _value_type > &T,int k)
{
    int n_node = 0;

    if(!T.empty())
    {
        search_level(T,T.root(),k,n_node);
    }

    return n_node;
}


template<class _value_type>
void until_n_tree<_value_type>::search_leafs( Dynamic_NTree< _value_type > &T, node n, int &count)
{
    if(n == NULL)
    {
        cout<<"Nodo in input non presente"<<endl;
    }
   if(T.isLeaf(n))
    {
        count++;
    }
    else
    {
        node temp = new Node<_value_type>;
        temp = n->getFirstSon();
        search_leafs(T,temp,count);

        while(T.last_brother(temp)!=true)
        {
            temp = (temp->getNext());
            search_leafs(T,temp,count);
        }
    }
}

template<class _value_type>
void until_n_tree<_value_type>::search_level(Dynamic_NTree< _value_type > &T, node n, int level, int &count)
{
    if(T.empty())
    {
        count = 0;
    }

    else if(n != NULL)
    {
        if(n->getLevel() == level)
        {
            cout << "[ " << n->getValue() << " ]"; //usare per i controlli
            count++;
        }
        if(T.isLeaf(n))
        {

        }
        else
        {
            node temp = new Node<_value_type>;
            temp = n->getFirstSon();
            search_level(T,temp,level,count);
            while(T.last_brother(temp)!=true)
            {
                temp = (temp->getNext());
                search_level(T,temp,level,count);

            }
        }
    }

}



#endif // ESAME_H_INCLUDED
