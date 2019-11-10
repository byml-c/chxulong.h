/*Binary Indexed Tree*/
#ifndef CSTDIO_INCLUDED
#include<cstdio>
#define CSTDIO_INCLUDED
#endif

#ifndef VECTOR_INCLUDED
#include<vector>
#define VECTOR_INCLUDED
#endif

template <typename TId, typename TValue> class BIT {
	private:
		TId nodeSize;
		std::vector<TValue>tree;
	public:
		TId lowbit(TId x) {
			return x&-x;
		}
		void add(TId u, TValue k) {
			while(u<=nodeSize) {
				tree[u]+=k;
				u+=lowbit(u);
			}
		}
		void add(TId u, TId v, TValue k) {
			add(u, k);
			if(v<nodeSize) {
				add(v+1, -k);
			}
		}
		TValue query(TId u) {
			TValue sum=0;
			while(u>0) {
				sum+=tree[u];
				u-=lowbit(u);
			}
			return sum;
		}
		treeArray(TId size) {
			nodeSize=size;
			tree.resize(nodeSize+1);
		}
};
