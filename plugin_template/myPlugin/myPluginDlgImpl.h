#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "myPluginDlg.h"
#include "myClass.h"
#include "myPlugin.h"
#include <LiveLogFeature.hpp>

///////////////////////////////////////////////////////////////////////////

class MyApp : public wxApp
{
  public:
    virtual bool OnInit();
    virtual int OnExit();
};

///////////////////////////////////////////////////////////////////////////

class MyPluginDlgImpl : public MyPluginDlg
{
  public:
    MyPluginDlgImpl(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(390, 977), long style = wxDEFAULT_DIALOG_STYLE);
    ~MyPluginDlgImpl();

  public:
    void initClient(IfcDB::Populationi* m_pDB, IfcDB::utils::PopulationStates* m_pStates);
    void setMyPluginAction(MyPluginAction* pMyPluginAction) { m_pMyPluginAction = pMyPluginAction; }
    void setLoggerInterface(sdm::plugin::LiveLogInterface* pLoggerInterface) { m_pLoggerInterface = pLoggerInterface; }

  private:
    virtual void OnInitDialog(wxInitDialogEvent& event);

  private:
    MyPluginAction* m_pMyPluginAction = nullptr;
    MyClass* m_pMyClass = nullptr;
    sdm::plugin::LiveLogInterface* m_pLoggerInterface = nullptr;
};
