#include "BaseActionGraph.h"
#include <algorithm>
#include <sstream>
#include "ActionExceptions.h"

BaseActionGraph::BaseActionGraph()
{
}

void BaseActionGraph::add_action(std::shared_ptr<IAction> action)
{
   // Validate action based on name
   auto duplicate_actions = std::find_if(m_dag.begin(), 
                                        m_dag.end(), 
                                        [action](std::pair<std::shared_ptr<IAction>, std::vector<ActionConnection>> dag_pair)
                                        {
                                           return dag_pair.first->name() == action->name();
                                        });
   if (duplicate_actions != m_dag.end())
   {
      throw DuplicateActionException(action->name());
   }
   // Insert the action
   m_dag[action] = std::vector<ActionConnection>();
   m_degree_map[action] = std::make_pair(0, 0);
}

void BaseActionGraph::add_connection(std::shared_ptr<IAction> src, int output_idx, std::shared_ptr<IAction> dst, int input_idx)
{
   // Check that both src and dst actions exist in the dag
   const bool src_action_exists = m_dag.find(src) == m_dag.end();
   const bool dst_action_exists = m_dag.find(dst) == m_dag.end();
   if (src_action_exists || dst_action_exists)
   {
      std::vector<std::string> missing_actions;
      if (!src_action_exists)
      {
         missing_actions.push_back(src->name());
      }
      if (!dst_action_exists)
      {
         missing_actions.push_back(dst->name());
      }
      throw ActionDoesNotExistException(missing_actions);
   }
   // Check that src and dst actions are different
   if (src == dst)
   {
      throw SelfConnectionActionException(src->name());
   }
   // Create the connection object
   ActionConnection connection(src, output_idx, dst, input_idx);
   // m_dag is basically an adjacency list so we add the connection (basically destination action to the src node)
   m_dag.at(src).push_back(connection);
   m_dag.at(dst).push_back(connection);
   m_degree_map.at(src).second++;
   m_degree_map.at(dst).first++;
}
