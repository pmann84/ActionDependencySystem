#ifndef __PARALLEL_ACTION_GRAPH__
#define __PARALLEL_ACTION_GRAPH__

#include "BaseActionGraph.h"

class ParallelActionGraph : public BaseActionGraph
{
public:
   ParallelActionGraph();
   ~ParallelActionGraph() = default;

   void run() override;

private:
   unsigned int m_max_threads;
};

#endif // __PARALLEL_ACTION_GRAPH__