//Perform the time complexity analysis of differnt operations (create,insert,delete,merge) for binary heap, leaftist heap, binomial heap.illustrate the comparison using a graph with atleast 5 different sizes,no. of comparision 
#include <iostream>
using namespace std;

/* ----------------------------- Metrics ----------------------------- */
struct Metrics {
    long long comparisons;
    long long links_or_swaps;
    Metrics(long long c=0,long long l=0):comparisons(c),links_or_swaps(l){}
    void reset(){comparisons=0;links_or_swaps=0;}
};

/* Utility deterministic value generator */
int gen_val(int i,int n,int seed){
    unsigned x=(unsigned)(i*(seed*131)+seed*31);
    x^=(x<<13);
    x^=(x>>7);
    x^=(x<<3);
    return (int)(x%(n*10+97))+1;
}

/* ------------------------- Binary Min-Heap ------------------------- */
class BinaryMinHeap {
    int* a; int sz; int cap;
    void ensure_capacity(int need){
        if(need<=cap) return;
        int newCap=cap;
        while(newCap<need) newCap<<=1;
        int* b=new int[newCap];
        for(int i=0;i<sz;i++) b[i]=a[i];
        delete[] a; a=b; cap=newCap;
    }
    void sift_up(int i,Metrics& m){
        while(i>0){
            int p=(i-1)/2;
            m.comparisons++;
            if(a[i]<a[p]){ int tmp=a[i]; a[i]=a[p]; a[p]=tmp; m.links_or_swaps++; i=p; }
            else break;
        }
    }
    void sift_down(int i,Metrics& m){
        while(true){
            int l=2*i+1; int r=2*i+2; int s=i;
            if(l<sz){ m.comparisons++; if(a[l]<a[s]) s=l; }
            if(r<sz){ m.comparisons++; if(a[r]<a[s]) s=r; }
            if(s!=i){ int tmp=a[i]; a[i]=a[s]; a[s]=tmp; m.links_or_swaps++; i=s; }
            else break;
        }
    }
public:
    BinaryMinHeap(int c=1){sz=0; cap=c<1?1:c; a=new int[cap];}
    ~BinaryMinHeap(){delete[] a;}
    void insert(int x,Metrics& m){ensure_capacity(sz+1); a[sz]=x; sz++; sift_up(sz-1,m);}
    int extract_min(Metrics& m){
        if(sz==0) return -1;
        int ret=a[0];
        a[0]=a[sz-1];
        sz--;
        if(sz>0) sift_down(0,m);
        return ret;
    }
    static BinaryMinHeap merge_heaps(const BinaryMinHeap& h1,const BinaryMinHeap& h2,Metrics& m){
        BinaryMinHeap merged(h1.sz+h2.sz);
        merged.sz=h1.sz+h2.sz;
        merged.ensure_capacity(merged.sz);
        for(int i=0;i<h1.sz;i++) merged.a[i]=h1.a[i];
        for(int i=0;i<h2.sz;i++) merged.a[h1.sz+i]=h2.a[i];
        for(int i=(merged.sz/2)-1;i>=0;i--) merged.sift_down(i,m);
        return merged;
    }
};

/* --------------------------- Leftist Heap -------------------------- */
struct LHNode{
    int key;
    LHNode* left;
    LHNode* right;
    int npl;
    LHNode(int k){key=k;left=0;right=0;npl=1;}
};

class LeftistMinHeap {
    LHNode* root;
    static int npl(LHNode* x){return x?x->npl:0;}
    static LHNode* merge_nodes(LHNode* h1,LHNode* h2,Metrics& m){
        if(!h1) return h2;
        if(!h2) return h1;
        m.comparisons++;
        if(h2->key<h1->key){LHNode* t=h1;h1=h2;h2=t;m.links_or_swaps++;}
        h1->right=merge_nodes(h1->right,h2,m); m.links_or_swaps++;
        if(npl(h1->left)<npl(h1->right)){LHNode* t=h1->left;h1->left=h1->right;h1->right=t;m.links_or_swaps++;}
        h1->npl=npl(h1->right)+1;
        return h1;
    }
    static void destroy_nodes(LHNode* r){
        if(!r) return;
        destroy_nodes(r->left);
        destroy_nodes(r->right);
        delete r;
    }
public:
    LeftistMinHeap(){root=0;}
    ~LeftistMinHeap(){destroy_nodes(root);}
    void insert(int x,Metrics& m){
        LHNode* s=new LHNode(x);
        root=merge_nodes(root,s,m);
    }
    int extract_min(Metrics& m){
        if(!root) return -1;
        int ret=root->key;
        LHNode* L=root->left;
        LHNode* R=root->right;
        delete root;
        root=merge_nodes(L,R,m);
        return ret;
    }
    static LeftistMinHeap merge_heaps(LeftistMinHeap& a,LeftistMinHeap& b,Metrics& m){
        LeftistMinHeap res;
        res.root=merge_nodes(a.root,b.root,m);
        a.root=0;
        b.root=0;
        return res;
    }
};

/* --------------------------- Binomial Heap ------------------------- */
struct BHNode{
    int key,degree;
    BHNode* parent;
    BHNode* child;
    BHNode* sibling;
    BHNode(int k){key=k;degree=0;parent=0;child=0;sibling=0;}
};

class BinomialMinHeap{
    BHNode* head;
    static BHNode* merge_root_lists(BHNode* h1,BHNode* h2,Metrics& m){
        BHNode dummy(0);
        BHNode* tail=&dummy;
        while(h1 && h2){
            m.comparisons++;
            if(h1->degree<=h2->degree){
                tail->sibling=h1; tail=h1; h1=h1->sibling; m.links_or_swaps++;
            } else {
                tail->sibling=h2; tail=h2; h2=h2->sibling; m.links_or_swaps++;
            }
        }
        if(h1){tail->sibling=h1; m.links_or_swaps++;}
        else if(h2){tail->sibling=h2; m.links_or_swaps++;}
        return dummy.sibling;
    }
    static BHNode* link_trees(BHNode* b1,BHNode* b2,Metrics& m){
        b2->parent=b1; m.links_or_swaps++;
        b2->sibling=b1->child; m.links_or_swaps++;
        b1->child=b2; m.links_or_swaps++;
        b1->degree++;
        return b1;
    }
    static BHNode* union_heaps(BHNode* h1,BHNode* h2,Metrics& m){
        BHNode* H=merge_root_lists(h1,h2,m);
        if(!H) return 0;
        BHNode* prev=0; BHNode* curr=H; BHNode* next=curr->sibling;
        while(next){
            m.comparisons++;
            bool deg_diff=(curr->degree!=next->degree);
            bool three_equal=false;
            if(!deg_diff && next->sibling){
                m.comparisons++;
                if(next->sibling->degree==curr->degree) three_equal=true;
            }
            if(deg_diff || three_equal){
                prev=curr; curr=next;
            } else {
                m.comparisons++;
                if(curr->key<=next->key){
                    curr->sibling=next->sibling; m.links_or_swaps++;
                    curr=link_trees(curr,next,m);
                } else {
                    if(!prev) H=next;
                    else prev->sibling=next; m.links_or_swaps++;
                    curr=link_trees(next,curr,m);
                }
            }
            next=curr->sibling;
        }
        return H;
    }
    static void destroy_tree(BHNode* r){
        if(!r) return;
        destroy_tree(r->child);
        destroy_tree(r->sibling);
        delete r;
    }
public:
    BinomialMinHeap(){head=0;}
    ~BinomialMinHeap(){destroy_tree(head);}
    void insert(int x,Metrics& m){
        BHNode* s=new BHNode(x);
        head=union_heaps(head,s,m);
    }
    int extract_min(Metrics& m){
        if(!head) return -1;
        BHNode* minPrev=0;
        BHNode* minNode=head;
        BHNode* prev=0;
        BHNode* curr=head;
        int minKey=curr->key;
        while(curr){
            m.comparisons++;
            if(curr->key<minKey){minKey=curr->key;minNode=curr;minPrev=prev;}
            prev=curr; curr=curr->sibling;
        }
        if(!minPrev) head=minNode->sibling;
        else minPrev->sibling=minNode->sibling; m.links_or_swaps++;
        BHNode* child=minNode->child;
        BHNode* rev=0;
        while(child){
            BHNode* next=child->sibling;
            child->parent=0;
            child->sibling=rev; m.links_or_swaps++;
            rev=child;
            child=next;
        }
        int ret=minNode->key;
        delete minNode;
        head=union_heaps(head,rev,m);
        return ret;
    }
    static BinomialMinHeap merge_heaps(BinomialMinHeap& a,BinomialMinHeap& b,Metrics& m){
        BinomialMinHeap res;
        res.head=union_heaps(a.head,b.head,m);
        a.head=0; b.head=0;
        return res;
    }
};

/* ------------------------- Main Table Code ------------------------- */
int main(){
    const int sizes[5]={100,200,300,400,500};

    long long binary[5][4];
    long long leftist[5][4];
    long long binomial[5][4];

    for(int idx=0;idx<5;idx++){
        int n=sizes[idx];

        // Binary
        {
            Metrics mc,mi,md,mm;
            BinaryMinHeap H1;
            for(int i=0;i<n;i++) H1.insert(gen_val(i,n,17),mc);
            H1.insert(gen_val(n+1,n,23),mi);
            H1.extract_min(md);
            BinaryMinHeap H2;
            for(int i=0;i<n;i++) H2.insert(gen_val(i,n,29),mc);
            BinaryMinHeap HM=BinaryMinHeap::merge_heaps(H1,H2,mm);
            binary[idx][0]=mc.comparisons;
            binary[idx][1]=mi.comparisons;
            binary[idx][2]=md.comparisons;
            binary[idx][3]=mm.comparisons;
        }

        // Leftist
        {
            Metrics mc,mi,md,mm;
            LeftistMinHeap L1;
            for(int i=0;i<n;i++) L1.insert(gen_val(i,n,37),mc);
            L1.insert(gen_val(n+1,n,41),mi);
            L1.extract_min(md);
            LeftistMinHeap L2;
            for(int i=0;i<n;i++) L2.insert(gen_val(i,n,43),mc);
            LeftistMinHeap LM=LeftistMinHeap::merge_heaps(L1,L2,mm);
            leftist[idx][0]=mc.comparisons;
            leftist[idx][1]=mi.comparisons;
            leftist[idx][2]=md.comparisons;
            leftist[idx][3]=mm.comparisons;
        }

        // Binomial
        {
            Metrics mc,mi,md,mm;
            BinomialMinHeap B1;
            for(int i=0;i<n;i++) B1.insert(gen_val(i,n,53),mc);
            B1.insert(gen_val(n+1,n,59),mi);
            B1.extract_min(md);
            BinomialMinHeap B2;
            for(int i=0;i<n;i++) B2.insert(gen_val(i,n,61),mc);
            BinomialMinHeap BM=BinomialMinHeap::merge_heaps(B1,B2,mm);
            binomial[idx][0]=mc.comparisons;
            binomial[idx][1]=mi.comparisons;
            binomial[idx][2]=md.comparisons;
            binomial[idx][3]=mm.comparisons;
        }
    }

    // Print table manually (no iomanip)
    cout<<"\nCOMPARISON COUNTS TABLE\n\n";
    cout<<"n    | Heap Type       | Create | Insert | Delete | Merge\n";
    cout<<"------------------------------------------------------------\n";
    for(int idx=0;idx<5;idx++){
        cout<<sizes[idx]<<"   | Binary Heap     | "<<binary[idx][0]<<"     "<<binary[idx][1]<<"      "<<binary[idx][2]<<"      "<<binary[idx][3]<<"\n";
        cout<<sizes[idx]<<"   | Leftist Heap    | "<<leftist[idx][0]<<"     "<<leftist[idx][1]<<"      "<<leftist[idx][2]<<"      "<<leftist[idx][3]<<"\n";
        cout<<sizes[idx]<<"   | Binomial Heap   | "<<binomial[idx][0]<<"     "<<binomial[idx][1]<<"      "<<binomial[idx][2]<<"      "<<binomial[idx][3]<<"\n";
        cout<<"------------------------------------------------------------\n";
    }

    return 0;
}

