/*
Write a C++ function to determine if the distance to any vertex is less than the
edge weight to the next adjacent vertex visited in a BFS. If such a vertex is
found, the function returns true (1), otherwise, the function returns false (0).
You must use the BFSfind() method in the class to search for the startVertex.
*/

bool Graph::BFSWithDistance(std::string startVertex) {
  int index = BFSFind(startVertex); // check if that vertex does/does not exists

  if (index == -1) {
    return false;
  }

  vertex *v = &vertices[index];
  v->visited = true;
  v->distance = 0;
  queue<vertex *> q;
  q.push(v);
  vertex *n;

  while (!q.empty()) {
    n = q.front();
    q.pop();
    int nAdjSize = n->adj.size();

    for (int x = 0; x < nAdjSize; x++) {
      if (!n->adj[x].v->visited) {
        n->adj[x].v->distance = n->distance + n->adj[x].weight;
        n->adj[x].v->visited = true;

        if (n->distance > 0 && n->distance < n->adj[x].weight) {
          return true;
        }

        q.push(n->adj[x].v);
      }
    }
  }

  return false;
}

/*
Write a c++ function to check if the unweighted shortest path between two
vertices passes through the third vertex. The function takes three parameters:
source vertex, destination vertex and intermediate vertex. It should check if
the unweighted shortest path between source and destination vertices passes
through the intermediate vertex. It should display "Yes" if the path passes
through intermediate vertex. Otherwise, it should display "No".
*/

void Graph::shortestPath(string source, string destination,
                         string intermediate) {
  int sIndex, dIndex;
  bool outputNo = false;

  for (std::size_t i = 0; i < vertices.size();
       i++) { // find the source and destination in vertices
    if (vertices[i].name == source) {
      sIndex = i;
    }

    if (vertices[i].name == destination) {
      dIndex = i;
    }
  }
  vertex *v = &vertices[sIndex]; // pointer to address of source
  v->visited = true;
  queue<vertex *> q; // push source pointer to the vertex
  q.push(v);
  vertex *n; // for adjacent vertices

  while (!q.empty()) {
    n = q.front();
    q.pop();

    for (std::size_t x = 0; x < n->adj.size();
         x++) { // loop through each adjacent

      if (!n->adj[x].v->visited) {   // if they haven't been visited
        n->adj[x].v->visited = true; // then visit and mark as such
        n->adj[x].v->prev = n;       // then set up the parent
        q.push(n->adj[x].v);
      }
    }
  }

  vertex *v2 = &vertices[dIndex]; // pointer to the address of the dest

  while (v2->prev->name != source) { // while the prev isn't the source (making
                                     // sure there is something between)
    if (v2->prev->name ==
        intermediate) { // checking if the intermediate is in the path
      cout << "Yes" << endl;
      outputNo = true;
    }

    v2 = v2->prev;
  }

  if (!outputNo) {
    cout << "No" << endl;
  }
}

/*
Write a c++ function to check if a path exists in a graph.The function takes two
parameters: path (array of strings), length. It should return true if path
exists. Otherwise, it should return false.
*/

bool Graph::pathExists(string path[], int length) {
  vertex *tmp;
  size_t len = vertices.size();

  for (std::size_t i = 0; i < len; i++) {
    if (vertices[i].name == path[0]) {
      tmp = &vertices[i];
      break;
    }
  }

  for (int i = 1; i < length; i++) {
    bool found = false;

    for (size_t j = 0; j < tmp->adj.size(); j++) {
      if (tmp->adj[j].v->name == path[i]) {
        tmp = tmp->adj[j].v;
        found = true;
        break;
      }
    }

    if (!found)
      return false;
  }

  return true;
}

/*
Implement a C++ function to build a hash table using a new hash function. In the
hash table, insert movies at the end of the linked list for movies that hash to
the same index.
*/

void HashTable::buildHashTable(string movies[], int length) {
  for (int i = 0; i < length; i++) {
    Movie *mov = new Movie(movies[i]);
    int id = newHashSum(movies[i], tableSize);

    if (hashTable[id]) {
      hashTable[id]->next = mov;
    }

    else {
      hashTable[id] = mov;
    }
  }
}

int HashTable::newHashSum(string inputString, int hashLen) {
  int sum = 0;

  for (size_t i = 0; i < inputString.size(); i++) {
    if (i % 2 == 0) {
      sum += (int)inputString[i];
    }
  }

  return sum % hashLen;
}

/*
Implement a C++ function to build a new hash table from an existing hash table
using a new hash function called hashSum2.  In the new hash table, insert the
movies at the front of the linked list when the movies hash to the same index.
*/

void HashTable::createNewHashTable() {
  for (int i = 0; i < tableSize; i++) { // check array if items in table

    if (hashTable[i] != NULL) { // check if something at that index
      Movie *temp = hashTable[i];

      while (temp != NULL) {
        int newHashIndex = hashSum2(temp->title, tableSize);
        // If there is nothing in this location.

        if (newHashTable[newHashIndex] == NULL) {
          newHashTable[newHashIndex] = new Movie(temp->title);
        }

        // If we need to add to a chain.
        else {
          Movie *temp2 = newHashTable[newHashIndex];
          Movie *newMovie = new Movie(temp->title);
          newMovie->next = temp2;
          newHashTable[newHashIndex] = newMovie;
          // cout << newMovie->title << endl;
        }

        temp = temp->next;
      }
    }
  }
}
