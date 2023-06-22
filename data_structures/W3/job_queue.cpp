#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>


using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;
using namespace std;


class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
      auto cmp = [] (pair<int, long long> l,  pair<int, long long> r) {
          if (l.second == r.second) {
              return l.first > r.first;
          }
          return l.second > r.second;
      };
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, decltype(cmp)> worker_queue(cmp);
      for (int i=0; i <num_workers_; i++){
          worker_queue.push(make_pair(i, 0));
      }

    for (int i = 0; i < jobs_.size(); i ++) {
        pair<int, long long> worker = worker_queue.top();
        worker_queue.pop();
        assigned_workers_[i] = worker.first;
        start_times_[i] = worker.second;
        worker.second += jobs_[i];
        worker_queue.push(worker);
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
