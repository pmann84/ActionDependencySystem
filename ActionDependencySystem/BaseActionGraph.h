#ifndef __ACTION_GRAPH_H__
#define __ACTION_GRAPH_H__

#include <map>

#include "BaseAction.h"
#include "ActionConnection.h"

using ActionDagT = std::map<std::shared_ptr<IAction>, std::vector<ActionConnection>>;
// Map of { action : <indegree, outdegree> }
using DagDegreeMapT = std::map<std::shared_ptr<IAction>, std::pair<unsigned int, unsigned int>>;

class BaseActionGraph : public BaseAction
{
public:
   BaseActionGraph();
   ~BaseActionGraph() override = default;

   virtual void run() = 0;

   void add_action(std::shared_ptr<IAction>);
   void add_connection(std::shared_ptr<IAction>, int, std::shared_ptr<IAction>, int);

   int size() { return m_dag.size(); }

protected:
   ActionDagT m_dag;
   DagDegreeMapT m_degree_map;
};

#endif // __ACTION_GRAPH_H__
