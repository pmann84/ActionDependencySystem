#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "IAction.h"

#include <functional>
#include <condition_variable>

class ThreadPool
{
public:
   ThreadPool(std::function<void(std::shared_ptr<IAction>)>, std::function<bool(std::shared_ptr<IAction>)>, unsigned int);
   ~ThreadPool();

   void add_jobs(std::vector<std::shared_ptr<IAction>>);
   void wait() const;

private:
   void work_func();

   std::mutex m_queue_mutex;
   unsigned int m_max_threads;
   bool m_stop;
   std::vector<std::shared_ptr<IAction>> m_tasks;
   std::vector<std::thread> m_workers;
   std::condition_variable m_condition;
   std::function<void(std::shared_ptr<IAction>)> m_post_action_run;
   std::function<bool(std::shared_ptr<IAction>)> m_validate_action;
};

#endif // __THREAD_POOL_H__

