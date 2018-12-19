#ifndef demo_plugin_h
#define demo_plugin_h

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <simd-diagonal-load-json-demo/demo-plugin-interface/demo_plugin_interface.h>

class DemoPlugin : public QObject, public DemoPluginInterface {
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "demo_plugin_interface.1.0")
  Q_INTERFACES(DemoPluginInterface)

 public:
  ~DemoPlugin() override{};
  QString demo_name() const override;
  QString simd_arch() const override;
  num_loads_t num_loads() const override;
  num_vertical_mixing_t num_vertical_mixing() const override;
  num_vertical_subdivisions_t num_vertical_subdivisions() const override;
  QString integertype() const override;
  unsigned simdvector_bitlength() const override;
  unsigned matrix_width() const override;
  std::uint8_t integertype_num_bits() const override;
  bool integertype_signed() const override;
  void iterate_diagonals(
      const InputMatricesRoot::Reader& input_matrices) const override;
};

#endif  // demo_plugin_h
