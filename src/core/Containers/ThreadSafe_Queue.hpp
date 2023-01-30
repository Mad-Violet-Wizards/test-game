#pragma once

#include <mutex>
#include <queue>

namespace ThreadSafe
{
  template <typename T>
  class Queue
  {

    public:

      Queue() = default;
      ~Queue() = default;

    // TODO: Implement copy & move constructors & assignemnt operator.
    Queue(const Queue &other) = delete;
    Queue(Queue &&other) = delete;

    Queue &operator=(const Queue &other) = delete;
    Queue &operator=(Queue &&other) = delete;

    void Push(T item)
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      m_queue.push(item);
    }

    [[nodiscard]] T Dequeue()
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      T item = m_queue.front();
      m_queue.pop();
      return item;
    }

    [[nodiscard]] bool Empty() const noexcept
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_queue.empty();
    }

    [[nodiscard]] size_t Size() const noexcept
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      return m_queue.size();
    }
            

    private:

        mutable std::mutex m_mutex;
        std::queue<T> m_queue;
  };
}