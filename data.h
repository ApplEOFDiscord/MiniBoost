#ifndef MINIBOOST_DATA_H
#define MINIBOOST_DATA_H

#include<cstdio>
#include<vector>
#include<algorithm>
#include"utils/utils.h"

namespace miniboost{
  class DMatrix{
    public:
      class Entry{
        public:
          unsigned index;
          float value;

          Entry(void){}

          Entry(unsigned index,float value):index(index),value(value){}

          static bool CmpEntry(const Entry& lhs,const Entry& rhs){
            return lhs.value<rhs.value;
          }
      };

      class DataIter{
        public:
          DataIter(const Entry *data_ptr,const Entry *data_end)
              :data_ptr(data_ptr),data_end(data_end){}

          bool Next(void){
            if(data_ptr==data_end) return false;
            data_ptr++;
            return true;
          }

          unsigned GetIndex(void) const{
            return data_ptr->index;
          }

          float GetValue(void) const{
            return data_ptr->value;
          }

        private:
          const Entry *data_ptr,*data_end;
      };

      DMatrix(void){
        row_ptr.push_back(0);
      }
      
      size_t AddRow(const std::vector<unsigned> findex,
          const std::vector<float> fvalue){
        for(size_t i=0;i<findex.size();i++){
          row_data.push_back(Entry(findex[i],fvalue[i]));
        }
        row_ptr.push_back(row_ptr.back()+findex.size());
        return row_ptr.size()-2;
      }

      size_t NumRow(void) const{
        return row_ptr.size()-1;
      }

      DataIter GetRow(size_t rid){
        return DataIter(&row_data[row_ptr[rid]]-1,&row_data[row_ptr[rid+1]]-1);
      }

      size_t NumCol(void) const{
        return col_ptr.size()-1;
      }

      DataIter GetCol(size_t cid){
        return DataIter(&col_data[col_ptr[cid]]-1,&col_data[col_ptr[cid+1]]-1);
      }

      void RowToCol(unsigned ncol){
        std::vector<std::vector<Entry>> col_temp(ncol);
        size_t nrow=NumRow();
        for(size_t i=0;i<nrow;i++){
          DataIter it=GetRow(i);
          while(it.Next()){
            unsigned index=it.GetIndex();
            float value=it.GetValue();
            col_temp[index].push_back(Entry(i,value));
          }
        }
        
        col_ptr.push_back(0);
        for(unsigned i=0;i<ncol;i++){
          col_ptr.push_back(col_ptr.back()+col_temp[i].size());
          for(Entry e:col_temp[i]){
            col_data.push_back(e);
          }
        }

        for(size_t i=0;i<ncol;i++){
          std::sort(&col_data[col_ptr[i]],&col_data[col_ptr[i+1]],Entry::CmpEntry);
        }
      }

      void LoadText(const char *fname){
        char tmp[512];
        float label;
        bool first_row=true;
        unsigned max_findex=0;
        std::vector<unsigned> findex;
        std::vector<float> fvalue;

        FILE *fp=utils::FopenCheck(fname,"r");
        while(fscanf(fp,"%s",tmp)==1){
          unsigned index;float value;
          if(sscanf(tmp,"%u:%f",&index,&value)==2){
            max_findex=std::max(max_findex,index);
            findex.push_back(index);
            fvalue.push_back(value);
          }
          else{
            if(!first_row){
              labels.push_back(label);
              AddRow(findex,fvalue);
            }
            findex.clear();
            fvalue.clear();
            sscanf(tmp,"%f",&label);
            first_row=false;
          }
        }
        labels.push_back(label);
        AddRow(findex,fvalue);
        
        RowToCol(max_findex+1);

        fclose(fp);
      }

    private:
      std::vector<size_t> row_ptr;
      std::vector<Entry> row_data;
      std::vector<size_t> col_ptr;
      std::vector<Entry> col_data;
      std::vector<float> labels;
  };
};

#endif