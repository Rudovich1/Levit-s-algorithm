#include "GraphGenerator.h"
#include "Levit.h"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>  

void graphGeneratorTest()
{
	std::cout << std::setprecision(20);
	std::cout << std::setw(20) << "Random graph V ~ E" << '\t'
		<< std::setw(20) << "Random graph V^1.5 ~ E" << '\t'
		<< std::setw(20) << "Random graph V^2 ~ E" << '\t'
		<< std::setw(20) << "Worst case" << '\t'
		<< std::setw(20) << "City block distance" << '\n';

	for (int i = 0; i < 100; ++i)
	{
		auto start = std::chrono::system_clock::now();
		GraphGenerator::randomGraph_V((i+1)*10);
		auto stop = std::chrono::system_clock::now();
		size_t res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';

		start = std::chrono::system_clock::now();
		GraphGenerator::randomGraph_V15((i + 1) * 10);
		stop = std::chrono::system_clock::now();
		res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';

		start = std::chrono::system_clock::now();
		GraphGenerator::randomGraph_V2((i + 1) * 10);
		stop = std::chrono::system_clock::now();
		res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';

		start = std::chrono::system_clock::now();
		GraphGenerator::levitWorstCase((i + 1) * 10);
		stop = std::chrono::system_clock::now();
		res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';

		start = std::chrono::system_clock::now();
		GraphGenerator::randomGraph_cityBlockDistance((i + 1) * 10);
		stop = std::chrono::system_clock::now();
		res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';
	}
}

void levitTest()
{
	std::cout << std::setprecision(20);
	std::cout << std::setw(20) << "Random graph V ~ E" << '\t'
		<< std::setw(20) << "Random graph V^1.5 ~ E" << '\t'
		<< std::setw(20) << "Random graph V^2 ~ E" << '\t'
		<< std::setw(20) << "Worst case" << '\t'
		<< std::setw(20) << "City block distance" << '\n';

	for (int i = 2; i <= 10000; i *= 2)
	{
		auto graph = GraphGenerator::randomGraph_V(i);
		auto start = std::chrono::system_clock::now();
		Levit::count(graph);
		auto stop = std::chrono::system_clock::now();
		size_t res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';

		graph = GraphGenerator::randomGraph_V15(i);
		start = std::chrono::system_clock::now();
		Levit::count(graph);
		stop = std::chrono::system_clock::now();
		res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';

		graph = GraphGenerator::randomGraph_V2(i);
		start = std::chrono::system_clock::now();
		Levit::count(graph);
		stop = std::chrono::system_clock::now();
		res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';

		graph = GraphGenerator::levitWorstCase(i);
		start = std::chrono::system_clock::now();
		Levit::count(graph);
		stop = std::chrono::system_clock::now();
		res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';

		graph = GraphGenerator::randomGraph_cityBlockDistance(i);
		start = std::chrono::system_clock::now();
		Levit::count(graph);
		stop = std::chrono::system_clock::now();
		res = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << std::setw(20) << res << '\t';
	}
}


int main()
{
	levitTest();
}