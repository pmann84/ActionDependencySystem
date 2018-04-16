#ifndef __PARALLEL_ACTION_GRAPH__
#define __PARALLEL_ACTION_GRAPH__

#include "BaseActionGraph.h"

class ParallelActionGraph : public BaseActionGraph
{
public:
   ParallelActionGraph() = default;
   ~ParallelActionGraph() = default;

   void run() override;
};

#endif // __PARALLEL_ACTION_GRAPH__