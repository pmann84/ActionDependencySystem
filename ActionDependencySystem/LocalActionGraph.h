#ifndef __LOCAL_ACTION_GRAPH__
#define __LOCAL_ACTION_GRAPH__

#include "BaseActionGraph.h"

class LocalActionGraph : public BaseActionGraph
{
public:
   LocalActionGraph() = default;
   ~LocalActionGraph() = default;

   void run() override;
};

#endif // __LOCAL_ACTION_GRAPH__
