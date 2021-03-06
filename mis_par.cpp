#include <iostream>
#include <vector>

using namespace std;

// P(n,k) such that n is even = 2*(n/2) = 2*alpha
// in this way spoke is an edge between ai -> ai+alpha
int n, k;
vector<vector<int> > graph;

vector<vector<int> > gpeterson()
{
     graph = vector<vector<int> >(2*n);
     for(int i=0;i<n;i++) graph[i] = vector<int> (2*n);
     for(int i=0;i<n;i++)for(int j=0;j<n;j++) graph[i][j] = 0; 
     
     for(int i=0;i<n;i++)
     {
         graph[i][(i+1)%n] = 1;
         graph[i][i+n] = 1;
         graph[n+i][n+(i+k)%n] = 1;
     }
     return graph;
}

//check if C is a mis or not
bool is_mis(vector<int> C)
{
  for(int i=0;i < C.size();i++)
  for(int j=i;j < C.size();j++)
    if(graph[C[i]][C[j]] == 1) return false;
  return true;
}

void print( vector<int> l)
{
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

