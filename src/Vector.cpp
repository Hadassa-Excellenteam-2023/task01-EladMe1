#include "..\include\vector.h"

Vector::Vector(size_t size, int value) : m_size(size), m_capacity(size), m_value(new int[size])
{
	for (int i = 0; i < size; i++)
		m_value[i] = value;
}

//destractor
Vector::~Vector()
{
	delete[] m_value;
}

//copy constractor
Vector::Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_value(new int[m_capacity])
{
	for (int i = 0; i < m_capacity && i < m_size; i++) {
		m_value[i] = other.m_value[i];
	}
}

//moving constractor
Vector::Vector(Vector&& other) noexcept : m_size(other.m_size), m_capacity(other.m_capacity), m_value(other.m_value)
{
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_value = nullptr;
}

Vector& Vector::operator=(const Vector& other)
{
	if (this != &other)
	{
		Vector tmp(other);
		this->swap(tmp);
	}
	return *this;

}

std::strong_ordering Vector::operator<=>(const Vector& other) const noexcept
{
	
	if (*this == other) {
		return std::strong_ordering::equal; 
	}
	
	else if (m_size < other.m_size) {
		return std::strong_ordering::less;
	}
	else {
		return std::strong_ordering::greater; 
	}
}



int& Vector::operator[](const int index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("index out of range");
	}

	return m_value[index];
}

const int& Vector::operator[](const int index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("index out of range");
	}

	return m_value[index];
}

const bool& Vector::operator==(const Vector& other) const noexcept
{
	if (other.m_size != m_size)
		return false;

	for (int i = 0; i < m_size; i++)
		if (other.m_value[i] != m_value[i])
			return false;

	return true;

}

const bool& Vector::operator!=(const Vector& other) const noexcept
{
	return !(this->operator==(other));
}


void Vector::swap(Vector& other) noexcept
{
	std::swap(m_value, other.m_value);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

int* Vector::data() const
{
	return m_value;
}

bool Vector::empty() const
{
	return (m_size == 0);
}

int Vector::size() const
{
	return m_size;
}

int Vector::capacity() const
{
	return m_capacity;
}

void Vector::clear()
{
	m_size = 0;
	m_capacity = 0;
	m_value = nullptr;
}


void Vector::reserve(size_t capacity)
{
	if (capacity <= m_capacity) {
		return;
	}

	int* new_value = new int[capacity];

	for (size_t i = 0; i < m_size; ++i) {
		new_value[i] = std::move(m_value[i]);
	}

	delete[] m_value;
	m_value = new_value;
	m_capacity = capacity;
}



void Vector::resize(int size, int value)
{
	if (size > m_size) {
		if (size > m_capacity) {
			reserve(size);
		}
		for (size_t i = m_size; i < size; ++i) {
			m_value[i] = value;
		}
	}
	m_size = size;
}

void Vector::push_back(int&& value)
{
	if (m_size == 0)
		reserve(1);

	if (m_size == m_capacity)
		if (m_size < CAPACITY)
			reserve(m_capacity * 2);
		else
			reserve(m_capacity * 1.5);

	m_value[m_size++] = value;

}

void Vector::pop_back()
{
	if (m_size == 0)
		return;

	m_size--;

}

void Vector::insert(size_t index, int value)
{
	try {
		if (index > m_size) {
			throw std::out_of_range("index out of range");
		}

		if (m_size == m_capacity) {
			reserve(m_capacity * 2);
		}

		
		for (int i = m_size - 1; i >= static_cast<int>(index); i--) {
			m_value[i + 1] = m_value[i];
		}

		m_value[index] = value;

		m_size++;
	}
	catch (const std::out_of_range& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}
}


void Vector::erase(int index)
{
	try {
		if (index >= m_size) {
			throw std::out_of_range("index out of range");
		}

		
		for (int i = index; i < m_size - 1; i++) {
			m_value[i] = m_value[i + 1];
		}

		m_size--;
	}
	catch (const std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}
}
