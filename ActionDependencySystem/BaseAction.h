#ifndef __BASE_ACTION_H__
#define __BASE_ACTION_H__

#include "IAction.h"

class BaseAction : public IAction
{
public:
   BaseAction();
   virtual ~BaseAction() = default;

   std::string name() const override { return m_name; };
   void name(std::string) override;

   void add_input(std::shared_ptr<ActionInput>) override;
   void add_output(std::shared_ptr<ActionInput>) override;
   
   void set_input(int i, std::any value) override;
   std::shared_ptr<ActionInput> get_output(const int i) override;

   bool validate_inputs() override;
   std::vector<std::string> invalid_inputs() override;

   virtual void run() = 0;

protected:
   std::string m_name;
   ActionInputListT m_inputs;
   ActionInputListT m_outputs;
};

#endif // __IACTION_H__