#pragma once

#ifdef EXPRESSION_SFINAE_SUPPORTED

template <typename...>
struct if_feasible_h
{
    using type = void;
};
template <typename... Types>
using if_feasible_t = typename if_feasible_h<Types...>::type;

template <typename Container>
using stdbegin_t = decltype(
	std::begin(std::declval<Container const&>())
	);

template <typename Container>
using stdend_t = decltype(
	std::end(std::declval<Container const&>())
	);

template <typename BeginIterator, typename EndIterator>
using iter_neq_t = decltype(
	std::declval<BeginIterator>() != std::declval<EndIterator>()
	);

template <typename BeginIterator>
using increment_t = decltype(
	++std::declval<BeginIterator&>()
	);

template <typename BeginIterator>
using deref_t = decltype(
	*std::declval<BeginIterator>()
	);

template <typename Container, typename = void>
struct is_full_container : std::false_type
{
};

template <typename Container>
struct is_full_container<Container, if_feasible_t<stdbegin_t<Container>
                                                 , stdend_t<Container>
										         , increment_t<stdbegin_t<Container>>
										         , iter_neq_t<stdbegin_t<Container>, stdend_t<Container>>
										         , deref_t<stdbegin_t<Container>>
                                    >
					    >
	: std::integral_constant<bool
							, std::is_convertible<iter_neq_t<stdbegin_t<Container>
														    , stdend_t<Container>>
											     , bool>::value
						   && !std::is_void<deref_t<stdbegin_t<Container>>>::value
						   && std::is_destructible<stdbegin_t<Container>>::value
						   && std::is_copy_constructible<stdbegin_t<Container>>::value
						   && std::is_destructible<stdend_t<Container>>::value
						   && std::is_copy_constructible<stdend_t<Container>>::value
						    >
{
};

#endif

namespace custom
{
    template <typename T>
    struct container
    {
        T* begin() { return nullptr; }
        T* end()   { return nullptr; }
        
        T const* begin() const { return nullptr; }
        T const* end()   const { return nullptr; }
    };
    
    struct mincontainer
    {
        struct iterator
        {
            bool operator!=(iterator const&);
            int operator*();
            iterator& operator++();
        };
        
        iterator begin() const;
        iterator end()   const;
    };
}

void test_full_container()
{
#ifdef EXPRESSION_SFINAE_SUPPORTED
    static_assert(!is_full_container<int>{}, "int");
    static_assert(is_full_container<int(&)[17]>{}, "int(&)[17]");
    static_assert(is_full_container<std::string>{}, "std::string");
    static_assert(is_full_container<std::vector<int>>{}, "std::vector<int>");
    static_assert(is_full_container<std::vector<bool>>{}, "std::vector<bool>");
    static_assert(is_full_container<std::set<int>>{}, "std::set<int>");
    static_assert(is_full_container<std::initializer_list<int>>{}, "std::initializer_list<int>");
    static_assert(is_full_container<custom::container<int>>{}, "custom::container<int>");
    static_assert(is_full_container<custom::mincontainer>{}, "custom::mincontainer");
#endif
}