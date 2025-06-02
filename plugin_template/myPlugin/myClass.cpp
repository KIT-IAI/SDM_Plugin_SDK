#include <LiveLogFeature.hpp>
#include <stdutils/utf8.hpp>
#include "myClass.h"
#include "myPluginDlgImpl.h"


MyClass::MyClass(IfcDB::Populationi* pDB, IfcDB::utils::PopulationStates* pStates, sdm::plugin::LiveLogInterface* pLogger)
  : m_pDB(pDB), m_pStates(pStates), m_pLogger(pLogger)
{
}

MyClass::~MyClass()
{
}
