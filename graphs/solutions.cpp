#include "graph.cpp"
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct PathNode {
    PathNode* parent;
    char data;

    PathNode(){};
    PathNode(PathNode* _parent, char _data)
        : parent(_parent)
        , data(_data)
    {
    }
};

class ExtendedGraph : public DirGraph<char> {
public:
    bool matchWord(const char* word) const
    {
        // empty word check
        if (word[0] == '\0')
            return true;

        char prevLetter = word[0];
        for (int i = 1; word[i] != '\0'; i++) {
            if (!hasEdge(prevLetter, word[i]))
                return false;

            prevLetter = word[i];
        }
        return true;
    }

    ExtendedGraph reversedGraph()
    {
        auto vertexIt = linkedGraph.begin(),
             end = linkedGraph.end();

        ExtendedGraph reversedGraph;

        char fromVertex,
            toVertex;
        for (; vertexIt != end; vertexIt++) {
            auto vertexRelsIt = vertexIt->begin(),
                 endRels = vertexIt->end();

            toVertex = *vertexRelsIt++;

            if (!reversedGraph.hasVertex(toVertex))
                reversedGraph.addVertex(toVertex);

            for (; vertexRelsIt != endRels; vertexRelsIt++) {
                fromVertex = *vertexRelsIt;

                if (!reversedGraph.hasVertex(fromVertex))
                    reversedGraph.addVertex(fromVertex);
                reversedGraph.addEdge(fromVertex, toVertex);
            }
        }
        return reversedGraph;
    }

    bool findPathRec(const char& a, const char& b, list<char>& path, vector<char> excludedVertices, int length, int maxLength)
    {
        if (length > maxLength) {
            return false; //or clear array
        }

        path.push_back(a);

        if (a == b && length == maxLength)
            return true;

        excludedVertices.push_back(a); // one more visited node

        list<char>* vertexRels = getVertexRels(a);
        auto vertexRelsIt = vertexRels->begin(),
             end = vertexRels->end();
        for (; vertexRelsIt != end; vertexRelsIt++) {
            if (find(excludedVertices.begin(), excludedVertices.end(), *vertexRelsIt) == excludedVertices.end()) {
                if (findPathRec(*vertexRelsIt, b, path, excludedVertices, length + 1, maxLength)) {
                    // returns, keeping the path's state
                    return true;
                }
            }
        }
        path.pop_back(); // remove the element we added

        return false;
    }

    ///
    /// Use `excludedVertices` also for visited notes
    list<char> findShortesPath(const char &a, const char &b, vector<char> excludedVertices)
    {
        // add node if not visited or not excluded


        vector<PathNode> nodes;

        nodes.push_back(PathNode(NULL, a));

        PathNode checkedNode,
                 foundNode;
        bool found = false;
        while (!nodes.empty())
        {
            checkedNode = nodes.back();
            nodes.pop_back();

            /// add it's neighbours
            // find the node rels
            auto verticesIt = linkedGraph.begin();
            for (; verticesIt != linkedGraph.end() &&
                    verticesIt->front() != checkedNode.data;
                    verticesIt++) {}

            auto vertexRelsIt = verticesIt->begin();
            for (; vertexRelsIt != verticesIt->end(); vertexRelsIt++)
            {
                if (*vertexRelsIt == b)
                {
                    foundNode = PathNode(&checkedNode, *vertexRelsIt);
                    found = true;
                }
                // is not yet visited or excluded
                if (find(excludedVertices.begin(), excludedVertices.end(), *vertexRelsIt) == excludedVertices.end())
                {
                    nodes.push_back(PathNode(&checkedNode, *vertexRelsIt));
                    excludedVertices.push_back(*vertexRelsIt);
                }
            }
        }

        if (!found)
        {
            // just return an empty path
            return list<char>();
        }

        list<char> path;
        // build path
        while (foundNode.parent)
        {
            path.push_front(foundNode.data);
        }
        return path;
    }
};


/**********************************************************************
*                               TESTS                                *
**********************************************************************/


using std::cout;
using std::cerr;
using std::endl;

int tests_counter = 0;
int failed_tests_counter = 0;

class UnitTests {
    public:
        template <typename T>
            static void AssertEq(T expected, T value) {
                tests_counter++;
                if (expected != value) {
                    cerr << "FAIL(" << tests_counter << "): Values mismatch!" << "\n-- expected: " << expected << "\n---- actual: " << value << endl; 
                    failed_tests_counter++;
                } else {
                    cout << "." << endl;
                }
            }
};


void testGraph()
{
    cout << "--- GRAPH TESTS ---" << endl;

    DirGraph<int> graph;

    graph.addVertex(1);
    UnitTests::AssertEq(true, graph.hasVertex(1));

    graph.addVertex(2);
    UnitTests::AssertEq(true, graph.hasVertex(1));
    UnitTests::AssertEq(true, graph.hasVertex(2));

    graph.addVertex(3);

    graph.addVertex(2);
    UnitTests::AssertEq(true, graph.hasVertex(1));
    UnitTests::AssertEq(true, graph.hasVertex(3));

    graph.addVertex(2);
    graph.addVertex(4);
    graph.addVertex(5);

    /// --- Edges ---

    graph.addEdge(1, 4);
    UnitTests::AssertEq(true, graph.hasEdge(1, 4));

    graph.addEdge(1, 2);
    UnitTests::AssertEq(true, graph.hasEdge(1, 2));
    UnitTests::AssertEq(false, graph.hasEdge(3, 1));

    graph.addEdge(3, 2);
    UnitTests::AssertEq(true, graph.hasEdge(3, 2));
    UnitTests::AssertEq(true, graph.hasEdge(1, 2));
    UnitTests::AssertEq(true, graph.hasEdge(1, 4));

    graph.removeEdge(3, 2);
    UnitTests::AssertEq(false, graph.hasEdge(3, 2));
    UnitTests::AssertEq(true, graph.hasEdge(1, 2));
    UnitTests::AssertEq(true, graph.hasEdge(1, 4));


    graph.addEdge(3, 2);
    graph.addEdge(2, 1);

    graph.removeVertex(2);
    UnitTests::AssertEq(false, graph.hasEdge(1, 2));
    UnitTests::AssertEq(false, graph.hasEdge(2, 1));
    UnitTests::AssertEq(false, graph.hasEdge(3, 2));
    UnitTests::AssertEq(true, graph.hasEdge(1, 4));
}


void testMatchWord(ExtendedGraph& graph) {
    cout << "----- matchWork TESTS -----" << endl;
    // matchWord
    UnitTests::AssertEq(true, graph.matchWord(""));
    UnitTests::AssertEq(true, graph.matchWord("a"));
    UnitTests::AssertEq(true, graph.matchWord("ab"));
    UnitTests::AssertEq(true, graph.matchWord("abc"));
    UnitTests::AssertEq(true, graph.matchWord("abcd"));
    UnitTests::AssertEq(false, graph.matchWord("abcde"));
    UnitTests::AssertEq(false, graph.matchWord("ae"));
    UnitTests::AssertEq(true, graph.matchWord("ada"));

}

void testReversedGraph(ExtendedGraph &graph) {
    cout << "----- reverseGraph TESTS -----" << endl;

    ExtendedGraph reversedGraph = graph.reversedGraph();

    UnitTests::AssertEq(true, reversedGraph.hasEdge('d', 'a'));
    UnitTests::AssertEq(true, reversedGraph.hasEdge('a', 'd'));
    UnitTests::AssertEq(false, reversedGraph.hasEdge('a', 'b'));
    UnitTests::AssertEq(true, reversedGraph.hasEdge('b', 'a'));
    UnitTests::AssertEq(true, reversedGraph.hasEdge('c', 'b'));
    UnitTests::AssertEq(true, reversedGraph.hasEdge('d', 'c'));
}

void testFindPath(ExtendedGraph &graph) {
    cout << "----- findPath TESTS -----" << endl;

    list<char> path;
    vector<char> exVertices;
    UnitTests::AssertEq(true, graph.findPathRec('a', 'd', path, exVertices, 0, 3));
    UnitTests::AssertEq('a', path.front());
    UnitTests::AssertEq('d', path.back());
    UnitTests::AssertEq<int>(4, path.size()); // it should include more than just 'a' and 'd'
}

void testGraphUtils() {
    cout << "--- GRAPH UTILS TESTS ---" << endl;

    ExtendedGraph graph;
    graph.addVertex('a');
    graph.addVertex('b');
    graph.addVertex('c');
    graph.addVertex('d');

    graph.addEdge('a', 'd');
    graph.addEdge('d', 'a');

    graph.addEdge('a', 'b');
    graph.addEdge('b', 'c');
    graph.addEdge('c', 'd');

    testMatchWord(graph);
    testReversedGraph(graph);
    testFindPath(graph);
}

int main()
{
    testGraph();
    testGraphUtils();


    return 0;
}
