#ifndef MINIBOOST_UTILS_H
#define MINIBOOST_UTILS_H

#include<cstdio>
#include<cstdlib>

namespace miniboost{
  namespace utils{
    inline void Error(const char *msg){
      fprintf(stderr,"Error:%s\n",msg);
    }

    inline void Assert(bool expr){
      if(!expr) Error("AssertError");
    }

    inline void Assert(bool expr,const char *msg){
      if(!expr) Error(msg);
    }

    inline void Warning(const char *msg){
      fprintf(stderr,"Warning:%s\n",msg);
    }

    inline FILE *FopenCheck(const char *fname,const char *flag){
      FILE *fp=fopen(fname,flag);
      if(fp==NULL){
        fprintf(stderr,"Cannot open file \"%s\"\n",fname);
        exit(-1);
      }
      return fp;
    }
  };
};

#endif