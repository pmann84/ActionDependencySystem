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
 * TODO: Add action registration system
 * TODO: Add graph ui
 * TODO: Test with more actions and more complicated graphs
 * TODO: Improve interface to the graph? so its more fluent 
 * TODO: Implement ForEach action
 * TODO: Add checks in add_connection (? maybe?) to check for loops in the graph!
 * TODO: Need to add/test functionality to be able to add inputs and outputs to graphs
 * TODO: Test nested graphs
 * TODO: Move the action input validation to the baseaction class. users implement the "action_run" (think of a better name) method but this should never be called directly, should only call "run"
 * TODO: Sort out waiting of the thread pool, so that it waits until all the tasks are finished
 * TODO: Make the deduction of number of threads more clever so that it can optimise how many threads it needs based on how many tasks can execute simultaneously might not need max hardware threads
 * TODO: Make the thread pool return futures when you add_jobs... this should use packaged tasks to get the future back - then we might be able to wait correctly
 */

#include "LocalActionGraph.h"
#include "ParallelActionGraph.h"
#include "Actions/CopyFileAction.h"
#include "Actions/RunPowerShellScriptAction.h"
#include "Actions/DelayAction.h"

void RunSerialisedTestGraphSimple()
{
   // Local graph code 
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
}

void RunParallelisedTestGraphSimple()
{
   // Parallel graph code 
   const std::string in = "C:\\Users\\peterm\\powershell\\actionTest.ps1";
   const std::string out = "C:\\Users\\peterm\\powershell\\actionScriptToRun.ps1";
   std::shared_ptr<IAction> action = std::make_shared<CopyFileAction>("CopyFileAction_1", in, out);

   std::shared_ptr<IAction> runScriptAction = std::make_shared<RunPowershellScriptAction>();
   runScriptAction->name("RunPowershellScriptAction_1");

   ParallelActionGraph graph;
   graph.name("ParallelActionGraph_1");
   graph.add_action(action);
   graph.add_action(runScriptAction);

   graph.add_connection(action, 0, runScriptAction, 0);
   graph.run();
}

void RunSerialisedTestGraphWithOptionalInputs()
{
   // Create actions
   std::shared_ptr<IAction> action1 = std::make_shared<DelayAction>("Action_1", 1);
   std::shared_ptr<IAction> action2 = std::make_shared<DelayAction>("Action_2", 5);
   std::shared_ptr<IAction> action3 = std::make_shared<DelayAction>("Action_3");
   std::shared_ptr<IAction> action4 = std::make_shared<DelayAction>("Action_4");
   std::shared_ptr<IAction> action5 = std::make_shared<DelayAction>("Action_5");
   std::shared_ptr<IAction> action6 = std::make_shared<DelayAction>("Action_6");
   std::vector<std::shared_ptr<IAction>> actions = { action1, action2, action3, action4, action5, action6 };

   // Initialise the graph
   LocalActionGraph graph;
   graph.name("LocalActionGraph_1");
   graph.add_actions(actions);

   // Setup the connections
   graph.add_connection(action2, 0, action5, 1);
   graph.add_connection(action2, 0, action6, 0);
   graph.add_connection(action1, 0, action3, 0);
   graph.add_connection(action3, 0, action4, 0);
   graph.add_connection(action4, 0, action5, 0);
   graph.add_connection(action6, 0, action4, 1);

   // GO! GO! GO!
   graph.run();
}

void RunParallelTestGraphWithOptionalInputs()
{
   // Create actions
   std::shared_ptr<IAction> action1 = std::make_shared<DelayAction>("Action_1", 1);
   std::shared_ptr<IAction> action2 = std::make_shared<DelayAction>("Action_2", 5);
   std::shared_ptr<IAction> action3 = std::make_shared<DelayAction>("Action_3");
   std::shared_ptr<IAction> action4 = std::make_shared<DelayAction>("Action_4");
   std::shared_ptr<IAction> action5 = std::make_shared<DelayAction>("Action_5");
   std::shared_ptr<IAction> action6 = std::make_shared<DelayAction>("Action_6");

   // Initialise the graph
   ParallelActionGraph graph;
   graph.name("ParallelActionGraph_1");
   graph.add_actions({ action1, action2, action3, action4, action5, action6 });

   // Setup the connections
   graph.add_connection(action2, 0, action5, 1);
   graph.add_connection(action2, 0, action6, 0);
   graph.add_connection(action1, 0, action3, 0);
   graph.add_connection(action3, 0, action4, 0);
   graph.add_connection(action4, 0, action5, 0);
   graph.add_connection(action6, 0, action4, 1);

   // GO! GO! GO!
   graph.run();
}

int main()
{
   //RunSerialisedTestGraphSimple();
   //RunParallelisedTestGraphSimple();
   //RunSerialisedTestGraphWithOptionalInputs();
   RunParallelTestGraphWithOptionalInputs();
   return 0;
}
