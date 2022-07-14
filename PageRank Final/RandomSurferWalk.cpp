#include "TransitionModel.cpp"
#include "RandomChoiceOnWeight.cpp"
using namespace std;
// finally the model1 of sample walk jitna time hum ek particular web page pe rahe uska divison karke ranking wapis kar di.......
unordered_map<int,double> random_surfer_walk(vector<int> adj[], double damping_factor, int total_vertices,int samples){
  int size = sizeof(adj);
  unordered_map<int, double> pagerank;
  int page = rand() % size; // randomly choosing a page (lies in 0 to size-1)
  // if (next_page < 0){
  //   next_page += size; // if rand gives negative value.... sirf postive nhi deta kya ??
  // } rand gives positive values only.

  for (int sample = 0; sample < samples; sample++){

    unordered_map<int, double> model = transition_model(adj, page, damping_factor, total_vertices);

    int next_page = random_choice_temp(model, 100); // need suggestion here for scale.....

    if (pagerank.find(next_page) != pagerank.end()){
      pagerank[next_page] += 1;
    }
    else{
      pagerank[next_page] = 1;
    }
  }
  // vector<double> ranks;
  for (auto it = pagerank.begin(); it != pagerank.end(); it++)
  {
    it->second = double(double(it->second) / double(samples));
    // ranks.push_back(it->second);
  }
  return pagerank;
}