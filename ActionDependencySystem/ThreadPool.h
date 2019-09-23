#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "ActionDependencySystemCore.h"

#include <functional>
#include <future>
#include <queue>

class ACTION_DEPENDENCY_SYSTEM_API ThreadPool
{
public:
   ThreadPool(const unsigned int num_threads = 0);
   ~ThreadPool();
   // For now we can only add void fns with no args, could expand to arbitrary functions - investigate std::result_of
   std::future<void> add_job(std::function<void()>);

private:
   void main_thread_loop();

   std::mutex m_queue_mutex;
   bool m_stop;
   std::queue<std::function<void()>> m_tasks;
   std::vector<std::thread> m_workers;
   std::condition_variable m_condition;
};

#endif // __THREAD_POOL_H__

