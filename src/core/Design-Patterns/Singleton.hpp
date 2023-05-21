#pragma once

template <typename C>
class Singleton
{
  public:

    using class_type = C;

    template<typename ...Args>
    static void Create(Args&&... args)
    {
      SingletonData& data = GetData();

      if (!data.m_valid)
      {
        data.m_instance = class_type(std::forward<Args>(args)...);
        data.m_valid = true;
      }
    }

    static void Destroy()
    {
      SingletonData& data = GetData();

      if (data.m_valid)
      {
        data.m_instance.~class_type();
        data.m_valid = false;
      }
    }

    static class_type& Instance()
    {
      SingletonData& data = GetData();

      if (!data.m_valid)
      {
        throw std::runtime_error("Singleton not created.");
      }

      return data.m_instance;
    }

    static bool IsValid()
    {
      return GetData().m_valid;
    }

  private:

    Singleton();
    Singleton(const Singleton&);
    Singleton& operator=(const Singleton&);

  private:

    struct SingletonData
    {
      SingletonData()
      : m_valid(false)
      {}

      class_type m_instance;
      bool m_valid;
    };

    static SingletonData& GetData()
    {
      static SingletonData s_data;

      return s_data;
    }
};