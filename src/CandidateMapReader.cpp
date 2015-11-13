#include "CandidateMapReader.hpp"

namespace CosmogenicHunter{
  
  void CandidateMapReader::Read(const boost::filesystem::path& mapPath){
      
    std::ifstream inputStream(mapPath.string(), std::ios::binary);
    cereal::BinaryInputArchive inputArchive(inputStream);
    inputArchive(candidatesMap);

  }
   
  unsigned CandidateMapReader::getCandidateMapSize() const{
    
    return candidatesMap.size();

  }
  
  bool CandidateMapReader::isCandidateMapEmpty() const{
    
    return candidatesMap.empty();

  }
  
  const std::vector<unsigned>& CandidateMapReader::getCandidateIdentifiers(unsigned runNumber){
  
    return candidatesMap.at(runNumber);

  }

}
