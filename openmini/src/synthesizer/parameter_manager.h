/// @filename parameters_manager.h
/// @brief Parameters Manager: holds all parameters descriptors & values,
/// interface between them and the user
///
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

#ifndef OPENMINI_SRC_SYNTHESIZER_PARAMETERS_MANAGER_H_
#define OPENMINI_SRC_SYNTHESIZER_PARAMETERS_MANAGER_H_

#include "openmini/src/synthesizer/parameter_meta.h"

namespace openmini {
namespace synthesizer {

// Normalization utilities

/// @brief Get a normalized value from a parameter metadata and its value
///
/// @param[in]    stored_value      Parameter stored value
/// @param[in]    metadata          Parameter metadata
///
/// @return The normalized value, e.g. within [0.0f ; 1.0f]
float StoredToNormalized(const float stored_value,
                         const ParameterMeta& metadata);

/// @brief Get a normalized value from a parameter metadata and its value
///
/// @param[in]    stored_value      Parameter stored value
/// @param[in]    metadata          Parameter metadata
///
/// @return The normalized value, e.g. within [0.0f ; 1.0f]
float NormalizedToStored(const float normalized,
                         const ParameterMeta& metadata);

/// @brief Get an integer from a parameter metadata and its normalized value
///
/// If called for a continuous parameter, will return:
/// 0 (if value < max)
/// 1 (if value = max)
///
/// @param[in]    normalized   Value in [0.0f ; 1.0f]
/// @param[in]    metadata     Parameter metadata
int NormalizedToInt(const float normalized,
                    const ParameterMeta& metadata);

/// @brief Get an integer from a parameter value
///
/// Simple float -> int conversion (floor)
///
/// @param[in]    unnormalized   Value
int UnnormalizedToInt(const float unnormalized);

/// @brief Parameter manager: holds a list of parameters and their descriptor,
/// allows interaction with them.
///
/// The parameter descriptors are static - they're given at instantiation
/// and cannot be changed afterwards.
///
/// Any synthesizer class should derive from it since a synthesizer "is a"
/// parameter manager.
class ParametersManager {
 public:
  /// @brief Default constructor:
  /// initialization done with static parameter descriptors data,
  /// but parameter values memory is dynamically allocated
  ///
  /// @param[in]   param_meta_begin    First parameter descriptor to handle
  /// @param[in]   count               Descriptors count
  ParametersManager(const ParameterMeta* param_meta_begin,
                    const int count);
  /// @brief Default destructor
  virtual ~ParametersManager();

  // Setters

  /// @brief Set parameter value
  ///
  /// @param[in]   parameter_id     ID of the parameter to be changed
  /// @param[in]   value            Value to set the parameter to
  virtual void SetValue(const int parameter_id, const float value);

  // Getters

  /// @brief Get parameter value (float version)
  ///
  /// This getter retrieves a floating point number,
  /// whatever the actual parameter format is
  ///
  /// @param[in]   parameter_id     ID of the parameter to be retrieved
  virtual float GetValue(const int parameter_id) const;

  /// @brief Get parameter value (typed discrete version)
  ///
  /// This getter retrieves an integer if asked, but it can also be asked
  /// for an enum, making it more type-safe.
  ///
  /// @param[in]   parameter_id     ID of the parameter to be retrieved
  template <typename TypeOutput>
  TypeOutput GetDiscreteValue(const int parameter_id) const;

  /// @brief Get parameter metadata
  ///
  /// @param[in]   parameter_id     ID of the parameter to be retrieved
  virtual const ParameterMeta& GetMetadata(const int parameter_id) const;

  /// @brief Return managed parameters count
  virtual int ParametersCount(void) const;

 protected:
  /// @brief Update internal generator variables with lastly set parameters
  ///
  /// When set, parameters are not immediately used - they must be processed
  /// into internal variables
  ///
  /// This function allows to make this update asynchronously
  /// it should probably be called from within a dedicated "update" loop
  virtual void ProcessParameters(void) = 0;

  bool update_;  //< True if internal values have to be changed

 private:
  /// @brief Assign to each parameter its default value
  void AssignDefault(void);

  // No assignment operator for this class
  ParametersManager& operator=(const ParametersManager& right);

  float* const values_;  ///< Parameters value data
  const ParameterMeta* param_meta_begin_;  ///< Parameters metadata
  const int count_;  ///< Parameters count
};


template <typename TypeOutput>
TypeOutput ParametersManager::GetDiscreteValue(const int parameter_id) const {
  const float value(GetValue(parameter_id));
  int int_value(UnnormalizedToInt(value));
  const ParameterMeta& metadata(GetMetadata(parameter_id));
  // If the parameter is normalized, then we have to pass through normalization
  if (metadata.is_normalized()) {
    // Note that "normalized parameter" does not mean that the stored value
    // is actually normalized - it means that the interface to access it
    // is normalized
    int_value = NormalizedToInt(value, metadata);
  }
  return static_cast<TypeOutput>(int_value);
}

}  // namespace synthesizer
}  // namespace openmini

#endif  // OPENMINI_SRC_SYNTHESIZER_PARAMETERS_MANAGER_H_