#ifndef DYNAMIC_NTREE_H_INCLUDED
#define DYNAMIC_NTREE_H_INCLUDED
#include "NTree.h"
#include"Node.h"

template <class Type>
class Dynamic_NTree : public NTree <Type, Node<Type>* >
//class Dynamic_NTree : public until_n_tree <Type >
{

public:

    typedef typename NTree <Type,Node<Type>*>:: value_type value_type;
    //Agiamo direttamente su nodi e non su posizioni//
    typedef Node<Type>* node;

    Dynamic_NTree(); //costruttore

    ~Dynamic_NTree(); //distruttore

    // OPERATORI  /////////////////////////////////////////////////////////////////////////////
    bool empty();

    //restituisce la radice dell'albero
    node root();

    //inserimento di una radice in albero vuoto dandogli direttamente il valore da assumere
    void insert_root(value_type);

//posizione del padre di un nodo in input
    node father (node);

    //il nodo in input è una foglia?
    bool isLeaf(node);

    //restituisce il primo figlio del nodo inserito
    node first_son (node);

// il nodo in input è l'ultimo dei figli?
    bool last_brother (node);

    //dato un nodo, avremo suo fratello appena successivo (se  l'input non è l'ultimo figlio)
    node next_brother(node);

//come PRIMO figlio di un nodo in input, avrò un nuovo sotto albero preso in input
    void insert_first_subtree(node, Dynamic_NTree<Type>&);

    //come  figlio (MAI PRIMO) di un nodo in input, avrò un nuovo sotto albero preso in input
    void insert_subtree(node,Dynamic_NTree<Type>&);

    //dato un nodo padre, inserisco un PRIMO FIGLIO avente il valore preso in input
    void insert_first_son(node, value_type);

    //dato un nodo padre, inserisco un figlio (MAI PRIMO)  avente il valore preso in input
    void insert_son(node, value_type);   //mai primo figlio

    //dato un nodo, rimuovo dall'albero tutto il sotto albero avente tale nodo come radice
    void erase_sub_tree (node);

    //lettura del valore di un nodo preso in input
    value_type read(node);

    //dato un nodo, ne sovrascrivo il contenuto
    void write ( node, value_type );


////ALGORITMO DI VISITA UTILE PER VARIE SITUAZIONI///
    void visita(node);

/////////////////////////////////////////////////////////////////////////////////////////////
    /// //FUNZIONI DI SERIVIZIO //////////////////////////////

    //aggiornamento dell'altezza (NON UTILE NEL MAIN)
    void change_height(int h)
    {
        if(h > height)
        {
            height = h;
        }
    }

    //ricalcolo del livello (in seguito ad unioni di alberi etc)
    void reset_level(node);

    int size()
    {
        return node_number;
    }

// restituisce l'altezza corrente dell'albero, utile per test ma deve essere soggetta ad aggiornamenti
    int getHeight()
    {
        return height;
    }

    //conta i nodi dell'albero
    int node_counter (node);

//iteratore dei nodi per settare la loro quantità etc.
    void node_iterator(node);

    //nodo di un sotto alberto in input, e restituisce la profondità di questo sottoalbero
    int deepness (node, int);

    //calcola l'altezza di un albero
    int height_counter(node);

 //stampa di tutti i nodi  per livello, a partire dal nodo in input
    void print(node);

   //CHIAMATA DA PRINT per la stampa a livelli
    void print_level(node,int);

    //trova il valore in input nell'albero con radice uguale al nodo preso in input
    node search_value(node,value_type);

    void print_Leafs(node n);

    //restituisce la larghezza dell'albero
    int get_width();

    //iteratore richiamato da tree_width
    void width_iterator(node, int,int &);

    void getCount ()
    {
        return count;
    }

///////////////////////////////////////////////////////////////////////////////////
private:
    int height;
    int node_number;  //quantità di nodi presenti
    node tree ; // puntatore alla radice
    int count;  //contatore di nodi

};
////  COSTRUTTORE
template<class Type>
Dynamic_NTree<Type>::Dynamic_NTree()
{
    tree = new Node<Type>;
    height = 0;
    count = 1;
    node_number = 0;
    tree->setLevel(0);
}

/// DISTRUTTORE
template<class Type>
Dynamic_NTree<Type>::~Dynamic_NTree()
{
    delete tree;
}


//////////////////   OPERATORI      ////////////////////////////////////
template<class Type>
bool Dynamic_NTree<Type>::empty()
{
    return (node_number == 0);
}

//creazione di una radice in un albero vuoto
template<class Type>
void Dynamic_NTree<Type>::insert_root(value_type a)
{
    if(empty())
    {
        node_number++;
        height = 0;
        tree->setLevel(0);
        write(root(),a);
    }
    else
    {
        cout<<"UNA RADICE GIA' PRESENTE. EVENTUALMENTE CANCELLARE E CREARE NUOVAMENTE"<<endl;
    }
}

//restiruisce il nodo radice,
template<class Type>
typename Dynamic_NTree<Type>::node Dynamic_NTree<Type>::root()
{
    if (tree != NULL)
    {
        return (tree);
    }
    else
    {
        cout<<"ALBERO VUOTO //(root)//"<<endl;
        throw "ALBERO VUOTO //(root)//" ;
    }
}

//posizione del padre di un nodo
template<class Type>
typename Dynamic_NTree<Type>::node Dynamic_NTree<Type>::father (node p)
{

    if (!empty() && p != NULL)
    {
        return p->getFather();
    }
    else if (p == root())
    {
        cout <<" IL NODO INSERITO E' LA RADICE DELL'ALBERO - non può avere un nodo padre //(father)//"<<endl;
        throw "NODO INSERITO = RADICE //(father)//" ;
    }
    else
    {
        cout<<"FIGLIO INSERITO NON ESISTENTE //(father)//"<<endl;
        throw "FIGLIO INSERITO NON PRESENTE //(father)//" ;
    }
}

// il nodo inserito è una foglia?
template<class Type>
bool Dynamic_NTree<Type>::isLeaf(node n)
{
    if(n != NULL)
    {
        return (n->getFirstSon() == NULL);
    }
    else
    {
        cout<<"FIGLIO INSERITO NON ESISTENTE (isleaf)"<<endl;
        throw "FIGLIO INSERITO NON PRESENTE (isleaf)" ;
    }
}


//restituisce il primo figlio del nodo inserito
template<class Type>
typename Dynamic_NTree<Type>::node Dynamic_NTree<Type>::first_son (node p)
{

    if (isLeaf(p) == false)
    {
        return p->getFirstSon();
    }
    else
    {
        cout<<"PRIMO FIGLIO NON PRESENTE - il nodo inserito è una foglia //(first_son)//"<<endl;
        throw "PRIMO FIGLIO NON PRESENTE - il nodo inserito è una foglia //(first_son)//" ;
    }
}


template<class Type>
bool Dynamic_NTree<Type>::last_brother(node p)
{
    if(p!= NULL)
    {
        return (p->getNext() == NULL);
    }
    else
    {
        cout<<"POSIZIONE INSERITA NON PRESENTE //(last_brother)//"<<endl;
        throw "POSIZIONE INSERITA NON PRESENTE //(last_brother)//";
    }
}

template<class Type>
typename Dynamic_NTree<Type>::node Dynamic_NTree<Type>::next_brother(node p)
{
    if (!last_brother(p))
    {
        return p->getNext();
    }
    else
    {
        cout<<"FRATELLO SUCCESSIVO NON PRESENTE //(next_brother)//"<<endl;
        throw "FRATELLO SUCCESSIVO NON PRESENTE //(next_brother)//" ;
    }
}




template<class Type>
void Dynamic_NTree<Type>::insert_first_son(node p, value_type a)
{
    node temp = new Node<Type>;
    if (!empty() && p != NULL && isLeaf(p) == true) //il nodo deve esistere e non deve avere figli
    {
        temp->setValue(a);
        temp->setLevel(p->getLevel() + 1);
        temp->setFather(p);
        p->setFirstSon(temp);
        p->setSonNumber(1);
        temp->setCurrent(1);

        node_number ++ ;
        change_height( temp->getLevel());

        //height = height_counter(root());
    }
    else if(p == NULL)
    {
        cout<<"NODO IN INPUT (padre) NON PRESENTE //(insert_first_son)//"<<endl;
    }
    else if(!isLeaf(p))
    {
        cout<<"NODO IN INPUT (padre) HA GIA' UN PRIMO FIGLIO //(insert_first_son)//"<<endl;
    }
    else if(empty())
    {
        cout<<"ALBERO VUOTO //(insert_first_son)//"<<endl;
    }

}

template<class Type>
void Dynamic_NTree<Type>::insert_son(node p, value_type a)
{

    node temp = new Node<Type>;
    node temp1= new Node<Type>;

    if (p != NULL && isLeaf(p) == false) //il nodo deve esistere  deve avere figli
    {
        temp->setValue(a);
        temp->setLevel(p->getLevel() + 1);
        temp->setFather(p);
        temp1 = p->getFirstSon();
        //mi sposto fino all'ultimo figlio, partendo dal primo
        while (temp1->getNext() != NULL)
        {
            cout<<"cerco ultimo fratello"<<endl;
            temp1 = temp1->getNext();

        }
        temp1->setNext(temp);
        temp->setCurrent(temp1->getCurrent() + 1);
        p->setSonNumber(p->getSonNumber() + 1);

        node_number ++ ;
    }
    else if(p == NULL)
    {
        cout<<"NODO IN INPUT (padre) NON PRESENTE //(insert_son)//"<<endl;
    }
    else
    {
        cout<<"NODO IN INPUT (padre) NON HA  UN PRIMO FIGLIO //(insert_son)//"<<endl;
    }
}


template <class Type>
void Dynamic_NTree<Type>::insert_first_subtree(node u, Dynamic_NTree<Type> &T)
{
    if(u != NULL)
    {
        u->setFirstSon(T.root());
        u->setSonNumber(1);
        T.root()->setLevel(u->getLevel() + 1);
        T.root()->setCurrent(1);
        T.root()->setFather(u);
        T.root()->setNext(NULL);

        height = height_counter(root()); //ricalcolo l'altezza dell'arbero
        node_number = node_counter(root()); //ricalcolo il numero dei nodi dell'arbero
        reset_level(root());
    }

}

template <class Type>
void Dynamic_NTree<Type>::insert_subtree(node u, Dynamic_NTree<Type> &T)
{

node temp1= new Node<Type>;

    if (u != NULL && isLeaf(u) == false) //il nodo deve esistere e  deve avere figli
    {
        T.root()->setLevel(u->getLevel() + 1);
        T.root()->setFather(u);
        temp1 = u->getFirstSon();
        //mi sposto fino all'ultimo figlio, partendo dal primo
        while (temp1->getNext() != NULL)
        {
            cout<<"cerco ultimo fratello"<<endl;
            temp1 = temp1->getNext();
        }
        temp1->setNext(T.root());
        T.root()->setCurrent(temp1->getCurrent() + 1);
        u->setSonNumber(u->getSonNumber() + 1);
    }
    else if(u == NULL)
    {
        cout<<"NODO IN INPUT (padre) NON PRESENTE //(insert_subtree)//"<<endl;
    }
    else
    {
        cout<<"NODO IN INPUT (padre) NON HA  UN PRIMO FIGLIO //(insert_subtree)//"<<endl;
    }

}

template<class Type>
void Dynamic_NTree<Type>::erase_sub_tree(node n)
{
    if(n == root())
    {
        delete tree;
        node_number = 0;
        height = 0;
        count = 0;
    }
    else if(n != NULL)
    {
        if(isLeaf(n))
        {

        }
        else
        {

            node temp = new Node<Type>;
            temp = n->getFirstSon();
            erase_sub_tree(temp);
            while(last_brother(temp)!=true)
            {
                temp = (temp->getNext());
                erase_sub_tree(temp);
            }
        }
        n->getFather()->setSonNumber(n->getFather()->getSonNumber() - 1);
        n->getFather()->setFirstSon(n->getNext());
        node_number--;
        count--;
        delete n;
        height = height_counter(root());
    }
}

template<class Type>
int Dynamic_NTree<Type> ::deepness(node n, int h)
{
    if(isLeaf(n))
    {
        h =0;
    }
    else
    {
        node temp = new Node<Type>;
        temp = n->getFirstSon();
        h = deepness(temp, h);

        while(last_brother(temp)!=true)
        {
            temp = (temp->getNext());
            int res = deepness(temp, h);


            if(res > h)
            {
                h = res;
            }
        }

    }
    return (h+1);
}

template<class Type>
int Dynamic_NTree<Type> :: height_counter(node n)
{

    int h = 0;
    h = deepness(n,h);

    return h - 1;
}


//restituisce valore presente nel nodo in quella posizione
template<class Type>
typename Dynamic_NTree<Type>::value_type Dynamic_NTree<Type>::read (node p)
{

    if(p != NULL)
    {
        return (p->getValue());
    }
    else
    {
        cout<<"POSIZIONE IN INPUT NON PRESENTE NELL'ALBERO"<<endl;
        throw "POSIZIONE IN INPUT NON PRESENTE NELL'ALBERO";
    }

}


// sovrascrittura dell'elemento nel nodo
template<class Type>
void Dynamic_NTree<Type>::write ( node p, value_type a )
{
    if(!empty() && p!= NULL) //il nodo deve essere scrivibile
    {
        p->setValue(a);      // sovrascrivo il valore del nodo
    }
}


/*template <class Type>
void Dynamic_NTree<Type>::costrNTree(Dynamic_NTree<Type> &t1, Dynamic_NTree<Type> &t2) //importante l'ordine di inserimento
{
    node temp1 = new Node<Type>;
    //node temp2 = new Node<Type>;

    tree->setLeft(t1.root());
    tree->setRight(t2.root());

    t1.root()->setFather(tree);
    t2.root()->setFather(tree);

    temp1->setLevel(0);
    tree->setFather(temp1);
    reset_level(root());
    tree->setFather(NULL);
    delete temp1;

    node_number = node_counter(root());
}
*/

template<class Type>
int Dynamic_NTree<Type> ::  node_counter (node n)
{
    count  = 0;
    node_iterator(n);
    return count;
}


template<class Type>
void Dynamic_NTree<Type> :: node_iterator(node n)
{
    if(n != NULL)
    {
        count++;
        if(isLeaf(n))
        {

        }
        else
        {
            node temp = new Node<Type>;
            temp = n->getFirstSon();
            node_iterator(temp);
            while(last_brother(temp)!=true)
            {
                temp = (temp->getNext());
                node_iterator(temp);

            }
        }
    }
}



template<class Type>
void Dynamic_NTree<Type> :: reset_level(node n)
{
    if(n != NULL)
    {
        if(n == root())
        {
            n->setLevel(0);
        }
        else
        {
            //print(root());
            n->setLevel(n->getFather()->getLevel() + 1);
        }
        if(isLeaf(n))
        {

        }
        else
        {

            node temp = new Node<Type>;
            temp = n->getFirstSon();
            reset_level(temp);
            while(last_brother(temp)!=true)
            {
                temp = (temp->getNext());
                reset_level(temp);

            }
        }
    }
}
/////////////////////////////////////////////////////FINE TODO///////////////////////////////

/*
template<class Type>
void Dynamic_NTree<Type>::print(node n)
{
    if(n != NULL)
    {
        cout << "Valore(fuori): " << n->getValue() << endl; //STAMPA IN PREORDINE
        if(isLeaf(n))
        {

            //cout << "(isLeaf) Valore: " << n->getValue() << endl;  //STAMPA SOLO LE FOGLIE
        }
        else
        {
            node temp = new Node<Type>;
            temp = n->getFirstSon();
            //cout << "(else )Valore: " << temp->getValue() << endl;
            print(temp);

            while(last_brother(temp)!=true)
            {

                //cout << "(while)Valore: " << temp->getValue() << endl;
                temp = (temp->getNext());
                print(temp);
            }
            //  cout << "Valore (dopo while): " << n->getValue() << endl;

        }
        //cout << "Valore(fuori): " << n->getValue() << endl;
        //return (h+1);
    }
}
*/
template<class Type>
void Dynamic_NTree<Type>::print_level(node n, int level)
{
    if(empty())
    {
        cout << "[ - ]";
    }

    else if(n != NULL)
    {
        if(n->getLevel() == level)
        {
            cout << "[ " << n->getValue() << " ]"; //STAMPA IN PREORDINE
        }
        if(isLeaf(n))
        {

        }
        else
        {

            node temp = new Node<Type>;
            temp = n->getFirstSon();
            print_level(temp,level);
            while(last_brother(temp)!=true)
            {
                temp = (temp->getNext());
                print_level(temp,level);

            }
        }
    }

}

template<class Type>
void Dynamic_NTree<Type>::print(node n)
{
    node temp = new Node<Type>;
    int level = n->getLevel();
    int deep =  height_counter(n);

    temp = n;
    for(int i = level; i <= deep; i++)
    {
        print_level(temp,i);
        cout << endl;
    }
}

template<class Type>
typename Dynamic_NTree<Type>::node Dynamic_NTree<Type>::search_value(node n, value_type a)
{
    if(n != NULL)
    {
        node temp1 = new Node<Type>;
        if(n->getValue() == a)
        {
            cout << "trovato: " << n->getValue() << endl;
            //temp1 = n;
        }
        if(isLeaf(n))
        {

        }
        else
        {

            node temp = new Node<Type>;
            temp = n->getFirstSon();
            search_value(temp,a);
            while(last_brother(temp)!=true)
            {

                temp = (temp->getNext());
                search_value(temp,a);

            }
        }
        //  return temp1;
    }
    else
    {
        cout << "IL NODO INSERITO NON È VALIDO //(search_value)//" << endl;
        throw"IL NODO INSERITO NON È VALIDO //(search_value)//";
    }
    //return temp1;

}


template<class Type>
void Dynamic_NTree<Type>::print_Leafs(node n)
{
    if(n == NULL)
    {
        cout<<"NODO IN INPUT NON ALLOCATO"<<endl;
    }
    if(isLeaf(n))
    {
        cout << "(isLeaf) Valore: " << n->getValue() << endl;  //STAMPA SOLO LE FOGLIE
    }
    //inizio a spostarmi sulle foglie
    else
    {
        node temp = new Node<Type>;
        temp = n->getFirstSon();
        print_Leafs(temp);

        while(last_brother(temp)!=true)
        {
            temp = (temp->getNext());
            print_Leafs(temp);
        }
    }
}
//

template<class Type>
int Dynamic_NTree<Type> ::get_width() //viene invocata da un oggetto albero
{
    int maxLevel = 0;
    int  node_counter = 0;
    int width = 0;
    int level = 0;
    maxLevel = height_counter(root());
    cout<<"entro nel for (get widht)"<<endl;
    for(int i = 0; i < maxLevel; i++)
    {
        node_counter = 0;
        cout<<"for: "<< i <<endl;
        width_iterator(root(),  level, node_counter);
        level++;
        if(node_counter > width)
        {
            width = node_counter;
        }
    }

    return (width);
}

//larghezza albero = maggior numero di nodi su uno stesso albero
template<class Type>
void Dynamic_NTree<Type> ::width_iterator(node n, int level,int & nodeN)
{
    if(n != NULL)
    {
        if(n->getLevel() == level)
        {
            nodeN ++;
        }
        if(isLeaf(n))
        {

        }
        else
        {

            node temp = new Node<Type>;
            temp = n->getFirstSon();
            width_iterator(temp,level,nodeN);

            while(last_brother(temp)!=true)
            {
                temp = (temp->getNext());
                width_iterator(temp,level,nodeN);

            }
        }
    }

    cout<<"Nodi  a questo livello: "<<  nodeN<<endl;
}

#endif // DYNAMIC_NTREE_H_INCLUDED
