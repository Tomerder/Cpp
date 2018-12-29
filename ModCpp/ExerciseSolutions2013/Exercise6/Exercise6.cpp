#include <iostream>
#include <vector>
#include <algorithm>

// New includes added
#include <functional>
#include <iterator>

#include <cpprest\http_client.h>
#include <cpprest\json.h>

using namespace std;
using namespace std::placeholders;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace pplx;

template <typename TaskIter, typename Callback>
struct when_any_helper
{
	TaskIter begin_;
	TaskIter end_;
	Callback callback_;

	using task_result_t = std::decay_t<decltype(std::declval<TaskIter>()->get())>;
	using pair_result_t = task<std::pair<task_result_t, size_t>>;

	when_any_helper(TaskIter begin, TaskIter end, Callback callback)
		: begin_(begin), end_(end), callback_(std::move(callback))
	{
		if (std::distance(begin, end) > 0)
		{
			when_any(begin, end).then([this](pair_result_t const& r) { continuation(r); });
		}
		else
		{
			delete this;
		}
	}
	void continuation(pair_result_t const& t)
	{
		auto result = t.get(); // TODO exception handling etc.
		callback_(result.first);
		--end_;
		if (std::distance(begin_, end_) > 0)
		{
			std::swap(*(begin_ + result.second), *end_);
			when_any(begin_, end_).then([this](pair_result_t const& r) { continuation(r); });
		}
		else
		{
			delete this;
		}
	}
};

template <typename TaskIter, typename Callback>
void when_any_repeat(TaskIter begin, TaskIter end, Callback&& callback)
{
	// The helper object cleans itself up when done. It has to be a heap allocation because
	// when_any_repeat returns before the callbacks are completed.
	new when_any_helper<TaskIter, Callback>(begin, end, std::forward<Callback>(callback));
}

task<http_response> get_weather_for_city(wstring city, wstring country)
{
	wstring url = L"http://api.openweathermap.org/data/2.5/weather?q=" + city + L"," + country;
	http_client client(url);
	return client.request(methods::GET);
}

static const double KELVIN_CELSIUS_OFFSET = -273.15;

void print_weather(const json::value& response)
{
	wcout << "Temperature in " << response.get(L"name").as_string() << " is "
		  << response.get(L"main").get(L"temp").as_double() + KELVIN_CELSIUS_OFFSET << endl;
}

int main(int argc, char * argv[])
{
	std::vector<std::pair<std::wstring, std::wstring>> cities{
			{ L"Jerusalem", L"Israel" },
			{ L"Haifa", L"Israel" },
			{ L"London", L"UK" },
			{ L"Paris", L"France" },
			{ L"Omsk", L"Russia" },
			{ L"Ulaanbaatar", L"Mongolia" }
	};

	std::vector<task<http_response>> tasks;
	std::transform(std::begin(cities), std::end(cities), std::back_inserter(tasks),
		[](std::pair<std::wstring, std::wstring> const& city)
		{
			return get_weather_for_city(city.first, city.second);
		}
	);

	// This is the generic approach using the 'when_any_repeat' helper implemented above.
	/*when_any_repeat(tasks.begin(), tasks.end(), [](http_response const& resp) {
		resp.extract_json().then(&print_weather);
	});
	getchar();*/

	std::function<void(std::pair<http_response, size_t>)> continuation;
	continuation = [&](std::pair<http_response, size_t> result)
	{
		tasks.erase(std::begin(tasks) + result.second);
		if (tasks.size() > 0)
		{
			when_any(std::begin(tasks), std::end(tasks)).then(continuation);
		}
		else
		{
			std::cout << "all tasks completed" << std::endl;
		}

		result.first.extract_json().then(&print_weather);
	};

	when_any(std::begin(tasks), std::end(tasks)).then(continuation);

	std::cout << "waiting for results" << std::endl;
	getchar();

	return 0;
}

