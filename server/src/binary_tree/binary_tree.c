#include "binary_tree/binary_tree.h"

/**
 *
 * fonction new_bst id:number value:*
 *
 * crée un noeud à partir d'un nombre (id) et d'un pointeur (value)
 * retourne le noeud créer
 *
 */
bst_node_t *new_bst(unsigned int id, void *value)
{
    bst_node_t *p = malloc(sizeof(bst_node_t));
    p->id = id;
    p->value = value;
    p->left = NULL;
    p->right = NULL;
    return p;
}

/**
 *
 * fonction search root:bst_node_t id:number
 *
 * cherche un noeud à partir d'un nombre (id)
 * retourne le noeud correspondant ( NULL si pas de noeud )
 *
 */
bst_node_t *search(bst_node_t *root, unsigned int id)
{
    // si on trouve l'id on retourne le noeud courant
    if (root == NULL || root->id == id)
        return root;
    // si l'id est supérieur on noeud courant on cherche dans le côté droit de l'arbre
    else if (id > root->id)
        return search(root->right, id);
    // sinon on cherche dans le côté gauche
    else
        return search(root->left, id);
}

/**
 *
 * fonction minimum root:bst_node_t
 *
 * cherche le noeud minimum à partir d'un noeud (root)
 * retourne le noeud minimum
 *
 */
bst_node_t *minimum(bst_node_t *root)
{
    // s'il n'y pas de racine on retourne NULL
    if (root == NULL)
        return NULL;
    // si le noeud courant possède un noeud gauche on retourne le minimum de ce noeud
    else if (root->left != NULL)
        return minimum(root->left);
    // sinon on retourne le noeud courant
    return root;
}

/**
 *
 * fonction maximum root:bst_node_t
 *
 * cherche le noeud maximum à partir d'un noeud (root)
 * retourne le noeud maximum
 *
 */
bst_node_t *maximum(bst_node_t *root)
{
    // s'il n'y pas de racine on retourne NULL
    if (root == NULL)
        return NULL;
    // si le noeud courant possède un noeud droit on retourne le minimum de ce noeud
    else if (root->right != NULL)
        return maximum(root->right);
    // sinon on retourne le noeud courant
    return root;
}

/**
 *
 * fonction insert_bst root:bst_node_t id:number value:*
 *
 * insérer un élémént dans dans l'arbre à partir d'un noeud
 * retourne le noeud racine
 *
 */
bst_node_t *insert_bst(bst_node_t *root, unsigned int id, void *value)
{
    // s'il n'y a pas de racine on crée un nouveau noeud
    if (root == NULL)
        return new_bst(id, value);
    // si l'id est supérieur au noeud courant, on insère dans le noeud droit
    else if (id > root->id)
        root->right = insert_bst(root->right, id, value);
    // si l'id est inférieur au noeud courant, on insère dans le noeud gauche
    else
        root->left = insert_bst(root->left, id, value);
    return root;
}

/**
 *
 * fonction delete_bst root:bst_node_t id:number
 *
 * supprimer un élémént dans dans l'arbre à partir d'un noeud
 * retourne le noeud racine
 *
 */
bst_node_t *delete_bst(bst_node_t *root, unsigned int id)
{
    // s'il n'y pas de racine on retourne NULL
    if (root == NULL)
        return NULL;
    // si l'id est supérieur au noeud courant, on supprime dans le noeud droit
    if (id > root->id)
        root->right = delete_bst(root->right, id);
    // si l'id est inférieur au noeud courant, on supprime dans le noeud gauche
    else if (id < root->id)
        root->left = delete_bst(root->left, id);
    // supprimer le noeud trouvé
    else
    {
        // cas pas de fils
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }
        // cas 1 fils
        else if (root->left == NULL || root->right == NULL)
        {
            bst_node_t *tmp;
            if (root->left == NULL)
                tmp = root->right;
            else
                tmp = root->left;
            free(root);
            return tmp;
        }
        // cas 2 fils
        else
        {
            bst_node_t *tmp = minimum(root->right);
            root->id = tmp->id;
            root->value = tmp->value;
            root->right = delete_bst(root->right, tmp->id);
        }
    }
    return root;
}

/**
 *
 * fonction bin_loop root:bst_node_t acc:* loop_fn:*
 *
 * éxécuter la fonction loop_fn sur chaque élément de l'arbre à partir d'un noeud
 * retourne le pointer de l'accumulateur utilisé
 * 
 */
void *bin_loop(bst_node_t *root, void *acc, void *(*loop_fn)(void *acc, bst_node_t *node))
{
    if (root != NULL) // checking if the root is not null
    {
        acc = bin_loop(root->left, acc, loop_fn); // visiting left child
        acc = loop_fn(acc, root);
        acc = bin_loop(root->right, acc, loop_fn); // visiting right child
    }
    return acc;
}