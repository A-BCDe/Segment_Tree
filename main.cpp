#include <iostream>
#include <vector>
#include "SegmentTree.h"

using ll=long long;

ll convert(const ll &in){return in;}

ll func(const ll &a, const ll &b){return a+b;}

int main()
{
    int n,m;
    std::cin>>n>>m;
    std::vector<ll> input;
    input.reserve(n);
    for(int i=0;i<n;i++){
        ll x;
        std::cin>>x;
        input.emplace_back(x);
    }
    SegmentTree<ll,ll> tree(input,convert,func,(ll)0);
    for(int i=0;i<m;i++){
        int x,a,b;
        std::cin>>x>>a>>b;
        switch(x){
            case 1:
                tree.set_element(a,b);
                break;
            case 2:
                std::cout<<tree.search(a,b)<<std::endl;
                break;
            default:
                break;
        }
    }
}