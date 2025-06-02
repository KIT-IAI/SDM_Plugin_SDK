#pragma once

#include <ifcdb/IfcDbInclude.h>
#include <ifcdb/utils/PopulationObserver.hpp>
#include <unordered_map>

namespace sdm
{
	namespace plugin
	{
		class LiveLogInterface;
	}
}

class MyPluginDlgImpl;

class MyClass
{
  public:
    MyClass(IfcDB::Populationi* pDB, IfcDB::utils::PopulationStates* pStates, sdm::plugin::LiveLogInterface* pLogger);
    ~MyClass();

    void setLogger(sdm::plugin::LiveLogInterface* pLogger) { m_pLogger = pLogger; }
    void setMyPluginDlg(MyPluginDlgImpl* pDlg) { m_pMyPluginDlg = pDlg; }
    MyPluginDlgImpl* getMyPluginDlg() { return m_pMyPluginDlg; }

  private:
    IfcDB::Populationi* m_pDB = nullptr;
		IfcDB::utils::PopulationStates* m_pStates = nullptr;
		sdm::plugin::LiveLogInterface* m_pLogger = nullptr;

    MyPluginDlgImpl* m_pMyPluginDlg = nullptr;
};
