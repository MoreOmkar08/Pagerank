#include<bits/stdc++.h>
using namespace std;
//BFS Traversal of the given graph. (Assuming Connected Component For Now.)
unordered_map<int, double> BFS(bool visited[], vector<int> adj[], unordered_map<int, double> markov_chain, double prob)
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
unordered_map<int, double> transition_model(vector<int> adj[], int page, double damping_factor, int total_vertices)
{
  // Function which will return a probability distribution of all the pages telling which page to visit next
  // Kitti probability se next wala page visit hoga

  // kya total vertices adj.size() nhi hoga ???

  unordered_map<int, double> markov_chain;           // transtion model to be made...... unordered_map of page to probabilty
  vector<int> potential_pages = adj[page]; // pages jisse curr page linked hai

  if (potential_pages.size() == 0){
    double prob = 1 / double(total_vertices);
    bool visited[total_vertices] = {false}; 
    BFS(visited, adj, markov_chain, prob);  // graph mai link nhi //BFS krke wo constant prob dedeti hai sare nodes ko
    return markov_chain;
  }

  double damping_prob = double(double(damping_factor) / double(potential_pages.size()));
  // probability with which it chooses one of the links out of potential pages

  double damping_prob_random = double(double(1 - damping_factor) / double(total_vertices));
  // probability with which it chooses one out of all the pages that we have - RESET

  for (int potential_page : potential_pages){
    markov_chain[potential_page] = damping_prob;
  } //Assigning damping probability iniatially to all the pages

  for (int pg = 0; pg < total_vertices; pg++){
    if (markov_chain.find(pg) == markov_chain.end()){ //Not Found -> assign it the random reset probability
      markov_chain[pg] = damping_prob_random;
    }
    else{ // When Found just add the prob to it
      markov_chain[pg] += damping_prob_random;
    }
  }
  return markov_chain;
}
