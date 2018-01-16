#ifndef __ACTION_INPUT_H__
#define __ACTION_INPUT_H__

#include "IActionInput.h"

class ActionInput : public IActionInput
{
public:
   ActionInput(const std::string name) 
      : m_name(name)
      , m_is_initialised(false)
   {
   }
   ~ActionInput() = default;

   std::string name() const override
   {
      return m_name;
   }

   bool is_initialised() const override
   {
      return m_is_initialised;
   }

   void set(std::any value) override
   {
      m_is_initialised = true;
      m_value = value;
   }

   std::any get() const override
   {
      return m_value;
   }

private:
   std::string m_name;
   std::any m_value;
   bool m_is_initialised;
};

#endif // __IACTION_INPUT_H__
