#ifndef __ACTION_GRAPH_H__
#define __ACTION_GRAPH_H__

#include <unordered_map>

#include "BaseAction.h"

using ActionDagT = std::unordered_map<std::unique_ptr<IAction>, ActionListT>;

class BaseActionGraph : public BaseAction
{
public:
   BaseActionGraph();
   ~BaseActionGraph() override = default;

   void run() override;

   void add_action(IAction&);
   void add_connection(IAction&, int, IAction&, int);

private:
   ActionDagT m_dag;
};

#endif // __ACTION_GRAPH_H__
