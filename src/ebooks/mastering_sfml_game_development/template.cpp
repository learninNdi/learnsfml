// #ifdef RUNNING_WINDOWS
// #define WIN32_LEAN_AND_MEAN // reduces the number of other headers that get included in the process
// #endif
// #include <windows.h>
// #include <shlwapi.h>
// #include <random>
// #include <mutex>
// #include <pthread.h>
// #include <SFML/Graphics/Rect.hpp>
// #include <SFML/Graphics/Text.hpp>

// inline std::string GetWorkingDirectory()
// {
//     HMODULE hModule = GetModuleHandle(nullptr);
//     if (!hModule)
//         return "";

//     char path[256];
//     GetModuleFileName(hModule, path, sizeof(path));
//     PathRemoveFileSpec(path);
//     strcat_s(path, "");

//     return std::string(path);
// }

// inline std::vector<std::string> GetFileList(
//     const std::string &l_directory,
//     const std::string &l_search = "*.*")
// {
//     std::vector<std::string> files;
//     if (l_search.empty())
//         return files;

//     std::string path = l_directory + l_search;
//     WIN32_FIND_DATA data;
//     HANDLE found = FindFirstFile(path.c_str(), &data);
//     if (found == INVALID_HANDLE_VALUE)
//         return files;

//     do
//     {
//         if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
//             files.emplace_back(data.cFileName);
//     } while (FindNextFile(found, &data));
//     FindClose(found);

//     return files;
// }

// inline std::vector<std::string> GetFileList(
//     const std::string &l_directory,
//     const std::string &l_search = "*.*")
// {
//     std::vector<std::string> files;

//     DIR *dpdf;
//     dpdf = opendir(l_directory.c_str());
//     if (!dpdf)
//         return files;

//     if (l_search.empty())
//         return files;

//     std::string search = l_search;
//     if (search[0] == '*')
//         search.erase(search.begin());

//     if (search[search.length() - 1] == '*')
//         search.pop_back();

//     struct dirent *epdf;
//     while (epdf = readdir(dpdf))
//     {
//         std::string name = epdf->d_name;
//         if (epdf->d_type == DT_DIR)
//             continue;

//         if (l_search != "*.*")
//         {
//             if (name.length() < search.length())
//                 continue;

//             if (search[0] == '.')
//             {
//                 if (name.compare(name.length() - search.length(), search.length(), search) != 0)
//                     continue;
//             }
//             else if (name.find(search) == std::string::npos)
//                 continue;
//         }

//         files.emplace_back(name);
//     }

//     closedir(dpdf);

//     return files;
// }

// inline void ReadQuotedStrings(std::stringstream &l_stream, std::string &l_string)
// {
//     l_stream >> l_string;
//     if (l_string.at(0) == '"')
//     {
//         while (l_string.at(l_string.length() - 1) != '"' || !l_stream.eof())
//         {
//             std::string str;
//             l_stream >> str;
//             l_string.append(" " + str);
//         }
//     }

//     l_string.erase(std::remove(l_string.begin(), l_string.end(), '"'), l_string.end());
// }

// template <class T>
// inline T Interpolate(float tBegin, float eEnd, const T &begin_val, const T &end_val, float tX)
// {
//     return static_cast<T>((((end_val - begin_val) / (tEnd - tBegin)) * (tX - tBegin)) + begin_val);
// }

// inline float GetSFMLTextMaxHeight(const sf::Text &l_text)
// {
//     auto charSize = l_text.getCharacterSize();
//     auto font = l_text.getFont();
//     auto string = l_text.getString().toAnsiString();
//     bool bold = (l_text.getStyle() & sf::Text::Bold);
//     float max = 0.f;
//     for (size_t i = 0; i < string.length(); ++i)
//     {
//         sf::Uint32 character = string[i];
//         auto glyph = font->getGlyph(character, charSize, bold);
//         auto height = glyph.bounds.height;
//         if (height <= max)
//             continue;

//         max = height;
//     }

//     return max;
// }

// inline void CenterSFMLText(sf::Text &l_text)
// {
//     sf::FloatRect rect = l_text.getLocalBounds();
//     auto maxHeight = Utils::GetSFMLTextMaxHeight(l_text);
//     l_text.setOrigin({rect.left + (rect.width * 0.5f),
//                       rect.top + ((maxHeight >= rect.height ? maxHeight * 0.5f : rect.height * 0.5f))});
// }

// class RandomGenerator
// {
// public:
//     RandomGenerator() : m_engine(m_device())
//     {
//     }

//     int Generate(int l_min, int l_max)
//     {
//         std::lock_guard<std::mutex> lock(m_mutex);
//         if (l_min > l_max)
//             std::swap(l_min, l_max);

//         if (l_min != m_intDistribution.min() || l_max != m_intDistribution.max())
//             m_intDistribution = std::uniform_int_distribution<int>(l_min, l_max);

//         return m_intDistribution(m_engine);
//     }

//     float Generate(float l_min, float l_max)
//     {
//         std::lock_guard<std::mutex> lock(m_mutex);
//         if (l_min > l_max)
//             std::swap(l_min, l_max);

//         if (l_min != m_floatDistribution.min() || l_max != m_floatDistribution.max())
//             m_floatDistribution = std::uniform_real_distribution<float>(l_min, l_max);

//         return m_floatDistribution(m_engine);
//     }

//     float operator()(float l_min, float l_max)
//     {
//         return Generate(l_min, l_max);
//     }

//     int operator()(int l_min, int l_max)
//     {
//         return Generate(l_min, l_max);
//     }

// private:
//     std::random_device m_device;
//     std::mt19937 m_engine;
//     std::uniform_int_distribution<int> m_intDistribution;
//     std::uniform_real_distribution<float> m_floatDistribution;
//     std::mutex m_mutex;
// }
