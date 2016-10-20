//  Created by Taras Lushney on 9/3/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef COMMAND_H_
#define COMMAND_H_

namespace patterns {

class Command {
 public:
  virtual ~Command() noexcept = default;
  // Defines the method to be called when the command is invoked.
  virtual void Execute() = 0;
};

class UndoableCommand : public Command {
 public:
  virtual void Undo() = 0;
};

}  // namespace patterns

#endif  // COMMAND_H_