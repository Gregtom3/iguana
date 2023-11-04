# pragma once

#include "services/Algorithm.h"
#include <unordered_map>
#include <memory>

// TODO: avoid listing the algos
#include "algorithms/clas12/fiducial_cuts/FiducialCuts.h"

namespace iguana {

  class Arbiter {

    public:
      Arbiter();
      ~Arbiter() {}

      // TODO: avoid listing the algos
      // TODO: who should own the algorithm instances: Arbiter or the user?
      enum algo {
        clas12_FiducialCuts
      };

      // TODO: make private
      std::unordered_map<Arbiter::algo, std::shared_ptr<Algorithm>> algo_map;

  };
}
