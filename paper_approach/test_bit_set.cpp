#include <bitset>
#include <map>
#include <vector>

using namespace std;

int main()
{
const int n = 100;
bitset<n> m;
vector<bitset<n> > a;
m.set(10,true);
//vector<int> test;
a.push_back(m);
//cout << a[m] << a[bitset<100>];
return 0;
}
