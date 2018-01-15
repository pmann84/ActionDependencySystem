#ifndef __ACTION_GRAPH_H__
#define __ACTION_GRAPH_H__

#include <unordered_map>

#include "BaseAction.h"

class ActionGraph : public BaseAction
{
public:
   ActionGraph();
   ~ActionGraph() override = default;

   void run() override;

   void add_action(BaseAction&);
   void add_connection(BaseAction&, BaseAction&);

private:
   std::unordered_map<BaseAction, std::vector<BaseAction>> m_dag;
};

#endif // __ACTION_GRAPH_H__