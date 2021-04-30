#ifndef MINIBOOST_CONFIG_H
#define MINIBOOST_CONFIG_H

#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<yaml-cpp/yaml.h>

namespace miniboost{
  namespace utils{
    class Config{
      public:
        Config(const char *fname){
          YAML::Node cfg=YAML::LoadFile(fname);
          for(auto it=cfg.begin();it!=cfg.end();it++){
            names.push_back(it->first.as<std::string>());
            values.push_back(it->second.as<std::string>());
          }
          cfg_ptr=0,cfg_end=names.size();
        }

        bool Next(){
          if(cfg_ptr==cfg_end) return false;
          cfg_ptr++;
          return true;
        }

        const char* GetName(void){
          return names[cfg_ptr-1].c_str();
        }
        
        const char* GetValue(void){
          return values[cfg_ptr-1].c_str();
        }

      private:
        std::vector<std::string> names;
        std::vector<std::string> values;
        size_t cfg_ptr,cfg_end;
    };
  };
};
#endif