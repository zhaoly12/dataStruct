
data structure

1. list
classes: 
       sequential list
       linked list
       circular linked list
       double list
       double linked list
       static list
       orthogonal linked list
       generalized list
methods:
       initialize a list
       insert an element into a list
       delete an element from a list
       find the index of an element in a list
       find a certain element using its index in a list
       delete a list
       calculate the lenght of a list
       show a list
       check if a list is empty
       merge two lists
       calculate the depth of a list (generalized list)
       calculate the number of atoms in a list (generalized list)
attributions:
       node (node.element, node.prior, node.next)
       node pointer
       rear pointer
       head pointer
       cursor (used in static list)
       right pointer (used in orthogonal linked list)
       down pointer (used in orthogonal linked list)
       generalized list node (generalized node is different from others)

2. stack(a special linear list)
classes:
      sequential stack
      dual stack
      linked stack
methods:
      initialize a stack
      push an element into a stack
      pop an element from a stack
      get an element from a stack
      check if a stack is empty
      check if a stack is full
      clear a stack
attributions:
      element
      top pointer

3. queue(a special linear list)
classes:
      sequential queue
      circular queue
      linked queue
methods:
      initialize a queue
      check if a queue is empty
      check if a queue is full
      enter an element into a queue
      delete an element from a queue
      get an element from a queue
      clear a queue
attributions:
      element
      rear pointer
      front pointer

4. array

5. tree
classes:
      binary tree (special cases: full binary tree, complete binary tree)
      tree(a tree can be changed into a binary tree)
      forest(a forest can be changed into a binary tree)
methods:
      initialize a tree/forest
      check if a tree /forest is empty
      return the root node of a tree(the root of the first tree in a forest)
      return the parent node of a node
      return the child nodes of a node
      return the next sibling of a node
      traverse a tree/forest
      create a tree/forest
      clear a tree/forest
      show a tree/forest
      calculate the number of the leaf nodes of a tree/forest
      calculate the depth of a tree(the deepest tree in a forest)
      add a child tree into a tree
      delete a child tree of a tree
attributions:
      width
      depth
      nodes (root node, leaf nodes, parent node, sibling nodes, child nodes, first/left child tree, right child tree(binary tree))
      node pointers (parent pointer, first/left child pointer, next sibling pointer(tree and forest), right child pointer(binary tree))

6. graph
classes:
methods:
attributions:
