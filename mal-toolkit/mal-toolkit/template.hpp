#pragma once
/**
 * @file template.hpp
 * @brief Defines template classes and functions used in the project.
 */

namespace mal_toolkit
{
    namespace _template_detail
    {
        template <>
        constexpr size_t CalculateSize()
        {
            return 0;
        }
        /**
         * @brief Calculates the total size of multiple types in bytes.
         * @tparam A The type whose size is to be calculated.
         * @return The size of the type `A` in bytes.
         */
        template <typename A>
        constexpr size_t CalculateSize()
        {
            return sizeof(A);
        }

        /**
         * @brief Calculates the total size of multiple types in bytes.
         * @tparam A The first type whose size is to be calculated.
         * @tparam B The second type whose size is to be calculated.
         * @tparam Args The remaining types whose sizes are to be calculated.
         * @return The sum of sizes of all specified types in bytes.
         */
        template <typename A, typename B, typename... Args>
        constexpr size_t CalculateSize()
        {
            return sizeof(A) + CalculateSize<B, Args...>();
        }

        /**
         * @brief Calculates the index of a type within a parameter pack.
         * @tparam T The type to search for.
         * @param index The current index being checked.
         * @return The index of type `T` if found, otherwise `std::numeric_limits<std::size_t>::max()`.
         */
        template <typename T>
        consteval size_t index_of_helper(std::size_t)
        {
            return std::numeric_limits<std::size_t>::max();
        }

        /**
         * @brief Calculates the index of a type within a parameter pack.
         * @tparam T The type to search for.
         * @tparam U The current type being checked.
         * @param index The current index being checked.
         * @return The index of type `T` if found, otherwise continues to the next type.
         */
        template <typename T, typename U>
        consteval size_t index_of_helper(std::size_t index)
        {
            if constexpr (std::is_same_v<T, U>)
            {
                return index;
            }
            return index_of_helper<T>(index + 1);
        }

        /**
         * @brief Calculates the index of a type within a parameter pack.
         * @tparam T The type to search for.
         * @tparam U The current type being checked.
         * @tparam V The next type to check.
         * @tparam Rest The remaining types to check.
         * @param index The current index being checked.
         * @return The index of type `T` if found, otherwise continues to the next type.
         */
        template <typename T, typename U, typename V, typename... Rest>
        consteval size_t index_of_helper(std::size_t index)
        {
            if constexpr (std::is_same_v<T, U>)
            {
                return index;
            }
            else
            {
                return index_of_helper<T, V, Rest...>(index + 1);
            }
        }

        /**
         * @brief Traits for extracting information from a function type.
         * @tparam Func The function type from which to extract traits.
         */
        template <typename Func>
        struct function_traits;

        /**
         * @brief Traits for extracting information from a function type.
         * @tparam Ret The return type of the function.
         * @tparam Args The argument types of the function.
         */
        template <typename Ret, typename... Args>
        struct function_traits<std::function<Ret(Args...)>>
        {
            using ArgumentTypes = std::tuple<Args...>;
        };

        /**
         * @brief Helper for calculating the index of a type within a function's argument list.
         * @tparam Func The function type in which to search for the type index.
         */
        template <typename Func>
        struct index_of_function_arg;

        /**
         * @brief Helper for calculating the index of a type within a function's argument list.
         * @tparam Ret The return type of the function.
         * @tparam Args The argument types of the function.
         */
        template <typename Ret, typename... Args>
        struct index_of_function_arg<std::function<Ret(Args...)>>
        {
            /**
             * @brief Calculates the index of a type within the function's argument list.
             * @tparam T The type to search for.
             * @return The index of type `T` within the function's argument list.
             */
            template <typename T>
            static consteval size_t index_of_type()
            {
                return index_of_helper<T, Args...>(0);
            }
        };
    }  // namespace _template_detail

    /**
     * @brief Provides information about a parameter pack.
     */
    template <typename... Args>
    struct parameter_pack_info
    {
        /**
         * @brief sizeof all types.
         */
        static constexpr size_t size = _template_detail::CalculateSize<Args...>();
        /**
         * @brief total amount of provided types.
         */
        static constexpr size_t amount = sizeof...(Args);

        /**
         * @struct parameter_pack_info::type_at
         * @brief Provides access to the type at a specific index within the parameter pack.
         * @tparam index The index of the type to retrieve.
         * @note The index should be less than the total size of the parameter pack.
         */
        template <size_t index>
        struct type_at
        {
            static_assert(index < size);
            using type = std::tuple_element_t<index, std::tuple<Args...>>;
        };
    };

    /**
     * @brief Function to find the index of a type in a parameter pack.
     *
     * This template function determines the index of a specified type `T` within a parameter pack
     * `Types`. The function is evaluated at compile time and returns the index of the first occurrence
     * of the specified type in the parameter pack.
     *
     * @tparam T The type whose index is to be found within the parameter pack.
     * @tparam Types The parameter pack in which the type index is searched.
     * @return The index of the first occurrence of type `T` in the parameter pack.
     */
    template <typename T, typename... Types>
    consteval size_t index_of_type()
    {
        return _template_detail::index_of_helper<T, Types...>(0);
    }

    /**
     * @brief Function to find the index of a type within a function's argument list.
     *
     * This template function determines the index of a specified type `T` within the argument list
     * of a provided function `Func`. The function is evaluated at compile time and returns the index
     * of the first occurrence of the specified type in the argument list of the function.
     *
     * @tparam T The type whose index is to be found within the function's argument list.
     * @tparam Func The function type whose argument list is to be searched.
     * @param func An instance of the function for which the argument list type index is sought.
     * @return The index of the first occurrence of type `T` in the function's argument list.
     */
    template <typename T, typename Func>
    consteval std::size_t index_of_function_arg([[maybe_unused]] Func const &func = {})
    {
        return _template_detail::index_of_function_arg<Func>::template index_of_type<T>();
    }

    // based on https://artificial-mind.net/blog/2020/10/31/constexpr-for

    /**
     * @brief A constexpr loop for compile-time iteration.
     */
    template <auto begin, auto end, auto inc, class F>
    constexpr void constexpr_for(F &&f)
    {
        f(std::integral_constant<decltype(begin), begin>{});
        if constexpr (begin + inc >= end)
        {
            return;
        }
        else  // else should be constexpr as well
        {
            constexpr_for<begin + inc, end, inc>(std::forward<F>(f));
        }
    }
    template <auto begin, auto end, auto inc, class F>
    constexpr void constexpr_for_break(F &&f)
    {
        if (not f(std::integral_constant<decltype(begin), begin>{}))
        {
            return;
        }
        if constexpr (begin + inc >= end)
        {
            return;
        }
        else  // else should be constexpr as well
        {
            constexpr_for<begin + inc, end, inc>(std::forward<F>(f));
        }
    }

    /**
     * @brief Applies a function to each element in a range and returns true if all return true.
     */
    template <class iterator, class F>
    constexpr bool for_each_true(iterator begin, iterator const &end, F &&f)
    {
        bool rv = true;
        for (; begin != end;)
        {
            rv &= f(begin++);
        }
        return rv;
    }

    /**
     * @brief Concept to check if a type is an enumeration class.
     */
    template <typename T>
    concept EnumClassConcept = std::is_enum_v<T> && !std::convertible_to<T, int>;

    /**
     * @brief Converts an enumeration class value to its underlying integer value.
     */
    template <EnumClassConcept Enumeration>
    constexpr auto as_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
    {
        return static_cast<typename std::underlying_type<Enumeration>::type>(value);
    }

    /**
     * @brief Extracts the return type of a function or function pointer.
     */
    template <typename T>
    struct return_type;

    template <typename R, typename... Args>
    struct return_type<R(Args...)>
    {
        using type = R;
    };

    template <typename R, typename... Args>
    struct return_type<R (*)(Args...)>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...)>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) &>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) &&>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) const>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) const &>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) const &&>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) volatile>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) volatile &>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) volatile &&>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) const volatile>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) const volatile &>
    {
        using type = R;
    };

    template <typename R, typename C, typename... Args>
    struct return_type<R (C::*)(Args...) const volatile &&>
    {
        using type = R;
    };

    template <typename T>
    using return_type_t = typename return_type<T>::type;
}  // namespace mal_toolkit