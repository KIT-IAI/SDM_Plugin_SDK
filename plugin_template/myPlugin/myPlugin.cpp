#include <iostream>
#include <string>
#include <vector>
#include <stdutils/executable.hpp>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "myPlugin.h"
#include "myClass.h"
#include "myPluginDlgImpl.h"

#include <ifcdb/IFCDBInterfaceVersion.hpp>
#include "PluginInterfaceVersion.hpp"
#include "ComponentRegistry.hpp"

using namespace std;
using namespace sdm::plugin;

IMPLEMENT_PLUGIN(MyPlugin);

MyPluginAction::MyPluginAction()
  : ActionFeatureHelper("ActionName")
{
  wxInitialize();
}

MyPluginAction::~MyPluginAction()
{
  wxUninitialize();
}

void MyPluginAction::execute() const
{
  try
  {
    auto pMyPluginDlg = new MyPluginDlgImpl(nullptr, wxID_ANY, wxT("myPlugin Dialog"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);
    m_pMyPluginDlg->setMyPluginAction(const_cast<MyPluginAction*>(this));
    m_pMyPluginDlg->setLoggerInterface(m_pLiveLogObserver);
    m_pMyPluginDlg->Show();

    const_cast<MyPluginDlgImpl*>(m_pMyPluginDlg) = pMyPluginDlg;
  }
  catch (const std::exception& e)
  {
    m_pLiveLogObserver->log("myPlugin", e.what());
  }
}

bool MyPluginAction::isActive() const
{
  if (m_pDB && !m_isDialogOpen)
  {
    return true;
  }

  return false;
}

void MyPluginAction::deleteDlg()
{
  m_pStates->unsubscribe(*m_pObserver);

  if (m_pMyPluginDlg)
  {
    delete m_pMyPluginDlg;
    m_pMyPluginDlg = nullptr;
  }

  if (m_pObserver)
  {
    delete m_pObserver;
    m_pObserver = nullptr;
  }
}

void MyPluginAction::setStates(IfcDB::utils::PopulationStates* pSates)
{
  m_pStates = pSates;

  if (!m_pObserver)
  {
    m_pObserver = new PluginObserver(*this);
    m_pStates->subscribe(*m_pObserver);
  }
}

MyPlugin::MyPlugin()
{
  m_MainFrameObserver.attach([&](sdm::plugin::MainFrameInterface* pMainFrameInterface) { m_myPluginAction.setMainFrameWnd(pMainFrameInterface->getParentWnd()); });
  m_documentObserver.attach([this](IfcDB::Populationi* pDB) { setDB(pDB); });
  m_documentObserver.attach([this](IfcDB::utils::PopulationSubject* pStates) { setStates(dynamic_cast<IfcDB::utils::PopulationStates*>(pStates)); });
  m_liveLogObserver.attach([this](sdm::plugin::LiveLogInterface* liveLogInterface) { m_myPluginAction.setLogger(liveLogInterface); });
}

MyPlugin::~MyPlugin()
{
}

sdm::plugin::Version MyPlugin::getInterfaceVersion() const
{
  return sdm::plugin::Version();
}

sdm::plugin::PluginInfo MyPlugin::getInfo() const
{
  sdm::plugin::PluginInfo info;
  info.name = "myPlugin";
  info.description = "myPlugin";
  info.version     = { 0, 1 };

  return info;
}

std::vector<sdm::plugin::Feature*> MyPlugin::getFeatures() const
{
  std::vector<sdm::plugin::Feature*> features;

  features.emplace_back(const_cast<MyPluginAction*>(&m_myPluginAction));
  features.emplace_back(const_cast<MainFrameObserverImpl*>(&m_MainFrameObserver));
  features.emplace_back(const_cast<sdm::plugin::LiveLogObserver*>(&m_liveLogObserver));
  features.emplace_back(const_cast<DocumentObserverImpl*>(&m_documentObserver));

  return features;
}

ComponentInfo MyPlugin::getComponentInfo(const RequiredComponent& requiredComponent) const
{
  ComponentRegistry availableComponents;
  availableComponents.addAvailable(IFCDB_INTERFACE_COMPONENT_NAME, IFCDB_INTERFACE_COMPONENT_VERSION, IFCDB_INTERFACE_COMPONENT_HINT, std::atoi(IFCDB_INTERFACE_COMPONENT_DATE.data()));
  availableComponents.addAvailable(PLUGIN_INTERFACE_COMPONENT_NAME, PLUGIN_INTERFACE_COMPONENT_VERSION, PLUGIN_INTERFACE_COMPONENT_HINT, std::atoi(PLUGIN_INTERFACE_COMPONENT_DATE.data()));

  return availableComponents.getInfo(requiredComponent);
}

const sdm::plugin::InitializationState& MyPlugin::getInitializationState() const
{
  return m_initState;
}

void MyPlugin::setDB(IfcDB::Populationi* pDB)
{
  IfcDB::assignGlobalStates(pDB);
  m_myPluginAction.setDB(pDB);
}

void MyPlugin::setStates(IfcDB::utils::PopulationStates* pStates)
{
  m_myPluginAction.setStates(pStates);
}
