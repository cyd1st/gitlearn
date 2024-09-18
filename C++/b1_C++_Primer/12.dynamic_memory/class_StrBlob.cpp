#include "class_StrBlob.h"

StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()) {};
StrBlob::StrBlob(std::initializer_list<std::string> sl): 
	data(std::make_shared<std::vector<std::string>>(sl)) {};

void StrBlob::check(size_type i, const std::string &msg) const
{
	if (i >= data->size())
		throw std::out_of_range(msg);
}

const std::string &StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

const std::string &StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back()
{
	check(0, "pop_back on rmpty StrBlob");
	data->pop_back();
}
