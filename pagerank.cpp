#include <bits/stdc++.h>

using namespace std;

// BFS trasversal of the graph jyada kuch nahi bass graph mai chalna tha DFS bhi lga skte the ......
map<int, double> BFS(bool visited[], vector<int> adj[], map<int, double> markov_chain, double prob)
{
  queue<int> q;
  q.push(0);
  while (q.empty() == false)
  {
    int temp = q.front();
    q.pop();
    visited[temp] = true;
    markov_chain[temp] = double(prob);
    for (int u : adj[temp])
    {
      if (visited[u] == false)
      {
        q.push(u);
      }
    }
  }
  return markov_chain;
}

// markov chain model return kar rha ye function......
map<int, double> transition_model(vector<int> adj[], int page, double damping_factor, int total_vertices)
{
  // Function which will return a probability distribution of all the pages telling which page to visit next
  // Kitti probability se next wala page visit hoga

  // kya total vertices adj.size() nhi hoga ???

  map<int, double> markov_chain;           // transtion model to be made...... map of page to probabilty
  vector<int> potential_pages = adj[page]; // pages jisse curr page linked hai

  if (potential_pages.size() == 0)
  {
    double prob = 1 / double(total_vertices);
    bool visited[total_vertices] = {false}; // ??? intialising??
    BFS(visited, adj, markov_chain, prob);  // graph mai link nhi //BFS krke wo constant prob dedeti hai sare nodes ko
    return markov_chain;
  }

  double damping_prob = double(double(damping_factor) / double(potential_pages.size()));
  // probability with which it chooses one of the links out of potential pages

  double damping_prob_random = double(double(1 - damping_factor) / double(total_vertices));
  // probability with which it chooses one out of all the pages that we have

  for (int potential_page : potential_pages)
  {
    markov_chain[potential_page] = damping_prob;
  }

  for (int i = 0; i < total_vertices; i++)
  {
    if (markov_chain.find(i) == markov_chain.end()) // Means Not Found
    {
      markov_chain[i] = damping_prob_random;
    }
    else // When Found just add the prob to it
    {
      markov_chain[i] += damping_prob_random;
    }
  }
  return markov_chain;
}

// ye wo random choice wala hai.....isme modification ho skti......
int random_choice(map<int, double> mp, int scale)
{
  int selected = -1;
  int totalprob = 0;
  for (auto it = mp.begin(); it != mp.end(); it++)
  {
    if (selected == -1)
    {
      selected = it->first;
      totalprob += (it->second * scale);
    }
    else
    {
      int maxi = (totalprob + (it->second * scale)); // iska logic statckoverflow pe tha usko thoda twist kra hai
      int t = rand() % maxi;                         // galat lage to btana.......
      if (t >= totalprob)
      {
        selected = it->first;
      }
      totalprob += (it->second * scale);
    }
  }
  return selected;
}

// Leetcode Random Pick Based Implementation
int random_choice_temporary(map<int, double> mp, int scale)
{
  // scale depending on kitna precision tk chaiye kitne decimal digits utne mai 10 ki power hogi
  vector<int> pages;   // keys of the map
  vector<int> weights; // values of the map
  for (auto it = mp.begin(); it != mp.end(); it++)
  {
    pages.push_back(it->first);
    weights.push_back(it->second * scale); // taki natural number line pe laa ske
  }
  vector<int> cumm_sum; // cumulative sum
  cumm_sum.push_back(weights[0]);
  for (int i = 1; i < weights.size(); i++)
  {
    cumm_sum.push_back(cumm_sum[i - 1] + weights[i]);
  }

  int random_no = rand() % cumm_sum[cumm_sum.size() - 1]; //pure sum se remainder liya taki uss range mai aaye
  auto it = upper_bound(cumm_sum.begin(), cumm_sum.end(), random_no);
  //upperbound se wo index milega jo just humare random se bda hoga
  return pages[it - cumm_sum.begin()]; //uss index wale page ko return kiya
}

// finally the model1 of sample walk jitna time hum ek particular web page pe rahe uska divison karke ranking wapis kar di.......
vector<double> random_surfer_walk(vector<int> adj[], double damping_factor, int samples, int total_vertices)
{
  int size = sizeof(adj);
  map<int, double> pagerank;
  int next_page = rand() % size; // randomly choosing a next page (lies in 0 to size-1)
  if (next_page < 0)
  {
    next_page += size; // if rand gives negative value.... sirf postive nhi deta kya ??
  }

  for (int i = 0; i < samples; i++)
  {
    map<int, double> model = transition_model(adj, next_page, damping_factor, total_vertices);

    next_page = random_choice(model, 100); // need suggestion here for scale.....

    if (pagerank.find(next_page) != pagerank.end())
    {
      pagerank[next_page] += 1;
    }
    else
    {
      pagerank[next_page] = 1;
    }
  }
  vector<double> ranks;
  for (auto it = pagerank.begin(); it != pagerank.end(); it++)
  {
    it->second = double(double(it->second) / double(samples));
    ranks.push_back(it->second);
  }
  return ranks;
}

map<int, double> iterate_Meth2(vector<int> adj[], double damping_factor, int size1){

    int sz = size1; //No. of nodes in graph
    map<int, double> pagerank; //adjacency list define krte hue
    //vector<double> ranks; //iske saath work krenge
    bool converged = false; //p<0.001 ko check krne ke liye

    for(int i=0;i<sz;i++) {pagerank[i]= double(double(1)/double(sz));} //Initial probability sabko same derahe

    while(!converged){
        map<int, double> ranks_cpy;
        for(int i=0;i<sz;i++) {ranks_cpy[i] = pagerank[i];}// ranks ko hi copy kiya
        map<int,double> ranks_diff; //threshold(0.001) maintain/check krne ke liye

        for(int i=0;i<sz;i++){
            double prb =0; //probability
            //int l=0; //calculating no. of links from one site to others
            for(auto x:adj[i]){
                if(adj[i].size()!=0) prb += double(ranks_cpy[i])/adj[i].size();
                else if(adj[i].size()==0) prb+= double(1)/sz;
            }
            // Be cautious. CHECK
            pagerank[i] = double(1-damping_factor)/sz + double(damping_factor*prb);
            ranks_diff[i] = abs(ranks_cpy[i]-pagerank[i]);
            cout<<ranks_diff[i]<<endl;

        }
        converged = true;
        for(int i=0;i<sz;i++){
            if(ranks_diff[i]>0.001) converged=false;
        }
    }

    //Precautionary Step to check sum of probabilities = 1?
    int sum_prb = 0;
    for(int i=0;i<sz;i++) sum_prb+=pagerank[i];
    for(int i=0;i<sz;i++) pagerank[i]=pagerank[i]/sum_prb;
    //Same hi result dega ye

    return pagerank;
}

int main()
{
    vector<int> c1[4];
    c1[0].push_back(1);
    c1[1].push_back(0);
    c1[1].push_back(2);
    c1[2].push_back(1);
    c1[2].push_back(3);
    c1[3].push_back(1);
    map<int,double> ans;
    ans = iterate_Meth2(c1,0.85,4);
    for(auto x:ans){
        cout<<x.first<<" "<<x.second<<endl;
    }
    vector<double> ans2 = random_surfer_walk(c1, 0.85, 10000, 4);
    for(auto)
  return 0;
}
