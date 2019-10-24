#include "graph.h"
#include "fstream.h"

EdgeData::EdgeData(){
	adjacentNode = NULL;
	weight = 0;
}

EdgeData::EdgeData(Vertice *node, int w /*= 0 */){
	adjacentNode = node;
	weight = w;
}

EdgeData::EdgeData(const EdgeData &right){ // copy constructor
	adjacentNode = right.adjacentNode;
	weight = right.weight;
}

void EdgeData::SetInfo(Vertice *node, int w /*= 0 */){
	adjacentNode = node;
	weight = w;
}

Vertice * EdgeData::GetAdjacentNode(){
	return adjacentNode;
}

bool EdgeData::operator<(const EdgeData &right) const{
	return adjacentNode->id < right.adjacentNode->id;
}

Vertice::Vertice(){
	id = '\0';
	Visited = false;
	nAdjacentNodes = 0;
}

void Vertice::SetID(char ID){
	id = ID;
	Visited = false;
	nAdjacentNodes = 0;
}

void Vertice::AddAdjacentNode(Vertice *addNode, int weight){
	AdjacentNodes.insertInOrder( EdgeData(addNode, weight));
	nAdjacentNodes++;
}

bool Vertice::IsVisited(){
	return Visited;
}
	
void Vertice::MarkVisited(){
	Visited = true;
}
	
void Vertice::ClearVisit(){
	Visited = false;
}

char Vertice::GetID(){
	return id;
}

Graph::Graph()
: nNodes(0), nEdges(0), Directed(0), Weighted(0)
{
	Nodes = NULL;
}

Graph::Graph(int n, bool IsD, bool IsW)
: nNodes(n), nEdges(0), Directed(IsD), Weighted(IsW)
{
	Nodes = new Vertice[nNodes];
}

Graph::~Graph()
{
	if (Nodes)
		delete [] Nodes;
}

void Graph::SetInfo(int n, bool IsD, bool IsW){
	nNodes = n;
	Directed = IsD;
	Weighted = IsW;
	if (Nodes)
		delete [] Nodes;
	Nodes = new Vertice[nNodes];
}

bool Graph::LoadGraph(istream &input){
	char directed, weighted;
	int nodes;
	if (!(input >> directed >> weighted >> nodes))
		return false;
	SetInfo(nodes, directed == 'Y' || directed == 'y', weighted == 'Y' || weighted == 'y');
	char ID;
	for (int wNode = 0; wNode < nodes; wNode++){
		if (!(input >> ID))
			return false;
		AssignID(wNode, ID);
	}
	
	char N1, N2;
	int weight = 0;
	if (!(input >> nEdges))
		return false;
	for (int wEdge = 0; wEdge < nEdges; wEdge++){
		if (!(input >> N1 >> N2))
			return false;
		if (IsWeighted()){
			if (!(input >> weight))
				return false;
		}
		AddEdge(N1, N2, weight);
		if (!IsDirected())
			AddEdge(N2, N1, weight);
	}
	return true;
}

void Graph::AssignID(int whichNode, char ID){
	Nodes[whichNode].SetID(ID);
}

void Graph::AddEdge(char Node1, char Node2, int Weight){
	Nodes[FindIndex(Node1)].AddAdjacentNode(GetVertPointer(FindIndex(Node2)), Weight);
}

int Graph::FindIndex(char n){
	for (int i = 0; i < nNodes; i++){
		if (Nodes[i].GetID() == n)
			return i;
	}
	return -1;
}

Vertice * Graph::GetVertPointer(int index){
	return &Nodes[index];
}

bool Graph::IsDirected(){
	return Directed;
}

bool Graph::IsWeighted(){
	return Weighted;
}

int Graph::GetNumNodes(){
	return nNodes;	
}

int Graph::GetNumEdges(){
	return nEdges;
}

void Graph::ClearAllVertices(){
	for (int v = 0; v < nNodes; v++)
		Nodes[v].ClearVisit();
}


void Graph::BreadthFirstTraversal(int startIndex, VisitFunctionType VisitFunction){
	ClearAllVertices();
	BreadthFirstTraversal(GetVertPointer(startIndex), VisitFunction);
}

void Graph::BreadthFirstTraversal(Vertice *startVertice, VisitFunctionType VisitFunction){
	ClearAllVertices();
	//startVertice->MarkVisited();
	VisitFunction(0, startVertice);
	BreadthFirstHelper(startVertice, VisitFunction);
}

void Graph::BreadthFirstHelper(Vertice *whichVertice, VisitFunctionType VisitFunction){

	List<Vertice *> NodesToVisit;
	Vertice *aVertex;// = whichVertice;
	EdgeData thisEdge;
	
	do {
		for (int i = 0; i < whichVertice->nAdjacentNodes; i++){
			whichVertice->AdjacentNodes.removeFromFront( thisEdge );
			aVertex = thisEdge.GetAdjacentNode();
			if (!aVertex->IsVisited()){
				//aVertex->MarkVisited();
				VisitFunction(whichVertice, aVertex);
				NodesToVisit.insertAtFront( aVertex );
			}
			whichVertice->AdjacentNodes.insertAtBack( thisEdge );
		}
 
	} while (NodesToVisit.removeFromBack(whichVertice));
}

void Graph::DepthFirstTraversal(int startIndex, VisitFunctionType VisitFunction){
	DepthFirstTraversal(GetVertPointer(startIndex), VisitFunction);
}

void Graph::DepthFirstTraversal(Vertice *startVertice, VisitFunctionType VisitFunction){
	ClearAllVertices();
	VisitFunction(0, startVertice);
	//startVertice->MarkVisited();
	DepthFirstHelper(startVertice, VisitFunction);
}

void Graph::DepthFirstHelper(Vertice *whichVertice, VisitFunctionType VisitFunction){
	
	//visit all its children
	EdgeData thisEdge;
	Vertice *aVertex;
	for (int i = 0; i < whichVertice->nAdjacentNodes; i++){
		whichVertice->AdjacentNodes.removeFromFront( thisEdge );
		aVertex = thisEdge.GetAdjacentNode();
		if (!aVertex->IsVisited()){
			//aVertex->MarkVisited();
			VisitFunction(whichVertice, aVertex);
			DepthFirstHelper(aVertex, VisitFunction);
		}
		whichVertice->AdjacentNodes.insertAtBack( thisEdge );
 	}

}

void Graph::FindComponents(int arrayC[], int nVert, int &nC){
	ClearAllVertices();
	nC = 0;
	for (int i = 0; i < nVert; i++){
		if (!Nodes[i].IsVisited()){
			arrayC[nC] = i;
			nC++;
			DepthFirstTraversal(i, JustMark);
		}
	}

}

bool Graph::IsConnected(){
	if (nEdges >= nNodes - 1){
		int numComp = 0;
		int *arrayC = new int[nNodes];
		FindComponents(arrayC, nNodes, numComp);
		delete [] arrayC;
		if (numComp == 1)
			return true;
	}
	return false;
}
	
Graph* Graph::MST(int startIndex){
	ClearAllVertices();
	Vertice * aVertex = GetVertPointer(startIndex);
	Graph *MSTGraph = new Graph(nNodes, false, true);
	int NumVisited = 1;
	Vertice *whichVertice;
	int cheapestPath;
	Vertice *cheapestNode;
	Vertice *cheapestParent;
	EdgeData thisEdge;
	
	aVertex->MarkVisited();
	for (int i = 0; i < nNodes; i++){
		MSTGraph->AssignID(i, Nodes[i].GetID());
	}

	while (NumVisited < nNodes){
		
		cheapestParent = NULL;
		cheapestPath = 0x7FFFFFFF;
		cheapestNode = NULL;
		for (int wNode = 0; wNode < nNodes; wNode++){
			whichVertice = &Nodes[wNode];
			if (whichVertice->IsVisited()) {// check to see if it has unvisited children

				for (int i = 0; i < whichVertice->nAdjacentNodes; i++){
					whichVertice->AdjacentNodes.removeFromFront( thisEdge );
					aVertex = thisEdge.GetAdjacentNode();
					if (!aVertex->IsVisited()){
						if (thisEdge.weight < cheapestPath){
							cheapestPath = thisEdge.weight;
							cheapestParent = whichVertice;
							cheapestNode = aVertex;
						}
					}
					whichVertice->AdjacentNodes.insertAtBack( thisEdge );
 				}
			}
		}
		if (cheapestNode){
			MSTGraph->AddEdge(cheapestParent->GetID(), cheapestNode->GetID(), cheapestPath);
			cheapestNode->MarkVisited();
			NumVisited++;
		}
	}
	return MSTGraph;
}

void PrintVertID(Vertice *h, Vertice *n){
	if (n)
		cout << n->GetID() << endl;	
	n->MarkVisited();
}

void PrintEdge(Vertice *h, Vertice *n){
	if (n && h)
		cout << h->GetID() << ' ' << n->GetID() << endl;
	n->MarkVisited();
}

void JustMark(Vertice *h, Vertice *n){
	n->MarkVisited();
}

// my graph class would be better if instead of having for every vertice a list of adjacent nodes
// I had a list of 'in' adjacent nodes and 'out' adjacent nodes.

//Also include functions to print out the edges composing the 
//depth-first spanning tree and the breadth-first spanning tree found 
//by searching starting from the first node of the graph. If the graph 
//is directed and not strongly connected, the spanning tree will be 
//only of the component in which the first node lies. If the graph is 
//undirected, print out spanning trees of all the components. If the 
//graph is undirected, connected, and weighted, print out the 
//minimum-cost spanning tree.
void main(){
	ifstream fin("c:\\graph.dat");
	Graph graph1;
	while (graph1.LoadGraph(fin)){
		
		cout << "Depth First Traversal" << endl;
		graph1.DepthFirstTraversal(0,PrintEdge);
		
		cout << "Breadth First Traversal" << endl;
		graph1.BreadthFirstTraversal(0,PrintEdge);
		

		if (!graph1.IsDirected()){
			int numComp = 0;
			int *arrayC = new int[graph1.GetNumNodes()];
			graph1.FindComponents(arrayC, graph1.GetNumNodes(), numComp);
			cout << "There are " << numComp << " components in this tree." << endl;
			for (int wComp = 0; wComp < numComp; wComp++){
				cout << "Component " << wComp + 1 << endl;
				cout << "Depth First Spanning Tree" << endl;
				graph1.DepthFirstTraversal(arrayC[wComp],PrintEdge);
		
				cout << "Breadth First Spanning Tree" << endl;
				graph1.BreadthFirstTraversal(arrayC[wComp],PrintEdge);

			}
			delete [] arrayC;
			if (graph1.IsWeighted() && graph1.IsConnected()){
				// print out the minimum cost spanning tree
				Graph *minimumST = graph1.MST(0);
				cout << "Minimum cost spanning tree, depth first traversal " << endl;
				minimumST->DepthFirstTraversal(0, PrintEdge);
			}
		}
	}
	fin.close();

}

/*
N
N
9
A B C D E F G H I
11
A I A F A B
B E B C
C E C D
D G D H
E G
F G
*/

/*
N
N
13
A B C D E F G H I J K L M
11
A I A F A B
B E B C
C E C D
D G D H
E G
F G
*/

/*
Y
N
6
A B C D E F
6
A B 
F B
D B
B C
C D
E A
*/

/*
N
Y
9
A B C D E F G H I
11
A I 2	A F 4	A B 6
B E 9	B C 7	
C E 3	C D 4
D G 5	D H 1
E G 8
F G 2
*/