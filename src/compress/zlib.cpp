#include <fc/compress/zlib.hpp>

#ifdef FC_USE_FULL_ZLIB
# include <zlib.h>
# include <memory>
# include <fstream>
#else
# include "miniz.c"
#endif

namespace fc
{
#ifdef FC_USE_FULL_ZLIB
  string zlib_compress(const string& in)
  {
    unsigned long bufferLen = compressBound(in.size());
    std::unique_ptr<char[]> buffer(new char[bufferLen]);
    compress((unsigned char*)buffer.get(), &bufferLen, (const unsigned char*)in.c_str(), in.size());
    string result(buffer.get(), bufferLen);
    return result;
  }

  void gzip_compress_file(const path& input_filename, const path& output_filename)
  {
    std::ifstream infile(input_filename.generic_string().c_str(), std::ios::binary);
    std::ofstream outfile(output_filename.generic_string().c_str(), std::ios::out | std::ios::binary);
    unsigned bufferLen = 1024 * 1024;
    std::unique_ptr<char[]> inputBuffer(new char[bufferLen]);
    std::unique_ptr<char[]> outputBuffer(new char[bufferLen]);

    z_stream outputStream;
    outputStream.zalloc = 0;
    outputStream.zfree = 0;
    outputStream.opaque = 0;
    int windowBits = 15;
    int GZIP_ENCODING = 16;

    deflateInit2(&outputStream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, windowBits | GZIP_ENCODING,
                 8, Z_DEFAULT_STRATEGY);

    if (infile)
    {
      do
      {
        infile.read(inputBuffer.get(), bufferLen);
        int bytesRead = infile.gcount();
        if (bytesRead == 0)
          break;
        outputStream.avail_in = bytesRead;
        outputStream.next_in = (unsigned char*)inputBuffer.get();
        do
        {
          outputStream.avail_out = bufferLen;
          outputStream.next_out = (unsigned char*)outputBuffer.get();
          deflate(&outputStream, Z_NO_FLUSH);
          int compressedBytesGenerated = bufferLen - outputStream.avail_out;
          outfile.write(outputBuffer.get(), compressedBytesGenerated);
        }
        while (outputStream.avail_out == 0);
      }
      while (infile);
    }
    do
    {
      outputStream.avail_out = bufferLen;
      outputStream.next_out = (unsigned char*)outputBuffer.get();
      deflate(&outputStream, Z_FINISH);
      int compressedBytesGenerated = bufferLen - outputStream.avail_out;
      outfile.write(outputBuffer.get(), compressedBytesGenerated);
    }
    while (outputStream.avail_out == 0);
    deflateEnd(&outputStream);
  }
#else
  string zlib_compress(const string& in)
  {
    size_t compressed_message_length;
    char* compressed_message = (char*)tdefl_compress_mem_to_heap(in.c_str(), in.size(), &compressed_message_length,  TDEFL_WRITE_ZLIB_HEADER | TDEFL_DEFAULT_MAX_PROBES);
    string result(compressed_message, compressed_message_length);
    free(compressed_message);
    return result;
  }
#endif
}
