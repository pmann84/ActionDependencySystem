#ifndef __IACTION_H__
#define __IACTION_H__

#include "IActionInput.h"

class IAction
{
public:
   virtual ~IAction() = default;

   virtual void add_input(std::unique_ptr<IActionInput>) = 0;
   virtual void add_output(std::unique_ptr<IActionInput>) = 0;

   virtual void run() = 0;
};

using ActionListT = std::vector<std::unique_ptr<IAction>>;

#endif // __IACTION_H__