#include <bits/stdc++.h>
#include "TransitionModel.cpp"
#include "RandomChoiceOnWeight.cpp"
#include "RandomSurferWalk.cpp"
#include "IterativeMethod.cpp"
using namespace std;

int main()
{
    vector<int> c1[4];
    c1[0].push_back(1);
    c1[1].push_back(0);
    c1[1].push_back(2);
    c1[2].push_back(1);
    c1[2].push_back(3);
    c1[3].push_back(1);
    unordered_map<int,double> ans;
    ans = iterate_Meth2(c1,0.85,4);
    cout<<"method2-Iteration"<<endl;
    for(auto x:ans){
        cout<<x.first<<" "<<x.second<<endl;
    }
    cout<<"method1-Sampling"<<endl;
    unordered_map<int,double> ans2;
    ans2 = random_surfer_walk(c1,0.85,4,1000);
    cout<<"method2-Iteration"<<endl;
    for(auto x:ans2){
        cout<<x.first<<" "<<x.second<<endl;
    }
    return 0;
}
