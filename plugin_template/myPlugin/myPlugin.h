#pragma once

#include <Plugin.hpp>
#include <ActionFeatureHelper.hpp>
#include <MainFrameObserverImpl.hpp>
#include <DocumentObserver.hpp>
#include <ifcdb/utils/PopulationObserver.hpp>
#include <LiveLogFeature.hpp>
#include <MessageDialogFeature.hpp>
#include <MessageDialogFeatureHelper.hpp>
#include <LogDialogFeature.hpp>
#include <LogDialogFeatureHelper.hpp>
#include <wx/nativewin.h>

class MyPluginDlgImpl;

class MyPluginAction : public sdm::plugin::ActionFeatureHelper
{
  public:
    MyPluginAction();
    virtual ~MyPluginAction();

    void execute() const override;
    bool isActive() const override;

    void setMainFrameWnd(intptr_t hParentWnd)
    {
      if (!m_pContainerWindow)
      {
        //m_pContainerWindow = new wxNativeContainerWindow((HWND)hParentWnd);
      }
    }
    void setLogger(sdm::plugin::LiveLogInterface* pLiveLogInterface) { m_pLiveLogObserver = pLiveLogInterface; }
    void setDB(IfcDB::Populationi* pDB) { m_pDB = pDB; }
    void setStates(IfcDB::utils::PopulationStates* pSates) { m_pStates = pSates; }

    void setIsDialogOpen(bool state) { m_isDialogOpen = state; }
    MyPluginDlgImpl* getMyPluginDlg() { return m_pMyPluginDlg; }

    sdm::plugin::LiveLogInterface* getLogger() { return m_pLiveLogObserver; }
    IfcDB::Populationi* getDB() { return m_pDB; }
    IfcDB::utils::PopulationStates* getStates() { return m_pStates; }

  protected:
    bool m_isDialogOpen = false;
    intptr_t m_hParentWnd = 0;
    wxNativeContainerWindow* m_pContainerWindow = nullptr;
    MyPluginDlgImpl* m_pMyPluginDlg = nullptr;
    sdm::plugin::LiveLogInterface* m_pLiveLogObserver = nullptr;
    IfcDB::Populationi* m_pDB = nullptr;
    IfcDB::utils::PopulationStates* m_pStates = nullptr;
};

class MyPlugin : public sdm::plugin::Plugin
{
  public:
    MyPlugin();
    ~MyPlugin();

    sdm::plugin::Version getInterfaceVersion() const override;
    sdm::plugin::PluginInfo getInfo() const override;
    std::vector<sdm::plugin::Feature*> getFeatures() const override;

    sdm::plugin::ComponentInfo getComponentInfo(const sdm::plugin::RequiredComponent& requiredComponent) const override;
    const sdm::plugin::InitializationState& getInitializationState() const override;

    void setDB(IfcDB::Populationi* pDB);
    void setStates(IfcDB::utils::PopulationStates* pStates);

  private:
    sdm::plugin::MainFrameObserverImpl m_MainFrameObserver;
    sdm::plugin::DocumentObserverImpl m_documentObserver;
    sdm::plugin::LiveLogObserver m_liveLogObserver;
    MyPluginAction m_myPluginAction;
    sdm::plugin::InitializationState m_initState;
    IfcDB::Populationi* m_pDB = nullptr;
    IfcDB::utils::PopulationStates* m_pStates = nullptr;
};