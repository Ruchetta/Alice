#include <functional>
#include <tuple>
#include <vector>

template<typename... T>
struct Chain {
    using middleware = std::function<std::tuple<T...>(T &&...)>;

    Chain<T...>() = default;

    Chain<T...>(std::initializer_list<middleware> ms) {
        _middlewares.insert(_middlewares.end(), ms.begin(), ms.end());
    }

    static Chain<T...> New(std::initializer_list<middleware> ms) {
        return Chain<T...>(ms);
    }

    std::tuple<T...> Then(std::tuple<T...> &&data) {
        for (auto reverse_it = _middlewares.rbegin(); reverse_it != _middlewares.rend(); ++reverse_it) {
            data = std::apply(*reverse_it, std::move(data));
        }
        return std::move(data);
    }

    Chain<T...> Append(std::initializer_list<middleware> ms) {
        Chain<T...> new_chain = *this;
        new_chain._middlewares.insert(new_chain._middlewares.end(), ms.begin(), ms.end());
        return new_chain;
    }

    Chain<T...> Shift(std::initializer_list<middleware> ms) {
        Chain<T...> new_chain = *this;
        new_chain._middlewares.insert(new_chain._middlewares.begin(), ms.begin(), ms.end());
        return new_chain;
    }

    Chain<T...> Extend(Chain<T...> chain) {
        Chain<T...> new_chain = *this;
        new_chain._middlewares.insert(new_chain._middlewares.end(), chain._middlewares.begin(),
                                      chain._middlewares.end());
        return new_chain;
    }

private:
    std::vector<middleware> _middlewares;
};
