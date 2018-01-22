#include "LocalActionGraph.h"

#include <iostream>
#include <sstream>

void LocalActionGraph::run()
{
   std::cout << "Executing graph [" << name() << "]" << std::endl;
   std::stack<std::shared_ptr<IAction>> sortedStack = topological_sort();
   // Loop over the stack 
   while (sortedStack.empty() == false)
   {
      std::shared_ptr<IAction> action = sortedStack.top();
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
         std::stringstream excMsgStream;
         excMsgStream << "Cannot execute graph! Some or all inputs for action [" << action->name() << "] are invalid!";
         throw std::exception(excMsgStream.str().c_str());
      }
      // Then run the action synchronously
      // TODO: Handle errors that come out of running actions
      action->run();
      std::cout << "Action [" << action->name() << "] executed successfully!" << std::endl;
      // Pop it off the stack
      sortedStack.pop();
   }
   std::cout << "Graph [" << name() << "] executed successfully!" << std::endl;
}

void LocalActionGraph::topological_sort_internal(std::shared_ptr<IAction> action, 
                                                 std::map<std::shared_ptr<IAction>, bool>& visited, 
                                                 std::stack<std::shared_ptr<IAction>>& stack)
{
   // Mark the current node as visited.
   visited[action] = true;
   
   // Get connected action
   std::vector<std::shared_ptr<IAction>> connected_actions;
   for(auto action_connection : m_dag[action])
   {
      std::shared_ptr<IAction> dst_action = action_connection.dst_action();
      if (dst_action != action)
      {
         connected_actions.push_back(dst_action);
      }
   }

   // Recur for all connected actions i.e. iterate over destination actions in associated ActionConnections
   std::vector<std::shared_ptr<IAction>>::iterator it;
   for (const auto connected_action : connected_actions)
   {
      if (!visited[connected_action])
      {
         topological_sort_internal(connected_action, visited, stack);
      }
   }
   // Push current vertex to stack which stores result
   stack.push(action);
}

std::stack<std::shared_ptr<IAction>> LocalActionGraph::topological_sort()
{
   std::stack<std::shared_ptr<IAction>> stack;
   
   // Mark all the vertices as not visited
   std::map<std::shared_ptr<IAction>, bool> visited;
   
   // Call the recursive helper function to store Topological
   // Sort starting from all vertices one by one
   for (auto action : m_dag)
   {
      if (visited[action.first] == false)
      {
         topological_sort_internal(action.first, visited, stack);
      }
   }
   return stack;
}