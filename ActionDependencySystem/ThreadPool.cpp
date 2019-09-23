#include "ThreadPool.h"

#include <iostream>

ThreadPool::ThreadPool(const unsigned int num_threads) : m_stop(false)
{
   // Check the number of threads we can use
   const unsigned long hardware_threads = std::thread::hardware_concurrency();
   const unsigned int max_threads = num_threads == 0 ? (hardware_threads != 0 ? hardware_threads : 2) : num_threads;
   std::cout << "Starting Thread Pool..." << std::endl;
   std::cout << "Max threads available: " << max_threads << std::endl;
   for (unsigned int i = 0; i < max_threads; ++i)
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
   std::lock_guard<std::mutex> lock(m_queue_mutex);
   auto packaged_task = std::make_shared<std::packaged_task<void()>>(std::packaged_task<void()>(task));
   std::future<void> result = packaged_task->get_future();
   m_tasks.emplace([packaged_task]() { (*packaged_task)(); });
   m_condition.notify_all();
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
      std::function<void()> task;
      {
         // Grab the next job off the queue
         std::unique_lock<std::mutex> lock(m_queue_mutex);
         m_condition.wait(lock, [&]() { return m_stop || !m_tasks.empty(); });
         if (m_stop && m_tasks.empty())
         {
            return;
         }
         task = std::move(m_tasks.front());
         m_tasks.pop();
      }
      // Actually run it
      task();
   }
}
