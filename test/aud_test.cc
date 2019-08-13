// AUD

#include <vector>

#include "../aud/OpenMP3/src/iterator.cpp"
#include "../aud/OpenMP3/src/decoder.cpp"
#include "../aud/OpenMP3/src/requantize.cpp"
#include "../aud/OpenMP3/src/stereo.cpp"
#include "../aud/OpenMP3/src/synthesis.cpp"
#include "../aud/OpenMP3/src/huffman.cpp"
#include "../aud/OpenMP3/src/tables.cpp"

#include "../aud/mp3.hh"

const char* song1 = "C:/home/music/The Games We Play.mp3";
const char* song2 = "C:/home/music/I Can Dig It Baby.mp3";

int main(int argc, char** argv){
  mp3 song = load_mp3(song1);

  FILE* fp = fopen(song1, "r");
  size_t len = fread(buf, sizeof(uchar), BUFLEN, fp);
  fclose(fp);
  OpenMP3::Library openmp3;
  OpenMP3::Iterator it(openmp3, (OpenMP3::UInt8*)buf, len);
  float fbuf[2][1152];
  std::vector<float> channels[2];
  bool mono = true;
  OpenMP3::Decoder decoder(openmp3);
  OpenMP3::Frame frame;

  while(it.GetNext(frame)){
    OpenMP3::UInt nsamples = decoder.ProcessFrame(frame, fbuf);
    for(int ch = 0; ch < 2; ++ch){
      auto& channel = channels[ch];
      auto* data = fbuf[ch];
      for(OpenMP3::UInt idx = 0; idx < nsamples; ++idx)
        channel.push_back(*data++);
    }
    mono = mono && (frame.GetMode() == OpenMP3::kModeMono);
  }
  OpenMP3::UInt samples = channels[0].size();

  for(int i = 0; i < channels[0].size(); ++i)
    printf("%f %f\n", channels[0][i], channels[1][i]);

  return 0;
}
