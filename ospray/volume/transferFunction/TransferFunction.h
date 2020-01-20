// Copyright 2009-2019 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "common/Managed.h"

namespace ospray {

/*! \brief A TransferFunction is an abstraction that maps a value to
  a color and opacity for rendering.

  The actual mapping is unknown to this class, and is implemented
  in subclasses.  A type string specifies a particular concrete
  implementation to createInstance().  This type string must be
  registered in OSPRay proper, or in a loaded module using
  OSP_REGISTER_TRANSFER_FUNCTION.
*/
struct OSPRAY_SDK_INTERFACE TransferFunction : public ManagedObject
{
  TransferFunction();
  virtual ~TransferFunction() override = default;
  virtual void commit() override;
  virtual std::string toString() const override;

  //! Create a transfer function of the given type.
  static TransferFunction *createInstance(const std::string &type);

  range1f valueRange;
  virtual std::vector<range1f> getPositiveOpacityValueRanges() const = 0;
  virtual std::vector<range1i> getPositiveOpacityIndexRanges() const = 0;
};

OSPTYPEFOR_SPECIALIZATION(TransferFunction *, OSP_TRANSFER_FUNCTION);

/*! \brief Define a function to create an instance of the InternalClass
  associated with external_name.

 \internal The function generated by this macro is used to create an
  instance of a concrete subtype of an abstract base class.  This
  macro is needed since the subclass type may not be known to OSPRay
  at build time.  Rather, the subclass can be defined in an external
  module and registered with OSPRay using this macro.
*/
#define OSP_REGISTER_TRANSFER_FUNCTION(InternalClass, external_name)           \
  OSP_REGISTER_OBJECT(::ospray::TransferFunction,                              \
      transfer_function,                                                       \
      InternalClass,                                                           \
      external_name)

} // namespace ospray
