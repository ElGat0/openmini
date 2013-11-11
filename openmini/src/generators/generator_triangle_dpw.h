/// @filename generator_triangle_dpw.h
/// @brief Triangle signal generator using DPW algorithm
/// @author gm
/// @copyright gm 2013
///
/// This file is part of OpenMini
///
/// OpenMini is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// OpenMini is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License
/// along with OpenMini.  If not, see <http://www.gnu.org/licenses/>.

#ifndef OPENMINI_SRC_GENERATORS_GENERATOR_TRIANGLE_DPW_H_
#define OPENMINI_SRC_GENERATORS_GENERATOR_TRIANGLE_DPW_H_

#include "openmini/src/common.h"
#include "openmini/src/generators/generators_common.h"

namespace openmini {
namespace generators {

/// @brief Triangle signal generator
/// using Differentiated Parabolic Wave (DPW) algorithm
class ALIGN TriangleDPW : public Generator_Base {
 public:
  explicit TriangleDPW(const float phase = 0.0f);
  virtual ~TriangleDPW() {
    // Nothing to do here for now
  };
  virtual Sample operator()(void);
  virtual void SetPhase(const float phase);
  virtual void SetFrequency(const float frequency);
  virtual float Phase(void) const;

 protected:
  PhaseAccumulator sawtooth_gen_;  //< Internal basic sawtooth signal generator
  Differentiator differentiator_;  //< Internal basic differentiator
  float normalization_factor_;  //< To be applied on the signal after synthesis
};

}  // namespace generators
}  // namespace openmini

#endif  // OPENMINI_SRC_GENERATORS_GENERATOR_TRIANGLE_DPW_H_
