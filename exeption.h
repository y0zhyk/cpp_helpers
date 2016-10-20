//  Created by Taras Lushney on 8/12/15.
//  Copyright (c) 2015 Taras Lushney. All rights reserved.

#ifndef EXEPTION_H_
#define EXEPTION_H_

template <typename Exeption, typename Expression, typename... Args>
void ThrowIf(Expression&& expression, Args&&... args) {
  if (expression) throw Exeption(std::forward<Args>(args)...);
}

template <typename Exeption, typename Expression, typename... Args>
void ThrowIfFailed(Expression&& expression, Args&&... args) {
  ThrowIf<Exeption>(!expression, args...);
}

#endif  // EXEPTION_H_