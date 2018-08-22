//clang 3.8.0

/*
Author: Shoshana Biro
rights: use freely just mention my name if significant amount is copied.

EdgeTree:
problem given by womentwhocodenyc github august 2018 problem set
problem description: 
given a non-cyclic connected graph with even number of vertices
what is the maximum number of edges that can be removed so that each of the connected components has even number of vertices.

Algorithm:

1. Create adjacency list using a unordered multimap, adj, as well as an edges list called E.
2. In a loop
for each edge e in E
	remove edges e and e-tag (reverse of e)
	do a BFS on the component whose root is one of vertices of the 
	removed edge, 
	return the number of vertices of this component in found_vertices 
	
	if # found_vertices in this component is odd 
		restore edges e and e-tag
	else
		move on to next edge
		increment amount of result edges
BFS algorithm
	in a loop:
	visit all vertices in bucket (connected to) of current vertex.
	store visited vertices in Visited set.
	store visited vertices (except root) in back queue
	pop from front of queue
	   
*/
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
#include <queue>
#include <sstream>
#include <exception>
#include <istream>

using namespace std;

class Graph
{
    using Edge = pair<int,int>;
    
   public:
    
    void ReadEdges(istream& in,int VerticesAmt, int EdgesAmount)
    {
       try
       {
        
        Edges.clear();
        Edges.reserve(EdgesAmount);
        int v,w;
        cout << "Reading " << EdgesAmount << " edges" << endl;
        for (int i=0; i < EdgesAmount; i++)
        {
            in >> v >> w;
            cout << i << " " << v << " " << w << endl;
            Edges.push_back(make_pair(v,w));
        }
        VerticesAmount = VerticesAmt;
      }
      catch (const exception &e)
      {
            cout << "ReadEdges exception:" << e.what() << endl;
      }
    }
    
    void CreateGraph()
    {
        if (Edges.empty())
            return;
        for (const auto &e : Edges)
        {
            adj.insert(e);
            adj.emplace(make_pair(e.second,e.first));
        }
       
    }
    
    void RemoveEdge(Edge &e) { 
        auto range = adj.equal_range(e.first);
        for (auto pos = range.first; pos != range.second; pos++)
        {
            if (pos->second == e.second)
            {
                adj.erase(pos);
                cout << "removing edge: " << e.first << " " << e.second << endl;
                break;
            }
        }
    }
    
    void AddEdge(Edge &e)
    {
        auto range = adj.equal_range(e.first);
        for (auto pos = range.first; pos != range.second; pos++)
        {
            if (pos->second == e.second)
            {
                
                return;
            }
        }     
        
        adj.emplace(e);
        cout << "adding edge: " << e.first << " " << e.second << endl;
    }
    
    void BFS_Component(int root, int *VerticesAmount);
    
    auto beginEdge() { return Edges.begin(); }
    
    auto endEdge() { return Edges.end(); }
    
  private:
    vector<pair<int,int>> Edges;
    unordered_multimap<int,int> adj;
    int VerticesAmount; 
};
  
void Graph::BFS_Component(int root, int *VerticesAmount)
{
    *VerticesAmount = 1;
    queue<int> q;
    int vertex = root;
    unordered_set<int> Visited;
    Visited.insert(vertex);
    
    for (;;)
    {
        auto range = adj.equal_range(vertex);
        
        for (auto it = range.first; it != range.second; it++)
        {
            auto res_pair = Visited.insert(it->second);
            if (res_pair.second == true )
            {
                q.push(it->second);
                (*VerticesAmount)++;
            }
        }
        if (q.empty())
            break;
        else
        {
            vertex = q.front();
            q.pop();
        } 
    }
    
}

int main()
{ 
   try
   {
    int M,N;
    //n >> M;
    //n >> N;
    M = 10;
    N = 9;
    Graph g;
    stringstream ss;

    //int v,w;
    //for (int i=0; i < N; i++)
    //
     // cin >> v >> w;
      //ss << v << " " << w << " ";
    //}
    //

    ss << 1 << " " << 2 << " ";
    
    ss << 2 << " " << 7 << " ";
    
    ss << 2 << " " <<  5 << " ";
   
    ss << 1 << " " << 3 << " ";
    ss << 3 << " " << 4 << " ";
    ss << 1 << " " << 6 << " ";
    ss << 6 << " " << 8 << " ";
    ss << 8 << " " << 9 << " ";
    ss << 8 << " " << 10 << " ";
    
    g.ReadEdges(ss,M,N);
    g.CreateGraph();
    auto beg = g.beginEdge();
    auto end = g.endEdge();
    int Res = 0;
    for (auto it = beg; it != end; it++)
    {
        g.RemoveEdge(*it);
        
        pair<int,int> p = make_pair(it->second,it->first);
        
        g.RemoveEdge(p);
        
        int NumVertices=0;
        g.BFS_Component(it->first,&NumVertices);
       
        if (NumVertices & 1)
        {
            g.AddEdge(*it);
            g.AddEdge(p);
        }
        else
        {
            Res++;
        }
    }
    cout << "Result: " << Res << endl;
  }
  catch (const exception &e)
  {
      cout << "Main() exception:" << e.what() << endl;
  }
  catch (...)
  {
        cout << "main any Exception occured" << endl;
  }
}
    
    
