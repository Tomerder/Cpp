#include <iostream>
#include <vector>
#include <algorithm>

#include <cpprest\http_client.h>
#include <cpprest\json.h>

using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace pplx;

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
	//TODO

	return 0;
}

