#pragma once

#include "iguana/algorithms/TypeDefs.h"
#include "iguana/algorithms/Validator.h"

#include <TCanvas.h>
#include <TFile.h>
#include <TH2.h>

namespace iguana::clas12 {

  /// @brief `iguana::clas12::FiducialFilter` validator
  class FiducialFilterValidator : public Validator
  {

      DEFINE_IGUANA_VALIDATOR(FiducialFilterValidator, clas12::FiducialFilterValidator)

    public:

      void Start(hipo::banklist& banks) override;
      void Run(hipo::banklist& banks) const override;
      void Stop() override;

      std::map<int, traj_row_data> GetTrajMap(hipo::bank const &bank) const;
      int determineSectorDC(float x, float y, float z) const;
      
    private:

      hipo::banklist::size_type b_particle;
      hipo::banklist::size_type b_traj;
      
      double const DC1xleft   = -500;
      double const DC1xright  = 500;
      double const DC1ybottom = -500;
      double const DC1ytop    = 500;
      double const DC2xleft   = -500;
      double const DC2xright  = 500;
      double const DC2ybottom = -500;
      double const DC2ytop    = 500;
      double const DC3xleft   = -500;
      double const DC3xright  = 500;
      double const DC3ybottom = -500;
      double const DC3ytop    = 500;
      
      double const PI = 3.14159265;
      
      std::vector<int> const u_pdg_list = {
          particle::PDG::electron,
          particle::PDG::pi_plus,
          particle::PDG::pi_minus,
          particle::PDG::proton};

      TString m_output_file_basename;
      TFile* m_output_file;
      mutable std::unordered_map<int, TH2D*> u_DC1_before;
      mutable std::unordered_map<int, TH2D*> u_DC2_before;
      mutable std::unordered_map<int, TH2D*> u_DC3_before;
      
      mutable std::unordered_map<int, TH2D*> u_DC1_after;
      mutable std::unordered_map<int, TH2D*> u_DC2_after; 
      mutable std::unordered_map<int, TH2D*> u_DC3_after;
  };

}
