#include "Poco/Timer.h"
#include "Poco/Thread.h"
#include "Poco/Stopwatch.h"
#include <iostream>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

using Poco::Stopwatch;
using Poco::Thread;
using Poco::Timer;
using Poco::TimerCallback;

class TimerExample
{
  public:
    TimerExample() { _sw.start(); }

    void onTimer(Timer &timer)
    {
      std::cout << "Callback called after " << _sw.elapsed() / 1000 << " milliseconds." << std::endl;
    }

  private:
    Stopwatch _sw;
};

void wait(int seconds)
{
  boost::this_thread::sleep_for(boost::chrono::seconds{seconds});
}

void thread()
{
  for (int i = 0; i < 5; ++i)
  {
    wait(1);
    std::cout << i << '\n';
  }
}

int main(int argc, char **argv)
{
  TimerExample example;
  Timer timer(250, 500);
  timer.start(TimerCallback<TimerExample>(example, &TimerExample::onTimer));

  Thread::sleep(5000);
  timer.stop();

  boost::thread t{thread};
  t.join();
  return 0;
}