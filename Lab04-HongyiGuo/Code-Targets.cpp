#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int maxCoins(vector<int>& nums) {
	// Create two virtual targets
	vector<int> B(1, 1);
	for (int i = 0; i < nums.size(); i++)
		B.push_back(nums[i]);
	B.push_back(1);

	int num = B.size();
	vector<vector<int> > f(num, vector<int>(num, 0)); //f: num x num, all-zero

	for (int t = 2; t < num; t++)
		for (int i = 0; i + t < num; i++) {
			int k = i + t;
			for (int j = i + 1; j < k; j++)
				f[i][k] = max(f[i][k], f[i][j] + f[j][k] + B[i] * B[j] * B[k]);
		}
	return f[0][num - 1];
}

int main() {
	int N;
	vector<int> nums;

	cin >> N;
	for (int tmp, i = 0; i < N; i++) {
		cin >> tmp;
		nums.push_back(tmp);
	}

	cout << maxCoins(nums) << endl;
	return 0;
}
