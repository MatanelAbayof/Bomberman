//---- include section ------
#include "IHandler.h"
#include <iostream>

template<class T>
void IHandler<T>::removeListeners()
{
	m_ListenerList.clear();
}

template <class T>
void IHandler<T>::addListener(Listener listener)
{
	m_ListenerList.push_back(listener);
}

template<class T>
void IHandler<T>::callListeners(T &t)
{
	for (Listener &listener : m_ListenerList)
		listener(t);
}

// Explicit instantiation, because the compiler is stupid!
#include "View.h"
template class IHandler<View>;  
