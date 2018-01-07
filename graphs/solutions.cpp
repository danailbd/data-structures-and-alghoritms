#include<iostream>
#include "graph.cpp"

using namespace std;

class ExtendedGraph: public OrGraph<char>
{
    public:
        bool matchWord(const char* word) const {
            // empty word check
            if (word[0] == '\0')
                return true;

            char prevLetter = word[0];
            for (int i = 1; word[i] != '\0'; i++)
            {
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
            for (; vertexIt != end; vertexIt++)
            {
                auto vertexRelsIt = vertexIt->begin(),
                     endRels = vertexIt->end();

                toVertex = *vertexRelsIt++;
                
                if (!reversedGraph.hasVertex(toVertex))
                    reversedGraph.addVertex(toVertex);
                

                for (; vertexRelsIt != endRels; vertexRelsIt++)
                {
                    fromVertex = *vertexRelsIt;

                    if (!reversedGraph.hasVertex(fromVertex))
                        reversedGraph.addVertex(fromVertex);
                    reversedGraph.addEdge(fromVertex, toVertex);
                }
            }
            return reversedGraph;
        }


};


int main()
{
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
    
    graph.print();

    // matchWord
    UnitTests::AssertEq(true, graph.matchWord(""));
    UnitTests::AssertEq(true, graph.matchWord("a"));
    UnitTests::AssertEq(true, graph.matchWord("ab"));
    UnitTests::AssertEq(true, graph.matchWord("abc"));
    UnitTests::AssertEq(true, graph.matchWord("abcd"));
    UnitTests::AssertEq(false, graph.matchWord("abcde"));
    UnitTests::AssertEq(false, graph.matchWord("ae"));
    UnitTests::AssertEq(true, graph.matchWord("ada"));


    // Reversed graph
    ExtendedGraph reversedGraph = graph.reversedGraph();

    reversedGraph.print();
    UnitTests::AssertEq(true, reversedGraph.hasEdge('d', 'a'));
    UnitTests::AssertEq(true, reversedGraph.hasEdge('a', 'd'));
    UnitTests::AssertEq(false, reversedGraph.hasEdge('a', 'b'));
    UnitTests::AssertEq(true, reversedGraph.hasEdge('b', 'a'));
    UnitTests::AssertEq(true, reversedGraph.hasEdge('c', 'b'));
    UnitTests::AssertEq(true, reversedGraph.hasEdge('d', 'c'));


   
    return 0;
}
