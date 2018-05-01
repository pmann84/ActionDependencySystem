#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "IAction.h"

#include <functional>
#include <condition_variable>
#include <future>
#include <queue>

class IThreadPool
{
public:
   virtual ~IThreadPool() {};
   // For now we can only add void fns with no args, could expand to arbitrary functions - investigate std::result_of
   virtual std::future<void> add_job(std::function<void()>) = 0;

private:
   virtual void main_thread_loop() = 0;
};

class ThreadPool : public IThreadPool
{
public:
   //ThreadPool(std::function<void(std::shared_ptr<IAction>)>, std::function<bool(std::shared_ptr<IAction>)>, unsigned int);
   ThreadPool(unsigned int);
   ~ThreadPool() override;

   std::future<void> add_job(std::function<void()>) override;
   //void wait() const;

private:
   void main_thread_loop() override;

   std::mutex m_queue_mutex;
   unsigned int m_max_threads;
   bool m_stop;
   std::queue<std::function<void()>> m_tasks;
   std::vector<std::thread> m_workers;
   std::condition_variable m_condition;
   //std::function<void(std::shared_ptr<IAction>)> m_post_action_run;
   //std::function<bool(std::shared_ptr<IAction>)> m_validate_action;
};

#endif // __THREAD_POOL_H__

