#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(std::function<void(std::shared_ptr<IAction>)> post_run_action, 
                       std::function<bool(std::shared_ptr<IAction>)> validate_action, 
                       unsigned int num_threads = 0) 
         : m_max_threads(0), 
           m_stop(false), 
           m_post_action_run(post_run_action), 
           m_validate_action(validate_action)
{
   // Check the number of threads we can use
   unsigned long const hardware_threads = std::thread::hardware_concurrency();
   m_max_threads = num_threads == 0 ? hardware_threads != 0 ? hardware_threads : 2 : num_threads;
   std::cout << "Starting Thread Pool..." << std::endl;
   std::cout << "Max threads available: " << m_max_threads << std::endl;
   // Start up the threads
   for (int i = 0; i < m_max_threads; ++i)
   {
      m_workers.push_back(std::thread(std::bind(&ThreadPool::work_func, this)));
   }
}

ThreadPool::~ThreadPool()
{
   m_stop = true;
   m_condition.notify_all();
   for (auto& worker : m_workers)
   {
      std::cout << "Shutting down thread Id [" << worker.get_id() << "]" << std::endl;
      worker.join();
   }
}

void ThreadPool::add_jobs(std::vector<std::shared_ptr<IAction>> jobs)
{
   std::unique_lock<std::mutex> lock(m_queue_mutex);
   for (auto job : jobs)
   {
      std::cout << "Adding action [" << job->name() << "] to queue..." << std::endl;
      m_tasks.push_back(job);
   }
   m_condition.notify_all();
}

void ThreadPool::wait() const
{
   // we're done waiting once all threads are waiting
   while (!m_tasks.empty());
}

void ThreadPool::work_func()
{
   std::cout << "Thread Id [" << std::this_thread::get_id() << "] started..." << std::endl;
   while (true)
   {
      std::shared_ptr<IAction> action;
      // Grab the next job off the queue
      {
         std::unique_lock<std::mutex> lock(m_queue_mutex);
         m_condition.wait(lock, [&]() { return m_stop || !m_tasks.empty(); });
         // Loop over the tasks here and see if there are any we can start - MOVE THIS LOOP OUT TO THE GRAPH CLASS AND LET THE GRAPH CLASS HANDLE WHEN TO ADD THE ACTIONS TO THE THREAD POOL. THAT WAY THE THREAD POOL ONLY NEEDS TO RUN FUNCTIONS AND RETURN FUTURES. THE GRAPH CLASS CAN THEN CHECK OUTPUTS ETC AND DETERMINE INPUTS, AND THEN QUEUE MORE UP WHEN WE HAVE RESPONSES BACK. 
         for (auto task : m_tasks)
         {
            if (m_validate_action(task))
            {
               action = task;
               break;
            }
         }
         // Remove from the queue so that no other threads start the same task
         const auto action_to_erase_iterator = std::find(m_tasks.begin(), m_tasks.end(), action);
         if (action_to_erase_iterator != m_tasks.end())
         {
            m_tasks.erase(action_to_erase_iterator);
         }
      }
      if (m_stop)
      {
         return;
      }
      if (action && m_validate_action(action))
      {
         std::cout << "Executing action [" << action->name() << "] on thread Id [" << std::this_thread::get_id() << "]" << std::endl;
         // Run action
         action->run();
         // Now propagate outputs, so check the action connections - only want inputs 
         // so we only care about the connections where this is a dst action
         m_post_action_run(action);
      }
   }
}