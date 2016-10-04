#include <iostream>
#include <stdlib.h>
#include <locale>
#include <vector>
#include <thread>
#include <fstream>
#include <ctime>
#include <utility>
#include <iomanip>
#include <math.h>
#include <string>

using namespace std;

vector<pair<string, long long> > vector1;

const long long stop = 31864915000000000000001;

bool is_prime(const long long number) {

  long long root = sqrt(number);

  for (long long i = 3; i <= root + 1; i += 2) {
    if (number % i == 0) {
      return false;
    }
  }

  return true;
}

void find_primes() {
  for (long long i = 5054500746937815487; i <= stop; i += 2) {
    if (is_prime(i)) {

      // Get current time
      time_t now = time(0);
      char* dt = ctime(&now);

      // Only keep the 10 last primes in the vector
      if (vector1.size() == 10) {
        vector1.pop_back();
      }

      vector1.insert(vector1.begin(), make_pair(string(dt), i));
    }
  }
}

void handle_logfile() {

  ofstream myfile;

  while (true) {
    this_thread::sleep_for(chrono::milliseconds(10000));

    myfile.open ("/www/primes.txt");

    for (size_t i = 0; i < vector1.size(); i++) {
      myfile << vector1.at(i).first << " " << vector1.at(i).second << endl << endl;
    }

    myfile.close();
    cout << "Last prime was " << vector1.at(0).second << endl;
  }

}

int main(const int argc, const char *argv[]) {

  thread t1(find_primes);
  thread t2(handle_logfile);

  t1.join();
  t2.join();

  return 0;
}
