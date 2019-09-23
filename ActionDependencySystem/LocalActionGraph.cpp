#include "LocalActionGraph.h"

#include <iostream>
#include <iterator>
#include <sstream>

#include "ActionExceptions.h"
#include "SortUtils.h"

void LocalActionGraph::run()
{
   std::cout << "Executing graph [" << name() << "]" << std::endl;
   std::vector<std::shared_ptr<IAction>> sorted_stack;
   SortUtils::topological_sort(m_dag, std::back_inserter(sorted_stack));

   // Loop over the stack 
   while (!sorted_stack.empty())
   {
      std::shared_ptr<IAction> action = sorted_stack.back();
      std::cout << "Executing action [" << action->name() << "]" << std::endl;
      // Check the action connections - only want inputs so we only care about the connections
      // where this is a dst action
      for (auto connection : m_dag[action])
      {
         if (connection.is_dst(action))
         {
            // Get the src action and the appropriate output
            std::shared_ptr<IAction> src = connection.src_action();
            std::any output_value = src->get_output(connection.src_output_idx())->get();
            action->set_input(connection.dst_input_idx(), output_value);
         }
      }
      // Loop the inputs and check they are all initialised
      // TODO: Move this onto the action itself????
      if (!action->validate_inputs())
      {
         throw InvalidActionInputsException(action->name(), action->invalid_inputs());
      }
      // Then run the action synchronously
      // TODO: Handle errors that come out of running actions
      action->run();
      std::cout << "Action [" << action->name() << "] executed successfully!" << std::endl;
      // Pop it off the stack
      sorted_stack.erase(sorted_stack.end()-1);
   }
   std::cout << "Graph [" << name() << "] executed successfully!" << std::endl;
}
