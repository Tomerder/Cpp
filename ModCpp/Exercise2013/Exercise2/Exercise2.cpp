#include <vector>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iostream>

struct point2d
{
	double x;
	double y;
	point2d(double xx, double yy) : x(xx), y(yy) {}
};

std::ostream& operator<<(std::ostream& os, point2d const& point)
{
	os << "(" << point.x << ", " << point.y << ")";
	return os;
}

template <typename Function>
double integrate(double from, double to, unsigned steps, Function f)
{
	double integral = 0.0;
	double step_size = (to-from)/steps;
	for (unsigned i = 0; i < steps; ++i)
	{
		integral += f(from + step_size/2) * step_size;
		from += step_size;
	}
	return integral;
}

double square(double x)
{
	return x * x;
}

const int STEPS = 100;

void print_points(std::vector<point2d> const& points)
{
	std::cout << "--------------------------" << std::endl;
	std::cout << "printing a vector of " << points.size() << " points" << std::endl;
	std::copy(points.begin(), points.end(), std::ostream_iterator<point2d>(std::cout, "\n"));
	std::cout << "--------------------------" << std::endl;
}

int main()
{
	std::string s1("hello");

	std::string& s2 = s1;

	s1.append(" world");
	s1.clear();

	std::cout << "integral of x^2 from 0 to 1        = " << integrate(0.0, 1.0, STEPS, square) << std::endl;
	std::cout << "integral of sin(x) from 0 to PI/2  = " << integrate(0.0, 3.14 / 2, STEPS, [](double x){ return std::sin(x); }) << std::endl; // You can use 22.0/14 as an approximation for PI/2
	std::cout << "integral of 1/log(x) from 2 to 100 = " << integrate(2.0, 100.0 / 2, STEPS, [](double x){ return 1/std::log(x); }) << std::endl;

	std::vector<point2d> points;
	points.push_back(point2d(3.0, 4.0));
	points.push_back(point2d(2.5, 0.5));
	points.push_back(point2d(3.5, 1.5));
	points.push_back(point2d(0.5, 0.0));
	points.push_back(point2d(-1.0, -1.0));
	points.push_back(point2d(2.5, -1.5));
	points.push_back(point2d(-1.5, 0.5));
	print_points(points);

	// TODO 3
	//	Sort the points by the 'x' axis (e.g. the point (0.5, -1.0) comes before (0.0, 2.0)).
	//	Use the std::sort algorithm and a lambda function to define the sort order.
	auto f = [](point2d& p1, point2d& p2){ 
		return p1.x < p2.x; 
	};
	std::sort(points.begin(), points.end(), f);

	print_points(points);

	point2d origin(0.0, 0.0);
	// TODO 4
	//	Determine how many points are in the upper right quadrant (i.e. to the right and above
	//	the point 'origin'). Use std::count_if and a lambda function to specify the predicate.
	//	Don't forget to capture the 'origin' variable so that you can access it from the lambda.
	auto a = std::count_if(points.begin(), points.end(), [&origin](point2d p){ return ((p.x >= origin.x) && (p.y >= origin.y)); });

	std::vector<double> magnitudes;
	// TODO 5
	//	Store the magnitude of each point (std::sqrt(x*x + y*y)) in the 'magnitudes' vector.
	//	Use std::transform and a lambda function to convert a point to its magnitude. Don't
	//	forget to use std::back_inserter as the output iterator for std::transform.
	std::transform(points.begin(), points.end(), std::back_inserter(magnitudes), [](point2d p){ return std::sqrt(p.x*p.x + p.y*p.y); });

#define LAMBDA_REF [&]
	int numbers[] = { 5, 8, 11, 4, 9, 1, 2, -13, 17, 12 };
	int min_num = std::numeric_limits<int>::max();
	int max_num = std::numeric_limits<int>::min();
	std::for_each(&numbers[0], &numbers[sizeof(numbers) / sizeof(numbers[0])], LAMBDA_REF(int n) {
		if (n < min_num) { min_num = n; }
		else { max_num = n;  }
	});

	return 0;
}