#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "IAction.h"

#include <functional>
#include <condition_variable>
#include <future>
#include <queue>

class ThreadPool
{
public:
   ThreadPool(const unsigned int num_threads = 0);
   ~ThreadPool();
   // For now we can only add void fns with no args, could expand to arbitrary functions - investigate std::result_of
   std::future<void> add_job(std::function<void()>);

private:
   void main_thread_loop();

   std::mutex m_queue_mutex;
   unsigned int m_max_threads;
   bool m_stop;
   std::queue<std::function<void()>> m_tasks;
   std::vector<std::thread> m_workers;
   std::condition_variable m_condition;
};

#endif // __THREAD_POOL_H__

