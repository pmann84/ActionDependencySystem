#ifndef __IACTION_H__
#define __IACTION_H__

#include "ActionInput.h"

#include <string>
#include <vector>
#include <memory>

class ActionConnection;

class IAction
{
public:
   virtual ~IAction() = default;

   virtual std::string name() const = 0;
   virtual void name(std::string) = 0;
   virtual void add_input(std::shared_ptr<ActionInput>) = 0;
   virtual void add_output(std::shared_ptr<ActionInput>) = 0;

   virtual void set_input(int i, std::any value) = 0;
   virtual std::shared_ptr<ActionInput> get_output(const int i) = 0;

   virtual bool validate_inputs() = 0;
   virtual bool validate_optional_inputs(std::vector<ActionConnection>) = 0;
   virtual std::vector<std::string> invalid_inputs() = 0;

   virtual std::vector<std::shared_ptr<IAction>> get_subsequent_actions(std::vector<ActionConnection> connections) = 0;
   virtual std::vector<std::shared_ptr<IAction>> get_prior_actions(std::vector<ActionConnection> connections) = 0;

   virtual void run() = 0;
};

using ActionListT = std::vector<std::shared_ptr<IAction>>;

#endif // __IACTION_H__