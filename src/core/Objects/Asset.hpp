#pragma once

template<typename T>
concept AssetAcceptableType = requires(T type)
{
  { std::is_same<T, sf::Texture>::value || 
    std::is_same<T, sf::Font>::value };
};

template<AssetAcceptableType T>
class Asset
{
  public:

    Asset() = default;

    Asset(uint32_t size)
      : m_asset(nullptr)
      , m_data(size) { };

    Asset(const std::shared_ptr<T> &asset, const std::vector<uint8_t> &data)
      : m_asset(asset)
      , m_data(data) { };

    Asset(const std::vector<uint8_t> &data)
    : m_asset(nullptr)
    , m_data(data) { };

    ~Asset() = default;

    Asset(const Asset &) = delete;
    Asset(Asset &&) = delete;

    Asset &operator=(const Asset &) = delete;
    Asset &operator=(Asset &&) = delete;

    void InitializeFromInternalData()
    {
      m_asset = std::make_shared<T>();

      if (!m_asset->loadFromMemory(m_data.data(), m_data.size()))
      {
        CONSOLE_LOG_ERROR("Failed to load asset.");
      }
    }

    void InitializeFromExternalData(const std::string &filePath)
    {
      m_asset = std::make_shared<T>();

      if (!m_asset->loadFromFile(filePath))
      {
        CONSOLE_LOG_ERROR("Failed to load asset.");
      }
    }

    void SetData(const std::vector<uint8_t> &data) { m_data = data; }

    std::shared_ptr<T> &GetAsset() { return m_asset; }
    const std::vector<uint8_t> &GetData() const { return m_data; }
    std::vector<uint8_t> &GetData() { return m_data; }

  std::shared_ptr<T> m_asset;
  std::vector<uint8_t> m_data;
};