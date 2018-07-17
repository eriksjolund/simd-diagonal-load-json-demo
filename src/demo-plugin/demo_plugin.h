#ifndef demo_plugin_h
#define demo_plugin_h

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <simd-diagonal-load-json-demo/demo-plugin-interface/demo_plugin_interface.h>
#include <simd-diagonal-load-json-demo/input-protobuf/input.pb.h>

class DemoPlugin : public QObject, public DemoPluginInterface {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "demo_plugin_interface.1.0")
  Q_INTERFACES(DemoPluginInterface)

 public:
  ~DemoPlugin() override{};
  QString demo_name() const override;
  QString simd_arch() const override;
  unsigned num_loads() const override;
  unsigned num_vertical_mixing() const override;
  unsigned num_vertical_subdivisions() const override;
  input::Spec::integertype integertype() const override;
  unsigned simdvector_bitlength() const override;
  unsigned matrix_width() const override;

  void iterate_diagonals(const input::Root& input_root) const override;
};

#endif  // demo_plugin_h
