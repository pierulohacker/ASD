#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED


using namespace std;

template <class Type>
class Node
{
public:

    Node()
    {
        setNext(NULL);
        setFirstSon(NULL);
        setFather(NULL);
        setSonNumber(0);
    }

    Type getValue()
    {
        return value;
    }

    int getLevel()
    {
        return level;
    }

    Node<Type>* getNext()
    {
        return next;
    }

    Node<Type>* getFirstSon()
    {
        return first_son;
    }

    Node<Type>* getFather()
    {
        return father;
    }

    int getSonNumber()
    {
        return son_number;
    }

    int getCurrent()
    {
        return current_son;
    }



    void setValue(Type v)
    {
        value = v;
    }

    void setLevel(int l)
    {
        level = l;
    }
////    FUNZIONI PER ALBERO DINAMICO        ////////////////////////////////////////////////////////////////
    void setNext(Node<Type>* n)
    {
        next = n;
    }

    void setFirstSon(Node<Type>* n)
    {
        first_son = n;
    }

    void setFather(Node<Type>* n)
    {
        father = n;
    }

    void setSonNumber(int n)
    {
        son_number = n;
    }
// Es questo è il figlio numero 3//
    void setCurrent(int n)
    {
        current_son = n;
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    Type value;
    int level;
    /// VARIABILI  UTILIZZATE SOLO DA ALBERO DINAMICO ///
    Node<Type>* next;
    Node<Type>* father;
    Node<Type>* first_son;
    int son_number;
    int current_son;
    //////////////////////////////////////////////////////


};





#endif // NODE_H_INCLUDED
