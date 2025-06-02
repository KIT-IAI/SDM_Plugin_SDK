#pragma once

#include <ifcdb/utils/PopulationObserver.hpp>

class MyClass;
class MyPluginAction;

class PluginObserver final : public IfcDB::utils::PopulationObserver
{
  public:
    explicit PluginObserver(MyPluginAction& myPluginAction);
    ~PluginObserver() override = default;

    void activate(bool first) override;
    void deactivate(bool last) override;
    void selectEntity(IfcDB::ifcOid oid, bool selected) override;

  private:
    MyPluginAction& m_myPluginAction;
};