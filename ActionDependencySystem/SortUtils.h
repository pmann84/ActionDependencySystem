#ifndef __SORT_UTILS_H__
#define __SORT_UTILS_H__

#include "IAction.h"
#include <map>
#include "LocalActionGraph.h"

namespace SortUtils
{
   template <class OutputIterator>
   void topological_sort(const ActionDagT& dag, OutputIterator output_iterator);
   template <class OutputIterator>
   void topological_sort_connected_actions(const ActionDagT& dag,
                                           std::shared_ptr<IAction> action,
                                           std::map<std::shared_ptr<IAction>, bool>& visited, 
                                           OutputIterator output_iterator);
}

#endif // __SORT_UTILS_H__