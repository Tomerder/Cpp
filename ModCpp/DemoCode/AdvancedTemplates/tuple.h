#pragma once

#include <type_traits>
#include <utility>
#include <initializer_list>

//
// A more-or-less complete implementation of std::tuple. There is lots
// of room for optimization, especially in terms of compilation time.
// For example, a reasonable implementation of make_index_sequence would
// use unrolling. Still, this is fairly representative of some techniques
// needed to implement this kind of facility.
//
// Note: tuple_cat is implemented in a separate file to illustrate two
//		 different implementations and their performance implications.
//
// Missing: 1) noexcept specifications on all functions
//          2) some additional and boring operators (<=, >, >=)
//
namespace library
{

#ifdef _MSC_VER
	// Remove warnings about multiple default constructors specified.
	// See details in the tuple_impl and tuple classes.
	#pragma warning (push)
	#pragma warning (disable: 4520)
#endif

    // A sequence of integers. For example: index_sequence<0, 1, 2>.
	// Note that this facility is now available in the standard library,
	// but we reimplement it here because its primary use case is with
	// tuples, so it would be unfair to not illustrate it.
    template <size_t... Ints>
    struct index_sequence
    {
        static constexpr size_t length = sizeof...(Ints);
		using type = index_sequence<Ints...>;
    };

    // Template to append an index to the tail of an index sequence.
    // Specialized specifically for index_sequence<...>. When given
    // an index_sequence<0, 1, 2, ..., N> and I = N+1, produces the
    // type index_sequence<0, 1, 2, ..., N, N+1>.
    template <size_t I, typename Sequence>
    struct append_tail_index_sequence;

    template <size_t I, size_t... Indices>
    struct append_tail_index_sequence<I, index_sequence<Indices...>>
		: index_sequence<Indices..., I>
    {
    };

    // Produces an index sequence with the elements 0, 1, ..., I-1 (length I).
    // For example: make_index_sequence<2> === index_sequence<0, 1>
    template <size_t I>
    struct make_index_sequence : append_tail_index_sequence<I - 1,
			typename make_index_sequence<I - 1>::type>::type
    {
    };

    // Base case for an index sequence of length 1. Produces index_sequence<0>.
    template <>
    struct make_index_sequence<1> : index_sequence<0>
    {
    };

    // Given a parameter pack of length N, produces an index sequence with elements 0, ..., N-1.
    template <typename... Types>
    using make_index_sequence_for_types = typename make_index_sequence<sizeof...(Types)>::type;

    template <template <class> class UnOp>
    constexpr bool is_any_of1()
    {
        return false;
    }

    // Checks whether any of the types T in [Head, Tail...] conform to the
    // unary metafunction predicate UnOp<T>.
    template <template <class> class UnOp, typename Head, typename... Tail>
    constexpr bool is_any_of1()
    {
        return UnOp<Head>::value || is_any_of1<UnOp, Tail...>();
    }

    template <template <class, class> class BinOp, typename First>
    constexpr bool is_any_of2()
    {
        return false;
    }

    // Checks whether any of the types T in [Head, Tail...] conform to the binary
    // metafunction predicate BinOp<First, T>.
    template <template <class, class> class BinOp, typename First, typename Head, typename... Tail>
    constexpr bool is_any_of2()
    {
        return BinOp<First, Head>::value || is_any_of2<BinOp, First, Tail...>();
    }

	template <size_t I, typename T>
	struct tuple_element;

	template <typename>
	struct is_tuple_element : std::false_type
	{
	};

	template <size_t I, typename T>
	struct is_tuple_element<tuple_element<I, T>> : std::true_type
	{
	};

    // An element in a tuple. The element knows its type and index in the tuple.
    template <size_t I, typename T>
    struct tuple_element
    {
        T value_;

        tuple_element() = default;

        tuple_element(tuple_element const&) = default;

        tuple_element(tuple_element&&) = default;

		tuple_element& operator=(tuple_element const&) = default;

		tuple_element& operator=(tuple_element&&) = default;

        template <typename U,
                typename = typename std::enable_if<!is_tuple_element<typename std::decay<U>::type>::value>::type>
        explicit tuple_element(U&& val) : value_(std::forward<U>(val))
        {
        }

        template <typename U>
        explicit tuple_element(tuple_element<I, U> const& rhs)
                : value_(rhs.value_)
        {
        }

        template <typename U>
        explicit tuple_element(tuple_element<I, U>&& rhs)
                : value_(std::move(rhs.value_))
        {
        }

        template <typename U,
                typename = typename std::enable_if<!is_tuple_element<typename std::decay<U>::type>::value>::type>
        tuple_element& operator=(U&& rhs)
        {
            value_ = std::forward<U>(rhs);
            return *this;
        }

        template <typename U>
        tuple_element& operator=(tuple_element<I, U> const& rhs)
        {
            value_ = rhs.value_;
            return *this;
        }

        template <typename U>
        tuple_element& operator=(tuple_element<I, U>&& rhs)
        {
            value_ = std::move(rhs.value_);
            return *this;
        }

        template <typename U>
        void swap(tuple_element<I, U>& rhs)
        {
            std::swap(value_, rhs.value_);
        }

        template <typename U>
        bool operator==(tuple_element<I, U> const& rhs) const
        {
            return value_ == rhs.value_;
        }

        template <typename U>
        bool operator<(tuple_element<I, U> const& rhs) const
        {
            return value_ < rhs.value_;
        }
    };

    // Returns the type at index I in the type list Types...
    template <size_t I, typename... Types>
    struct type_at_index;

    template <typename Head, typename... Tail>
    struct type_at_index<0, Head, Tail...>
    {
        using type = Head;
    };

    template <size_t I, typename Head, typename... Tail>
    struct type_at_index<I, Head, Tail...>
    {
        using type = typename type_at_index<I - 1, Tail...>::type;
    };

    template <size_t I, typename... Types>
    using type_at_index_t = typename type_at_index<I, Types...>::type;

    template <typename Sequence, typename... Types>
    struct tuple_impl;

	template <typename>
	struct is_tuple_impl : std::false_type
	{
	};

	template <typename Sequence, typename... Types>
	struct is_tuple_impl<tuple_impl<Sequence, Types...>> : std::true_type
	{
	};

    // The actual implementation for the tuple's storage. Inherits from a
    // tuple_element for each index and type in the provided list. The actual
    // elements are stored in each base class.
    template <size_t... Ints, typename... Types>
    struct tuple_impl<index_sequence<Ints...>, Types...> : tuple_element<Ints, Types> ...
    {
        static constexpr int length = sizeof...(Types);

		// Visual C++ incorrectly (?) thinks that the explicit constructor from OtherTypes&&... is another declaration
		// of the defaulted constructor. Clang is willing to compile this code.
#ifndef _MSC_VER
		tuple_impl() = default;
#else
		tuple_impl(void* = nullptr)
		{
		}
#endif

        tuple_impl(tuple_impl const&) = default;

        tuple_impl(tuple_impl&&) = default;

		tuple_impl& operator=(tuple_impl const&) = default;

		tuple_impl& operator=(tuple_impl&&) = default;

		// To avoid hiding the copy constructor with this template, which could generate tuple_impl(tuple_impl&) for lvalues,
		// we have the enable_if pruning that signature when necessary. First, we accept only when the number of types in the
		// list is exactly right, and when there is no type in the list that is itself a tuple_element.
        template <typename... OtherTypes, typename =
			typename std::enable_if<(sizeof...(OtherTypes) == sizeof...(Ints)) && !((sizeof...(OtherTypes) == 1) && is_any_of1<is_tuple_impl, typename std::decay<OtherTypes>::type...>())>::type
        >
        explicit tuple_impl(OtherTypes&& ... elements)
                : tuple_element<Ints, Types>(std::forward<OtherTypes>(elements))...
        {
        }

        template <typename... OtherTypes>
        explicit tuple_impl(tuple_impl<index_sequence<Ints...>, OtherTypes...> const& rhs)
                : tuple_element<Ints, Types>((tuple_element<Ints, OtherTypes>&)rhs)...
        {
        }

        template <typename... OtherTypes>
        explicit tuple_impl(tuple_impl<index_sequence<Ints...>, OtherTypes...>&& rhs)
                : tuple_element<Ints, Types>(std::move((tuple_element<Ints, OtherTypes>&)rhs))...
        {
        }

        template <typename... OtherTypes>
        tuple_impl& operator=(tuple_impl<index_sequence<Ints...>, OtherTypes...> const& rhs)
        {
            // We're taking an initializer list that ensures we're throwing away the return values
			// from operator=, and that we're evaluating them in-order.
            int ignorable[]{ 0, ((void)(((tuple_element<Ints, Types>&)*this) = ((tuple_element<Ints, OtherTypes>&)rhs)), 0)... };
			(void)ignorable; // To avoid unreferenced local variable warnings
            return *this;
        }

        template <typename... OtherTypes>
        tuple_impl& operator=(tuple_impl<index_sequence<Ints...>, OtherTypes...>&& rhs)
        {
            int ignorable[]{ 0, ((void)(((tuple_element<Ints, Types>&)*this) = std::move(((tuple_element<Ints, OtherTypes>&)rhs))), 0)... };
			(void)ignorable;
            return *this;
        }

        template <typename... OtherTypes>
        void swap(tuple_impl<index_sequence<Ints...>, OtherTypes...>& rhs)
        {
            int ignorable[]{ 0, ((void)(((tuple_element<Ints, Types>&)*this).swap((tuple_element<Ints, OtherTypes>&)rhs)), 0)... };
			(void)ignorable;
        }

        template <typename U1, typename U2>
        tuple_impl& operator=(std::pair<U1, U2> const& rhs)
        {
            (tuple_element<0, type_at_index_t<0, Types...>>&)*this = rhs.first;
            (tuple_element<1, type_at_index_t<1, Types...>>&)*this = rhs.second;
            return *this;
        }

        template <typename U1, typename U2>
        tuple_impl& operator=(std::pair<U1, U2>&& rhs)
        {
            (tuple_element<0, type_at_index_t<0, Types...>>&)*this = std::move(rhs.first);
            (tuple_element<1, type_at_index_t<1, Types...>>&)*this = std::move(rhs.second);
            return *this;
        }

        template <typename... OtherTypes>
        bool operator==(tuple_impl<index_sequence<Ints...>, OtherTypes...> const& rhs) const
        {
            return equality_impl(std::integral_constant<int, length-1>{}, rhs);
        }

        template <typename... OtherTypes>
        bool equality_impl(std::integral_constant<int, -1>, tuple_impl<index_sequence<Ints...>, OtherTypes...> const& rhs) const
        {
            return true;
        }

        template <int I, typename... OtherTypes>
        bool equality_impl(std::integral_constant<int, I>, tuple_impl<index_sequence<Ints...>, OtherTypes...> const& rhs) const
        {
            auto& lhs_element = (tuple_element<I, type_at_index_t<I, Types...>>&)*this;
            auto& rhs_element = (tuple_element<I, type_at_index_t<I, OtherTypes...>>&)rhs;
            return (lhs_element == rhs_element) && equality_impl(std::integral_constant<int, I-1>{}, rhs);
        }

        template <typename... OtherTypes>
        bool operator<(tuple_impl<index_sequence<Ints...>, OtherTypes...> const& rhs) const
        {
            return less_than_impl(std::integral_constant<int, length-1>{}, rhs);
        }

        template <typename... OtherTypes>
        bool less_than_impl(std::integral_constant<int, -1>, tuple_impl<index_sequence<Ints...>, OtherTypes...> const& rhs) const
        {
            return false;
        }

        template <int I, typename... OtherTypes>
        bool less_than_impl(std::integral_constant<int, I>, tuple_impl<index_sequence<Ints...>, OtherTypes...> const& rhs) const
        {
            auto& lhs_element = (tuple_element<I, type_at_index_t<I, Types...>>&)*this;
            auto& rhs_element = (tuple_element<I, type_at_index_t<I, OtherTypes...>>&)rhs;
            if (lhs_element < rhs_element) {
                return true;
            }
            if (!(lhs_element == rhs_element)) {
                return false;
            }
            return less_than_impl(std::integral_constant<int, I-1>{}, rhs);
        }
    };

	template <typename...>
	struct tuple;

	template <typename>
	struct is_tuple : std::false_type
	{
	};

	template <typename... Types>
	struct is_tuple<tuple<Types...>> : std::true_type
	{
	};

    // The tuple class itself. Implemented in terms of tuple_impl and provides
    // a facade for most required operations.
    template <typename... Types>
    struct tuple : tuple_impl<make_index_sequence_for_types<Types...>, Types...>
    {
        using base_t = tuple_impl<make_index_sequence_for_types<Types...>, Types...>;

#ifndef _MSC_VER
        tuple() = default;
#else
		tuple(void* = nullptr)
		{
		}
#endif

        tuple(tuple const&) = default;

        tuple(tuple&&) = default;

		tuple& operator=(tuple const& rhs) = default;

        tuple& operator=(tuple&&) = default;

        template <typename... OtherTypes, typename =
			typename std::enable_if<(sizeof...(OtherTypes) == sizeof...(Types)) && !((sizeof...(Types) == 1) && is_any_of1<is_tuple, typename std::decay<OtherTypes>::type...>())>::type
        >
        explicit tuple(OtherTypes&& ... elements)
                : base_t(std::forward<OtherTypes>(elements)...)
        {
        }

        template <typename... OtherTypes>
        explicit tuple(tuple<OtherTypes...> const& rhs) : base_t(rhs)
        {
        }

        template <typename... OtherTypes>
        explicit tuple(tuple<OtherTypes...>&& rhs) : base_t(std::move(rhs))
        {
        }

        template <typename U1, typename U2>
        explicit tuple(std::pair<U1, U2> const& rhs)
                : base_t(rhs.first, rhs.second)
        {
        }

        template <typename U1, typename U2>
        explicit tuple(std::pair<U1, U2>&& rhs)
                : base_t(std::move(rhs.first), std::move(rhs.second))
        {
        }

        template <typename... OtherTypes>
        tuple& operator=(tuple<OtherTypes...> const& rhs)
        {
            base_t::operator=(rhs);
            return *this;
        }

        template <typename... OtherTypes>
        tuple& operator=(tuple<OtherTypes...>&& rhs)
        {
            base_t::operator=(std::move(rhs));
            return *this;
        }

        template <typename... OtherTypes>
        void swap(tuple<OtherTypes...>& other)
        {
            base_t::swap(other);
        }

        template <typename U1, typename U2>
        tuple& operator=(std::pair<U1, U2> const& rhs)
        {
            base_t::operator=(rhs);
            return *this;
        }

        template <typename U1, typename U2>
        tuple& operator=(std::pair<U1, U2>&& rhs)
        {
            base_t::operator=(std::move(rhs));
            return *this;
        }

        template <typename... OtherTypes>
        bool operator==(tuple<OtherTypes...> const& rhs) const
        {
            base_t::operator==(rhs);
            return true;
        }

        template <typename... OtherTypes>
        bool operator!=(tuple<OtherTypes...> const& rhs) const
        {
            return !(*this == rhs);
        }
    };

    // It doesn't make much sense to perform any operations on empty tuples.
	// It could be worth the effort to consolidate this specialization into
	// the base template, though.
    template <>
    struct tuple<>
    {
    };

    // Returns the tuple element at the given index.
    template <size_t I, typename... Types>
    type_at_index_t<I, Types...>& get(tuple<Types...>& tup)
    {
        tuple_element<I, type_at_index_t<I, Types...>>& element = tup;
        return element.value_;
    }

    // Returns the tuple element at the given index (for a const tuple).
    template <size_t I, typename... Types>
    type_at_index_t<I, Types...> const& get(tuple<Types...> const& tup)
    {
        tuple_element<I, type_at_index_t<I, Types...>> const& element = tup;
        return element.value_;
    }

	// Returns the tuple element at the given index (for an rvalue tuple).
	// Note that the decay type is required here, because if the tuple element type
	// is an lvalue reference, appending && doesn't form an rvalue reference.
	template <size_t I, typename... Types>
	typename std::decay<type_at_index_t<I, Types...>>::type&& get(tuple<Types...>&& tup)
	{
		tuple_element<I, type_at_index_t<I, Types...>>&& element = std::move(tup);
		return std::move(element.value_);
	}

    template <typename T>
    constexpr int count_in_types()
    {
        return 0;
    }

    // Returns the number of times the type T appears in the type list [Head, Tail...].
    template <typename T, typename Head, typename... Tail>
    constexpr int count_in_types()
    {
        return count_in_types<T, Tail...>() + (std::is_same<T, Head>::value ? 1 : 0);
    }

    template <typename T>
    constexpr int find_exactly_one_helper(int)
    {
        return -1;
    }

    // Returns the first index of type T in the type list [Head, Tail...], or -1 if not found.
    template <typename T, typename Head, typename... Tail>
    constexpr int find_exactly_one_helper(int depth)
    {
        return std::is_same<T, Head>::value ? depth : find_exactly_one_helper<T, Tail...>(depth + 1);
    }

    // Returns the first index of the type T in the type list [Types...], granted that it
    // appears exactly once. Otherwise, produces a compilation error.
    template <typename T, typename... Types>
    constexpr int find_exactly_one()
    {
        static_assert(count_in_types<T, Types...>() == 1, "type not found or found more than once");
        return find_exactly_one_helper<T, Types...>(0);
    }

    // Returns the element of the specified type, granted that it appears exactly once
    // in the tuple. Otherwise, produces a compilation error.
    template <typename T, typename... Types>
    T& get(tuple<Types...>& tup)
    {
        return get<find_exactly_one<T, Types...>()>(tup);
    }

    // Same as above but for const tuples.
    template <typename T, typename... Types>
    T const& get(tuple<Types...> const& tup)
    {
        return get<find_exactly_one<T, Types...>()>(tup);
    }

	// Same as above but for rvalue tuples.
	template <typename T, typename... Types>
	T&& get(tuple<Types...>&& tup)
	{
		return get<find_exactly_one<T, Types...>()>(std::move(tup));
	}

    // Like std::decay, but recognizes std::reference_wrapper.
    template <typename T>
    struct decay_unless_refwrapper
    {
        using type = typename std::decay<T>::type;
    };

    template <typename T>
    struct decay_unless_refwrapper<std::reference_wrapper<T>>
    {
        using type = T&;
    };

    // Creates a tuple from a variadic parameter pack. Decays their type
    // (which copies or moves them) unless reference wrappers are provided,
    // which are then taken by reference.
    template <typename... Types>
    tuple<typename decay_unless_refwrapper<Types>::type...> make_tuple(Types&& ... elements)
    {
        return tuple<typename decay_unless_refwrapper<Types>::type...>(std::forward<Types>(elements)...);
    }

    // Returns a tuple of references to the provided lvalues. Useful for
    // parameter unpacking (see tests).
    template <typename... Types>
    tuple<Types& ...> tie(Types& ... elements)
    {
        return tuple<Types& ...>(elements...);
    }

    template <typename>
    struct tuple_size;

    // Returns the size of a tuple.
    template <typename... Types>
    struct tuple_size<tuple<Types...>> : std::integral_constant<int, sizeof...(Types)>
    {
    };

    // Placeholder for ignorable elements in std::tie. When assigned to,
    // this class does nothing.
    struct ignore_t
    {
        template <typename T>
        ignore_t& operator=(T const&)
        {
            return *this;
        }
    } ignore;

    template <typename... Types>
    tuple<Types&&...> forward_as_tuple(Types&&... args)
    {
        return tuple<Types&&...>(std::forward<Types>(args)...);
    }

    template <size_t, typename>
    struct type_of_element;

    // Returns the type of the I'th element in the tuple.
    template <size_t I, typename... Types>
    struct type_of_element<I, tuple<Types...>>
    {
        using type = type_at_index_t<I, Types...>;
    };

#ifdef _MSC_VER
	#pragma warning (pop)
#endif
}

namespace std
{
    template <typename... Types>
    void swap(library::tuple<Types...>& lhs, library::tuple<Types...>& rhs)
    {
        lhs.swap(rhs);
    }
}