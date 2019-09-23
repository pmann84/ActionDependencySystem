#ifndef __LOCAL_ACTION_GRAPH__
#define __LOCAL_ACTION_GRAPH__

#include "ActionDependencySystemCore.h"
#include "BaseActionGraph.h"

class ACTION_DEPENDENCY_SYSTEM_API LocalActionGraph : public BaseActionGraph
{
public:
   LocalActionGraph() = default;
   ~LocalActionGraph() = default;

   void run() override;
};

#endif // __LOCAL_ACTION_GRAPH__
