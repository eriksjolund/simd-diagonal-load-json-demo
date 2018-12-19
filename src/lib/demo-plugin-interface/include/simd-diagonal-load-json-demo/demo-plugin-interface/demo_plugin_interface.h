#ifndef DEMO_PLUGIN_INTERFACE_H
#define DEMO_PLUGIN_INTERFACE_H

#include <QString>
#include <QtPlugin>
#include <simd-diagonal-load-json-demo/input-matrices/input-matrices.capnp.h>

#include <simd-diagonal-load/algorithm/algorithm_types.h>

class DemoPluginInterface {
 public:
  virtual ~DemoPluginInterface() {}

  virtual QString demo_name() const = 0;
  virtual QString simd_arch() const = 0;
  virtual num_loads_t num_loads() const = 0;
  virtual num_vertical_mixing_t num_vertical_mixing() const = 0;
  virtual num_vertical_subdivisions_t num_vertical_subdivisions() const = 0;

  //  virtual input::Spec::integertype integertype() const = 0;
  virtual QString integertype() const = 0;
  virtual std::uint8_t integertype_num_bits() const = 0;
  virtual bool integertype_signed() const = 0;

  virtual unsigned simdvector_bitlength() const = 0;
  virtual unsigned matrix_width() const = 0;
  virtual void iterate_diagonals(
      const InputMatricesRoot::Reader& input_matrices) const = 0;
};

Q_DECLARE_INTERFACE(DemoPluginInterface, "demo_plugin_interface.1.0")

#endif  // DEMO_PLUGIN_INTERFACE_H
