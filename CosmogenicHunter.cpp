#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "DCActionUnit.hh"
#include "Muon.hpp"
#include "Neutron.hpp"
#include "Candidate.hpp"
#include "Shower.hpp"

namespace CsHt = CosmogenicHunter;
namespace bpo = boost::program_options;
using MuonShower = CsHt::Shower<CsHt::Muon, CsHt::Neutron>;

void hunt(unsigned runNumber, boost::filesystem::path outputPath){
  
  CsHt::Event event(31.5e9, 30, 9873528);
  
  CsHt::Window<CsHt::Event> window(30e9, 2e9);
  window.emplaceEvent(31e9, 30, 9873528);
  window.pushBackEvent(event);
  
  CsHt::Point<float> point1(1, 1, 2);
  CsHt::Point<float> point2(3, 2, 3);
  CsHt::Segment<float> segment(point1, point2);
  
  CsHt::Muon muon(event, 5e4, 8e4, segment);
  CsHt::Neutron neutron(event, point2);
  CsHt::Candidate candidate(event, point2, 3);
  MuonShower muonShower(muon, 2e9);
  muonShower.pushBackFollower(neutron);
  muonShower.emplaceFollower(event, CsHt::Point<float>(5, 5, 5));
  muonShower.emplaceFollower(33e9, 8, 106785, CsHt::Point<float>(1, 5, 5));
  CsHt::Window<MuonShower> muonShowers(muonShower.getTriggerTime(), 20e9);
  for(unsigned k = 0; k  < 10*30*20; ++k) muonShowers.pushBackEvent(muonShower);
  
  {
    
    std::ofstream outputStream(outputPath.string(), std::ios::binary);
    cereal::BinaryOutputArchive outputArchive(outputStream);
    outputArchive(event);
    outputArchive(neutron);
    outputArchive(muon);
    outputArchive(muonShowers);
  
  }
  
  std::ifstream inputStream(outputPath.string(), std::ios::binary);
  cereal::BinaryInputArchive inputArchive(inputStream);
  
  CsHt::Window<MuonShower> muonShowersInput;
  CsHt::Event inputEvent;
  inputArchive(inputEvent);
  inputArchive(CsHt::Neutron());
  inputArchive(CsHt::Muon());
  inputArchive(muonShowersInput);
//   std::cout<<muonShowersInput<<std::endl;
  
  Message::SetLevelMSG(DC::kMERROR);
  
  EnDep::SetDirDataINPUT("$HOME/Documents/dchooz/cosmogenic/Data/RunsCT/");
  EnDep::SetRunNumber(runNumber);
  
  Processor::GetME()->CancelAllInfoCapsule_Tree();
  Processor::GetME()->UncancelInfoCapsule_Tree(DC::kGlobalIT);
  Processor::GetME()->UncancelInfoCapsule_Tree(DC::kRecoBAMAIT);
  Processor::GetME()->UncancelInfoCapsule_Tree(DC::kRecoMuHamIDIT);
  Processor::GetME()->SaveOutput(false);
//   Processor::GetME()->Run();
  
}

int main(int argc, char* argv[]){
  
  unsigned runNumber;
  boost::filesystem::path outputPath;
  
  bpo::options_description optionDescription("CosmogenicHunter usage");
  optionDescription.add_options()
  ("help,h", "Display this help message")
  ("run,r", bpo::value<unsigned>(&runNumber)->required(), "Run number of the CT file to process")
  ("output,o", bpo::value<boost::filesystem::path>(&outputPath)->required(), "Output file where to save the candidate trees");

  bpo::positional_options_description positionalOptions;//to use arguments without "--"
  positionalOptions.add("run", 1);
  
  bpo::variables_map arguments;
  try{
    
    bpo::store(bpo::command_line_parser(argc, argv).options(optionDescription).positional(positionalOptions).run(), arguments);
    
    if(arguments.count("help")){
      
      std::cout<<optionDescription<<std::endl;
      return 0;
      
    }
      
    bpo::notify(arguments);//the arguments are ready to be used
    
  }
  catch(bpo::error& e){
    
    std::cout<<e.what()<<std::endl;
    return 1;
    
  }
  
  hunt(runNumber, outputPath);
  
}
