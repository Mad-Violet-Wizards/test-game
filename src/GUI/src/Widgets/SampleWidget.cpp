#include <iostream>

#include "SampleWidget.hpp"

SampleWidget::SampleWidget()
{
	std::cout << "[Sample Widget] created!\n";
}

SampleWidget::~SampleWidget()
{
	std::cout << "[Sample Widget] destroyed!\n";
}