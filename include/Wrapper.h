#include "Subject.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <stdexcept>

template<typename T, class ...Args>
class Wrapper {
public:
    Wrapper(Subject* _subjRaw, T(Subject::* _func)(Args...), std::initializer_list<std::pair<const std::string, std::string>>&& _defArgs) : subjPtr(_subjRaw), funcPtr(_func), defArgs(_defArgs) {}
    T call(Args... args) {
        if (subjPtr) {
            return (subjPtr.get()->*funcPtr)(args...);
        }
        else
        {
            throw std::runtime_error("instance of Subject not available");
        }
    }
private:
    std::unique_ptr<Subject> subjPtr{ nullptr };
    T(Subject::* funcPtr)(Args...) = nullptr;
    std::unordered_map<std::string, std::string> defArgs = {};
};