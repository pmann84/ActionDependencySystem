#include "ParallelActionGraph.h"

#include "SortUtils.h"

#include <thread>
#include <stack>
#include <iostream>

ParallelActionGraph::ParallelActionGraph()
{
   unsigned long const hardware_threads = std::thread::hardware_concurrency();
   m_max_threads = hardware_threads != 0 ? hardware_threads : 2;
}

void ParallelActionGraph::run()
{
   std::cout << "Executing graph [" << name() << "]" << std::endl;
   std::stack<std::shared_ptr<IAction>> sorted_stack;
   SortUtils::topological_sort(m_dag, std::back_inserter(sorted_stack));
   // TODO - Keep a record of a list of ptrs to actions and associated threads -  so we can keep track of these
   // std::map<std::shared_ptr<IAction>, std::thread>
   while(!sorted_stack.empty())
   {
      std::shared_ptr<IAction> action = sorted_stack.top();
      std::cout << "Executing action [" << action->name() << "]" << std::endl;
      
      // Check that the action is not part of the action-thread cache i.e. its still running

      // Give the action to the thread and then move on only if the action has no dependent inputs or all the input actions have finished

      // Check the action connections - only want inputs so we only care about the connections
      // where this is a dst action
      for (auto connection : m_dag[action])
      {
         if (connection.is_dst(action))
         {
            // Get the src action and the appropriate output
            std::shared_ptr<IAction> src = connection.src_action();
            // Should check here that the action output is DEFINITELY initialised! We should handle optional outputs here too!
            std::any output_value = src->get_output(connection.src_output_idx())->get();
            action->set_input(connection.dst_input_idx(), output_value);
         }
      }

      //// Loop the inputs and check they are all initialised
      //// TODO: Move this onto the action itself????
      //if (!action->validate_inputs())
      //{
      //   throw InvalidActionInputsException(action->name(), action->invalid_inputs());
      //}
      //// Then run the action synchronously
      //// TODO: Handle errors that come out of running actions
      //action->run();
      //std::cout << "Action [" << action->name() << "] executed successfully!" << std::endl;
      // Pop it off the stack
      sorted_stack.pop();
   }
   std::cout << "Graph [" << name() << "] executed successfully!" << std::endl;
}
