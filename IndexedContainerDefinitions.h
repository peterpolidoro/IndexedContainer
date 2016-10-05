// ----------------------------------------------------------------------------
// IndexedContainerDefinitions.h
//
//
// Authors:
// Peter Polidoro polidorop@janelia.hhmi.org
// ----------------------------------------------------------------------------
#ifndef INDEXED_CONTAINER_DEFINITIONS_H
#define INDEXED_CONTAINER_DEFINITIONS_H


template <typename T, int max_size_>
IndexedContainer<T,max_size_>::IndexedContainer()
{
  clear();
}

template <typename T, int max_size_>
T& IndexedContainer<T, max_size_>::operator[](const int index)
{
  if ((index >= 0) && !available_[index])
  {
    return values_[index];
  }
}

template <typename T, int max_size_>
T& IndexedContainer<T, max_size_>::at(const int index)
{
  if ((index >= 0) && !available_[index])
  {
    return values_.at(index);
  }
}

template <typename T, int max_size_>
void IndexedContainer<T, max_size_>::clear()
{
  size_ = 0;
  for (int index=0; index<max_size_; ++index)
  {
    available_[index] = true;
  }
}

template <typename T, int max_size_>
int IndexedContainer<T, max_size_>::add(const T &value)
{
  if (size_ < max_size_)
  {
    bool found_available = false;
    int index = -1;
    while (!found_available && (++index < max_size_))
    {
      found_available = available_[index];
    }
    if (found_available)
    {
      values_[index] = value;
      available_[index] = false;
      ++size_;
      return index;
    }
  }
  return -1;
}

template <typename T, int max_size_>
void IndexedContainer<T, max_size_>::remove(const int index)
{
  if ((index >= 0) && (!available_[index]))
  {
    available_[index] = true;
    --size_;
  }
}

template <typename T, int max_size_>
bool IndexedContainer<T, max_size_>::indexHasValue(const int index)
{
  if (index < 0)
  {
    return false;
  }
  return !available_[index];
}

template <typename T, int max_size_>
int IndexedContainer<T, max_size_>::size()
{
  return size_;
}

template <typename T, int max_size_>
int IndexedContainer<T, max_size_>::max_size()
{
  return max_size_;
}

template <typename T, int max_size_>
bool IndexedContainer<T, max_size_>::empty()
{
  return size_ == 0;
}

template <typename T, int max_size_>
bool IndexedContainer<T, max_size_>::full()
{
  return size_ == max_size_;
}

#endif
