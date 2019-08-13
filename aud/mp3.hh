// MP3

#ifndef mp3_hh
#define mp3_hh

#include <stdio.h>
#include <vector>

#define uchar unsigned char
#define vec std::vector
#define pb push_back


enum mp3channel {
  STEREO
, JOINT_STEREO
, DUAL
, MONO
};

struct mp3frame {
  mp3channel channel;
  bool pad;
  int bitrate, frequency, jsmode;
  vec<uchar> data;
};

struct mp3 {
  vec<mp3frame> frames;
};

const int BUFLEN = 100000000;
uchar buf[BUFLEN+1]; // Almost 100Mb

mp3 load_mp3(const char* fpath){
  uchar m;
  int i,j,k,n;
  mp3 r;

  FILE* fp = fopen(fpath, "r");
  size_t len = fread(buf, sizeof(uchar), BUFLEN, fp);
  fclose(fp);
  printf("File %s opened with length %d bytes\n", fpath, len);

  // Frame header
  j = -1;
  for(i = 0; i < len-3; ++i){
    mp3frame frame;

    // Constant identifier
    m = (uchar)((1 << 8) - 1);
    if(buf[i] != m) continue;
    m ^= (uchar)((1 << 5) - 1);
    if((buf[i+1] & m) != m) continue;
    m = (uchar)((1 << 5) - 1) ^ (uchar)((1 << 3) - 1);
    if((buf[i+1] & m) != m) continue;
    m = (uchar)((1 << 3) - 1) ^ 1;
    if((buf[i+1] & m) != (m ^ (1 << 2))) continue;
    if((buf[i+1] & 1) != 1) continue;

    // Bitrate
    m = (uchar)((1 << 8) - 1) ^ (uchar)((1 << 4) - 1);
    n = (buf[i+2] & m) >> 4;

    if     (n == 1)  frame.bitrate = 32;
    else if(n == 2)  frame.bitrate = 40;
    else if(n == 3)  frame.bitrate = 48;
    else if(n == 4)  frame.bitrate = 56;
    else if(n == 5)  frame.bitrate = 64;
    else if(n == 6)  frame.bitrate = 80;
    else if(n == 7)  frame.bitrate = 96;
    else if(n == 8)  frame.bitrate = 112;
    else if(n == 9)  frame.bitrate = 128;
    else if(n == 10) frame.bitrate = 160;
    else if(n == 11) frame.bitrate = 192;
    else if(n == 12) frame.bitrate = 224;
    else if(n == 13) frame.bitrate = 256;
    else if(n == 14) frame.bitrate = 320;
    else continue;

    // Frequency
    m = (uchar)((1 << 4) - 1) ^ (uchar)((1 << 2) - 1);
    n = (buf[i+2] & m) >> 2;
    if     (n == 0) frame.frequency = 44100;
    // else if(n == 1) r.frequency = 48000;
    // else if(n == 2) r.frequency = 32000;
    else continue;

    // Padding
    m = (uchar)(1 << 1);
    n = (buf[i+2] & m) >> 1;
    frame.pad = (n == 1);

    // Channel
    m = (uchar)((1 << 8) - 1) ^ (uchar)((1 << 6) - 1);
    n = (buf[i+3] & m) >> 6;
    if     (n == 0) frame.channel = STEREO;
    else if(n == 1) frame.channel = JOINT_STEREO;
    else if(n == 2) frame.channel = DUAL;
    else if(n == 3) frame.channel = MONO;
    else continue;

    // Mode Extension for Joint Stereo
    m = (uchar)((1 << 6) - 1) ^ (uchar)((1 << 4) - 1);
    n = (buf[i+3] & m) >> 4;
    frame.jsmode = n;

    // Copyright
    m = (uchar)(1 << 3);
    n = (buf[i+3] & m) >> 3;

    // Original
    m = (uchar)(1 << 2);
    n = (buf[i+3] & m) >> 2;

    // Emphasis
    m = (uchar)((1 << 2) - 1);
    n = buf[i+3] & m;

    // Data may still look like a header - compare against first frame length
    if(r.frames.size() > 1 && i-j-4 < r.frames[0].data.size()-1) continue;

    // Previous frame's data
    if(r.frames.size() > 0)
      for(k = j+4; k < i; ++k)
        r.frames.back().data.pb(buf[k]);

    r.frames.pb(frame);
    j = i;
  }

  // Final frame's data
  for(k = j+4; k < len; ++k)
    r.frames.back().data.pb(buf[k]);

  // Validate frame sizes
  printf("%d total frames\n", r.frames.size());
  for(i = 0; i < r.frames.size(); ++i)
    if(r.frames[i].data.size() < r.frames[0].data.size()-1 ||
       r.frames[i].data.size() > r.frames[0].data.size()+1)
      printf("Bad frame[%d]: len = %d\n", i, r.frames[i].data.size());

  return r;
}


#endif
