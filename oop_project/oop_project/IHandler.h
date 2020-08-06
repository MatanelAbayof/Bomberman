#pragma once
//---- include section ------
#include <functional>
#include <vector>

//---- using section --------
using std::vector;

/*
 * IHandler interface
 */
template <class T>
class IHandler
{
public:
	// type of handler
	using Listener = std::function<void(T&)>;
	// remove listeners
	void removeListeners();
	// listen to event
	void addListener(Listener listener);
	// call all listeners
	void callListeners(T &t);
private:
	// vector of functions that listen to event
	vector<Listener> m_ListenerList;
};

