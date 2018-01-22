#include "BaseActionGraph.h"

BaseActionGraph::BaseActionGraph()
{
}

void BaseActionGraph::add_action(std::shared_ptr<IAction> action)
{
   // TODO: ** Check action doesnt exist in the dag - based on action name **
   m_dag[action] = std::vector<ActionConnection>();
   m_degree_map[action] = std::make_pair(0, 0);
}

void BaseActionGraph::add_connection(std::shared_ptr<IAction> src, int output_idx, std::shared_ptr<IAction> dst, int input_idx)
{
   // TODO: ** Check src and dst action both exist in the dag **
   ActionConnection connection(src, output_idx, dst, input_idx);
   // m_dag is basically an adjacency list so we add the connection (basically destination action to the src node)
   m_dag.at(src).push_back(connection);
   m_dag.at(dst).push_back(connection);
   m_degree_map.at(src).second++;
   m_degree_map.at(dst).first++;
}
