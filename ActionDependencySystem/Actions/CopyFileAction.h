#ifndef __COPYFILE_ACTION_H__
#define __COPYFILE_ACTION_H__

#include "../BaseAction.h"

#include <string>

class CopyFileAction : public BaseAction
{
public:
   CopyFileAction();
   CopyFileAction(std::string in, std::string out);
   ~CopyFileAction() final = default;

   void run() override;
};

#endif // __COPYFILE_ACTION_H__