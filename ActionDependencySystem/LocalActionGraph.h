#ifndef __LOCAL_ACTION_GRAPH__
#define __LOCAL_ACTION_GRAPH__

#include "BaseActionGraph.h"
#include <stack>

class LocalActionGraph : public BaseActionGraph
{
public:
   LocalActionGraph() = default;
   ~LocalActionGraph() = default;

   void run() override;

   void topological_sort_internal(std::shared_ptr<IAction>, std::map<std::shared_ptr<IAction>, bool>& visited, std::stack<std::shared_ptr<IAction>>& stack);
   std::stack<std::shared_ptr<IAction>> topological_sort();
};

#endif // __LOCAL_ACTION_GRAPH__
