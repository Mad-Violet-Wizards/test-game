#include "Compressor.hpp"

#include <filesystem>

#include "Directory.hpp"
#include "Log.hpp"

void OnyxTools::Compressor::Compressor::CompressPathes(const std::vector<std::string> &pathes)
{
  auto StringContains = [](const std::string &str, const std::string &substr)
  {
    return str.find(substr) != std::string::npos;
  };

  for (const std::string &path : pathes)
  {
    // We currently don't support compressing .JSON files
    // so skip them and save as they are in compressed output.
    if (StringContains(path, ".json"))
    {
      std::ifstream input(path, std::ios::in);

      std::ostringstream ss;
      ss << input.rdbuf();
      std::string data = ss.str();

      std::string newJsonDirectory = std::regex_replace(path, std::regex(ASSETS_DIRECTORY_INPUT), ASSETS_DIRECTORY_OUTPUT);

      std::ofstream output(newJsonDirectory, std::ios::out);

      output.write(reinterpret_cast<char*>(data.data()), data.size());

      input.close();
      output.close();

      continue;
    }

    std::ifstream input(path, std::ios::binary);

    std::ostringstream ss;
    ss << input.rdbuf();
    std::string data = ss.str();

    std::string compressed_output = Compressor::CompressString(data);

    std::string pathAfterCompression = ReplaceFileExtension(path, ".dat");

    pathAfterCompression = std::regex_replace(pathAfterCompression, std::regex(ASSETS_DIRECTORY_INPUT), ASSETS_DIRECTORY_OUTPUT);

    std::ofstream output(pathAfterCompression, std::ios::binary);

    output.write(reinterpret_cast<char*>(compressed_output.data()), compressed_output.size());

    input.close();
    output.close();
  }
}

void OnyxTools::Compressor::Compressor::DecompressPathes(const std::vector<std::string> &pathes)
{
  // TODO.
}

std::string OnyxTools::Compressor::Compressor::CompressString(const std::string &str, int compressionlevel)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (deflateInit(&zs, compressionlevel) != Z_OK)
        throw(std::runtime_error("deflateInit failed while compressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();           // set the z_stream's input

    int ret;
    char outbuffer[32768];
    std::string outstring;

    // retrieve the compressed bytes blockwise
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = deflate(&zs, Z_FINISH);

        if (outstring.size() < zs.total_out) {
            // append the block to the output string
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }
    } while (ret == Z_OK);

    deflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib compression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
    }

    return outstring;
}

std::string OnyxTools::Compressor::Compressor::DecompressString(const std::string &str)
{
    z_stream zs;                        // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = str.size();

    int ret;
    char outbuffer[32768];
    std::string outstring;

    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs, 0);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer,
                             zs.total_out - outstring.size());
        }

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") "
            << zs.msg;
        std::cout << oss.str() << "\n";
    }

    return outstring;
}

std::string OnyxTools::Compressor::Compressor::ReplaceFileExtension(const std::string &path, const std::string &newExtension)
{
  const size_t lastDot = path.find_last_of('.');
  std::string res = "";
  if (lastDot != std::string::npos) {
    res = path.substr(0, lastDot) + newExtension;
  }
  return res;
}