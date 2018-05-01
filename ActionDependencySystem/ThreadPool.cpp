#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(unsigned int num_threads = 0) : m_max_threads(0), m_stop(false)
{
   // Check the number of threads we can use
   unsigned long const hardware_threads = std::thread::hardware_concurrency();
   m_max_threads = num_threads == 0 ? hardware_threads != 0 ? hardware_threads : 2 : num_threads;
   std::cout << "Starting Thread Pool..." << std::endl;
   std::cout << "Max threads available: " << m_max_threads << std::endl;
   for (int i = 0; i < m_max_threads; ++i)
   {
      m_workers.push_back(std::thread(std::bind(&ThreadPool::main_thread_loop, this)));
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

std::future<void> ThreadPool::add_job(std::function<void()> task)
{
   std::unique_lock<std::mutex> lock(m_queue_mutex);
   auto packaged_task = std::make_shared<std::packaged_task<void()>>(std::packaged_task<void()>(task));
   std::future<void> result = packaged_task->get_future();
   m_tasks.emplace([packaged_task]() { (*packaged_task)(); });
   m_condition.notify_one();
   return result;
}

void ThreadPool::main_thread_loop()
{
   std::cout << "Thread Id [" << std::this_thread::get_id() << "] started..." << std::endl;
   while (true)
   {
      if (m_stop)
      {
         return;
      }
      if (!m_tasks.empty())
      {
         std::function<void()> task;
         {
            // Grab the next job off the queue
            std::unique_lock<std::mutex> lock(m_queue_mutex);
            m_condition.wait(lock, [&]() { return m_stop || !m_tasks.empty(); });
            task = std::move(m_tasks.front());
            m_tasks.pop();
         }
         // Actually run it
         task();
      }
   }
}

//ThreadPool::ThreadPool(std::function<void(std::shared_ptr<IAction>)> post_run_action, 
//                       std::function<bool(std::shared_ptr<IAction>)> validate_action, 
//                       unsigned int num_threads = 0) 
//         : m_max_threads(0), 
//           m_stop(false), 
//           m_post_action_run(post_run_action), 
//           m_validate_action(validate_action)
//{
//   // Check the number of threads we can use
//   unsigned long const hardware_threads = std::thread::hardware_concurrency();
//   m_max_threads = num_threads == 0 ? hardware_threads != 0 ? hardware_threads : 2 : num_threads;
//   std::cout << "Starting Thread Pool..." << std::endl;
//   std::cout << "Max threads available: " << m_max_threads << std::endl;
//   // Start up the threads
//   for (int i = 0; i < m_max_threads; ++i)
//   {
//      m_workers.push_back(std::thread(std::bind(&ThreadPool::work_func, this)));
//   }
//}
//
//void ThreadPool::work_func()
//{
//   std::cout << "Thread Id [" << std::this_thread::get_id() << "] started..." << std::endl;
//   while (true)
//   {
//      std::shared_ptr<IAction> action;
//      // Grab the next job off the queue
//      {
//         std::unique_lock<std::mutex> lock(m_queue_mutex);
//         m_condition.wait(lock, [&]() { return m_stop || !m_tasks.empty(); });
//         // Loop over the tasks here and see if there are any we can start - MOVE THIS LOOP OUT TO THE GRAPH CLASS AND LET THE GRAPH CLASS HANDLE WHEN TO ADD THE ACTIONS TO THE THREAD POOL. THAT WAY THE THREAD POOL ONLY NEEDS TO RUN FUNCTIONS AND RETURN FUTURES. THE GRAPH CLASS CAN THEN CHECK OUTPUTS ETC AND DETERMINE INPUTS, AND THEN QUEUE MORE UP WHEN WE HAVE RESPONSES BACK. 
//         for (auto task : m_tasks)
//         {
//            if (m_validate_action(task))
//            {
//               action = task;
//               break;
//            }
//         }
//         // Remove from the queue so that no other threads start the same task
//         const auto action_to_erase_iterator = std::find(m_tasks.begin(), m_tasks.end(), action);
//         if (action_to_erase_iterator != m_tasks.end())
//         {
//            m_tasks.erase(action_to_erase_iterator);
//         }
//      }
//      if (m_stop)
//      {
//         return;
//      }
//      if (action && m_validate_action(action))
//      {
//         std::cout << "Executing action [" << action->name() << "] on thread Id [" << std::this_thread::get_id() << "]" << std::endl;
//         // Run action
//         action->run();
//         // Now propagate outputs, so check the action connections - only want inputs 
//         // so we only care about the connections where this is a dst action
//         m_post_action_run(action);
//      }
//   }
//}
