#include <algorithm>
#include <iostream>
#include <list>

#include <sstream>

using std::list;
using std::cout;
using std::endl;

/**
 * Restrictions:
 * - unique vertices
 */
template <typename T>
class DirGraph {
public:
    void addVertex(const T& v);
    void removeVertex(const T& v);
    bool hasVertex(const T& v) const;

    void addEdge(const T& vFrom, const T& vTo);
    void removeEdge(const T& vFrom, const T& vTo);
    bool hasEdge(const T& vFrom, const T& vTo) const;

    list<T>* getVertexRels(const T& v);
    list<T> getVetices() const;

    void print() const;

protected:
    list<list<T> > linkedGraph;
};


template <typename T>
list<T>* DirGraph<T>::getVertexRels(const T& v)
{
    auto verticesIt = linkedGraph.begin(),
         end = linkedGraph.end();

    while (verticesIt != end) {
        if (verticesIt->front() == v)
            return &(*verticesIt);
        verticesIt++;
    }
    return NULL;
}

template <typename T>
void DirGraph<T>::addVertex(const T& v)
{
    list<T> vertex;
    vertex.push_front(v);

    linkedGraph.push_back(vertex);
}

template <typename T>
void DirGraph<T>::print() const
{
    cout << "Vertex -- Refs" << endl;
    cout << "-----------------" << endl;
    for (auto& vertexRefs : linkedGraph) {
        for (auto& ref : vertexRefs)
            cout << ref << ' ';
        cout << endl;
    }
}

template <typename T>
void DirGraph<T>::removeVertex(const T& v)
{
    auto it = linkedGraph.begin();
    auto end = linkedGraph.end();

    /// iterate over all nodes and remove invalid relation
    for (; it != end; it++) {
        /// find matching vertex list & delete
        if (it->front() == v) {
            // delete the node itself;
            // as the initial iterator is invalidated, replace it with the returned one
            //   that is from the next element
            it = linkedGraph.erase(it);
        }

        // clean invalid relations left
        auto vertexRelIt = std::find(it->begin(), it->end(), v);
        if (*vertexRelIt == v) {
            it->erase(vertexRelIt);
        }
    }
}

template <typename T>
void DirGraph<T>::addEdge(const T& vFrom, const T& vTo)
{
    for (auto& vertexRels : linkedGraph) {
        if (vertexRels.front() == vFrom) {
            vertexRels.push_back(vTo);
            break;
        }
    }
}

template <typename T>
void DirGraph<T>::removeEdge(const T& vFrom, const T& vTo)
{
    list<T>* vertexRels = getVertexRels(vFrom);

    if (!vertexRels->empty()) {
        auto elemIterator = std::find(vertexRels->begin(), vertexRels->end(), vTo);
        // there exists such relation
        if (*elemIterator == vTo) {
            vertexRels->erase(elemIterator);
        }
    }
}

template <typename T>
bool DirGraph<T>::hasVertex(const T& v) const
{
    auto verticesIt = linkedGraph.begin(),
         end = linkedGraph.end();

    for (; verticesIt != end && verticesIt->front() != v; verticesIt++) {
    }

    return verticesIt != end;
}

template <typename T>
bool DirGraph<T>::hasEdge(const T& vFrom, const T& vTo) const
{
    auto fromVertexIt = linkedGraph.begin(),
         end = linkedGraph.end();

    // find matching vertex
    while (fromVertexIt != end && fromVertexIt->front() != vFrom) {
        fromVertexIt++;
    }

    if (fromVertexIt != end) {
        return std::find(fromVertexIt->begin(), fromVertexIt->end(), vTo) != fromVertexIt->end();
    }
    return false;
}

template <typename T>
list<T> DirGraph<T>::getVetices() const
{
    list<T> vertices;
    for (auto& vertexRels : linkedGraph)
        vertices.push_back(vertexRels.front());

    return vertices;
}
