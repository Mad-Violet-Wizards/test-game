#pragma once


class ThreadTask
{

  public:

    ThreadTask();
    ~ThreadTask() = default;

    template<typename F, typename... Args>
    void Assign(F&& f, Args&&... args)
    {
      m_task = std::function{[f, args...](){ return f(args...); }};
    }

    void Run();

    bool IsFinished() const;
 
  private:

    std::function<void()> m_task;

    mutable sf::Mutex m_mutex;
    volatile bool m_finished;
};