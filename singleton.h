#ifndef SINGLETON_H_
#define SINGLETON_H_
 
template <class T>
class Singleton {
 public:
    template <typename... Args>
    static T& instance(Args&&... args) {
        call_once(once_flag(), [&, args...]() {
            instance_.reset(new T(std::forward<Args>(args)...));
        });
      return *instance_.get();
    }
 
 protected:
    explicit Singleton<T>() = default;
    ~Singleton<T>() = default;
 
 private:
    static std::once_flag& once_flag() {
        static std::once_flag once;
        return once;
    }

    static std::unique_ptr<T> instance_;
};
 
template<class T> std::unique_ptr<T> Singleton<T>::instance_ = nullptr;
 
#endif
