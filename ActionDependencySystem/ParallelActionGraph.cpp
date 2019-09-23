#include "ParallelActionGraph.h"

#include <iostream>

#include "SortUtils.h"
#include "ThreadPool.h"

ParallelActionGraph::ParallelActionGraph()
{
}

void ParallelActionGraph::run()
{
   std::cout << "Executing graph [" << name() << "]" << std::endl;
   // Sort the actions
   std::vector<std::shared_ptr<IAction>> sorted_actions;
   SortUtils::topological_sort(m_dag, std::back_inserter(sorted_actions));

   // Setup functions for convenience
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

   // Next start off the thread pool
   std::vector<std::future<void>> results;
   ThreadPool pool;

   std::map<std::shared_ptr<IAction>, std::future<void>> submitted_actions;
   // Wait while we still have actions to process
   while(!sorted_actions.empty())
   {
      // Loop over the tasks here and see if there are any we can start - MOVE THIS LOOP OUT TO THE GRAPH CLASS AND LET THE GRAPH CLASS HANDLE WHEN TO ADD THE ACTIONS TO THE THREAD POOL. THAT WAY THE THREAD POOL ONLY NEEDS TO RUN FUNCTIONS AND RETURN FUTURES. THE GRAPH CLASS CAN THEN CHECK OUTPUTS ETC AND DETERMINE INPUTS, AND THEN QUEUE MORE UP WHEN WE HAVE RESPONSES BACK. 
      for (auto action : sorted_actions)
      {
         if (action_validate_function(action))
         {
            submitted_actions[action] = pool.add_job([action]() { action->run(); });
         }
      }
      // Remove from the queue so that no other threads start the same task
      for (auto& action_to_erase : submitted_actions)
      {
         const auto action_to_erase_iterator = std::find(sorted_actions.begin(), sorted_actions.end(), action_to_erase.first);
         if (action_to_erase_iterator != sorted_actions.end())
         {
            sorted_actions.erase(action_to_erase_iterator);
         }
      }
      std::vector<std::shared_ptr<IAction>> finished_actions;
      for (auto& submitted_action : submitted_actions)
      {
         auto& action_result = submitted_action.second;
         if (action_result.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
         {
            auto action = submitted_action.first;
            // Wait for the actions to finish then run the post action shizz
            if (action && action_validate_function(action))
            {
               // Now propagate outputs, so check the action connections - only want inputs 
               // so we only care about the connections where this is a dst action
               post_run_action(action);
            }
            // Erase this from the submitted actions as its finished
            finished_actions.push_back(action);
         }
      }
      for (auto action : finished_actions)
      {
         auto action_erase_it = submitted_actions.find(action);
         if (action_erase_it != submitted_actions.end())
         {
            submitted_actions.erase(action_erase_it);
         }
      }
   }
   // Wait for any final actions to finish
   for (auto& submitted_action : submitted_actions)
   {
      auto& action_result = submitted_action.second;
      action_result.get();
   }
   // Graph executed!
   std::cout << "Graph [" << name() << "] finished executing!" << std::endl;
}
