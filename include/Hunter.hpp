#ifndef HUNTER_H
#define HUNTER_H

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

    auto entry = infoAccessor.getEntry();
    auto flavour = entrySorter.getFlavour(entry);
    
    muonShowerWindow.setEndTime(entry.triggerTime + 1);
    
    if(flavour == Flavour::Muon){
      
      auto track = infoAccessor.getMuonTrack<MuonAccuracy>();
      if(track != Segment<MuonAccuracy>())
	muonShowerWindow.emplaceEvent(Muon<MuonAccuracy>(entry.triggerTime, entry.IVCharge, entry.energy, entry.identifier, track, entry.IDCharge), neutronWindowLenght);
    
    }
    else if(flavour == Flavour::Neutron){
      
      Single<SingleAccuracy> neutron(entry.triggerTime, entry.IVCharge, entry.energy, entry.identifier, infoAccessor.getPosition<SingleAccuracy>(), infoAccessor.getReconstructionGoodness<SingleAccuracy>(), infoAccessor.getChargeInformation<SingleAccuracy>());
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
    else if(flavour == Flavour::Candidate){
      
      Single<SingleAccuracy> candidate(entry.triggerTime, entry.IVCharge, entry.energy, entry.identifier, infoAccessor.getPosition<SingleAccuracy>(), infoAccessor.getReconstructionGoodness<SingleAccuracy>(), infoAccessor.getChargeInformation<SingleAccuracy>());
      pairSeeker.catchPrompt(candidate);
      
    }
    
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