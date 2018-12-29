#pragma once

#include <type_traits>

struct button
{
	// Assume it is both movable and copyable, and we want to optimize passing buttons
	// around whenever it is required.
};
struct menu
{
	// Assume it is both movable and copyable, and we want to optimize passing buttons
	// around whenever it is required.
};

struct dialog0
{
	button ok_;
	menu main_;

	void configure(button const& ok, menu const& main)
	{
		ok_ = ok;
		main_ = main;
	}
	void configure(button const& ok, menu&& main)
	{
		ok_ = ok;
		main_ = std::move(main);
	}
	void configure(button&& ok, menu const& main)
	{
		ok_ = std::move(ok);
		main_ = main;
	}
	void configure(button&& ok, menu&& main)
	{
		ok_ = std::move(ok);
		main_ = std::move(main_);
	}
};

struct dialog1
{
	button ok_;
	menu main_;

	template <typename Button, typename Menu>
	void configure(Button&& ok, Menu&& main)
	{
		ok_ = std::forward<Button>(ok);
		main_ = std::forward<Menu>(main);
	}
};

struct dialog2
{
	button ok_;
	menu main_;

	template <typename Button, typename Menu>
	void configure(Button&& ok, Menu&& main)
	{
		static_assert(std::is_assignable<button, Button>::value, "button must be assignable from Button");
		static_assert(std::is_assignable<menu, Menu>::value, "menu must be assignable from Menu");

		ok_ = std::forward<Button>(ok);
		main_ = std::forward<Menu>(main);
	}
};

struct dialog3
{
	button ok_;
	menu main_;

	template <typename Button, typename Menu>
	void configure(Button&& ok, Menu&& main)
	{
		constexpr bool btnok = std::is_assignable<button, Button>::value;
		constexpr bool menuok = std::is_assignable<menu, Menu>::value;

		static_assert(btnok, "button must be assignable from Button");
		static_assert(menuok, "menu must be assignable from Menu");

		using all_ok_t = std::integral_constant<bool, btnok && menuok>;
		configure_helper(std::forward<Button>(ok), std::forward<Menu>(main), all_ok_t{});
	}

private:
	template <typename Button, typename Menu>
	void configure_helper(Button&& ok, Menu&& main, std::true_type)
	{
		ok_ = std::forward<Button>(ok);
		main_ = std::forward<Menu>(main);
	}
	template <typename Button, typename Menu>
	void configure_helper(Button&& ok, Menu&& main, std::false_type)
	{
	}
};

struct dialog4
{
	button ok_;
	menu main_;

	template <typename Button, typename Menu>
	std::enable_if_t<std::is_assignable<button, Button>::value && std::is_assignable<menu, Menu>::value>
	configure(Button&& ok, Menu&& main)
	{
		ok_ = std::forward<Button>(ok);
		main_ = std::forward<Menu>(main);
	}
};

template <typename Dialog>
void configure_dialog()
{
	Dialog d;
	d.configure(button{}, menu{});			// rvalues
	d.configure(*new button, *new menu);	// lvalues
//	d.configure(42, std::string{});			// invalid
}

template <typename T = void>	// template so that it's not compiled unless called by 'main'
void param_passing()
{
	configure_dialog<dialog0>();	// the most straightforward error
	configure_dialog<dialog1>();
	configure_dialog<dialog2>();
	configure_dialog<dialog3>();
	configure_dialog<dialog4>();
}