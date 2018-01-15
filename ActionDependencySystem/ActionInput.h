#ifndef __ACTION_INPUT_H__
#define __ACTION_INPUT_H__

#include <string>
#include <any>

class IActionInput
{
public:
   virtual ~IActionInput() = default;

   virtual std::string name() const = 0;
   virtual bool is_initialised() const = 0;
};

class ActionInput : public IActionInput
{
public:
   ActionInput(const std::string name) : m_name(name), m_is_initialised(false)
   {
      
   }
   ~ActionInput() = default;

   std::string name() const override
   {
      return m_name;
   }

   template<typename Type>
   void set(Type value)
   {
      m_is_initialised = true;
      m_value = std::make_any<Type>(value);
   }

   template<typename Type>
   Type get() const
   {
      return std::any_cast<Type>(m_value);
   }

   bool is_initialised() const override
   {
      return m_is_initialised;
   }

private:
   std::string m_name;
   std::any m_value;
   bool m_is_initialised;
};

#endif // __IACTION_INPUT_H__
