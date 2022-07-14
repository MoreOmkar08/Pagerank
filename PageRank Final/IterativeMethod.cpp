#include<bits/stdc++.h>
using namespace std;
unordered_map<int, double> iterate_Meth2(vector<int> adj[], double damping_factor, int size1){

    int sz = size1; //No. of nodes in graph
    unordered_map<int, double> pagerank; //adjacency list define krte hue
    //vector<double> ranks; //iske saath work krenge
    bool converged = false; //p<0.001 ko check krne ke liye

    for(int i=0;i<sz;i++) {pagerank[i]= double(double(1)/double(sz));} //Initial probability sabko same derahe
    unordered_map<int, double> ranks_cpy;
    while(!converged){
        for(int i=0;i<sz;i++) {ranks_cpy[i] = pagerank[i];}// ranks ko hi copy kiya
        unordered_map<int,double> ranks_diff; //threshold(0.001) maintain/check krne ke liye
        //double prb[sz]; //probability

        for(int i=0;i<sz;i++){
            double prb=0;
            //int l=0; //calculating no. of links from one site to others
            for(int j=0;j<sz;j++){
            for(auto x:adj[j]){
                if(x==i) prb += double(ranks_cpy[j])/adj[j].size();
                else if(adj[j].size()==0) prb+= double(1)/sz;
            }
            // Be cautious. CHECK
            }
            pagerank[i] = double(1-damping_factor)/sz + double(damping_factor*prb);
            ranks_diff[i] = abs(ranks_cpy[i]-pagerank[i]);
            //cout<<pagerank[i]<<endl;
            //cout<<ranks_diff[i]<<endl;
        }

        /*for(int j=0;j<sz;j++){
            //pagerank[j] = double(1-damping_factor)/sz + double(damping_factor*prb[j]);
            ranks_diff[j] = abs(ranks_cpy[j]-pagerank[j]);
        }*/

        converged = true;
        for(int i=0;i<sz;i++){
            if(ranks_diff[i]>0.002) converged=false;
        }
    }

    //Precautionary Step to check sum of probabilities = 1?
    /*
    int sum_prb = 0;
    for(int i=0;i<sz;i++) sum_prb+=pagerank[i];
    for(int i=0;i<sz;i++) pagerank[i]=pagerank[i]/sum_prb;
    */
    //Same hi result dega ye

    return pagerank;
}