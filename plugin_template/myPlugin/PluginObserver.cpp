#include "PluginObserver.h"
#include "myPlugin.h"
#include "myClass.h"
#include "myPluginDlgImpl.h"

PluginObserver::PluginObserver(MyPluginAction& myPluginAction)
  : m_myPluginAction(myPluginAction)
{
}

void PluginObserver::activate(bool first)
{

}

void PluginObserver::deactivate(bool last)
{
  if (last)
  {
    m_myPluginAction.setIsDialogOpen(false);

    auto pMyPluginDlg = m_myPluginAction.getMyPluginDlg();

    if (pMyPluginDlg)
    {
      pMyPluginDlg->Close();
    }
  }
}

void PluginObserver::selectEntity(IfcDB::ifcOid oid, bool selected)
{

}
