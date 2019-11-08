#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED
#include<vector>
#endif

#ifndef CSTDIO_INCLUDED
#include<cstdio>
#define CSTDIO_INCLUDED
#endif

#ifndef CSTRING_INCLUDED
#include<cstring>
#define CSTRING_INCLUDED
#endif

#ifndef ASSERT_H_INCLUDED
#include<assert.h>
#define ASSERT_H_INCLUDED
#endif

#ifndef QUEUE_INCLUDED
#include<queue>
#define QUEUE_INCLUDED
#endif

template <typename TId, typename TValue> class Graph {
	private:
		TId nodeSize;
		std::vector<TValue>dis;
		std::vector<std::vector<std::pair<TId,TValue> > >edges;
	public:
		void insert(TId u,TId v,TValue val) {
			assert(u<nodeSize&&v<nodeSize);
			edges[u].push_back(std::make_pair(v,val));
		}
		bool Dijkstra(TId st) {
			assert(st<nodeSize);
			std::fill(dis.begin(),dis.end(),0x3f3f3f3f);
			std::priority_queue<std::pair<TId, TValue>>q;
			dis[st]=0;
			q.push(std::make_pair(st,dis[st]));
			while(!q.empty()) {
				TId u=q.top().first;
				q.pop();
				for(TId i=0,lenv=edges[u].size(); i<lenv; ++i) {
					TId v=edges[u][i].first;
					TValue w=edges[u][i].second;
					if(dis[u]+w<dis[v]){
						dis[v]=dis[u]+w;
						q.push(std::make_pair(v,-dis[v]));
					}
				}
			}
			return true;
		}
		int getNodeSize() {
			return nodeSize;
		}
		Graph(int size) {
			edges.resize(size);
			dis.resize(size);
			nodeSize=size;
		}
};
