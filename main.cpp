#include<string>
#include<cstring>
#include<ctime>
#include"data.h"
#include"utils/config.h"

namespace miniboost{
  enum TaskType{
    Train=0,
    Predict=1
  };

  class Task{
    public:
      Task(void){
        num_round=10;
        save_period=0;
        task=Train;
        model_in="NULL";
        model_out="NULL";
      }

      int Run(int argc,char *argv[]){
        utils::Config cfg(argv[1]);
        while(cfg.Next()){
          SetParam(cfg.GetName(),cfg.GetValue());
        }
        
        InitData();
        switch(task){
          case Train:
            TaskTrain();
            break;
          case Predict:
            TaskPredict();
            break;
        }
        return 0;
      }
      
      void SetParam(const char *name,const char *value){
        if(!strcmp("num_round",name)) num_round=atoi(value);
        if(!strcmp("save_period",name)) save_period=atoi(value);
        if(!strcmp("task",name)) task=atoi(value);
        if(!strcmp("train_path",name)) train_path=value;
        if(!strcmp("test_path",name)) test_path=value;
        if(!strcmp("model_in",name)) model_in=value;
        if(!strcmp("model_out",name)) model_out=value;
      }

      void InitData(void){
        switch(task){
          case Train:
            data.LoadText(train_path.c_str());
            break;
          case Predict:
            data.LoadText(test_path.c_str());
            break;
        }
      }

      void TaskTrain(void){
        const time_t start=time(NULL);
        unsigned long elapsed = 0;
        for(int i=0;i<num_round;i++){
          elapsed=(unsigned long)(time(NULL)-start);
          printf("Boosting round %d,%lu sec elapsed\n",i,elapsed);

        }
      }

      void TaskPredict(void){

      }

    private:
      int num_round;
      int save_period;
      int task;
      std::string train_path;
      std::string test_path;
      std::string model_in;
      std::string model_out;
      DMatrix data;
  };
};

int main(int argc,char *argv[]){
  miniboost::Task task;
  return task.Run(argc,argv);
}