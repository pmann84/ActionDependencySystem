#ifndef __SORT_UTILS_H__
#define __SORT_UTILS_H__

#include "BaseActionGraph.h"

#include "IAction.h"
#include <map>

namespace SortUtils
{
   template <class OutputIterator>
   void topological_sort_connected_actions(const ActionDagT& dag,
                                           std::shared_ptr<IAction> action,
                                           std::map<std::shared_ptr<IAction>, bool>& visited,
                                           OutputIterator output_iterator)
   {
      // Mark the current node as visited.
      visited[action] = true;

      // Get connected action
      std::vector<std::shared_ptr<IAction>> connected_actions;
      for (auto action_connection : dag.at(action))
      {
         std::shared_ptr<IAction> dst_action = action_connection.dst_action();
         if (dst_action != action)
         {
            connected_actions.push_back(dst_action);
         }
      }

      // Recur for all connected actions i.e. iterate over destination actions in associated ActionConnections
      for (const auto connected_action : connected_actions)
      {
         if (!visited[connected_action])
         {
            topological_sort_connected_actions(dag, connected_action, visited, output_iterator);
         }
      }
      // Push current vertex to iterator which stores result
      *output_iterator = action;
   }

   template <class OutputIterator>
   void topological_sort(const ActionDagT& dag, OutputIterator output_iterator)
   {
      // Mark all the vertices as not visited
      std::map<std::shared_ptr<IAction>, bool> visited;

      // Call the recursive helper function to store Topological
      // Sort starting from all vertices one by one
      for (auto action : dag)
      {
         if (!visited[action.first])
         {
            SortUtils::topological_sort_connected_actions(dag, action.first, visited, output_iterator);
         }
      }
   }
}

#endif // __SORT_UTILS_H__