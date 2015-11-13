#ifndef CANDIDATE_MAP_READER_H
#define CANDIDATE_MAP_READER_H

#include <fstream>
#include "boost/filesystem.hpp"
#include "cereal/archives/binary.hpp"
#include "cereal/types/unordered_map.hpp"
#include "cereal/types/vector.hpp"

namespace CosmogenicHunter{

  class CandidateMapReader{
    std::unordered_map<unsigned, std::vector<unsigned>> candidatesMap;
    
  public:
    CandidateMapReader() = default;
    void Read(const boost::filesystem::path& mapPath);
    const std::vector<unsigned>& getCandidateIdentifiers(unsigned runNumber);
    
  };

}


#endif