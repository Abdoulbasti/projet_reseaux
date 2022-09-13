#ifndef BINARY_TREE_H
#define BINARY_TREE_H

// structure de données principale
typedef struct binary_search_tree_node {
    unsigned int id; 
    void * value;
    struct binary_search_tree_node * left;
    struct binary_search_tree_node * right;
} bst_node_t;

// créer un arbre
bst_node_t * new_bst(unsigned int id, void * value);
// chercher dans l'abre à partir d'un indice
bst_node_t * search(bst_node_t * root, unsigned int id);
// obtenir le minimum dans un arbre
bst_node_t * minimum(bst_node_t * root);
// obtenir le maximum dans un arbre
bst_node_t * maximum(bst_node_t * root);
// insérer un élément dans l'arbre
bst_node_t * insert_bst(bst_node_t *root, unsigned int id, void * value);
// retirer un élément dans l'arbre
bst_node_t * delete_bst(bst_node_t *root, unsigned int id);
// éxécuter une fonction sur chaque élément de l'arbre ( parcours en largeur )
void * bin_loop(bst_node_t * root, void * acc, void * (* loop_fn)(void * acc, bst_node_t * node));

#endif // BINARY_TREE_H