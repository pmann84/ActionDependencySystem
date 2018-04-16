/* 
 * This class acts as the base for actions/graphs. In this frameworks, they are actually
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
 * Need to consider how exactly to store connections between multiple inputs and outputs, not traditional dag structure?
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
 * 
 * Graph
 * Should do a topological sort to get the order in which to execute the actions
 * For a local graph this doesnt matter too much as its all synchronous
 * For parallel graphs we need to determine which actions can be executed in parallel
 * 
 * TODO: Implement serialisation to text file
 *    This requires we have the serialise an action so that it has the * type, * name, * list of inputs, * list of outputs
 * TODO: Implement command line interface to execute serialised graphs
 * TODO: Add parallel graph execution
 * TODO: Add action registration system
 * TODO: Add graph ui
 * TODO: Test with more actions and more complicated graphs
 * TODO: Improve interface to the graph? so its more fluent 
 * TODO: Implement ForEach action
 * TODO: Add checks in add_connection (? maybe?) to check for loops in the graph!
 * TODO: Need to add/test functionality to be able to add inputs and outputs to graphs
 * TODO: Test nested graphs
 */

#include "LocalActionGraph.h"
#include "Actions/CopyFileAction.h"
#include "Actions/RunPowerShellScriptAction.h"

int main()
{
   const std::string in = "C:\\Users\\peterm\\powershell\\actionTest.ps1";
   const std::string out = "C:\\Users\\peterm\\powershell\\actionScriptToRun.ps1";
   std::shared_ptr<IAction> action = std::make_shared<CopyFileAction>("CopyFileAction_1", in, out);

   std::shared_ptr<IAction> runScriptAction = std::make_shared<RunPowershellScriptAction>();
   runScriptAction->name("RunPowershellScriptAction_1");

   LocalActionGraph graph;
   graph.name("LocalActionGraph_1");
   graph.add_action(action);
   graph.add_action(runScriptAction);

   graph.add_connection(action, 0, runScriptAction, 0);
   graph.run();
   return 0;
}
