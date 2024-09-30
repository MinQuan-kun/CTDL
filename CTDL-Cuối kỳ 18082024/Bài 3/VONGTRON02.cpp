#include <iostream>
#include <vector>

using namespace std;


vector<int> playGame(int n, vector<int> k_values) {
    vector<int> people(n);
    vector<int> result;
    int k_index = 0;
    for (int i = 0; i < n; i++) {
        people[i] = i;
    }
    int index = 0;
    
    while (!people.empty()) {
        
        index = (index + k_values[k_index] - 1) % people.size();
        
       
        result.push_back(people[index]);
        
        
        people.erase(people.begin() + index);
        
       
        k_index = (k_index + 1) % k_values.size();
    }
    return result;
}

int main() {
    int n, k;
    
    cin >> n >> k;
    vector<int> k_values(k);
   
    for (int i = 0; i < k; i++) {
        cin >> k_values[i];
    }
    
    vector<int> result = playGame(n, k_values);
    
    
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    
    return 0;
}
