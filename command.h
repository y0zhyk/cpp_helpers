//
//  command.h
//
//  Created by Taras Lushney on 9/3/15.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.
//

#ifndef COMMAND_H_
#define COMMAND_H_

namespace patterns {

class Command {
 public:
    virtual void Execute() = 0;
    virtual ~Command() = default;
};

}  // namespace patterns

#endif  // COMMAND_H_