#pragma once

#include <fc/string.hpp>
#ifdef FC_USE_FULL_ZLIB
# include <fc/filesystem.hpp>
#endif

namespace fc 
{

  string zlib_compress(const string& in);
#ifdef FC_USE_FULL_ZLIB
  void gzip_compress_file(const path& input_filename, const path& output_filename);
#endif

} // namespace fc
