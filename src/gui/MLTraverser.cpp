#include "MLTraverser.h"
#include <wx/dir.h>

wxDirTraverseResult wxDirTraverserSimple::OnFile(const wxString& filename)
{
  m_files.Add(filename);
  return (wxDIR_CONTINUE);
}

wxDirTraverseResult wxDirTraverserSimple::OnDir(const wxString& WXUNUSED(dirname))
{
  return (wxDIR_CONTINUE);
}

//wxOpenErrorTraverseResult OnOpenError(const wxString& openerrorname)
