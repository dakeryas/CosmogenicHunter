#include <iostream>
#include "boost/filesystem.hpp"
#include "boost/program_options.hpp"
#include "DCActionUnit.hh"
#include "Event.hpp"
#include "Window.hpp"

namespace bpo = boost::program_options;

void hunt(unsigned runNumber, boost::filesystem::path outputPath){
  
  CosmogenicHunter::Event event(31.5e9, 30, 9873528);
  
  CosmogenicHunter::Window<CosmogenicHunter::Event> window(30e9, 2e9);
  window.emplaceEvent(31e9, 30, 9873528);
  window.pushBackEvent(event);
  
  std::ofstream outputStream(outputPath.string());
  outputStream<<window<<std::endl;
  
  Message::SetLevelMSG(DC::kMERROR);
  
  EnDep::SetDirDataINPUT("$HOME/Documents/dchooz/cosmogenic/Data/RunsCT/");
  EnDep::SetRunNumber(runNumber);
  
  Processor::GetME()->CancelAllInfoCapsule_Tree();
  Processor::GetME()->UncancelInfoCapsule_Tree(DC::kGlobalIT);
  Processor::GetME()->UncancelInfoCapsule_Tree(DC::kRecoBAMAIT);
  Processor::GetME()->UncancelInfoCapsule_Tree(DC::kRecoMuHamIDIT);
  Processor::GetME()->SaveOutput(false);
  Processor::GetME()->Run();
  
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
