#include <iostream>
#include <vector>

using namespace std;

// P(n,k) such that n is even = 2*(n/2) = 2*alpha
// in this way spoke is an edge between ai -> ai+alpha
int n, k;
vector<vector<int> > graph;

vector<vector<int> > all_code;
vector<int> all_vec;

//number of spokes of set C
int num_of_spokes(vector<int> C)
{
  int ret = 0;
  for(int i=0;i < C.size();i++)
  for(int j=i;j < C.size();j++)
    if(C[i] == C[j] + n/2) ret++;
  return ret;
}

//return 0-1 coding of a subset
vector<int> code(vector<int> C, size)
{
  vector<vector<int> > ret(size);
  for(int i=0;i < C.size();i++)
  {
    ret[C[i]] = 1;
  }
  return ret;
}


//check if C is a mis or not
bool is_mis(vector<int> C)
{
  for(int i=0;i < C.size();i++)
  for(int j=i;j < C.size();j++)
    if(graph[i][j] == 1) return false;
  return true;
}

//find all mis of a set C
vector<vector<int> > mis_subset(vector<int> C)
{
   vector<vector<int> > all_mis;
   for(int i=0;i < A.size();i++)
   {
     vector<int> lt;
     vector<vector<int> > ret;
     subsets(A, A.size(), i, 0, lt, ret); 
     for(int i=0;i < ret.size();i++)
       if(is_mis(ret[i]) == true)
          all_mis.push_back(ret[i]);
   }
   return all_mis
}

vector<int> cup(vector<int> a, vector<int> b)
{
   vector<vector<int> > ret;
   ret.reserve( a.size() + b.size() ); // preallocate memory
   ret.insert( ret.end(), a.begin(), a.end() );
   ret.insert( ret.end(), b.begin(), b.end() );
   return ret;
}

void exhaustive_mis(vector<int> A1, vector<int> B, vector<int> A2)
{
   //map code to B_j
   vector<code_vector> ret;
   // A = A1 cup A2
   vector<vector<int> > A = cup(A1,A2);
   vector<vector<int> > all_mis_A = mis_subset(A);
   vector<vector<int> > all_mis_B = mis_subset(B);
   
   for(int i=0;i < all_mis_A.size();i++)
   {
     vector<int> A_i = all_mis_A[i];
     int max_size = 0, max_index = 0;
     for(int j=0;j < all_mis_B.size();j++)
     {
       vector<int> B_j = all_mis_B[j];
       vector<int> tmp = cup(A_i, B_j);
       if(is_mis(tmp) == false) continue;
       if(max_size < B_j.size()) {max_size=B_j.size();max_index=j;}
     }
     
     all_code.push_back(cup(cup(code(A1),code(B)),code(A2)),code(A_i)));
     all_vec.push_back(all_mis_B[max_index]);
   }
}

void subset(vector<int> arr, int size, int left, int index, vector<int> &l, vector<vector<int> >& ret){
    if(left==0){
        ret.push_back(l);
        return;
    }
    for(int i=index; i < size;i++){
        l.push_back(arr[i]);
        subset(arr,size,left-1,i+1,l,ret);
        l.pop_back();
    }
}     
int spkes_index = 0;
vector<vector<int> > get_k_spokes(vector<int> A)
{
  vector<vector<int> > ret(2);
  for(int i=0;i < C.size();i++)
  for(int j=i;j < C.size();j++)
  
}

// returns a independent subset of B like retX
// that X cup retX is an independent subset of G
// and retX is maximum with respect to previous property
vector<int> MIS(vector<int> A1, vector<int> B, vector<int> A2)
{
  if(num_of_spoke(B) < 3*k)
  {
      exhaustive_mis(A1,B,A2);
  }
  else
  {
      
  }
}


void print( vector<int> l){
    for(vector<int>::iterator it=l.begin(); it!=l.end() ; ++it)
            cout << " " << *it;
    cout<<endl;
}

int main(){
    int array[5]={1,2,3,4,5};
    vector<int> lt;   
    vector<vector<int> > subsets;
    subset(array,5,3,0,lt,subsets);
    
    for(int i=0;i < subsets.size();i++)
       print(subsets[i]);
    return 0;
}

