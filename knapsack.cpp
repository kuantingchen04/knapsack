#include <iostream>     // std::cout
#include <vector>       // std::vector
using namespace std;

class knapsack{
private:
    vector<int> C = {20,10,12}; // cost
    vector<int> W = {5,4,3}; // worth
    int n = C.size();
    int pack_V = 42; // volume of knapsack

    void print_row(const vector<int>& arr){
        for (int i=0;i<arr.size();i++){
            if (arr[i]==INT_MIN) cout << "." << " ";
            else cout << arr[i] << " ";
        }
        cout << endl;
    }

public:
    void knapsack01_2d(){
        vector<vector<int>> dp(n+1, vector<int>(pack_V+1,0)); // item: 1-N (pad 1), volume: 0-packV

        print_row(dp[0]);
        for(int i=1; i<=n; ++i){
            for(int j=C[i-1]; j<=pack_V; ++j){
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-C[i-1]]+W[i-1]);
            }
            print_row(dp[i]);
        }
        cout << "ans:" << dp[n][pack_V] << endl; // get_answer
        for (int i=1; i<=n; ++i){
            if (dp[i][pack_V] > dp[i-1][pack_V]) 
                cout << "pick:" << i << ", worth:" << W[i-1] << endl; // get pick info
        }
    }

    void knapsack01_1d(){ // basis
        vector<int> dp(pack_V+1,0);

        for(int i=1; i<=n; ++i){
            for(int j=pack_V; j>=C[i-1]; --j){ // careful, only difference from 2d to 1d
                dp[j] = max(dp[j], dp[j-C[i-1]]+W[i-1]);
            }
            print_row(dp);
        }
        cout << "ans:" << dp[pack_V] << endl; // get answer
    }

    void knapsack01_1d_equal(){
        vector<int> dp(pack_V+1,INT_MIN); // initialization: all invalid except dp[0]
        dp[0] = 0;

        for(int i=1; i<=n; ++i){
            for(int j=pack_V; j>=C[i-1]; --j){ 
                if (dp[j-C[i-1]]!=INT_MIN) dp[j] = max(dp[j], dp[j-C[i-1]]+W[i-1]);
            }
            print_row(dp);
        }
        // check valid solution
        if (dp[pack_V]==INT_MIN) cout << "no solution" << endl;
        else cout << "ans:" << dp[pack_V] << endl;
    }

};

int main () {
    knapsack bp;
    bp.knapsack01_2d();
    cout << "---" << endl;
    bp.knapsack01_1d();
    cout << "---" << endl;
    bp.knapsack01_1d_equal();

    return 0;
}