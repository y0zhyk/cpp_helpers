
#include <memory>

class StageResult {};

class Stage : public StageResult {
 public:
    virtual std::unique_ptr<StageResult> Start() = 0;
    virtual std::string name() const = 0;
};

class StageBase : public Stage {
 private:
};
