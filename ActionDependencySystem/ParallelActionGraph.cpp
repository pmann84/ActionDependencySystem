#include "ParallelActionGraph.h"

#include "SortUtils.h"

#include <iostream>
#include "ThreadPool.h"

ParallelActionGraph::ParallelActionGraph()
{
}

void ParallelActionGraph::run()
{
   std::cout << "Executing graph [" << name() << "]" << std::endl;
   std::vector<std::shared_ptr<IAction>> sorted_actions;
   SortUtils::topological_sort(m_dag, std::back_inserter(sorted_actions));

   auto post_run_action = [this](std::shared_ptr<IAction> action)
      {
         std::lock_guard<std::mutex> lock(m_dag_mutex);
         this->propagate_outputs(action);
      };

   auto action_validate_function = [this](std::shared_ptr<IAction> action) -> bool
      {
         std::lock_guard<std::mutex> lock(m_dag_mutex);
         return action->validate_inputs() && action->validate_optional_inputs(m_dag[action]);
      };

   // Start thread pool
   std::vector<std::future<void>> results;
   ThreadPool pool(2);
   results.push_back(pool.add_job([]() { std::cout << "Sleeping for 5 seconds..." << std::endl; std::this_thread::sleep_for(std::chrono::seconds(5)); std::cout << "Completed Sleeping for 5 seconds!" << std::endl; }));
   results.push_back(pool.add_job([]() { std::cout << "Sleeping for 4 seconds..." << std::endl; std::this_thread::sleep_for(std::chrono::seconds(4)); std::cout << "Completed Sleeping for 4 seconds!" << std::endl; }));
   results.push_back(pool.add_job([]() { std::cout << "Sleeping for 2 seconds..." << std::endl; std::this_thread::sleep_for(std::chrono::seconds(2)); std::cout << "Completed Sleeping for 2 seconds!" << std::endl; }));
   results.push_back(pool.add_job([]() { std::cout << "Sleeping for 1 seconds..." << std::endl; std::this_thread::sleep_for(std::chrono::seconds(1)); std::cout << "Completed Sleeping for 1 seconds!" << std::endl; }));
   
   // Wait on the threads
   for (auto it = results.rbegin(); it != results.rend(); ++it)
   {
      it->get();
   }
   //ThreadPool pool(post_run_action, action_validate_function, 2);
   //pool.add_jobs(sorted_actions);
   //// Wait for all the jobs to finish!
   //pool.wait();

   // Graph executed!
   std::cout << "Graph [" << name() << "] finished executing!" << std::endl;
}
