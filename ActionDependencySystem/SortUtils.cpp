#include "SortUtils.h"
#include "LocalActionGraph.h"
#include <iterator>

template<class OutputIterator>
void SortUtils::topological_sort(const ActionDagT& dag, OutputIterator output_iterator)
{
   // Mark all the vertices as not visited
   std::map<std::shared_ptr<IAction>, bool> visited;

   // Call the recursive helper function to store Topological
   // Sort starting from all vertices one by one
   for (auto action : dag)
   {
      if (visited[action.first] == false)
      {
         SortUtils::topological_sort_connected_actions(dag, action.first, visited, output_iterator);
      }
   }
}

template<class OutputIterator>
void SortUtils::topological_sort_connected_actions(const ActionDagT& dag,
                                                   std::shared_ptr<IAction> first_action,
                                                   std::map<std::shared_ptr<IAction>, bool>& visited, 
                                                   OutputIterator output_iterator)
{
   // Mark the current node as visited.
   visited[first_action] = true;
   
   // Get connected action
   std::vector<std::shared_ptr<IAction>> connected_actions;
   for (auto action_connection : dag.at(first_action))
   {
      std::shared_ptr<IAction> dst_action = action_connection.dst_action();
      if (dst_action != first_action)
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
         topological_sort_connected_actions(dag, connected_action, visited, output_iterator);
      }
   }
   // Push current vertex to stack which stores result
   *output_iterator = first_action;
}
