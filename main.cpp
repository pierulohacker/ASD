#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "NTree.h"
#include "Dynamic_NTree.h"
#include "Node.h"
#include "ESAME.h"


using namespace std;

int main()
{
 cout << "Alberi Ennari - TEST" << endl;


    Dynamic_NTree<int> tree;
    until_n_tree<int> until;

    tree.insert_root(1);

   // tree.print(tree.root());
    cout << endl;

    tree.insert_first_son(tree.root(), 100);
     tree.insert_son(tree.root(),4);
     tree.insert_son(tree.root(),5);
     tree.insert_son(tree.root(),5);
     tree.insert_son(tree.root(),6);
     tree.insert_first_son(tree.first_son(tree.root()), 99);




 tree.print(tree.root());

 cout<<"Nodi Foglia"<<until.n_leaf(tree)<<endl;


 for (int i = 0; i<6;i++)
 {
      cout<<"TEST NODI A LIVELLO "<< i<<endl;
 cout<< until.n_level(tree,i)<<endl;
 }


    system("pause");
    return 0;
}
