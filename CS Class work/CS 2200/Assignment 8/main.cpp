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

void Graph::SpecialCycleTraversal(Vertice *whichVertice, VisitFunctionType VisitFunction){
	ClearAllVertices();
	Vertice *startVertice = whichVertice;
	
	List<Vertice *> NodesToVisit;
	Vertice *aVertex;
	Vertice *bVertex;
	EdgeData thisEdge;
	EdgeData nextEdge;
	
	for (int t = 0; t < startVertice->nAdjacentNodes; t++){
		startVertice->AdjacentNodes.removeFromFront(thisEdge);
		aVertex = thisEdge.GetAdjacentNode();
		
		for (int i = 0; i < aVertex->nAdjacentNodes; i++){
			aVertex->AdjacentNodes.removeFromFront(nextEdge);
			bVertex = nextEdge.GetAdjacentNode();
			if (bVertex != startVertice){
				ClearAllVertices();
				aVertex->MarkVisited();
				BreadthFirstHelper(bVertex, VisitFunction);
			}
			aVertex->AdjacentNodes.insertAtBack(nextEdge);
			if (startVertice->IsVisited())
				break;
		}
		startVertice->AdjacentNodes.insertAtBack(thisEdge);
		if (startVertice->IsVisited())
			return;
	}
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
		if (whichVertice->AdjacentNodes.removeFromFront( thisEdge )){
			aVertex = thisEdge.GetAdjacentNode();
			if (!aVertex->IsVisited()){
				//aVertex->MarkVisited();
				VisitFunction(whichVertice, aVertex);
				DepthFirstHelper(aVertex, VisitFunction);
			}
			whichVertice->AdjacentNodes.insertAtBack( thisEdge );
		}
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

bool Graph::IsStronglyConnected(){
	if (!IsDirected())
		return true;

	ClearAllVertices();

	DepthFirstTraversal(0, JustMark);

	for (int i = 0; i < nNodes; i++){
		if (!Nodes[i].IsVisited())
			return false;
	}
	return true;
}

bool Graph::IsCycle(int index){
	if (!IsDirected())
		SpecialCycleTraversal(GetVertPointer(index), CheckCycle);
	else
		BreadthFirstTraversal(GetVertPointer(index), CheckCycle);
		// check cycle will mark every node (except for the first node on the first pass)
	return (GetVertPointer(index)->IsVisited()); 
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

void CheckCycle(Vertice *h, Vertice *n){
	if (h && n)
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

//Homework 8 August 4

//Extend the program for Homework 7 to also print a statement about whether the graph is connected, 
//if undirected, or strongly connected, if directed. The program will finally output the prompt
//Cycle?
//and when the user inputs a letter identifying one of the nodes, will indicate whether there is a 
//cycle including that node. The program will halt when the user inputs a letter which doesn’t
//identify one of the nodes.

//strongly connected means that you can reach all of the nodes from one location???

void main(){
	ifstream fin("c:\\graph.dat");
	Graph graph1;
	while (graph1.LoadGraph(fin)){
		
		if (!graph1.IsDirected()){
			cout << "This graph " << (graph1.IsConnected() ? "is connnected." : "is not connected.") << endl;
		}
		else {
			cout << "This graph " << (graph1.IsStronglyConnected() ? "is strongly connnected." : "is not strongly connected.") << endl;
		}
		
		int wIndex;
		char C;
		cout << "Cycle?";
		cin >> C;
		while ((wIndex = graph1.FindIndex(C)) != -1){
			cout << C << (graph1.IsCycle(wIndex) ? " is in a cycle." : " is not in a cycle.") << endl;
			cout << "Cycle?";
			cin >> C;
		}

	}
	fin.close();

}

/*
Y
N
9
A B C D E F G H I
13
A B
B H
H G
G C
C E
E G
A C
B D
F G
F I
I C
C D
D H
*/
/*
N
N
10
A B C D E F G H I J
11
A B
B G
G I
I J
I H
H D
D B
B C
C D
C E
E F
*/