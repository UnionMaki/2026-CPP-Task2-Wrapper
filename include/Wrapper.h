#ifndef WRAPPER_H
#define WRAPPER_H

#include "Subject.h"
#include <memory>
#include <vector>
#include <string>
#include <tuple>
#include <stdexcept>

class IWrapper {
public:
    virtual ~IWrapper() = default;
    virtual std::string call(std::initializer_list<std::pair<const std::string, std::string>>&& args) = 0;
};

template<typename T, typename ...Param>
class Wrapper : public IWrapper {
public:
    Wrapper(std::unique_ptr<Subject> _subjPtr, T(Subject::* _func)(Param...), std::initializer_list<std::pair<const std::string, std::string>>&& _defArgs) : subjPtr(std::move(_subjPtr)), funcPtr(_func) {
        for (auto item : _defArgs) {
            defArgs.push_back(std::move(item.second));
        }

        if (defArgs.size() < sizeof...(Param))
            throw std::domain_error("Expected at least" + std::to_string(sizeof...(Param)) + "arguments");
    }

    std::string call(std::initializer_list<std::pair<const std::string, std::string>>&& _inArgs) override {
        if constexpr (std::is_void_v<T>) {
            call_template(std::move(_inArgs));
            return "";
        }
        else {
            return std::to_string(call_template(std::move(_inArgs)));
        }
    }

private:
    std::unique_ptr<Subject> subjPtr{ nullptr };
    T(Subject::* funcPtr)(Param...) = nullptr;
    std::vector<std::string> defArgs = {};

    T call_template(std::initializer_list<std::pair<const std::string, std::string>>&& _inArgs) {
        std::vector<std::string> callArgs;
        int i = 0;
        for (auto item : _inArgs) {
            callArgs.push_back(std::move(item.second));
            i++;
        }
        //i++;
        for (;i < sizeof...(Param); i++) {
            callArgs.push_back(defArgs[i]);
        }
        return call_impl(callArgs, std::make_index_sequence<sizeof...(Param)>{});
    }

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

#endif