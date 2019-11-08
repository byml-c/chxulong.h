#ifndef VECTOR_INCLUDED
	#define VECTOR_INCLUDED
	#include<vector>
#endif

#ifndef CSTDIO
	#define CSTDIO
	#include<cstdio>
#endif

#ifndef ASSERT_H_INCLUDED
	#include<assert.h>
	#define ASSERT_H_INCLUDED
#endif

class Graph {
	private:
		int nodeSize;
		std::vector<std::vector<std::pair<int,int> > >edges;
	public:
		void insert(int u,int v,int val) {
			assert(u<nodeSize&&v<nodeSize);
			edges[u].push_back(std::make_pair(v,val));
		}
		void printOutDegree(int u,const char* format) {
			for(std::pair<int,int> i:edges[u]) {
				printf(format,i.first,i.second);
			}
		}
		void printOutDegree(int u) {
			printOutDegree(u,"[%d,%d]");
		}
		void printOutDegree() {
			for(int i=0;i<nodeSize;i++) {
				printOutDegree(i);
				puts("");
			}
		}
		int getNodeSize() {
			return nodeSize;
		}
		Graph(int size) {
			edges.resize(size);
			nodeSize=size;
		}
};
