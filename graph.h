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
		std::vector<std::vector<std::pair<TId,TValue> > >edges;
	public:
		std::vector<std::vector<TValue> >dist;
		void insert(TId u,TId v,TValue val) {
			assert(u<nodeSize&&v<nodeSize);
			edges[u].push_back(std::make_pair(v,val));
		}
		//maybe we can optimize it...
		//I don't think returning a std::vector is a choice.
		//But never make a public:vector<typename>dis!!
		std::vector<TValue> Dijkstra(TId st) {
			std::vector<TValue>dis;
			dis.resize(nodeSize);
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
			return dis;
		}
		void Floyd(){
			dist.resize(nodeSize);
			for(TId i=0;i<nodeSize;++i){
				dist[i].resize(nodeSize);
				std::fill(dist[i].begin(),dist[i].end(),0x3f3f3f3f);	
			}
			for(TId u=0;u<nodeSize;++u){
				for(TId j=0,lenv=edges[u].size();j<lenv;++j){
					TId v=edges[u][j].first;
					TValue w=edges[u][j].second;
					dist[u][v]=w;
				}dist[u][u]=0;
			}
			for(TId k=0;k<nodeSize;++k){
				for(TId i=0;i<nodeSize;++i){
					for(TId j=0;j<nodeSize;++j){
						if(dist[i][k]+dist[k][j]<dist[i][j]){
							dist[i][j]=dist[i][k]+dist[k][j];
						}
					}
				}
			}
		}
		int getNodeSize() {
			return nodeSize;
		}
		Graph(TId size) {
			edges.resize(size);
			nodeSize=size;
		}
};
