#include "ActionGraph.h"

BaseActionGraph::BaseActionGraph()
{
}

void BaseActionGraph::run()
{
}

void BaseActionGraph::add_action(IAction& action)
{
}

void BaseActionGraph::add_connection(IAction& src, int output_idx, IAction& dst, int intput_idx)
{
}
