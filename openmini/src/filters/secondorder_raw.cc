/// @filename secondorder_raw.cc
/// @brief Low Pass filter using a simple ("raw") 2nd order implementation
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

#include "openmini/src/filters/filters_common.h"
#include "openmini/src/filters/secondorder_raw.h"

namespace openmini {
namespace filters {

SecondOrderRaw::SecondOrderRaw()
    : Filter_Base() {
}

Sample SecondOrderRaw::operator()(const Sample& sample) {
  return sample;
}

}

void SecondOrderRaw::SetParameters(const float frequency,
                                   const float resonance) {
  ASSERT(frequency >= 0.0f);
  ASSERT(frequency <= 0.5f);
}

}  // namespace filters
}  // namespace openmini
