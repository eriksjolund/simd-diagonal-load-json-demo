#ifndef DEMO_PLUGIN_INTERFACE_H
#define DEMO_PLUGIN_INTERFACE_H

#include <QString>
#include <QtPlugin>
#include <simd-diagonal-load-json-demo/input-protobuf/input.pb.h>

class DemoPluginInterface {
 public:
  virtual ~DemoPluginInterface() {}

  virtual QString demo_name() const = 0;
  virtual unsigned num_loads() const = 0;
  virtual unsigned num_vertical_mixing() const = 0;
  virtual unsigned num_vertical_subdivisions() const = 0;

  virtual input::Spec::integertype integertype() const = 0;
  virtual unsigned simdvector_bitlength() const = 0;
  virtual unsigned matrix_width() const = 0;
  virtual void iterate_diagonals(const input::Root& input_root) const = 0;
};

Q_DECLARE_INTERFACE(DemoPluginInterface, "demo_plugin_interface.1.0")

#endif  // DEMO_PLUGIN_INTERFACE_H
