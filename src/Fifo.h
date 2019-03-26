/**
 * @file Fifo.h
 * @brief Implementation of the Fifo class
 */

#ifndef FIFO_INCLUDED
#define FIFO_INCLUDED

#include <exception>
#include <queue>
#include <string>

#include "Mutex.h"

/**
 * @brief A template class that implements a thread-safe FIFO data structure
 *
 * Internally, it relies on C++'s `std::queue` template class.
 */
template <typename T> class Fifo {
private:
	/**
	 * @brief The underlying data structure (`std::queue`)
	 */
	std::queue<T> elements;
	/**
	 * @brief The mutex to protect from concurrent accesses
	 */
	Mutex mtx;

public:
	/**
	 * @brief A nested exception class
	 *
	 * This exception is returned when attempting to retrieve an object from an
	 * empty queue with a timeout.
	 */
	class EmptyException : std::exception {
	public:
		/**
		 * @brief Return a character string describing the error
		 */
		const char *what() const noexcept;
	};

public:
	/**
	 * @brief Constructor
	 */
	Fifo();
	/**
	 * @brief Destructor
	 */
	~Fifo();
	/**
	 * @brief Push an element to the queue
	 *
	 * @param element the element to push
	 */
	void push(T element);
	/**
	 * @brief Pop an element from the queue
	 *
	 * @return the element popped from the queue
	 */
	T pop();
	/**
	 * @brief Pop an element from the queue (with a timeout)
	 * If the operation fails, the method throws an EmptyException exception.
	 *
	 * @return the element popped from the queue
	 */
	T pop(double timeout_ms);
};

template <typename T> Fifo<T>::Fifo() : elements(), mtx() {}
template <typename T> Fifo<T>::~Fifo() {}

template <typename T> void Fifo<T>::push(T element) {
	Mutex::Lock lck(mtx);
	elements.push(element);
}

template <typename T> T Fifo<T>::pop() {
	Mutex::Lock lck(mtx);
	while (elements.size() == 0) {
		lck.wait();
	}
	return elements.pop();
}

template <typename T> T Fifo<T>::pop(double timeout_ms) {
	Mutex::Lock lck(mtx);
	if (elements.size() == 0) {
		lck.wait(timeout_ms);
	}
	if (elements.size() > 0) {
		return elements.pop();
	} else {
		throw Fifo<T>::EmptyException();
	}
}

template <typename T>
const char *Fifo<T>::EmptyException::what() const noexcept {
	return "Timed out while attempting to pop an element (empty queue)";
}

#endif