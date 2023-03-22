#include "..\include\vector.h"

/**
	* @brief Constructs a new Vector with a given size and value for all elements.
	* @param size The size of the vector.
	* @param value The value of all elements in the vector.
	*/
Vector::Vector(size_t size, int value) : m_size(size), m_capacity(size), m_value(new int[size])
{
	for (int i = 0; i < size; i++)
		m_value[i] = value;
}

/**
	 * @brief Destroys the Vector and frees the memory.
	 */
Vector::~Vector()
{
	delete[] m_value;
}

/**
	 * @brief Constructs a new Vector by copying an existing Vector.
	 * @param other The Vector to be copied.
	 */
Vector::Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_value(new int[m_capacity])
{
	for (int i = 0; i < m_capacity && i < m_size; i++) {
		m_value[i] = other.m_value[i];
	}
}
/**
	* @brief Constructs a new Vector by moving an existing Vector.
	* @param other The Vector to be moved.
	*/
Vector::Vector(Vector&& other) noexcept : m_size(other.m_size), m_capacity(other.m_capacity), m_value(other.m_value)
{
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_value = nullptr;
}

/**
	* @brief Copies the elements of one Vector into another Vector.
	* @param other The Vector to be copied.
	* @return A reference to the current Vector.
	*/
Vector& Vector::operator=(const Vector& other)
{
	if (this != &other)
	{
		Vector tmp(other);
		this->swap(tmp);
	}
	return *this;

}

/**
   * @brief Compares two vectors lexicographically.
   * @param other The Vector to be compared to.
   * @return A std::strong_ordering value that indicates the relationship between the two vectors.
   */

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

/**
	 * @brief Gets a reference to an element of the Vector by index.
	 * @param index The index of the element to retrieve.
	 * @return A reference to the element at the specified index.
	 * @throws std::out_of_range if the index is out of bounds.
	 */

int& Vector::operator[](const int index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("index out of range");
	}

	return m_value[index];
}

/**
   * @brief Gets a const reference to an element of the Vector by index.
   * @param index The index of the element to retrieve.
   * @return A const reference to the element at the specified index.
   * @throws std::out_of_range if the index is out of bounds.
   */

const int& Vector::operator[](const int index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("index out of range");
	}

	return m_value[index];
}

/**
	 * @brief Checks if two Vectors are equal.
	 * @param other The Vector to be compared to.
	 * @return True if the Vectors are equal, false otherwise.
	 */

const bool& Vector::operator==(const Vector& other) const noexcept
{
	if (other.m_size != m_size)
		return false;

	for (int i = 0; i < m_size; i++)
		if (other.m_value[i] != m_value[i])
			return false;

	return true;

}

/**
	* @brief Checks if two Vectors are not equal.
	* @param other The Vector to be compared to.
	* @return True if the Vectors are not equal, false otherwise.
	*/

const bool& Vector::operator!=(const Vector& other) const noexcept
{
	return !(this->operator==(other));
}

/**
	* @brief Swaps the contents of two Vectors.
	* @param other The Vector to swap with.
	*/

void Vector::swap(Vector& other) noexcept
{
	std::swap(m_value, other.m_value);
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
}

/**
* Returns a pointer to the underlying data of the vector.
* @return Pointer to the underlying data.
*/
int* Vector::data() const
{
	return m_value;
}

/**
* Checks if the vector is empty.
* @return True if the vector is empty, false otherwise.
*/
bool Vector::empty() const
{
	return (m_size == 0);
}

/**
* Returns the number of elements in the vector.
* @return Number of elements in the vector.
*/
int Vector::size() const
{
	return m_size;
}

/**
* Returns the capacity of the vector.
* @return Capacity of the vector.
*/
int Vector::capacity() const
{
	return m_capacity;
}

/**
* Clears the vector by setting its size, capacity, and underlying data to zero/nullptr.
*/
void Vector::clear()
{
	m_size = 0;
	m_capacity = 0;
	m_value = nullptr;
}

/**
* Reserves capacity for the vector.
* @param capacity The new capacity to reserve for the vector.
*/
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


/**
* Resizes the vector.
* @param size The new size of the vector.
* @param value The value to fill the new elements with.
*/
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

/**
* Appends a new element to the end of the vector.
* @param value The value of the new element to add to the vector.
*/
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

/**
* Removes the last element from the vector.
*/
void Vector::pop_back()
{
	if (m_size == 0)
		return;

	m_size--;

}

/**
* insert element to the vector.
*/
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

/**
* delete the last element from the vector.
*/
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
