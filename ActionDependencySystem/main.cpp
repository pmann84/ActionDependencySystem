#include "Actions/CopyFileAction.h"

/* This class acts as the base for actions/graphs. In this frameworks, they are actually
* the same thing, so actions can contain actions. So an action must store all its inputs
* and outputs. These can be connected to other actions contained within it. Otherwise
* they can be used to run the action itself.
*
* The run method actually executes the actions primary purpose, but the execute method
* actually executes a the "graph". So this should iterate through the day and call the
* run method on each action
*
* Or have two types, action and actiongraph, both derived from a common type, then
* actions can be put inside graphs, and graphs can be put inside graphs.
*
* Then the graph has the execution functionality on it, and no "run" functionality.
*
* Maybe not!
*
* Need an action connection to store vertices?
*
* Ways to store DAG in code:
* Store as an adjency list - basically a map of actions to a list of actions that it is connected to (ahead of it)
*
* Iteration
* Parallel - Need to write a parallelised executor to sort these actions
* Series - just run a topological sort and iterate that list
* 
* Action Registration
* Should there be some system to register actions? Possibly not, could consider a Houdini style dso registration system?
* 
* Features
* Add timing stats i.e. how long it takes for action to "run", total graph exec time etc etc
* 
* Graph
* Actions are keyed off their names - can only have uniquely named actions/graphs so an unordered_map is fine
*/

int main()
{
   const std::string in = "C:\\Users\\peterm\\PDM\\Documents\\Bug Details.txt";
   const std::string out = "C:\\Users\\peterm\\PDM\\Documents\\Bug Details Copy.txt";
   CopyFileAction action(in, out);
   action.run();
   return 0;
}
