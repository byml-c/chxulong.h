/*Segment Tree*/
#ifndef CSTDIO_INCLUDED
#include<cstdio>
#define CSTDIO_INCLUDED
#endif

#ifndef CSTRING_INCLUDED
#include<cstring>
#define CSTRING_INCLUDED
#endif

#ifndef VECTOR_INCLUDED
#include<vector>
#define VECTOR_INCLUDED
#endif

template <typename TId, typename TValue> class RMQSegmentTree {
	private:
		bool RMQType;//0 means Max; 1 means Min;
		TId NodeSize;
		TValue INF;
		std::vector<TValue>Tree,Lazy;
		
		TValue Compare(TValue a,TValue b){
			if(RMQType)return a<b?a:b;
			else return a>b?a:b;
		}
		void RangeAdd(TId lf,TId rt,TId tot,TId ll,TId rr,TValue k){
			if(lf>rr||rt<ll){
				return ;
			}else if(lf>=ll&&rt<=rr){
				if(lf==rt)Tree[tot]+=k;
				else Lazy[tot]+=k;
			}else{
				TId mid=(lf+rt)>>1;
				RangeAdd(lf,mid,tot*2,ll,rr,k);
				RangeAdd(mid+1,rt,tot*2+1,ll,rr,k);
				Tree[tot]=Compare(Tree[tot*2]+Lazy[tot*2],Tree[tot*2+1]+Lazy[tot*2+1])+Lazy[tot];
			}
		}
		void RangeRevise(TId lf,TId rt,TId tot,TId ll,TId rr,TValue k){
			if(lf>rr||rt<ll){
				return ;
			}else if(lf>=ll&&rt<=rr){
				if(lf==rt){
					Tree[tot]=k;
					Lazy[tot]=0;
				}else{
					TId mid=(lf+rt)>>1;
					RangeRevise(lf,mid,tot*2,ll,rr,k);
					RangeRevise(lf,mid,tot*2+1,ll,rr,k);
					Lazy[tot]=0;
					Tree[tot]=Compare(Tree[tot*2],Tree[tot*2+1]);
				}
			}else{
				TId mid=(lf+rt)>>1;
				RangeRevise(lf,mid,tot*2,ll,rr,k);
				RangeRevise(mid+1,rt,tot*2+1,ll,rr,k);
				Tree[tot]=Compare(Tree[tot*2]+Lazy[tot*2],Tree[tot*2+1]+Lazy[tot*2+1])+Lazy[tot];
			}
		}
		void SpreadTag(TId lf,TId rt,TValue tot){
			if(lf==rt){
				Tree[tot]+=Lazy[tot];
			}else{
				Lazy[tot*2]+=Lazy[tot];
				Lazy[tot*2+1]+=Lazy[tot];
				Tree[tot]=Compare(Tree[tot*2]+Lazy[tot*2],Tree[tot*2+1]+Lazy[tot*2+1]);
				Lazy[tot]=0;
			}
		}
		TValue RangeQuery(TId lf,TId rt,TId tot,TId ll,TId rr){
			if(lf>rr||rt<ll){
				return INF;
			}else{
				SpreadTag(lf,rt,tot);
				if(lf>=ll&&rt<=rr){
					return Tree[tot]+Lazy[tot];
				}else{
					TId mid=(lf+rt)>>1;
					TValue v1=RangeQuery(lf,mid,tot*2,ll,rr);
					TValue v2=RangeQuery(mid+1,rt,tot*2+1,ll,rr);
					return Compare(v1,v2);
				}
			}
		}
		void PrintTree(int d,int td,std::vector<TValue>& Tree){
			if(d>td)return ;
			for(int i=1;i<(1<<(td-d));++i)
				printf(" ");
			int lf=1<<(d-1),rt=(1<<d)-1;
			for(int i=lf;i<=rt;++i){
				printf("%d",Tree[i]);
				if(i==rt)continue;
				for(int j=1;j<(1<<(td-d+1));++j)
					printf(" ");
			}printf("\n");
			PrintTree(d+1,td,Tree);
		}
	public:
		RMQSegmentTree(TId Size,bool Type,TValue EdgeValue,TValue BeginValue){
			RMQType=Type;
			NodeSize=Size;
			Tree.resize(Size*4);Tree.clear();
			Lazy.resize(Size*4);Lazy.clear();
			INF=EdgeValue;
			Revise(1,Size,BeginValue);
		}
		void Add(TId Pos,TValue Value)
		{
			RangeAdd(1,NodeSize,1,Pos,Pos,Value);
		}
		void Revise(TId Pos,TValue Value)
		{
			RangeRevise(1,NodeSize,1,Pos,Pos,Value);
		}
		TValue Query(TId Pos)
		{
			return RangeQuery(1,NodeSize,1,Pos,Pos);
		}
		void Add(TId Pos_left,TId Pos_right,TValue Value)
		{
			RangeAdd(1,NodeSize,1,Pos_left,Pos_right,Value);
		}
		void Revise(TId Pos_left,TId Pos_right,TValue Value)
		{
			RangeRevise(1,NodeSize,1,Pos_left,Pos_right,Value);
		}
		TValue Query(TId Pos_left,TId Pos_right)
		{
			return RangeQuery(1,NodeSize,1,Pos_left,Pos_right);
		}
		void Print(){
			int i=1,j=1;
			while(j<NodeSize)++i,j<<=1;
			PrintTree(1,i,Tree);
			PrintTree(1,i,Lazy);
		}
};

template <typename TId, typename TValue> class SUMSegmentTree{
	private:
		std::vector<TValue>Tree,Lazy;
		TId NodeSize;
		
		void Swap(TId& a,TId& b){TId t=a;a=b;b=t;}
		void RangeRevise(TId lf,TId rt,TId tot,TId ll,TId rr,TValue k){
			if(rt<ll||lf>rr){
				return ;
			}else if(lf>=ll&&rt<=rr){
				if(lf==rt){
					Tree[tot]=k;Lazy[tot]=0;
				}else{
					TId mid=(lf+rt)>>1;
					RangeRevise(lf,mid,tot<<1,ll,rr,k);
					RangeRevise(mid+1,rt,tot<<1|1,ll,rr,k);
					Lazy[tot]=0;
					Tree[tot]=Tree[tot<<1]+Tree[tot<<1|1];
				}
			}else{
				TId mid=(lf+rt)>>1;
				RangeRevise(lf,mid,tot<<1,ll,rr,k);
				RangeRevise(mid+1,rt,tot<<1|1,ll,rr,k);
				Tree[tot]=Tree[tot<<1]+Tree[tot<<1|1];
			}
		}
		void SpreadTag(TId lf,TId rt,TId tot){
			if(Lazy[tot]){
				TId mid=(lf+rt)>>1;
				Lazy[tot<<1]+=Lazy[tot];
				Lazy[tot<<1|1]+=Lazy[tot];
				Tree[tot<<1]+=Lazy[tot]*(mid-lf+1);
				Tree[tot<<1|1]+=Lazy[tot]*(rt-mid);
				Lazy[tot]=0;
			}
		}
		void RangeAdd(TId lf,TId rt,TId tot,TId ll,TId rr,TValue k){
			if(rt<ll||lf>rr){
				return ;
			}else if(lf>=ll&&rt<=rr){
				Tree[tot]+=k*(rt-lf+1);
				Lazy[tot]+=k;
			}else{
				SpreadTag(lf,rt,tot);
				TId mid=(lf+rt)>>1;
				RangeAdd(lf,mid,tot<<1,ll,rr,k);
				RangeAdd(mid+1,rt,tot<<1|1,ll,rr,k);
				Tree[tot]=Tree[tot<<1]+Tree[tot<<1|1];
			}
		}
		TValue RangeQuery(TId lf,TId rt,TId tot,TId ll,TId rr){
			if(rt<ll||lf>rr){
				return 0;
			}else if(lf>=ll&&rt<=rr){
				return Tree[tot];
			}else{
				SpreadTag(lf,rt,tot);
				TId mid=(lf+rt)>>1;
				TValue v1=RangeQuery(lf,mid,tot<<1,ll,rr);
				TValue v2=RangeQuery(mid+1,rt,tot<<1|1,ll,rr);
				return v1+v2;
			}
		}
		void PrintTree(TId d,TId td,std::vector<TValue>& Tree){
			if(d>td)return ;
			for(TId i=1;i<(1<<(td-d));++i)
				printf(" ");
			TId lf=1<<(d-1),rt=(1<<d)-1;
			for(TId i=lf;i<=rt;++i){
				printf("%d",Tree[i]);
				if(i==rt)continue;
				for(TId j=1;j<(1<<(td-d+1));++j)
					printf(" ");
			}printf("\n");
			PrintTree(d+1,td,Tree);
		}
	public:
		SUMSegmentTree(TId Size,TValue BeginValue){
			NodeSize=Size;
			Tree.resize(Size*4);Tree.clear();
			Lazy.resize(Size*4);Tree.clear();
			revise(1,Size,BeginValue);
		}
		void revise(TId Pos,TValue Value)
		{
			RangeRevise(1,NodeSize,1,Pos,Pos,Value);
		}
		void revise(TId Pos_left,TId Pos_right,TValue Value)
		{
			if(Pos_left>Pos_right)Swap(Pos_left,Pos_right);
			RangeRevise(1,NodeSize,1,Pos_left,Pos_right,Value);
		}
		void add(TId Pos,TValue Value)
		{
			RangeAdd(1,NodeSize,1,Pos,Pos,Value);
		}
		void add(TId Pos_left,TId Pos_right,TValue Value)
		{
			if(Pos_left>Pos_right)Swap(Pos_left,Pos_right);
			RangeAdd(1,NodeSize,1,Pos_left,Pos_right,Value);
		}
		TValue query(TId Pos)
		{
			return RangeQuery(1,NodeSize,1,Pos,Pos);
		}
		TValue query(TId Pos_left,TId Pos_right)
		{
			if(Pos_left>Pos_right)Swap(Pos_left,Pos_right);
			return RangeQuery(1,NodeSize,1,Pos_left,Pos_right);
		}
		void Print(){
			TId i=1,j=1;
			while(j<NodeSize)++i,j<<=1;
			PrintTree(1,i,Tree);
			PrintTree(1,i,Lazy);
		}
};
