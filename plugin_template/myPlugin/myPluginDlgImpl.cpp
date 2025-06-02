#include "myPluginDlgImpl.h"
#include <wx/valnum.h>

IMPLEMENT_APP_NO_MAIN(MyApp)

bool MyApp::OnInit()
{
  return true;
}

int MyApp::OnExit()
{
  return 0;
}

///////////////////////////////////////////////////////////////////////////

MyPluginDlgImpl::MyPluginDlgImpl(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
  : MyPluginDlg(parent, id, title, pos, size, style)
{
  SetSize(wxSize(379, 1026));
  Centre();

  SetDoubleBuffered(true);

  wxSize minSize = this->GetBestSize();
  this->SetSize(minSize);
}

MyPluginDlgImpl::~MyPluginDlgImpl()
{
  m_pMyPluginAction->setIsDialogOpen(false);

  delete m_pMyClass;
}

void MyPluginDlgImpl::initClient(IfcDB::Populationi* pDB, IfcDB::utils::PopulationStates* pStates)
{
  m_pMyClass = new MyClass(pDB, pStates, m_pMyPluginAction->getLogger());
}

void MyPluginDlgImpl::OnInitDialog(wxInitDialogEvent& event)
{
  m_pMyPluginAction->setIsDialogOpen(true);

  DoGetBestClientSize();
  DoGetBestSize();
}

//void MyPluginDlgImpl::OnCLose(wxCloseEvent& event)
//{
//  m_pMyPluginAction->setIsDialogOpen(false);
//
//  MyPluginDlg::OnCLose(event);
//}
//
//void MyPluginDlgImpl::OnCancel(wxCommandEvent& event)
//{
//  m_pMyPluginAction->setIsDialogOpen(false);
//
//  MyPluginDlg::OnCancel(event);
//}
