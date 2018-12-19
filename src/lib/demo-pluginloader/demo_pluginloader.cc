#include "demo_pluginloader.h"
#include <cassert>
#include <QDebug>
#include <simd-diagonal-load-json-demo/demo-plugin-interface/demo_plugin_interface.h>

DemoPluginLoader::DemoPluginLoader(QString filepath) : loader_(filepath) {
  assert(QLibrary::isLibrary(filepath));
  QObject* plugin = loader_.instance();
  if (plugin) {
    demo_plugin_ = qobject_cast<DemoPluginInterface*>(plugin);
  }
  if (!demo_plugin_) {
    throw std::runtime_error("failed to load plugin");
  }
}

DemoPluginInterface& DemoPluginLoader::demo_plugin() {
  assert(demo_plugin_);
  return *demo_plugin_;
}
