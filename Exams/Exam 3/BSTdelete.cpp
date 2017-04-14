void MovieTree::deleteMovieNode(string title) {

    MovieNode * foundMovie = treeSearch(root, title);

    // If the movie exists
    if (foundMovie != NULL)
    {
        // If it has no children
        if (foundMovie->left == leaf && foundMovie->right == leaf)
        {
            // If this node is the left child, set the parents left child to NULL
            if (foundMovie->parent->left == foundMovie)
                foundMovie->parent->left = leaf;
            // Else, this node is the right child, set that to NULL
            else
                foundMovie->parent->right = leaf;
            // Delete the node
            delete foundMovie;

        }
        // If it only has a left child
        else if (foundMovie->right == leaf)
        {
            if (foundMovie->parent->left == foundMovie)
                foundMovie->parent->left = foundMovie->left;
            else
                 foundMovie->parent->right = foundMovie->left;

            delete foundMovie;

        }
        // If it only has a right child
        else if (foundMovie->left == leaf)
        {
            if (foundMovie->parent->left == foundMovie)
                foundMovie->parent->left = foundMovie->right;
            else
                 foundMovie->parent->right = foundMovie->right;

            delete foundMovie;
        }

        // Node has two children, we need the smallest node from the right child
        else
        {
            // Start on the right sub-tree
            MovieNode * replacementNode = foundMovie->right;

            // search for the smallest left child
            while (replacementNode->left != leaf)
            {
                replacementNode = replacementNode->left;
            }

            // Swap in all the info from the replacement to this node we are "deleting"
            foundMovie->title = replacementNode->title;
            foundMovie->quantity = replacementNode->quantity;
            foundMovie->ranking = replacementNode->ranking;
            foundMovie->year = replacementNode->year;


            // If the replacement node has a right child, update the parent
            if (replacementNode->right != leaf)
                replacementNode->right->parent = replacementNode->parent;

            // If the replacement node is a left child
            if (replacementNode->parent->left == replacementNode)
                replacementNode->parent->left = replacementNode->right;
            // If it is a right child
            else
                replacementNode->parent->right = replacementNode->right;

            // Delete the node
            delete replacementNode;
        }
    }
    // If it doesn't exist
    else
        cout << "Movie not found." << endl;


}
