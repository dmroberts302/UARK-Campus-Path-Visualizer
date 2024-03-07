#include <search.hpp>
#include <bst.hpp>

void bfs(Graph &G, int start, int destination) {
    BST<std::pair<int, int> > bst;

    G.reset();

    G.distance(start) = 0;
    bst.insert(std::pair<int, int>(G.distance(start), start));
    
    G.setTrace(start, -1);

    while (true) {
        std::pair<int, int> pair = bst.findMaximum()->key;
        bst.remove(pair);

        if (pair.first != G.distance(pair.second))
            continue;

        int u = pair.second;
        int dist = pair.first;

        G.setVisited(u);

        if (u == destination)
            break;

        int numberOfAdjacencyNodes = G.e[u].size();
        LinkedListNode<std::pair<int, int> > *p = G.e[u].getRoot();
        for (int i = 0; i < numberOfAdjacencyNodes; i += 1, p = p->next) {
            int v = p->value.first;
            int w = p->value.second;
            if (G.isVisited(v))
                continue;
            if (dist + w < G.distance(v)) {
                G.distance(v) = dist  + w ;
                bst.insert( std::pair<int, int>(G.distance(v), v) );
                G.setTrace(v, u);   
            }
        }
    }
}
