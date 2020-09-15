#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX_NUM 20
#define INFINITY 32768

typedef enum{
	DG, // directed gragh
	DN, // directed network
	UDG, // undirected gragh
	UDN  // undirected network
} graphKind;
typedef char vertexData;
typedef int adjType;
typedef char* otherInfo;

/*
define a gragh
*/
// express a graph
// 1. adjacency matrix
// 2. adjacency list 
// 3. orthogonal linked list
// 4. adjacency multilist(for undirected graph and undirected network)
typedef struct
{
	adjType adj;
	otherInfo info;
} node;
typedef struct
{
	vertexData vexs[MAX_VERTEX_NUM]; // vertexes
	node arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // arches/edges
	int vexnum, arcnum; // the number of vertexes and arches/edges
	//graghKind kind; 
} adjMat;

// initialize a directex/undirected network/graph
adjMat* init()
{
	adjMat* g = (adjMat*)malloc(sizeof(adjMat));
	g->arcnum = 0;
	g->vexnum = 0;
	int i,j;
	for(i=0;i<MAX_VERTEX_NUM;i++)
	{
		for(j=0;j<MAX_VERTEX_NUM;j++)
			g->arcs[i][j].adj = INFINITY;
	}
	for(i=0;i<MAX_VERTEX_NUM;i++)
		g->vexs[i] = '\t';
	return g;
}

// find the position of a vertex in a directed/undirected graph/network
int locate(adjMat* g, vertexData data)
{
	if(data == '\t')
		return -1;
	int n;
	for(n=0;n<g->vexnum;n++)
	{
		if(g->vexs[n] == data)
			return n;
	}
	//puts("node is not in the graph!");
	return -1;
}

// create a directed network(directed graph, undirected gragh, undirected network are all alike)
void create(adjMat* g)
{
	int vexnum, arcnum;
	puts("please input the number of vertexes:");
	scanf("%d", &vexnum);
	puts("please input the number of arches/edges:");
	scanf("%d", &arcnum);
	g->vexnum = vexnum;
	g->arcnum = arcnum;
	
	int i;
	char c;
	for(i=0;i<vexnum;i++)
	{
		// clear buffer
		while(char buff=getchar() == '\t' || buff == EOF)
			printf("%c", buff);
		printf("please input the name of NO.%d vertex:\n", i);
		scanf("%c", &c);
		g->vexs[i] = c;
	}
	
	int t, h, value;
	char tail, head;
	for(i=0;i<arcnum;i++)
	{
		// clear buffer
		while(char buff=getchar() == '\t' || buff == EOF)
			printf("%c", buff);
		printf("please input the tail, head, value of the NO.%d arch in sequence:\n", i);
		scanf("%c %c %d", &tail, &head, &value);
		t = locate(g, tail);
		h = locate(g, head);
		(g->arcs[t][h]).adj = value;
	}
	puts("done!");
}

// show a graph using adjacent matrix
void show(adjMat* g)
{
	int row;
	int col;
	for(col=0;col<g->vexnum;col++)
		printf("  %c", g->vexs[col]);
	for(row=0;row<g->vexnum;row++)
	{
		printf("\n%c ", g->vexs[row]);
		for(col=0;col<g->vexnum;col++)
		{
			if(g->arcs[row][col].adj == INFINITY)
				printf("-- ");
			else
				printf("%d, ", g->arcs[row][col].adj);		
		}
		printf("\n");
	}
	printf("\n");
}

// get the value of a vertex in a directed/undirected graph/network
vertexData get(adjMat* g, int k)
{
	if(k >= g->vexnum || k < 0)
	{
		//printf("ERROR:index error! please input a number between 0 and %d!\n", g->vexnum-1);
		return '\t';
	}
	return g->vexs[k];
}


// find the first adjacent vertex of a vertex(when it is a directed the adjacent vertex is the head of an arch)
vertexData firstAdj(adjMat* g, vertexData data)
{
	int n = locate(g, data);
	if(n == -1)
		return '\t';
	int i;
	for(i=0;i<g->vexnum;i++)
	{
		if((g->arcs[n][i]).adj != INFINITY)
			return g->vexs[i];
	}
	//puts("this vertex does not have an adjacent vertex!");
	return '\t';
}

// find the next adjacent vertex(when it is a directed the adjacent vertex is the head of an arch)
vertexData nextAdj(adjMat* g, vertexData data, vertexData data1)
{
	int n = locate(g, data);
	if(n == -1)
		return '\t';
	int i = locate(g, data1);
	if(i == -1)
		return '\t';
	else
		i = i + 1;
	for(;i<g->vexnum;i++)
	{
		if((g->arcs[n][i]).adj != INFINITY)
			return g->vexs[i];
	}
	//puts("the vertex %c is already the last adjacent vertex of vertex %c", data1, data);
	return '\t';
}

// insert a vertex(without new arches/edges) into a graph
void insert(adjMat* g, vertexData data)
{
	if(g->vexnum == MAX_VERTEX_NUM)
	{
		puts("the graph/network has no place for new nodes!");
		return;
	}
	if(locate(g, data) != -1)
	{
		puts("vertex already included!");
		return;
	}  
	g->vexnum++;
	g->vexs[g->vexnum-1] = data;
}

// delete a vertex(includeing its all adjacent arches/edges) from a graph
void del(adjMat* g, vertexData data)
{
	int pos = locate(g, data);
	if(pos == -1)
		return;
	// delete the arches/edges
	int n = 0;
	int i;
	for(i=0;i<g->vexnum;i++)
	{
		if(g->arcs[pos][i].adj != INFINITY)
			n++;
		if(g->arcs[i][pos].adj != INFINITY)
			n++;
	}
	g->arcnum = g->arcnum-n;
	
	// delete the vertex
	for(i=pos;i<g->vexnum-1;i++)
	{
		g->vexs[i] = g->vexs[i+1];
	}
	g->vexs[i] = '\t';

	int j;
	for(i=pos;i<g->vexnum-1;i++)
		for(j=0;j<g->vexnum;j++)
			g->arcs[i][j].adj = g->arcs[i+1][j].adj;			
	for(i=pos;i<g->vexnum-1;i++)
		for(j=0;j<g->vexnum;j++)
			g->arcs[j][i].adj = g->arcs[j][i+1].adj;
	for(j=0;j<g->vexnum;j++)
	{
		g->arcs[i][j].adj = INFINITY;
		g->arcs[j][i].adj = INFINITY;
	}
	
	g->vexnum--;
}

// insert an edge/arch bewteen two vertexes
void insArc(adjMat* g, vertexData s, vertexData e, adjType value)
{
	int start = locate(g, s);
	int end = locate(g, e);
	if(start == -1 || end == -1)
	{
		printf("%c or %c unknow please add vertex firstly\n", s, e);
		return;
	}
	g->arcs[start][end].adj = value;
	g->arcnum++;
}

// delete the arch between two vertexes
void delArc(adjMat* g, vertexData s, vertexData e)
{
	int start =  locate(g, s);
	int end = locate(g, e);
	if(start == -1 || end == -1)
		return;
	if(g->arcs[start][end].adj != INFINITY)
		g->arcs[start][end].adj = INFINITY;
	g->arcnum--;
}

// traverse a graph
int visited[MAX_VERTEX_NUM];

void depthFirst(adjMat* g, vertexData d)
{
	if(visited[locate(g, d)] != 1) 
	{
		printf("%c", d);
		visited[locate(g, d)] = 1;
	}
	vertexData dt = firstAdj(g, d);
	while(dt != '\t')
	{
		if(visited[locate(g, dt)] != 1)
			depthFirst(g, dt);
		dt = nextAdj(g, d, dt);
	}
}

void breathFirst(adjMat* g, vertexData d)
{
	if(visited[locate(g, d)] == 1)
		return;
	// use queue
	vertexData queue[g->vexnum];
	int head = 0, rear = 0;
	// print
	printf("%c", d);
	visited[locate(g, d)] = 1;
	// enter
	queue[rear] = d;
	rear = (rear+1)%g->vexnum;
	vertexData dt;
	while(head != rear)
	{
		dt = queue[head];
		head = (head+1)%g->vexnum; 
		// visit and enter all the adjacent vertexes which have not been visited yet
		vertexData dAdj = firstAdj(g, dt);
		while(dAdj != '\t')
		{
			if(visited[locate(g, dAdj)] != 1)
			{
				// print
				printf("%c", dAdj);
				visited[locate(g, dAdj)] = 1;
				// enter
				queue[rear] = dAdj;
				rear = (rear+1)%g->vexnum;		
			}
			dAdj = nextAdj(g, dt, dAdj);		
		}
	} 
}

void traverse(adjMat*g, vertexData d, char mode)
{
	if(locate(g, d) == -1)
		return;
	
	int i;
	for(i=0;i<MAX_VERTEX_NUM;i++)
	{
		visited[i] = 0;
	}
	// traverse in depth first mode
	if(mode == 'd')
		depthFirst(g, d);
	// traverse in breadth first mode
	else
		breathFirst(g, d);	
	int k;
	for(k=0;k<g->vexnum;k++)
	{
		if(visited[k] != 1)
		{
			d = get(g, k);
			if(mode == 'd')
				depthFirst(g, d);
			else
				breathFirst(g, d);
		}
	}		
} 

// find a path between two vertexes
int* pre;

void printPath(adjMat* g, int s, int e)
{
	char stack[g->vexnum];
	int i = -1;
	int n = e;
	while(n != s)
	{
		i++;
		stack[i] = get(g, n);
		n = pre[n];
	}
	printf("%c", get(g,s));
	for(;i>=0;i--)
	{
		printf("->%c", stack[i]);
	}
}

int depthFP(adjMat* g, int s, int e)
{
	char start = get(g, s);
	char c;
	for(c=firstAdj(g, start);c!='\t';c=nextAdj(g, start, c))
	{
		if(pre[locate(g, c)] == -1)
		{
			pre[locate(g, c)] = s;
			if(locate(g, c) == e)
				return 1;		
			else if(depthFP(g, locate(g,c), e) == 1)
				return 1;
		}
	}
	return 0;
}

void path(adjMat* g, int s, int e)
{
	if(s < 0 || e < 0 || s >= g->vexnum || e >= g->vexnum || s == e)
	{
		printf("index error! index should no less than 0 and less than %d and start point and end point should be different!\n", g->vexnum);
		return;
	}
	pre = (int*)malloc(g->vexnum*sizeof(int));
	int i;
	for(i=0;i<g->vexnum;i++)
		pre[i] = -1;
	pre[s] = s;
	// find a path using depth first search
	if(depthFP(g, s, e) == 1)
		printPath(g, s, e);
	else
		printf("there is no path from %c to %c\n", get(g, s), get(g, e));
	free(pre);
}

// minimum spanning tree(for a connected graph or connected network)
typedef struct nod
{
	int tail;
	int head;
	int weight;
} nod, *mstree;
// prim algorithm is suitable for a connected graph or network with many edges
// it can be used for a strongly connected graph/network(in this case, a root node should be selected first(not all node can be used as the root node!))
// prim algorithm is a kind of greedy algorithm
int notIn(int* array, int count, int i)
{
	int k;
	for(k=0;k<count;k++)
	{
		if(array[k] == i)
			return 0;	
	}
	return 1;
}

void miniSpanTreePrim(adjMat* g, vertexData root)
{
	// preparation
	nod t[g->vexnum-1];
	int r = locate(g, root);
	int used[g->vexnum];// group of vertexes which have been included in the minimum spanning tree
	int unused[g->vexnum];// group of vertexes which have not been included in the minimum spanning tree yet
	used[0] = r;
	int count = 1;
	int i, j, min, head, tail; 
	for(i=0;i<(g->vexnum-1);i++)
		t[i].head = -1, used[i+1] = -1;
	// main part
	while(count < g->vexnum)
	{
		j = 0;
		// update the group of vertexes which have not been included in the minimum spanning tree
		for(i=0;i<g->vexnum;i++)
		{
			if(notIn(used, count, i))
				unused[j] = i, j++;
			if(j == g->vexnum-count)
				break;
		}
		// find the minimum arch
		min = g->arcs[used[0]][unused[0]].adj;
		for(i=0;i<count;i++)
		{
			for(j=0;j<(g->vexnum-count);j++)
			{
				if (g->arcs[used[i]][unused[j]].adj <= min)
				{
					min = g->arcs[used[i]][unused[j]].adj;
					head = unused[j];
					tail = used[i];
				}
			}
		}
		// add new vertex into the minimum spanning tree
		used[count] = head;
		t[count-1].head = head;
		t[count-1].tail = tail;
		t[count-1].weight = min;
		//printf("arch added: %c-[%d]->%c\n", get(g,tail), min, get(g,head));
		count++;
	}
	// show the tree
	puts("\narches in the tree:");
	for(i=0;i<count-1;i++)
		printf("arch: %c-[%d]->%c\n", get(g, t[i].tail), t[i].weight, get(g, t[i].head));
	printf("\n");
}

// kruskal algorithm is suitable for a connected graph or network with few edges
// it is not suitable for a strongly connected graph/network
// kruskal algorithm is a kind of greedy algorithm
typedef struct
{
	int head;
	int tail;
	int weight;
	int used;
} arches;
int* vertexes(int vernum)
{
	int* vertex = (int*)malloc(vernum*sizeof(int));
	int i;
	for(i=0;i<vernum;i++)
		vertex[i] = -1;
	return vertex;
}
int* vertex;
void findTree(arches* arc, int arcnum, int root)
{
	 int pos;
	 for(pos=0;pos<arcnum;pos++)
	 {
	 	if(arc[pos].tail == root && arc[pos].used == 1)
		{
			*(vertex) = arc[pos].head;
			vertex++;
			findTree(arc, arcnum, arc[pos].head);
		}
	 }
}
void miniSpanTreeKruskal(adjMat* g)
{
	// preparation
	nod t[g->vexnum-1];
	int group[g->vexnum];
	int i,j,k;
	for(i=0;i<g->vexnum;i++)
		group[i] = i;
	arches arc[g->arcnum];
	k = 0;
	for(i=0;i<g->vexnum;i++)
	{
		for(j=0;j<g->vexnum;j++)
		{
			if(g->arcs[i][j].adj != INFINITY)
			{
				arc[k].tail = i;
				arc[k].head = j;
				arc[k].weight = g->arcs[i][j].adj;
				arc[k].used = 0;
				k++;	
			}		
		}
	}
	// main part
	int min;
	int head, tail, count=1, pos;
	while(count < g->vexnum)
	{
		// find the arch with minimum weight 
		for(i=0;i<g->arcnum;i++)
		{
			if(group[arc[i].head] != group[arc[i].tail])// find nodes belong to different trees
			{
				min = arc[i].weight;
				break;				
			}
		}		
		for(i=0;i<g->arcnum;i++)
		{
			if(group[arc[i].head] != group[arc[i].tail] && arc[i].weight <= min)
			{
				min = arc[i].weight;
				head = arc[i].head;
				tail = arc[i].tail;
				pos = i; 
			}
		}
		// add new arch
		arc[pos].used = 1;
		vertex = vertexes(g->vexnum);
		int* start = vertex;
		findTree(arc, g->arcnum, arc[pos].tail);
		while(*(start)!= -1)
		{
			printf("node in tree %c set to %d group\n", get(g, *start), group[tail]);
			group[*(start)] = group[tail];
			start++;
		}
		t[count-1].head = head;
		t[count-1].tail = tail;
		t[count-1].weight = min;
		count++;
	}

	// show the tree
	puts("\nedges in the tree:");
	for(i=0;i<count-1;i++)
		printf("edge: %c-[%d]-%c\n", get(g, t[i].tail), t[i].weight, get(g, t[i].head));
	printf("\n");
}

// activity on vertex network(the weight on each arches does not matter)
// for a directed acyclic graph/network there is a toposort of its vertexes 
void aovTopoSort(adjMat g)
{
	int i,j, count = 0;
	int used[g.vexnum];
	for(i=0;i<g.vexnum;i++)
		used[i] = 0;
	printf("\nstart");
	while(count < g.vexnum)
	{
		// find a vertex without a prior vertex
		for(i=0;i<g.vexnum;i++)
		{
			if(used[i] == 0)
			{
				for(j=0;j<g.vexnum;j++)
				{
					if(g.arcs[j][i].adj != INFINITY)// if vertex i has a prior vertex, it should not be chosen, jump out and check next vertex
						break;		
				}
				if(j == g.vexnum)// if vertex i has no prior vertex, jump out
					break;	
			}
		}
		if(i == g.vexnum)// if all vertexes have prior vertexes, AOV can't be arranged
		{
			puts("ERROR: this network is not a acyclic network!");
			return;
		}	
		// clear all the arches whose tail is the vertex just found
		for(j=0;j<g.vexnum;j++)
			g.arcs[i][j].adj = INFINITY;
		// print the vertex
		printf("->%c", g.vexs[i]);
		used[i] = 1; 
		count++;
	}
	printf("\n");
} 

// activity on edge network(weight matters and there is only one vertex without prior vertex(source vertex) and only one vertex without next vertex(counter vertex))
// for this directed network there is a critical path
int* indegree(adjMat* g)
{
	int* in = (int*)malloc(g->vexnum*sizeof(int));
	int i;
	for(i=0;i<g->vexnum;i++)
		in[i] = 0;
	int j;
	for(i=0;i<g->vexnum;i++)
	{
		for(j=0;j<g->vexnum;j++)
		{
			if(g->arcs[j][i].adj != INFINITY)
				in[i]++;
		}
	}
	return in;
}
void criticalPath(adjMat* g)
{
	// find the counter vertex
	int source, counter;
	int i,j;
	for(i=0;i<g->vexnum;i++)
	{
		for(j=0;j<g->vexnum;j++)
		{
			if(g->arcs[i][j].adj != INFINITY)
				break;
		} 
		if(j == g->vexnum)
			break;
	} 
	if(i == g->vexnum)
	{
		puts("ERROR: this network does not have counter vertex!");
		return;
	}
	else
	{
		counter = i;
	}
	// find the source vertex 
	for(i=0;i<g->vexnum;i++)
	{
		for(j=0;j<g->vexnum;j++)
		{
			if(g->arcs[j][i].adj != INFINITY)
				break;
		} 
		if(j == g->vexnum)
			break;
	} 
	if(i == g->vexnum)
	{
		puts("ERROR: this network does not have source vertex!");
		return;
	}
	else
	{
		source = i;
	}	
	// calculate the earliest of every activities
	int e[g->vexnum];// earliest of every activities
	for(i=0;i<g->vexnum;i++)
		e[i] = 0;
	int aovTopo[g->vexnum]; // aov topo sort
	int reverseTopo[g->vexnum];
	int aovp = 0, reversep = g->vexnum-1;// stack pointer
	aovTopo[0] = source;
	aovp++;
	reverseTopo[g->vexnum-1] = source;
	reversep--;
	int* ins = indegree(g);// indegree of every vertexes
	while(aovp != 0)
	{
		aovp--;
		i = aovTopo[aovp];
		j = locate(g, firstAdj(g, get(g, i)));
		while(j != -1)
		{
			if(e[j] < e[i] + g->arcs[i][j].adj)
				e[j] = e[i] + g->arcs[i][j].adj;
			ins[j]--;
			if(ins[j] == 0)
			{
				aovTopo[aovp] = j;
				aovp++;
				reverseTopo[reversep] = j;
				reversep--;
			}
			j = locate(g, nextAdj(g, get(g, i), get(g, j)));
		} 	
	}
	reverseTopo[0] = counter;// reversep must be 0 now
	// calculate the latest start time of every activities
	int l[g->vexnum];
	for(i=0;i<g->vexnum;i++)
		l[i] = e[g->vexnum-1];
	for(reversep=1;reversep<g->vexnum;reversep++)
	{
		j = reverseTopo[reversep];
		for(i=0;i<g->vexnum;i++)
			if(l[j] > l[i] - g->arcs[j][i].adj && g->arcs[j][i].adj != INFINITY)
				l[j] = l[i] - g->arcs[j][i].adj;
	}
	// find the critical activities and print the critical path
	printf("\nvertexes in critical path:");
	for(i=g->vexnum-1;i>=0;i--)
	{
		if(l[reverseTopo[i]] == e[reverseTopo[i]])
			printf(" %c ", get(g, reverseTopo[i]));
	}

}

// shortest path
// Dijkstra algorithm
// source is a vertex from which can go to any other vertexes
// Dijkstra algorithm is a kind of dynamic algorithm
void Dijkstra(adjMat* g, int source)
{
	if(source == -1)
	{
		puts("vertex not found!");
		return;
	}
	// preparation
	int selected [g->vexnum];// vertexes already counted
	int mark[g->vexnum];// if a vertex has already counted its mark will be set to 1, if not the mark will be set to 0
	int distance[g->vexnum];// distance from source to other vertexes
	char path[g->vexnum][g->vexnum];// path[a][x] means the path from vertex source to vertex a 
	int i;
	for(i=0;i<g->vexnum;i++)
	{
		selected[i] = -1;
		mark[i] = 0;	
		distance[i] = g->arcs[source][i].adj;
		path[i][0] = '\0';
	}
	selected[0] = source;
	mark[source] = 1;
	distance[source] = 0;
	path[source][0] = get(g, source);
	path[source][1] = '\0';
	// main part
	int count = 1;// the number of vertexes already counted
	int point, tail, p, minDist;// point is the vertex to be added, tail->point is the arch to be added
	while(count < g->vexnum)
	{
		minDist = INFINITY;
		for(i=0;i<count;i++)
		{
			// get the first p that has not been used yet (p is the adjacent vertex of selected[i])
			p = locate(g, firstAdj(g, get(g, selected[i])));// be careful that the vertex p should not be in selected[]
			while(mark[p] == 1 && p != -1)
			{
				p = locate(g, nextAdj(g, get(g, selected[i]), get(g, p)));
			}	
			// update minimum distance from source to p
			while(p != -1)
			{
				if(g->arcs[selected[i]][p].adj + distance[selected[i]] <= distance[p])
				{
					distance[p] = g->arcs[selected[i]][p].adj + distance[selected[i]];
					if(distance[p] < minDist)
					{
						point = p;
						tail = selected[i];
						minDist = distance[p];
					}								
				}
				do{
					p = locate(g, nextAdj(g, get(g, selected[i]), get(g, p)));
				}
				while(mark[p] == 1 && p != -1);
			}
		}
		selected[count] = point;
		mark[point] = 1;
		for(i=0;i<strlen(path[tail]);i++)
			path[point][i] = path[tail][i];
		path[point][i] = get(g, point);
		path[point][i+1] = '\0';
		////
		//printf("\nnew path %s added, distance %d", path[point], distance[point]);
		////
		count++;
	}
	// show the result
	for(i=0;i<g->vexnum;i++)
	{
		printf("\nthe shortest distance from %c to %c is %d\n", get(g, source), get(g, i), distance[i]);
		printf("and the shortest path is %s\n", path[i]);
	}
}

// Floyd algorithm
// Floyd algorithm is a kind of dynamic algorithm
void Floyd(adjMat* g)
{
	// initialize 
	int i,j,k,len1,len2;
	int dist[g->vexnum][g->vexnum];
	char path[g->vexnum][g->vexnum][g->vexnum+1];// path[i][j][x] is the path from i to j
	for(i=0;i<g->vexnum;i++)
	{
		for(j=0;j<g->vexnum;j++)
		{
			dist[i][j] = g->arcs[i][j].adj;
			dist[i][i] = 0;
			if(dist[i][j] < INFINITY)
			{
				path[i][j][0] = get(g, i);
				if(i == j)
					path[i][j][1] = '\0';
				else
				{
					path[i][j][1] = get(g, j);
					path[i][j][2] = '\0';	
				}	
			}
			else
				path[i][j][0] = '\0';
		}
	}
	// update path and distance
	for(k=0;k<g->vexnum;k++)
	{
		for(i=0;i<g->vexnum;i++)
		{
			for(j=0;j<g->vexnum;j++)
			{
				if(dist[i][k] + dist[k][j] < dist[i][j])
				{
					dist[i][j] = dist[i][k] + dist[k][j];
					for(len1=0;path[i][k][len1]!='\0';len1++)		
						path[i][j][len1] = path[i][k][len1];
					for(len2=1;path[k][j][len2]!='\0';len2++)
						path[i][j][len1+len2-1] = path[k][j][len2];
					path[i][j][len1+len2-1] = '\0';
				}
			}
		}
	}
	// print 
	for(i=0;i<g->vexnum;i++)
	{
		for(j=0;j<g->vexnum;j++)
		{
			if(dist[i][j] == INFINITY)
			{
				printf("there is no path from %c to %c\n", get(g, i), get(g, j));
			}
			else
			{
				printf("the shortest distance from %c to %c is %d, path is:\n%s\n", get(g, i), get(g, j), dist[i][j], path[i][j]);
			}
		}
	}
}

// destroy a graph
void destroy(adjMat*g)
{
	free(g); 
} 


// test
int main()
{
	// create a graph/network
	adjMat* g = init();
	create(g);
	puts("show the graph/network using adjacent matrix:");
	show(g);
		
	// get adjacent vertex
	while(1)
	{
		puts("\nget adjacent vertexes of vertex:");
		while(char buff=getchar() == '\t' || buff == EOF)
			printf("%c", buff);
		puts("please input an vertex(input 'k' to end):");
		char c = getchar();
		if(c == 'k')
			break;
		char d = firstAdj(g, c);
		while(d != '\t')
		{
			printf("%c ", d);
			d = nextAdj(g, c, d);
		}
	}
	
	// traverse the graph/network
	printf("\ntraverse by depth first search\n");
	traverse(g, g->vexs[0], 'd');
	printf("\ntraverse by breadth first search\n");
	traverse(g, g->vexs[0], 'b');
	
	// insert a vertex into the graph/network
	while(1)
	{
		puts("\nadd vertexes, enter 'k' to end:");
		while(char buff=getchar()=='\t' || buff == EOF)
			printf("%c", buff);
		puts("please input the vertex you want to add:");
		char c = getchar();
		if(c == 'k')
			break;
		insert(g, c);
		show(g);
		printf("\ntraverse by depth first search\n");
		traverse(g, g->vexs[0], 'd');
		printf("\ntraverse by breadth first search\n");
		traverse(g, g->vexs[0], 'b');
	}
	
	// insert an arch/edge into the graph/network
	while(1)
	{
		puts("\nadd arches, set head or tail as 'k' to end:");
		while(char buff=getchar()=='\t' || buff == EOF)
			printf("%c", buff);
		puts("please input the arch you want to add inform of 'head tail value':");
		char h, t;
		int value;
		scanf("%c %c %d", &h, &t, &value);
		if(h == 'k' || t == 'k')
			break;
		insArc(g, h, t, value);
		show(g);		
		printf("\ntraverse by depth first search\n");
		traverse(g, g->vexs[0], 'd');
		printf("\ntraverse by breadth first search\n");
		traverse(g, g->vexs[0], 'b');
	}
	
	// find a simple path from a vertex to another vertex
	while(1)
	{
		puts("\nfind a simple path from a vertex to another vertex");
		puts("please input the vertexes inform of 'start end', enter 'k end' or 'start k' to terminate:");
		char s, e;
		// clear buffer
		while(char buff=getchar()== '\t' || buff == EOF)
			printf("%c", buff);
		scanf("%c %c", &s, &e); 
		if(s == 'k' || e == 'k')
			break;
		puts("\nfind a simple path using depth first search:");
		path(g, locate(g, s), locate(g, e));
		printf("\ntraverse by depth first search\n");
		traverse(g, s, 'd');		
	}
	
	// find the minimum spanning tree
	puts("\nuse Kruskal algorithm to find the minimum spanning tree for a connected network");
	miniSpanTreeKruskal(g);
	puts("\nuse prim algorithm to find the minimum spanning tree for a strongly connected network:");
	while(1)
	{
mst:		puts("please selected a vertex you want to be used as the root node, input 'k' to end:");
		char root;
		while(char buff=getchar()=='\t'|| buff == EOF)
			printf("%c", buff);
		root = getchar();
		if(root == 'k')
			break;
		if(locate(g, root) == -1)
			goto mst;
		miniSpanTreePrim(g, root);	
	}
	
	// shortest path
	while(1)
	{
		puts("\nfind the shortest path from a vertex to all the other vertex can be connected, using Dijkstra algorithm");
		puts("please input the vertex you care about, input 'k' to end:");
		while(char buff=getchar()=='\t' || buff == EOF)
			printf("%c", buff);
		char c = getchar();
		if(c == 'k')
			break;
		Dijkstra(g, locate(g, c));
	}
	puts("\nuse Floyd algorithm to calculate all the shortest path:");
	Floyd(g);
	
	// delete an arch/edge from the graph/network
	while(1)
	{
		puts("\ndelete arches, set head or tail as 'k' to end:");
		while(char buff=getchar()=='\t' || buff == EOF)
			printf("%c", buff);
		puts("please input the arch you want to delete inform of 'head tail'");
		char h, t;
		scanf("%c %c", &h, &t);
		if(h == 'k' || t == 'k')
			break;
		delArc(g, h, t);
		show(g);		
		printf("\ntraverse by depth first search\n");
		traverse(g, g->vexs[0], 'd');
		printf("\ntraverse by breadth first search\n");
		traverse(g, g->vexs[0], 'b');
	}
		
	// delete a vertex from the graph/network
	while(1)
	{
		puts("\ndelete vertexes, enter 'k' to end:");
		while(char buff=getchar()=='\t' || buff == EOF)
			printf("%c", buff);
		puts("please input the vertex you want to delete:");
		char c = getchar();
		if(c == 'k')
			break;
		del(g, c);
		show(g);
		printf("\ntraverse by depth first search\n");
		traverse(g, g->vexs[0], 'd');
		printf("\ntraverse by breadth first search\n");
		traverse(g, g->vexs[0], 'b');
	}
	
	/* 
	for AOV and AOE(a->b, c->b, a->c)
	 a - b
 	 \  /
	  c
	is also illegal! because a->b is actually redundant
	*/
	// create a graph/network
	destroy(g);
	g = init();
	puts("\ncreate a new directed acyclic network for activity on vertex(AOV) and activity on edge(AOE) test:");
	create(g);
	puts("show the graph/network using adjacent matrix:");
	show(g);

	// activity on vertex
	puts("\nAOV topo sort for a directed acylic graph/network: \n");
	aovTopoSort(*g);
	
	// activity on edge
	puts("\nthe critical path for a directed acylic network which has a source and a counter:\n");
	criticalPath(g);
	
	return 0;	
}
