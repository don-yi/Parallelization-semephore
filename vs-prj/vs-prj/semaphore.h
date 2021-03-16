#include <atomic>
#include <condition_variable>

class Semaphore
{

public:
  explicit Semaphore(int const max) : max(max) {};
  void wait() {
    std::unique_lock<std::mutex> lk(mtx);
    while (ct == max) cv.wait(lk);
    ++ct;
  }
  void signal() {
    std::unique_lock<std::mutex> lk(mtx);
    --ct;
    cv.notify_one();
	}

private:
  std::mutex mtx;
  std::condition_variable cv;
  int max;
  int ct = 0;
};

