#ifndef __PARALLEL_ACTION_GRAPH__
#define __PARALLEL_ACTION_GRAPH__

#include <mutex>

#include "ActionDependencySystemCore.h"
#include "BaseActionGraph.h"

class ACTION_DEPENDENCY_SYSTEM_API ParallelActionGraph : public BaseActionGraph
{
public:
   ParallelActionGraph();
   ~ParallelActionGraph() = default;

   void run() override;

private:
   std::mutex m_dag_mutex;
};

#endif // __PARALLEL_ACTION_GRAPH__