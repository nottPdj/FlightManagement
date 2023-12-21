
/****************** Provided constructors and functions ********************/
/*
template <class T>
Airport::Vertex(T in): info(in) {}

template <class T>
Edge<T>::Edge(Airport *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
vector<Airport * > Graph<T>::getVertexSet() const {
    return vertexSet;
}

template<class T>
T Airport::getInfo() const {
    return info;
}

template<class T>
void Airport::setInfo(T in) {
    Vertex::info = in;
}

template<class T>
bool Airport::isProcessing() const {
    return processing;
}

template<class T>
void Airport::setProcessing(bool p) {
    Vertex::processing = p;
}

template<class T>
Airport *Edge<T>::getDest() const {
    return dest;
}

template<class T>
void Edge<T>::setDest(Airport *d) {
    Edge::dest = d;
}

template<class T>
double Edge<T>::getWeight() const {
    return weight;
}

template<class T>
void Edge<T>::setWeight(double weight) {
    Edge::weight = weight;
}

*//*
 * Auxiliary function to find a vertex with a given content.
 *//*
template <class T>
Airport * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->info == in)
            return v;
    return NULL;
}

template <class T>
bool Airport::isVisited() const {
    return visited;
}

template <class T>
void Airport::setVisited(bool v) {
    Vertex::visited = v;
}

template<class T>
const vector<Edge<T> > &Airport::getAdj() const {
    return adj;
}

template <class T>
void Airport::setAdj(const vector<Edge<T> > &adj) {
    Vertex::adj = adj;
}


*//*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 *//*
template <class T>
bool Graph<T>::addVertex(const T &in) {
    if ( findVertex(in) != NULL)
        return false;
    vertexSet.push_back(new Airport(in));
    return true;
}


*//*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 *//*
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2,w);
    return true;
}

*//*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 *//*
template <class T>
void Airport::addEdge(Airport *d, double w) {
    adj.push_back(Edge<T>(d, w));
}


*//*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 *//*
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

*//*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 *//*
template <class T>
bool Airport::removeEdgeTo(Airport *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

*//*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 *//*
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->info  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}


//=============================================================================
// Exercise 1.1: Depth First Search
//=============================================================================
// Subexercise 1.1.1: Depth First Search (Graph Traversal)
//=============================================================================
*//*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 *//*
template <class T>
vector<T> Graph<T>::dfs() const {
    vector<T> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

*//*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 *//*
template <class T>
void Graph<T>::dfsVisit(Airport *v, vector<T> & res) const {
    v->visited = true;
    res.push_back(v->info);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}

//=============================================================================
// Subexercise 1.1.2: Depth First Search (From a source node)
//=============================================================================
*//*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 *//*
template <class T>
vector<T> Graph<T>::dfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}


//=============================================================================
// Exercise 2: Breadth-First Search
//=============================================================================
*//*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 *//*
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
    vector<T> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Airport *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->info);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}*/

#include "Graph.h"


Airport *Graph::getAirport(std::string code) {
    return this->airports[code];
}

Airline *Graph::getAirline(std::string code) {
    return this->airlines[code];

}

void Graph::addFlight(Flight flight) {
    flight.source->addFlight(flight);
}

void Graph::addAirport(std::string code, Airport* airport) {
    airports.insert(make_pair(code, airport));
}

void Graph::addAirline(std::string code, Airline* airline) {
    airlines.insert(make_pair(code, airline));
}

