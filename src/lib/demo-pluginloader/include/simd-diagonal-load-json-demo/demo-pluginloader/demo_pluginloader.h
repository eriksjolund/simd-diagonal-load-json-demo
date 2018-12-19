#ifndef DEMO_PLUGINLOADER_H
#define DEMO_PLUGINLOADER_H

#include <QPluginLoader>

class DemoPluginInterface;

class DemoPluginLoader {
 public:
  DemoPluginLoader(QString filepath);
  DemoPluginInterface& demo_plugin();

 private:
  QPluginLoader loader_;
  DemoPluginInterface* demo_plugin_ = nullptr;
};

#endif  // DEMO_PLUGINLOADER_H
