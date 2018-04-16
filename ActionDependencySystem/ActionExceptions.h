#ifndef __ACTION_EXCEPTIONS_H__
#define __ACTION_EXCEPTIONS_H__

#include <sstream>
#include <exception>

class DuplicateActionException : public std::runtime_error
{
public:
   explicit DuplicateActionException(const std::string name) : std::runtime_error("Cannot add action with name " + name + ". An action with this name already exists!") {}
};

class SelfConnectionActionException : public std::runtime_error
{
public:
   explicit SelfConnectionActionException(std::string action) : std::runtime_error("Cannot connect [" + action + "] action to itself.") {}
};

class InvalidActionInputsException : public std::exception
{
public:
   explicit InvalidActionInputsException(std::string action_name, 
                                         std::vector<std::string> invalid_inputs) 
                                       : m_action_name(action_name)
                                       , m_invalid_inputs(invalid_inputs)
   {}

private:
   virtual const char* what() const throw()
   {
      std::stringstream excMsgStream;
      excMsgStream << "The following inputs are invalid for action [" << m_action_name << "]: ";
      for (const auto input : m_invalid_inputs)
      {
         excMsgStream << input;
      }
      return excMsgStream.str().c_str();
   }

   std::string m_action_name;
   std::vector<std::string> m_invalid_inputs;
};

class ActionDoesNotExistException : public std::exception
{
public:
   explicit ActionDoesNotExistException(std::vector<std::string> actions)
      : m_actions(actions)
   {}

private:
   virtual const char* what() const throw()
   {
      std::stringstream excMsgStream;
      excMsgStream << "The following action(s) do not exist! [";
      for (const auto input : m_actions)
      {
         excMsgStream << input << ",";
      }
      excMsgStream << "]";
      return excMsgStream.str().c_str();
   }

   std::vector<std::string> m_actions;
};

#endif //__ACTION_EXCEPTIONS_H__