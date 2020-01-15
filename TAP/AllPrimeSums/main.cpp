#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

bool isPrimeNumber (int x) {
    bool prime = true;

    if (x == 2) {
        return true;
    }

    for (int i = 2; i <= x/2; ++i) {
        if (x % i == 0) {
            prime = false;
            break;
        }
    }

    return prime;
}

int findBiggerPrime (int x) { // equal is a flag value
    if (x == 2) {
        return 3;
    }

    for (int i = x+1; i < INT_MAX; ++i) {
        if (isPrimeNumber(i)) {
            return i;
        }
    }
}

void bktSumPrimes (int &sum, int x, vector<int> primes) {
    if (sum > x) {
        sum -= primes.back();
        primes.pop_back();

        // no more elements => Terminate
        if (primes.empty()) {
            return;
        }

        // incrementing the last element
        sum -= primes.back();
        int num = primes.back();
        primes.pop_back();
        primes.push_back(findBiggerPrime(num));
        sum += primes.back();

        bktSumPrimes(sum, x, primes);
    }
    else if (sum  < x) {
        sum += primes.back();
        primes.push_back(primes.back());
        bktSumPrimes(sum, x, primes);
    }
    else {
        for (auto i : primes) {
            cout << i << " ";
        }
        cout << endl;

        sum -= primes.back();
        primes.pop_back();

        if (primes.empty()) {
            return;
        }

        // incrementing the last element
        sum -= primes.back();
        int num = primes.back();
        primes.pop_back();
        primes.push_back(findBiggerPrime(num));
        sum += primes.back();

        bktSumPrimes(sum, x, primes);
    }
}

int main() {
    bool found = false;

    int sum = 2;

    vector<int> primes; primes.push_back(2);

    bktSumPrimes(sum, 10, primes);

    return 0;
}
