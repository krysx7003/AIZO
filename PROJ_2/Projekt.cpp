#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

using namespace std;
string fileNames[4] = {"PrimResoult","KruskalResoult","DijkstraResoult","FordBellResoult"};

class Edge{
    int startVertice = 0;
    int endVertice = 0;
    int weigth = 0;
    public:
    int GetStart(){return startVertice;}
    int GetEnd(){return endVertice;}
    int GetWeight(){return weigth;}
    void Print(){
        cout << startVertice << " - " << endVertice << " \t"<< weigth<< " \n";
    }
    Edge(int startVertice,int endVertice,int weigth){
        this->startVertice = startVertice;
        this->endVertice = endVertice;
        this->weigth = weigth;
    }
    Edge(){}
};
class Element{
    int endVertice = 0;
    int weigth = 0;
    public:
    Element* prev;
    Element* next;
    void Print(){
        cout<<endVertice<<"#"<<weigth<<" ";
    }
    int GetEndVertice(){
        return endVertice;
    }
    int GetWieght(){
        return weigth;
    }
    void setAll(int vert,int weight){
        this->weigth = weight;
        endVertice = vert;
    }
    Element(int secondVertice,int newWeight){
        endVertice = secondVertice;
        weigth = newWeight;
    }
    Element(){
        prev = 0;
    }
};
class List{
    int length = 0;
    Element* startElement;
    public:
    void Add(int secondVertice,int newWeight){
        Element* newElement = new Element(secondVertice,newWeight);
        if(startElement==0){
            startElement = newElement;
        }else{
            Element* tmp = startElement;
            for(int i=1;i<length;i++){
                tmp = tmp->next;
            }
            tmp->next = newElement;
            newElement->prev = tmp;
            newElement->next = 0;  
        }
        length++;
    }
    void Print(){
        Element* tmp = startElement;
        for(int i=0;i<length;i++){
            tmp->Print();
            tmp = tmp->next;
        }
    }
    bool CheckForConnection(int lookingFor){
        for(int i=0;i<length;i++){
            if(lookingFor == this->Get(i)->GetEndVertice()){
                return true;
            }
        }
        return false;
    }
    int GetLenght(){
        return length;
    }
    
    Element* Get(int id){
        if(id<length){
            Element* tmp = startElement;
            for(int i=0;i<id;i++){
                tmp = tmp->next;
            }
            return tmp; 
        }
        return nullptr;
    }
    List(){
        startElement=0;
    }
};
class Set{
    int* firstVal;
    int* secondVal;
    int length;
    int pos = 0;
    public:
    void AddAt(int fval,int sval){
        firstVal[pos] = fval;
        secondVal[pos] = sval;
        pos++;
    }
    bool IsInSet(int fval,int sval){
        for(int i=0;i<pos;i++){
            if(firstVal[i]==fval && secondVal[i] ==sval){
                return true;
            }else{
                if(firstVal[i]==sval && secondVal[i] ==fval){
                    return true;
                }
            }
        }
        return false;
    }
    int getLength(){return pos;}
    Set(int length){
        this->length = length;
        firstVal = new int[length];
        secondVal = new int[length];
        for (int i = 0; i < length; i++) {
            firstVal[i] = 0;
            secondVal[i] = 0;
        }
    }
};
struct DisjointSets   
{   
    int *parent, *rnk;   
    int n;     
    int Find(int u){   
        if (u != parent[u])   
            parent[u] = Find(parent[u]);   
        return parent[u];   
    }   
    void Merge(int x, int y){   
        x = Find(x), y = Find(y);    
        if (rnk[x] > rnk[y])   
            parent[y] = x;   
        else 
            parent[x] = y;   
  
        if (rnk[x] == rnk[y])   
            rnk[y]++;   
    }
    DisjointSets(int n){   
        this->n = n;   
        parent = new int[n+1];   
        rnk = new int[n+1];   
        for (int i = 0; i <= n; i++)   
        {   
            rnk[i] = 0;   
            parent[i] = i;   
        }   
    }    
};   
class Graph{
    double internalDensity = 0.25;
    List** adjacencyList;
    int** graphMatrix;
    int vertices = 0;
    int edges = 0;
    bool internalDirected;
    public:
    void ReadFromFile(string fileName,bool directed){
        ifstream file;
        int buffer;
        int firstVertice,secondVertice,newWeight;
        file.open(fileName);
        if(file.good()==true){
            file>>vertices;
            file>>edges;
            InitializeMemory();
            int i = 0;
            while(!file.eof()){
                file>>firstVertice>>secondVertice>>newWeight;
                adjacencyList[firstVertice]->Add(secondVertice,newWeight);
                if(!directed){
                    adjacencyList[secondVertice]->Add(firstVertice,newWeight);
                }
                graphMatrix[i][firstVertice] = newWeight;
                if(!directed){
                    graphMatrix[i][secondVertice] = newWeight;
                }else{
                    graphMatrix[i][secondVertice] = newWeight*-1;
                }
                i++;
            }
            file.close();
        }
    }
    void InitializeMemory(){
        adjacencyList = new List*[vertices];
        graphMatrix =new int*[edges];
        for(int i=0;i<vertices;i++){
            adjacencyList[i] = new List();
        }
        for(int i=0;i<edges;i++){
            graphMatrix[i] = new int[vertices];
        }
        for (int i = 0; i < edges; i++) {
            for (int j = 0; j < vertices; j++) {
                graphMatrix[i][j] = 0;
            }
        }
    }
    void GenerateUp(){
        int j=0;
        edges = edges*internalDensity;
        for(int i=1;i<vertices;i++){
            int u = i-1;
            int v = i;
            int weight = rand()%100+1;
            adjacencyList[v]->Add(u,weight);
            adjacencyList[u]->Add(v,weight);
            graphMatrix[i-1][v] = weight;
            if(!internalDirected){
                graphMatrix[i-1][u] = weight;
            }else{
                graphMatrix[i-1][u] = weight*-1;
            }
            j++;
        }
        for(;j<edges;j++){
            int u =0;
            int v =0;
            while(u==v || adjacencyList[u]->CheckForConnection(v)){
                u = rand()%vertices;
                v = rand()%vertices;    
            }
            int weight = rand()%100+1;
            adjacencyList[v]->Add(u,weight);
            adjacencyList[u]->Add(v,weight);
            graphMatrix[j][v] = weight;
            if(!internalDirected){
                graphMatrix[j][u] = weight;
            }else{
                graphMatrix[j][u] = weight*-1;
            }
        }
    }
    bool wasRemoved(int removedEdges[],int edgesToRemove,int e){
        for(int j=0;j<edgesToRemove;j++){
            if(removedEdges[j]==e){
                return true;
            }
        }
        return false;
    }
    void CreateList(){
        adjacencyList = new List*[vertices];
        for(int i=0;i<vertices;i++){
            adjacencyList[i] = new List();
        }
        
        for(int e =0;e<edges;e++){
            int isSecond = 0;
            int startVert=0;
            int endVert=0;
            int weight=0;
            for(int v=0;v<vertices;v++){
                if(graphMatrix[e][v]>0 && isSecond==0){
                    startVert=v;
                    weight = graphMatrix[e][v];
                    isSecond++;
                }else{
                    if(graphMatrix[e][v]){
                        endVert=v;
                    }
                }
            }
            adjacencyList[startVert]->Add(endVert,weight);
            adjacencyList[endVert]->Add(startVert,weight);
        }    
    }
    void GenerateDown(){
        int e=0;
        for(int v=0;v<vertices;v++){
            int i;
            if(!internalDirected){
                i=v+1;
            }else{
                i = 0;
            }
            for(;i<vertices;i++){
                if(i!=v){
                    int weight = rand()%100+1;
                    graphMatrix[e][v] = weight;
                    if(!internalDirected){
                        graphMatrix[e][i] = weight;
                    }else{
                        graphMatrix[e][i] = weight*-1;
                    }
                    e++;
                }
            }  
        }
        double dens = 1-internalDensity;
        int edgesToRemove = dens*edges;
        int removedEdges[edgesToRemove];
        int edgeCount = 1;
        for(int i=0;i<edgesToRemove;i++){
            removedEdges[i]=0;
        }
        for(int i=0;i<edgesToRemove;i++){
            int e = rand()%edges;
            while(wasRemoved(removedEdges,edgesToRemove,e)){
                e = rand()%edges;
            }
            int j=e;
            while(j<edges-edgeCount){
                int* tmp = graphMatrix[j+1];
                graphMatrix[j] = tmp;
                j++;
            }
            graphMatrix[j] = nullptr;
            edgeCount++;
            removedEdges[i]=e;
        }
        edges=internalDensity*edges;
        CreateList();
    }   
    void GenerateRandom(){ 
        InitializeMemory();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        if(internalDensity<=0.5){
            GenerateUp();
        }else{
            GenerateDown();
        }
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        cout<<duration.count()<<"\n";
    }
    void PrintList(){
        cout<<edges<<"\n";
        if(vertices ==0){
            cout<<"Graf nie zostal wypelniony\n";
        }
        for(int i=0;i<vertices;i++){
            cout<<i<<":";
            adjacencyList[i]->Print();
            cout<<"\n";
        }
    }
    void PrintMatrix(){
        if(vertices == 0){
            cout<<"Graf nie zostal wypelniony\n";
        }
        for(int j=0;j<vertices;j++){
            for(int i=0;i<edges;i++){ 
                cout.width(3);
                cout<<right<< graphMatrix[i][j]<<" ";
            }
            cout<<"\n";
        }      
    }
    void SetDensity(double targetDensity){
        if(targetDensity<=1){
            internalDensity = targetDensity;
        }else{
            cout<<"Gestosc nie moze przekroczyc 1\n";
        } 
    }
    void SetEdges(int targetEdges){edges = targetEdges;}
    double GetDensity(){return internalDensity;}
    bool GetDirected(){return internalDirected;}
    int GetEdges(){return edges;}
    int GetVertices(){return vertices;}
    List* GetListItem(int id){return adjacencyList[id];}
    int GetMatrixItem(int i,int j){return graphMatrix[i][j]; }
    Graph(){}
    Graph(int verticeAmmount,bool directed,double density){
        vertices = verticeAmmount;
        internalDensity = density;
        internalDirected = directed;
        if(!internalDirected){
            edges = ((vertices*(vertices-1))/2);
        }else{
            edges = ((vertices*(vertices-1)));
        }
    }
};
class Algorithm{
    Graph* graphToSolve;
    public:
    virtual double RunList(){return 0;}
    virtual double RunMatrix(){return 0;}
    virtual void PrintReturnList(){}
    void RunAlgorithm(){
        WriteToFile(to_string(this->RunList())+","+to_string(this->RunMatrix())+",");
    }
    virtual void SetGraph(Graph* graph){}
    virtual void WriteToFile(string row){}
    Algorithm(string file){
        
    }
    Algorithm(){}

};
class Prim : public Algorithm{
    string fileName = "PrimResoult";
    Graph* graphToSolve;
    bool test = false;
    void printMST(Edge* edges[]){
        cout << "Edge \tWeight\n";
        for (int i = 0; i < graphToSolve->GetVertices()-1; i++){
            edges[i]->Print();
        }    
    }
    void WriteToFile(string row)override{
        ofstream file;
        file.open(fileName+".csv",ios_base::app);
        file<<row;
        file.close();
    }
    public:
    double RunList() override{
        int V = graphToSolve->GetVertices();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        bool visited[V];
        for(int i=0;i<V;i++){
            visited[i]=false;
        }
        visited[0]=true;
        List* list;
        Edge* edges[V];
        int numEdges = 0;
        while(numEdges<V-1){
            int min = INT_MAX;
            for(int v=0; v<V;v++){
                if(visited[v]==true){
                    list = this->graphToSolve->GetListItem(v);
                    for(int e=0;e<list->GetLenght();e++){
                        Element* element = list->Get(e);
                        int weight = element->GetWieght();
                        int id = element->GetEndVertice();
                        if(min>weight && weight && !visited[id]){
                            min = weight;
                            edges[numEdges] = new Edge(v,id,min);
                        }
                    }
                }
            }
            visited[edges[numEdges]->GetEnd()]=true;
            numEdges++;
        }
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        if(test){
            printMST(edges);
        }
        return duration.count();}
    double RunMatrix() override{
        int V = graphToSolve->GetVertices();
        int E = graphToSolve->GetEdges();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        bool visited[V];
        for(int i=0;i<V;i++){
            visited[i]=false;
        }
        int numEdges = 0;
        visited[0]=true;
        Edge* edges[V];
        while(numEdges<V-1){
            int min = INT_MAX;
            for(int v=0; v<V;v++){
                if(visited[v]==true){
                    for(int e=0;e<E;e++){
                        if(min>graphToSolve->GetMatrixItem(e,v) && graphToSolve->GetMatrixItem(e,v) ){
                            int id=0;
                            for(int i =0;i<V;i++){
                                if(graphToSolve->GetMatrixItem(e,i) && i!=v){
                                    id = i;
                                    i=V;
                                    if(!visited[id]){
                                        min = graphToSolve->GetMatrixItem(e,v);
                                        edges[numEdges] = new Edge(v,id,min);
                                    }
                                }
                            }
                            
                        }
                    }
                }
            }
            visited[edges[numEdges]->GetEnd()]=true;
            numEdges++;
        }
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        if(test){
            printMST(edges);
        }
        return duration.count();
    }
    void RunAlgorithm(){Algorithm::RunAlgorithm();}
    Prim(string fileName,Graph* graf){
        this->graphToSolve = graf;
        this->fileName=fileName;
    }
    Prim(){}
    Prim(Graph* graf,bool test){
        this->graphToSolve = graf;
        this->test = test;
    }
};
class Kruskal : public Algorithm{
    string fileName = "KruskalResoult";
    Graph* graphToSolve;
    bool test = false;
    void WriteToFile(string row)override{
        ofstream file;
        file.open(fileName+".csv",ios_base::app);
        file<<row;
        file.close();
    }
    void printMST(Edge* edges[]){
        cout << "Edge \tWeight\n";
        for (int i = 0; i < graphToSolve->GetVertices()-1; i++){
            edges[i]->Print();
        }    
    }
    void QuickSort(Edge* toBeSortedTabel[],int start,int stop){
        int i = start;//Indeks i to początek ciągu/podciągu
        int j = stop;//Indeks j to koniec ciągu/podciągu
        Edge* pivot = toBeSortedTabel[(start+stop)/2];//Wybór wartości pivota według wybranego trybu
        while (i <= j) {
            //Iteracja z obu końców tablicy
            //Jeżeli i-ty element jest mniejszy od pivota zostaje wybrany
            while (toBeSortedTabel[i]->GetWeight() < pivot->GetWeight()) {
                i++;
            }
            //Jeżeli j-ty element jest większy od pivota zostaje wybrany
            while (toBeSortedTabel[j]->GetWeight() > pivot->GetWeight()) {
                j--;
            }
            //Jeżeli ideksy się nie przecięły
            if (i <= j) {
                //Wybrane elementy zostają zamienione 
                swap(toBeSortedTabel[i], toBeSortedTabel[j]);
                i++;
                j--;
            }
        }
        //Warunkowa rekurencja
        if (start < j) {
            QuickSort(toBeSortedTabel,start, j);
        }
        if (i < stop) {
            QuickSort(toBeSortedTabel,i, stop);
        }
    }
    void GetMST(Edge* edges[]){
        int V = graphToSolve->GetVertices();
        int E = graphToSolve->GetEdges();
        int numEdges = 0;
        Edge* mst[E];
        DisjointSets ds(V);   
        for(int i=0;i<E;i++){
            int u = edges[i]->GetStart();
            int v = edges[i]->GetEnd();
            int set_u = ds.Find(u);
            int set_v = ds.Find(v);
            if (set_u != set_v)   
            {   
                ds.Merge(set_u, set_v);
                mst[numEdges]=new Edge(u,v,edges[i]->GetWeight());
                numEdges++;   
            }
            if(numEdges>=V-1){
                break;
            }
        }
        if(test){
            printMST(mst);
        }
        
    }
    public:
    double RunList() override{
        int V = graphToSolve->GetVertices();
        int E = graphToSolve->GetEdges();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        Edge* edges[E];
        List* list;
        Set* setFilled = new Set(E);
        int numEdges = 0;
        for(int v =0;v<V;v++){
            list = this->graphToSolve->GetListItem(v);
            int tmp = list->GetLenght();
            for(int e=0;e<tmp;e++){
                Element* element = list->Get(e);
                int endVertice = element->GetEndVertice();
                if(!setFilled->IsInSet(v,endVertice)){
                    edges[numEdges] = new Edge(v,endVertice,element->GetWieght());
                    numEdges++;
                    setFilled->AddAt(v,endVertice);
                }
            }
        }
        QuickSort(edges,0,E-1);
        GetMST(edges);
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        return duration.count();
    }
    double RunMatrix() override{
        int V = graphToSolve->GetVertices();
        int E = graphToSolve->GetEdges();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        Edge* edges[E];
        for(int e=0;e<E;e++){
            for(int v =0;v<V;v++){
                if(graphToSolve->GetMatrixItem(e,v)){
                    for(int i =v+1;i<V;i++){
                        if(graphToSolve->GetMatrixItem(e,i)){
                            edges[e] = new Edge(v,i,graphToSolve->GetMatrixItem(e,v));
                            v=V;
                            i=V;
                        }
                    }
                }
            }
        }
        QuickSort(edges,0,E-1);
        GetMST(edges);
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        return duration.count();
    }
    void RunAlgorithm(){Algorithm::RunAlgorithm();}
    void SetGraph(Graph* graph)override{this->graphToSolve= graph;}
    Kruskal(string fileName,Graph* graf){
        this->graphToSolve = graf;
        this->fileName=fileName;
    }
    Kruskal(){}
    Kruskal(Graph* graf,bool test){
        this->graphToSolve = graf;
        this->test = test;
    }
};
class Dijkstra : public Algorithm{
    string fileName = "DijkstraResoult";
    Graph* graphToSolve;
    bool test = false;
    void WriteToFile(string row)override{
        ofstream file;
        file.open(fileName+".csv",ios_base::app);
        file<<row;
        file.close();
    }
    int minDistance(int dist[], bool sptSet[]){
        int V = graphToSolve->GetVertices();
        int min = INT_MAX, min_index;
        for (int v = 0; v < V; v++){
            if (sptSet[v] == false && dist[v] <= min){
                min = dist[v], min_index = v;
            }
        }
        return min_index;
    }
    void printSolution(int dist[]){
        int V = graphToSolve->GetVertices();
        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < V; i++)
            cout << i << " \t\t\t\t" << dist[i] << endl;
    }
    public:
    double RunList() override{
        int V = graphToSolve->GetVertices();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        int dist[V];
        bool sptSet[V];
        List* list;
        for (int i = 0; i < V; i++)
            dist[i] = INT_MAX, sptSet[i] = false;
        dist[0] = 0;
        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;
            list = this->graphToSolve->GetListItem(u);
            for(int e=0;e<list->GetLenght();e++){
                Element* element = list->Get(e);
                int weight = element->GetWieght();
                int vertice = element->GetEndVertice();
                if (!sptSet[vertice] && dist[u] != INT_MAX && dist[u] + weight < dist[vertice]){
                    dist[vertice] = dist[u] + weight;
                }  
            }
                   
        }
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        if(test){
            printSolution(dist);
        }
        return duration.count();
    }
    double RunMatrix() override{
        int V = graphToSolve->GetVertices();
        int E = graphToSolve->GetEdges();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        int dist[V]; 
        bool sptSet[V];
        for (int i = 0; i < V; i++)
            dist[i] = INT_MAX, sptSet[i] = false;
        dist[0] = 0;
        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;
            for (int e = 0; e < E; e++){
                if (graphToSolve->GetMatrixItem(e,u)>0 && dist[u] != INT_MAX){
                    for(int i =0;i<V;i++){
                        if(graphToSolve->GetMatrixItem(e,i) && i!=u){
                            int id = i;
                            i=V;
                            if(!sptSet[id] && dist[u] + graphToSolve->GetMatrixItem(e,u)  < dist[id] ){
                                dist[id] = dist[u] + graphToSolve->GetMatrixItem(e,u) ;
                            }
                        }
                    }  
                }
            }        
        }
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        if(test){
            printSolution(dist);
        }
        return duration.count();
    }
    void RunAlgorithm(){Algorithm::RunAlgorithm();}
    void SetGraph(Graph* graph)override{this->graphToSolve= graph;}
    Dijkstra(string fileName,Graph* graf){
        this->graphToSolve = graf;
        this->fileName=fileName;
    }
    Dijkstra(){}
    Dijkstra(Graph* graf,bool test){
        this->graphToSolve = graf;
        this->test = test;
    }
};
class FordBell : public Algorithm{
    string fileName = "FordBellResoult";
    Graph* graphToSolve;
    bool test = false;
    void WriteToFile(string row)override{
        ofstream file;
        file.open(fileName+".csv",ios_base::app);
        file<<row;
        file.close();
    }
    void printSolution(int dist[]){
        int V = graphToSolve->GetVertices();
        cout << "Vertex \t Distance from Source" << endl;
        for (int i = 0; i < V; i++)
            cout << i << " \t\t\t\t" << dist[i] << endl;
    }
    public:
    double RunList() override{
        int V = graphToSolve->GetVertices();
        int E = graphToSolve->GetEdges();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        int dist[V];
        List* list;
        for (int i = 0; i < V; i++)
            dist[i] = INT_MAX;
        dist[0] = 0;
        for (int u = 0; u <= V - 1; u++) {
            list = this->graphToSolve->GetListItem(u);
            for (int e = 0; e < list->GetLenght(); e++) {
                Element* element = list->Get(e);
                int v = element->GetEndVertice();
                int weight = element->GetWieght();
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                    dist[v] = dist[u] + weight;
                }   
            }
        }
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        if(test){
            printSolution(dist);
        }
        return duration.count();
    }
    double RunMatrix() override{
        int V = graphToSolve->GetVertices();
        int E = graphToSolve->GetEdges();
        auto startT = chrono::high_resolution_clock::now();//Początek pomiaru czasu
        int dist[V];
        for (int i = 0; i < V; i++)
            dist[i] = INT_MAX;
        dist[0] = 0;
        for (int u = 0; u <= V - 1; u++) {
            for (int e = 0; e < E; e++) {
                if(graphToSolve->GetMatrixItem(e,u)>0){
                    for(int k = 0;k<V;k++){
                        if(graphToSolve->GetMatrixItem(e,k) && k!=u){
                            int v =k;
                            k=V;
                            int weight = graphToSolve->GetMatrixItem(e,u);   
                            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                                dist[v] = dist[u] + weight;
                            }                            
                        }
                    }
                }        
            }
        }
        auto endT = chrono::high_resolution_clock::now();//Koniec pomiaru czasu
        chrono::duration<double, nano> duration = endT - startT;//Czas wykonania zapisany w ns
        if(test){
            printSolution(dist);
        }
        return duration.count();
    }
    void RunAlgorithm(){Algorithm::RunAlgorithm();}
    void SetGraph(Graph* graph)override{this->graphToSolve= graph;}
    FordBell(string fileName,Graph* graf){
        this->graphToSolve = graf;
        this->fileName=fileName;
    }
    FordBell(){}
    FordBell(Graph* graf,bool test){
        this->graphToSolve = graf;
        this->test = test;
    }
};
class Simulation{
    int repetitions;
    double densities[4] = {0.25,0.5,0.75,0.99};
    Algorithm* algorithms[4];
    void WriteToFile(string row,string fileName[]){
       ofstream file;
       for(int i=0;i<4;i++){
            file.open(fileName[i]+".csv",ios_base::app);
            file<<row;
            file.close();
       }
    }
    void WriteHeader(int vertices){
        WriteToFile(to_string(vertices)+"\n",fileNames);
        for(int i=0;i<4;i++){
            WriteToFile("Density "+to_string(densities[i])+",,",fileNames);
        }
        WriteToFile("\n",fileNames);
        for(int i=0;i<4;i++){
            WriteToFile("Time with List,Time with Matrix,",fileNames);
        }
        WriteToFile("\n",fileNames);
    }
    public:
    void Run(int vertices){    
        WriteHeader(vertices);
        for(int i=0;i<repetitions;i++){
            for(int j=0;j<4;j++){ 
                Graph* grafProb1 = new Graph(vertices,false,densities[j]);
                Graph* grafProb2 = new Graph(vertices,true,densities[j]);
                grafProb1->GenerateRandom(); 
                grafProb2->GenerateRandom();
                algorithms[0] = new Prim(fileNames[0],grafProb1);
                algorithms[1] = new Kruskal(fileNames[1],grafProb1);
                algorithms[2] = new Dijkstra(fileNames[2],grafProb2);
                algorithms[3] = new FordBell(fileNames[3],grafProb2);
                for(int k=0;k<4;k++){
                    algorithms[k]->RunAlgorithm();  
                }
                   
            }
            WriteToFile("\n",fileNames);
        }
    }
    Simulation(int repetitions){
        this->repetitions=repetitions;
    }
    Simulation(){}       
};
Graph* graf = new Graph();
Simulation* sim = new Simulation();
void RunSingleAlg(Algorithm* algToRun){
    char choice;
    cout<<"Jak wykonac algorytm Listowo/Macierzowo(l/m)\n";
    cout<<"> ";
    cin>>choice;
    if(choice =='l'){
        cout<<algToRun->RunList()<<"\n";
        algToRun->PrintReturnList();
    }else{
        if(choice == 'm'){
            cout<<algToRun->RunMatrix()<<"\n";
            algToRun->PrintReturnList();
        }else{
            cout<<"Niepoprawny wybor\n";
        }
    }
    cout<<"Kontynuuj";
    cout<<"> ";
    cin>>choice;
}
void menu(){
    cout<<"=====================================\n";
    cout<<"                Menu                 \n";
    cout<<"=====================================\n";
    cout<<"1.Wczytaj dane z pliku\n";
    cout<<"2.Wygeneruj losowe dane\n";
    cout<<"3.Wyswietl graf listowo i macierzowo\n";
    cout<<"4.Problem 1 metoda Prima\n";
    cout<<"5.Problem 1 metoda Kruskala\n";
    cout<<"6.Problem 2 metoda Dijkstry\n";
    cout<<"7.Problem 2 metoda Forda-Bellmana\n";
    cout<<"8.Uruchom symulacje\n";
    cout<<"9.Zakoncz program\n";
    cout<<"=====================================\n";
    cout<<"Wybierz akcje: \n";//Zapytanie do użytkownika
    char choice;
    int vertices = 0;
    int edges = 0;
    double density = 0;
    string buffor;
    ofstream file;
    bool directed;
    Prim* primAlg;
    Kruskal* kruskAlg;
    Dijkstra* djikAlg;
    FordBell* fordAlg;
    srand (time(NULL));
    cout<<"> ";
    cin>>choice;
    switch (choice)
    {
    case '1':
        graf = new Graph();
        cout<<"Podaj nazwe pliku do otworzenia(bez .txt)\n";
        cout<<"> ";
        cin>>buffor;
        cout<<"Czy graf powinien byc skierowany(y/n)\n";
        cout<<"> ";
        cin>>choice;
        if(choice =='y'){
            directed =true;
        }
        else{
            if(choice =='n'){
                directed =false;
            }
            else{
                cout<<"Niepoprawny wybor\n";
                menu();
            }
        }
        graf->ReadFromFile(buffor+".txt",directed);
        menu();
        break;
    case '2':
        cout<<"Podaj ilosc wierzcholkow:\n";
        cout<<"> ";
        cin>>vertices;
        cout<<"Podaj gestosc:\n";
        cout<<"> ";
        cin>>density;
        cout<<"Czy graf powinien byc skierowany(y/n)\n";
        cout<<"> ";
        cin>>choice;
        if(choice =='y'){
            directed =true;
        }
        else{
            if(choice =='n'){
                directed =false;
            }
            else{
                cout<<"Niepoprawny wybor\n";
                menu();
            }
        }
        graf = new Graph(vertices,directed,density); 
        graf->GenerateRandom();
        menu();
        break;
    case '3':
        cout<<"Jak wypisac Graf(l/m)\n";
        cout<<"> ";
        cin>>choice;
        if(choice =='l'){
            graf->PrintList();
        }else{
            if(choice == 'm'){
                graf->PrintMatrix();
            }else{
                cout<<"Niepoprawny wybor\n";
            }
        }
        cout<<"Kontynuuj";
        cout<<"> ";
        cin>>choice;
        menu();
        break;
    case '4':
        if(!graf->GetDirected()){
            primAlg=new Prim(graf,true); 
            RunSingleAlg(primAlg);
        }else{
            cout<<"Podany graf jest skierowany";
        }
        menu();
        break;
    case '5':
        if(!graf->GetDirected()){
            kruskAlg = new Kruskal(graf,true);
            RunSingleAlg(kruskAlg);
        }else{
            cout<<"Podany graf jest skierowany";
        }
        menu();
        break;
    case '6':
        if(graf->GetDirected()){
            djikAlg = new Dijkstra(graf,true);
            RunSingleAlg(djikAlg);
        }else{
            cout<<"Podany graf nie jest skierowany";
        }
        menu();
        break;
    case '7':
        if(graf->GetDirected()){
            fordAlg = new FordBell(graf,true);
        }else{
            cout<<"Podany graf nie jest skierowany";
        }
        RunSingleAlg(fordAlg);
        menu();
        break;
    case '8':
        sim = new Simulation(50);
        for(int i=0;i<4;i++){
            file.open(fileNames[i]+".csv");
            file.clear();
            file.close();
        }
        sim->Run(100);
        sim->Run(200);
        sim->Run(300);
        sim->Run(400);
        sim->Run(500);
        sim->Run(600);
        sim->Run(700);
        menu();
        break;
    case '9':
        break;        
    default:
        cout<<"Niepoprawny wybor\n";
        menu();
    }
}

int main(){
    menu();
    return 0;
}    