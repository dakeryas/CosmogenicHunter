#ifndef COSMOGENIC_HUNTER_HUNTER_H
#define COSMOGENIC_HUNTER_HUNTER_H

#include <iomanip>
#include "EntrySorter.hpp"
#include "PairSeeker.hpp"
#include "InfoAccessor.hpp"
#include "Cosmogenic/CandidateTree.hpp"

namespace CosmogenicHunter{

  template <class MuonAccuracy, class SingleAccuracy, class EntryAccuracy>//to accept entries saved with the accuracy of type T
  class Hunter{
    
    EntrySorter<EntryAccuracy> entrySorter;
    PairSeeker<SingleAccuracy> pairSeeker;
    double muonWindowLenght;
    double neutronWindowLenght;
    Window<Shower<Muon<MuonAccuracy>, Single<SingleAccuracy>>> muonShowerWindow;
    
    void processCurrentEntry(InfoAccessor& infoAccessor, cereal::BinaryOutputArchive& outputArchive);
    
  public:
    Hunter(EntrySorter<EntryAccuracy> entrySorter, PairSeeker<SingleAccuracy> pairSeeker, double muonWindowLenght, double neutronWindowLenght);
    void chaseAndSave(TTree* globalInfo, std::ofstream& outputStream);//read 'globaInfo' and save the results into 'outputStream'
    
  };
  
  template <class MuonAccuracy, class SingleAccuracy, class EntryAccuracy>
  Hunter<MuonAccuracy, SingleAccuracy, EntryAccuracy>::Hunter(EntrySorter<EntryAccuracy> entrySorter, PairSeeker<SingleAccuracy> pairSeeker, double muonWindowLenght, double neutronWindowLenght)
  :entrySorter(std::move(entrySorter)),pairSeeker(std::move(pairSeeker)),muonWindowLenght(muonWindowLenght),neutronWindowLenght(neutronWindowLenght),muonShowerWindow(0, muonWindowLenght){
    
  }
  
  template <class MuonAccuracy, class SingleAccuracy, class EntryAccuracy>
  void Hunter<MuonAccuracy, SingleAccuracy, EntryAccuracy>::processCurrentEntry(InfoAccessor& infoAccessor, cereal::BinaryOutputArchive& outputArchive){

    auto flavour = infoAccessor.getFlavour(entrySorter);
    muonShowerWindow.setEndTime(infoAccessor.getEntry().triggerTime + 1);
    
    if(flavour == Flavour::Muon){
      
      auto track = infoAccessor.getMuonTrack<MuonAccuracy>();
      if(track != Segment<MuonAccuracy>())
	muonShowerWindow.emplaceEvent(infoAccessor.getAsMuon<MuonAccuracy>(), neutronWindowLenght);
    
    }
    else if(flavour == Flavour::Neutron){
      
      auto neutron = infoAccessor.getAsSingle<SingleAccuracy>();
      pairSeeker.catchDelayed(neutron);
      
      if(pairSeeker.caughtDelayed()){
	
	outputArchive(CandidateTree<SingleAccuracy,MuonAccuracy>(pairSeeker.getCandidatePair(), muonShowerWindow));
	pairSeeker.reset();
	
      }
      else{
      
	for(auto& muonShower : muonShowerWindow)
	  muonShower.emplaceFollower(neutron);
	
      }
      
    }
    else if(flavour == Flavour::Candidate) pairSeeker.catchPrompt(infoAccessor.getAsSingle<SingleAccuracy>());
    
  }
  
  template <class MuonAccuracy, class SingleAccuracy, class EntryAccuracy>
  void Hunter<MuonAccuracy, SingleAccuracy, EntryAccuracy>::chaseAndSave(TTree* globalInfo, std::ofstream& outputStream){
    
    muonShowerWindow.clear();//empty potentiel previous muon showers
    InfoAccessor infoAccessor(globalInfo);
    cereal::BinaryOutputArchive outputArchive(outputStream);
    
    while(infoAccessor.loadInfo()) processCurrentEntry(infoAccessor, outputArchive);
    
  }

  
}

#endif