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

template <typename Tp> class Graph {
	private:
		Tp nodeSize;
		std::vector<std::vector<std::pair<Tp,Tp> > >edges;
	public:
		void insert(Tp u,Tp v,Tp val) {
			assert(u<nodeSize&&v<nodeSize);
			edges[u].push_back(std::make_pair(v,val));
		}
		//no need.
//		void printOutDegree(Tp u,const char* format) {
//			for(std::pair<Tp,Tp> i:edges[u]) {//auto i?
//				prTpf(format,i.first,i.second);
//			}
//		}
//		void printOutDegree(Tp u) {
//			prTpOutDegree(u,"[%d,%d]");
//		}
//		void printOutDegree() {
//			for(Tp i=0;i<nodeSize;i++) {
//				prTpOutDegree(i);
//				puts("");
//			}
//		}
		Tp getNodeSize() {
			return nodeSize;
		}
		Graph(Tp size) {
			edges.resize(size);
			nodeSize=size;
		}
};
