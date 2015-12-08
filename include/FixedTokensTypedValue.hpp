#ifndef BOOST_PROGRAM_OPTIONS_FIXED_TOKENS_TYPED_VALUE_H
#define BOOST_PROGRAM_OPTIONS_FIXED_TOKENS_TYPED_VALUE_H

#include "boost/program_options.hpp"

namespace boost{
  
  namespace program_options{
      
    template <class T>
    class fixed_tokens_typed_value : public typed_value<std::vector<T>>{
      
      unsigned minTokens, maxTokens;
      
    public:
      fixed_tokens_typed_value(std::vector<T>* typedValues, unsigned minTokens, unsigned maxTokens);
      unsigned min_tokens() const;
      unsigned max_tokens() const;
      
    };
    
    template <class T>
    fixed_tokens_typed_value<T>::fixed_tokens_typed_value(std::vector<T>* typedValues, unsigned minTokens, unsigned maxTokens):typed_value<std::vector<T>>(typedValues),minTokens(minTokens),maxTokens(maxTokens){
      
    }
    
    template <class T>
    unsigned fixed_tokens_typed_value<T>::min_tokens() const{
      
      return minTokens;
      
    }
    
    template <class T>
    unsigned fixed_tokens_typed_value<T>::max_tokens() const{
      
      return maxTokens;
      
    }
    
    template<class T>
    fixed_tokens_typed_value<T>* fixed_tokens_value(unsigned minTokens, unsigned maxTokens){
      
      return new fixed_tokens_typed_value<T>(nullptr, minTokens, maxTokens);; 
      
    }
    
    template<class T>
    fixed_tokens_typed_value<T>* fixed_tokens_value(std::vector<T>* typedValues, unsigned minTokens, unsigned maxTokens){
      
      return new fixed_tokens_typed_value<T>(typedValues, minTokens, maxTokens);; 
      
    }
    
  }
  
}

#endif