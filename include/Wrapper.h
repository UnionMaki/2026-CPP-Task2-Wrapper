#include "Subject.h"
#include <memory>
#include <vector>
#include <string>
#include <tuple>
#include <stdexcept>

template<typename T, typename ...Param>
class Wrapper {
public:
    Wrapper(Subject* _subjRaw, T(Subject::* _func)(Param...), std::initializer_list<std::pair<const std::string, std::string>>&& _defArgs) : subjPtr(std::move(_subjRaw)), funcPtr(_func) {
        for (auto item : _defArgs) {
            defArgs.push_back(std::move(item.second));
        }

        if (defArgs.size() < sizeof...(Param))
            throw std::domain_error("Expected at least" + std::to_string(sizeof...(Param)) + "arguments");
    }

    T call(std::initializer_list<std::pair<const std::string, std::string>>&& _inArgs) {
        std::vector<std::string> callArgs;
        int i = 0;

        for (auto item : _inArgs) {
            callArgs.push_back(std::move(item.second));
            i++;
        }

        i++;

        for (;i < sizeof...(Param); i++) {
            callArgs.push_back(defArgs[i]);
        }

        return call_impl(callArgs, std::make_index_sequence<sizeof...(Param)>{});
    }
private:
    std::unique_ptr<Subject> subjPtr{ nullptr };
    T(Subject::* funcPtr)(Param...) = nullptr;
    std::vector<std::string> defArgs = {};

    template <std::size_t... I>
    T call_impl(const std::vector<std::string>& v, std::index_sequence<I...>) {
        if (subjPtr) {
            return (subjPtr.get()->*funcPtr)(v[I]...);
        }
        else
        {
            throw std::runtime_error("instance of Subject not available");
        }
    }
};