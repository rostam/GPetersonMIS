#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

// P(n,k) such that n is even = 2*(n/2) = 2*alpha
// in this way spoke is an edge between ai -> ai+alpha
const int n = 60, k = 5, m = 30;
int graph[n][n];

bitset<100> b;

vector<bitset<4*n> > all_code;
vector<vector<int> > all_vect;


void print( vector<int> l){
    for(vector<int>::iterator it=l.begin(); it!=l.end() ; ++it)
            cout << " " << *it;
    cout<<endl;
}

void generalized_peterson()
{
     for(int i=0;i<n;i++)
     for(int j=0;j<n;j++)
       graph[i][j] = 0;
     for(int i=0;i<m;i++)
     {
         graph[i][(i+1)%m] = 1;
         graph[i][i+m] = 1;
         graph[i + m][(i+k)%m + m] = 1;
     }
}

void subsets(vector<int> arr, int size, int left, int index, vector<int> *l, vector<vector<int> >* ret){
    if(left==0){
        ret->push_back(*l);
        return;
    }
    for(int i=index; i < size;i++){
        l->push_back(arr[i]);
        subsets(arr,size,left-1,i+1,l,ret);
        l->pop_back();
    }
}   

//number of spokes of set C
int num_of_spokes(vector<int> C)
{
  int ret = 0;
  cout << "in num of spokes: "; print(C);
  for(int i=0;i < C.size();i++)
  for(int j=i;j < C.size();j++)
  if(C[i] == (C[j] + m)%n) 
  {
    ret++;
  }
  return ret;
}

//return 0-1 coding of a subset
bitset<4*n> only_code(vector<int> A1, vector<int> B, vector<int> A2, vector<int> indA)
{
  bitset<4*n> temp;
  for(int i=0;i < A1.size();i++)
    temp.set(A1[i],true);
  
  for(int i=0;i < B.size();i++)
    temp.set(B[i] + n,true);

  for(int i=0;i < A2.size();i++)
    temp.set(A2[i] + n + n,true);

  for(int i=0;i < indA.size();i++)
    temp.set(indA[i] + n + n + n,true);

  return temp;
}


//return 0-1 coding of a subset
void code(vector<int> A1, vector<int> B, vector<int> A2, vector<int> indA, vector<int> indB)
{
  bitset<4*n> temp;
  for(int i=0;i < A1.size();i++)
    temp.set(A1[i],true);
  
  for(int i=0;i < B.size();i++)
    temp.set(B[i] + n,true);

  for(int i=0;i < A2.size();i++)
    temp.set(A2[i] + n + n,true);

  for(int i=0;i < indA.size();i++)
    temp.set(indA[i] + n + n + n,true);

  all_code.push_back(temp);
  all_vect.push_back(indB);
}


//check if C is a mis or not
bool is_mis(vector<int> C)
{
  for(int i=0;i < C.size();i++)
  for(int j=i;j < C.size();j++)
    if(graph[C[i]][C[j]] == 1) return false;
  return true;
}



//find all mis of a set C
vector<vector<int> > mis_subset(vector<int> A)
{
   vector<vector<int> > all_mis;
   for(int i=0;i < A.size();i++)
   {
     vector<int> *lt = new vector<int>();
     vector<vector<int> > *ret = new vector<vector<int> >();
     subsets(A, A.size(), i, 0, lt, ret);
     delete lt;
     for(int i=0;i < ret->size();i++)
       if(is_mis((*ret)[i]) == true)
          all_mis.push_back((*ret)[i]);
       delete ret; 
     
   }
   return all_mis;
}

vector<int> cup(vector<int> a, vector<int> b)
{
   vector<int> ret;
   ret.reserve( a.size() + b.size() ); // preallocate memory
   ret.insert( ret.end(), a.begin(), a.end() );
   ret.insert( ret.end(), b.begin(), b.end() );
   return ret;
}

void exhaustive_mis(vector<int> A1, vector<int> B, vector<int> A2)
{

   // A = A1 cup A2
   vector<int> A = cup(A1,A2);
   vector<vector<int> > all_mis_A = mis_subset(A);
   vector<vector<int> > all_mis_B = mis_subset(B);
   
   for(int i=0;i < all_mis_A.size();i++)
   {
     vector<int> A_i = all_mis_A[i];
     int maxY1Y2_size = 0, maxY1Y2_index = 0;
     for(int j=0;j < all_mis_B.size();j++)
     {
       vector<int> B_j = all_mis_B[j];
       vector<int> tmp = cup(A_i, B_j);
       if(is_mis(tmp) == false) continue;
       if(maxY1Y2_size < B_j.size()) {maxY1Y2_size=B_j.size();maxY1Y2_index=j;}
     }
     
     code(A1, B, A2, A_i,all_mis_B[maxY1Y2_index]);
   }
}

vector<vector<int> > get_k_spokes(vector<int> B)
{
  
  vector<vector<int> > ret(3);
  ret[0] = vector<int>();
  for(int i=0;i < B.size();i++)
  {
    vector<int>::iterator iter = find(B.begin(), B.end(), (B[i] + m)%n);
    if( iter != B.end())
    {
      ret[0].push_back(B[i]);
      ret[0].push_back(B[i+n]);
      B.erase(iter);
      B.erase(find(B.begin(), B.end(), B[i]));
    }
    
    if(ret[0].size() == 2*k) break;
  }
  
  ret[2] = vector<int>();
  for(int i=0;i < B.size();i++)
  {
    vector<int>::iterator iter = find(B.begin(), B.end(), (B[i] + m)%n);
    if( iter != B.end())
    {
      ret[2].push_back(B[i]);
      ret[2].push_back(B[i+n]);
      B.erase(iter);
      B.erase(find(B.begin(), B.end(), B[i]));
    }
    
    if(ret[2].size() == 2*k) break;
  }
   
  ret[1] = B;
  cout << "ret[0] : ";print(ret[0]);
  cout << "ret[1] : ";print(ret[1]);
  cout << "ret[2] : ";print(ret[2]);
  return ret;
}

// returns a independent subset of B like retX
// that X cup retX is an independent subset of G
// and retX is maximum with respect to previous property
vector<int> MIS(vector<int> A1, vector<int> B, vector<int> A2)
{
  cerr << "size of B: " << B.size() << endl;
  cerr << "num of spokes: " << num_of_spokes(B) << endl;
  if(num_of_spokes(B) < 3*k)
  {
      exhaustive_mis(A1,B,A2);
  }
  else
  {
      vector<vector<int> > ret = get_k_spokes(B);
      vector<int> B1 = ret[0];
      vector<int> B3 = ret[1];
      vector<int> B2 = ret[2];
      MIS(B1,B2,B3); 
      vector<vector<int> > all_mis_X1 = mis_subset(A1);
      vector<vector<int> > all_mis_X2 = mis_subset(A2);
      vector<vector<int> > all_mis_Y1 = mis_subset(B1);
      vector<vector<int> > all_mis_Y2 = mis_subset(B3);

      vector<int> maxY1Y2;

      for(int i1=0;i1 < all_mis_X1.size();i1++)
      for(int i2=0;i2 < all_mis_X2.size();i2++)
      for(int i3=0;i3 < all_mis_Y1.size();i3++)
      for(int i4=0;i4 < all_mis_Y2.size();i4++)
      {
        vector<int> X1 = all_mis_X1[i1];
	vector<int> X2 = all_mis_X2[i2];
	vector<int> Y1 = all_mis_Y1[i3];
	vector<int> Y2 = all_mis_Y2[i4];
        bitset<4*n> ret = only_code(B1, B2, B3, cup(Y1,Y2));
        for(int i5=0;i5 < all_code.size();i5++)
		if(all_code[i5] == ret)
			if(is_mis(cup (X1, cup(X2, cup(Y1, cup(Y2, all_vect[i5]))))))
				if(maxY1Y2.size() < cup(Y1, cup(Y2, all_vect[i5])).size())
					maxY1Y2 = cup(Y1, cup(Y2, all_vect[i5]));
				
	
      }
      return maxY1Y2;
  }
  return vector<int>();
}


int main(){
    generalized_peterson();
    vector<int> one_to_n;
    for(int i=0;i < n;i++) one_to_n.push_back(i);
    vector<vector<int> > ret = get_k_spokes(one_to_n);
    cout << "getting k spodes" << endl;
    vector<int> B1 = ret[0];
    vector<int> B3 = ret[1];
    vector<int> B2 = ret[2];
    //cerr << "size :  " << B1.size() << " " << B2.size() << " " << B3.size << " " << endl;
    cerr << "starting with the algorithm" << endl;
    vector<int> max_ind_set = MIS(B1,B2,B3);
    return 0;
}

