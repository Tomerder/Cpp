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
	std::cout << "integral of x^2 from 0 to 1        = " << integrate(0.0, 1.0, STEPS, square) << std::endl;
	std::cout << "integral of sin(x) from 0 to PI/2  = " << integrate(0.0, 22.0/14, STEPS, [](double x) { return std::sin(x); }) << std::endl;
	std::cout << "integral of 1/log(x) from 2 to 100 = " << integrate(2, 100, STEPS, [](double x) { return 1 / std::log(x); }) << std::endl;

	std::vector<point2d> points{
			{ 3.0, 1.0 },
			{ 2.5, 0.5 },
			{ 3.5, 1.5 },
			{ 0.5, 0.0 },
			{ -1.0, -1.0 },
			{ 2.5, -1.5 },
			{ -1.5, 0.5 }
	};
	print_points(points);

	std::sort(points.begin(), points.end(),
		[](point2d const& a, point2d const& b) {
			return a.x < b.x;
		}
	);
	print_points(points);

	point2d origin(0.0, 0.0);
	std::cout << "In upper right quadrant: "
		<< std::count_if(
			points.begin(),
			points.end(),
			[origin](point2d const& pt) {
				return pt.x > origin.x && pt.y > origin.y;
			}
			)
		<< std::endl;

	std::vector<double> magnitudes;
	std::transform(
		points.begin(),
		points.end(),
		std::back_inserter(magnitudes),
		[](point2d const& pt) {
			return std::sqrt(pt.x*pt.x + pt.y*pt.y);
		}
	);

	int numbers[] = { 5, 8, 11, 4, 9, 1, 2, 13, 17, 12 };
	int min_num = std::numeric_limits<int>::max();
	int max_num = std::numeric_limits<int>::min();
	std::for_each(&numbers[0], &numbers[sizeof(numbers) / sizeof(numbers[0])],
		[&](int n) {
		min_num = std::min(min_num, n);
		max_num = std::max(max_num, n);
	});

	return 0;
}