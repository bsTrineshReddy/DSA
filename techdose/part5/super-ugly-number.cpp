// method 1: inspired by ugly number 2
int nthSuperUglyNumber(int n, vector<int>& primes) {
	int k = primes.size();
	vector<int> pos(k, 0);
	vector<int> res(n);
	res[0] = 1;
	for (int i = 1; i < n; i++) {
		int temp = INT_MAX;
		for (int j = 0; j < k; j++) 
			temp = min(temp, res[pos[j]] * primes[j]);
		for (int j = 0; j < k; j++) {
			if (temp == res[pos[j]] * primes[j])
				pos[j]++;
		}
		res[i] = temp;
	}
	return res[n - 1];
}
===============
