struct point {
	double x, y;
};

/* A vector is an array of points.  N is the number of
   points, and p points to the first point in the array.  */
struct vector {
	int n;
	struct point *p;
};

/* A binary tree of vectors, ordered by KEY.  */
struct tree {
	struct tree *left, *right;
	int key;
	struct vector *vector;
};

/* Return the node in TREE whose key is KEY.
   Return zero if there is no such node.  */
struct tree *find (struct tree *tree, int key)
{
	if (!tree)
		return 0;

	if (key < tree->key)
		return find (tree->left, key);
	else if (key > tree->key)
		return find (tree->right, key);
	else
		return tree;
}

