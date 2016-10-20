//  Created by Taras Lushney on 3/21/14.
//  Copyright (c) 2014 Taras Lushney. All rights reserved.

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <vector>

template <typename Events>
class Listener;

template <typename Events>
class Notifier {
    typedef Listener<Events> EventsListener;
    std::vector<EventsListener*> listeners_;
    friend EventsNotifier;

    bool Attach(EventsListener* listener) {
        if (std::find(listeners_.begin(), listeners_.end(), listener) != listeners_.end())
            return false;
        listeners_.push_back(listener);
        return true;
    }

    bool Detach(EventsListener* listener) {
        auto found_listener = std::find(listeners_.begin(), listeners_.end(), listener);
        if (found_listener == listeners_.end())
            return false;
        listeners_.erase(found_listener);
        return true;
    }

 protected:
    template<typename Function, typename... Arguments>
    void Notify(Function func, Arguments... params) const {
        for (auto listener: listeners_)
            std::mem_fun(func)(listener, params...);
    }
};

template <typename Events>
class Listener : private Events {
 protected:
    void AttachTo(EventsNotifier* notifier) {
        if (notifier->Attach(this))
            notifiers_.push_back(notifier);
    }

    void DetachFrom(EventsNotifier* notifier) {
        auto found_notifier = std::find(notifiers_.begin(), notifiers_.end(), notifier);
        if (found_notifier != notifiers_.end()) {
            notifiers_.erase(found_notifier);
            notifier->Detach(this);
        }
    }

    virtual ~Listener() {
        for (auto notifier: notifiers_)
            notifier->Detach(this);
    }
 private:
    typedef Notifier<Events> EventsNotifier;
    std::vector<EventsNotifier*> notifiers_;
};

#endif  // OBSERVER_H_
