#include<bits/stdc++.h>
using namespace std;
// Leetcode Random Pick Based Implementation - can be optimised to O(1) ?
int random_choice_temp(unordered_map<int, double> model, int scale){
  //Randomly picking a page from pages weighted on their probabilities
  // scale depending on kitna precision tk chaiye kitne decimal digits utne mai 10 ki power hogi
  vector<int> pages;   // keys of the map -> Pages
  vector<int> weights; // values of the map -> Probability associated with that Page
  for (auto it = model.begin(); it != model.end(); it++){
    pages.push_back(it->first);
    weights.push_back(it->second * scale); // taki natural number line pe laa ske
  }
  vector<int> cumm_sum; // cumulative sum
  cumm_sum.push_back(weights[0]);

  for (int i = 1; i < weights.size(); i++){
    cumm_sum.push_back(cumm_sum[i - 1] + weights[i]);
  }

  int random_no = rand() % cumm_sum[cumm_sum.size() - 1]; //pure sum se remainder liya taki uss range mai aaye
  auto it = upper_bound(cumm_sum.begin(), cumm_sum.end(), random_no);
  //upperbound se wo index milega jo just humare random se bda hoga
  return pages[it - cumm_sum.begin()]; //uss index wale page ko return kiya
}


// ye wo random choice wala hai.....isme modification ho skti......
int random_choice(unordered_map<int, double> mp, int scale){
  int selected = -1;
  int totalprob = 0;
  for (auto it = mp.begin(); it != mp.end(); it++){
    if (selected == -1){
      selected = it->first;
      totalprob += (it->second * scale);
    }
    else{
      int maxi = (totalprob + (it->second * scale)); // iska logic statckoverflow pe tha usko thoda twist kra hai
      int t = rand() % maxi;                         // galat lage to btana.......
      if (t >= totalprob){
        selected = it->first;
      }
      totalprob += (it->second * scale);
    }
  }
  return selected;
}
