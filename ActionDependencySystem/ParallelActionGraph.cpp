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
   ThreadPool pool(post_run_action, action_validate_function, 2);
   pool.add_jobs(sorted_actions);
   // Wait for all the jobs to finish!
   pool.wait();
   // Graph executed!
   std::cout << "Graph [" << name() << "] finished executing!" << std::endl;
}
